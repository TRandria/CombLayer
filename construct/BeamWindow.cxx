/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   construct/BeamWindow.cxx
*
 * Copyright (c) 2004-2013 by Stuart Ansell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *
 ****************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "localRotate.h"
#include "masterRotate.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "surfEqual.h"
#include "surfDivide.h"
#include "surfDIter.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Line.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Object.h"
#include "Qhull.h"
#include "Simulation.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "ContainedComp.h"
#include "BeamWindow.h"

namespace ts1System
{

BeamWindow::BeamWindow(const std::string& Key)  :
  attachSystem::ContainedComp(),attachSystem::FixedComp(Key,2),
  bwIndex(ModelSupport::objectRegister::Instance().cell(Key)),
  cellIndex(bwIndex+1),populated(0)
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}

BeamWindow::BeamWindow(const BeamWindow& A) : 
  attachSystem::ContainedComp(A),attachSystem::FixedComp(A),
  bwIndex(A.bwIndex),cellIndex(A.cellIndex),
  populated(A.populated),yStep(A.yStep),
  incThick1(A.incThick1),waterThick(A.waterThick),
  incThick2(A.incThick2),heMat(A.heMat),
  inconelMat(A.inconelMat),waterMat(A.waterMat)
  /*!
    Copy constructor
    \param A :: BeamWindow to copy
  */
{}

BeamWindow&
BeamWindow::operator=(const BeamWindow& A)
  /*!
    Assignment operator
    \param A :: BeamWindow to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::ContainedComp::operator=(A);
      attachSystem::FixedComp::operator=(A);
      cellIndex=A.cellIndex;
      populated=A.populated;
      yStep=A.yStep;
      incThick1=A.incThick1;
      waterThick=A.waterThick;
      incThick2=A.incThick2;
      heMat=A.heMat;
      inconelMat=A.inconelMat;
      waterMat=A.waterMat;
    }
  return *this;
}


BeamWindow::~BeamWindow() 
 /*!
   Destructor
 */
{}

void
BeamWindow::populate(const Simulation& System)
 /*!
   Populate all the variables
   \param System :: Simulation to use
 */
{
  ELog::RegMethod RegA("BeamWindow","populate");
  
  const FuncDataBase& Control=System.getDataBase();

  try
    {
      // Master values
      yStep=Control.EvalVar<double>(keyName+"YStep");
      incThick1=Control.EvalVar<double>(keyName+"IncThick1");
      waterThick=Control.EvalVar<double>(keyName+"WaterThick");
      incThick2=Control.EvalVar<double>(keyName+"IncThick2");
      
      // Materials
      inconelMat=ModelSupport::EvalMat<int>(Control,keyName+"InconelMat");
      waterMat=ModelSupport::EvalMat<int>(Control,keyName+"WaterMat");

      populated = (incThick1*waterThick*incThick2
		   <Geometry::zeroTol) ? 0 : 1;
    }
  // Exit and don't report if we are not using this scatter plate
  catch (ColErr::InContainerError<std::string>& EType)
    {
      ELog::EM<<keyName<<" not in use Var:"
	      <<EType.getItem()<<ELog::endWarn;
      populated=0;   
    }

  return;
}
  
void
BeamWindow::createUnitVector(const attachSystem::FixedComp& FC,
			     const size_t indexPt)
  /*!
    Create the unit vectors
    - Y Down the beamline
    \param FC :: Linked object
    \param indexPt :: connection point
  */
{
  ELog::RegMethod RegA("BeamWindow","createUnitVector");

  const masterRotate& MR=masterRotate::Instance();

  attachSystem::FixedComp::createUnitVector(FC);
  // Origin is in the wrong place as it is at the EXIT:
  FixedComp::createUnitVector(FC);
  Origin=FC.getLinkPt(indexPt)-Y*yStep;

  return;
}

void
BeamWindow::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("BeamWindow","createSurface");

  // Thick
  ModelSupport::buildPlane(SMap,bwIndex+1,Origin,Y);
  ModelSupport::buildPlane(SMap,bwIndex+2,Origin+Y*incThick1,Y);
  ModelSupport::buildPlane(SMap,bwIndex+3,Origin+
			   Y*(incThick1+waterThick),Y);
  ModelSupport::buildPlane(SMap,bwIndex+4,Origin+
			   Y*(incThick1+waterThick+incThick2),Y);

  return;
}

void
BeamWindow::createObjects(Simulation& System)
  /*!
    Adds the objects
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("BeamWindow","createObjects");

  // Master box: 
  std::string Out= 
    ModelSupport::getComposite(SMap,bwIndex,"1 -4 ");
  addOuterSurf(Out);

  const std::string Boundary=getCompContainer();
  // Inconel1 
  Out=ModelSupport::getComposite(SMap,bwIndex,"1 -2  ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,inconelMat,0.0,Out+Boundary));
  // Water 
  Out=ModelSupport::getComposite(SMap,bwIndex,"2 -3 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,waterMat,0.0,Out+Boundary));
  // Inconel2 
  Out=ModelSupport::getComposite(SMap,bwIndex,"3 -4 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,inconelMat,0.0,Out+Boundary));

  return;
}

void
BeamWindow::createLinks()
  /*!
    Creates a full attachment set
  */
{
  // set Links:
  FixedComp::setLinkSurf(0,-SMap.realSurf(bwIndex+1));
  FixedComp::setLinkSurf(1,SMap.realSurf(bwIndex+4));

  FixedComp::setConnect(0,Origin,-Y);
  FixedComp::setConnect(1,Origin+Y*(incThick1+waterThick+incThick2),Y);

  return;
}

void
BeamWindow::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const size_t targetFrontIndex)
  /*!
    Global creation of the hutch
    \param System :: Simulation to add vessel to
    \param FC :: Fixed target object
    \param targetFrontIndex :: front point of the target
  */
{
  ELog::RegMethod RegA("BeamWindow","createAll");
  populate(System);
  if (populated)
    {
      createUnitVector(FC,targetFrontIndex);
      createSurfaces();
      createObjects(System);
      createLinks();
      insertObjects(System);       
    }

  return;
}

  
}  // NAMESPACE ts1System
