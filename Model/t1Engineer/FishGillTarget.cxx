/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   t1Engineer/FishGillTarget.cxx
 *
 * Copyright (c) 2004-2016 by Stuart Ansell/Goran Skoro
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
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Simulation.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "ProtonVoid.h"
#include "BeamWindow.h"
#include "TargetBase.h"
#include "FishGillVessel.h"
#include "BulletPlates.h"
#include "BulletDivider.h"
#include "FishGillTarget.h"

namespace ts1System
{

FishGillTarget::FishGillTarget(const std::string& Key)  :
  TargetBase(Key,12),
  tIndex(ModelSupport::objectRegister::Instance().cell(Key)),
  PlateTarObj(new BulletPlates("BPlates")),
  PressVObj(new FishGillVessel("BVessel"))
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
   */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  DObj.push_back(std::shared_ptr<BulletDivider>(new BulletDivider("BDiv",0,1)));
  OR.addObject(DObj.back());
  DObj.push_back(std::shared_ptr<BulletDivider>(new BulletDivider("BDiv",1,0)));
  OR.addObject(DObj.back());

  OR.addObject(PressVObj);
  OR.addObject(PlateTarObj);
}

FishGillTarget::FishGillTarget(const FishGillTarget& A) : 
  constructSystem::TargetBase(A),
  tIndex(A.tIndex),PlateTarObj(A.PlateTarObj),
  PressVObj(A.PressVObj)
  /*!
    Copy constructor
    \param A :: FishGillTarget to copy
  */
{}

FishGillTarget&
FishGillTarget::operator=(const FishGillTarget& A)
  /*!
    Assignment operator
    \param A :: FishGillTarget to copy
    \return *this
  */
{
  if (this!=&A)
    {
      constructSystem::TargetBase::operator=(A);
      PlateTarObj=A.PlateTarObj;
      PressVObj=A.PressVObj;
    }
  return *this;
}


FishGillTarget*
FishGillTarget::clone() const
  /*!
    Clone funciton
    \return new(this)
  */
{
  return new FishGillTarget(*this);
}

FishGillTarget::~FishGillTarget() 
 /*!
   Destructor
 */
{}
  
void
FishGillTarget::createBeamWindow(Simulation& System)
  /*!
    Create the beamwindow if present
    \param System :: Simulation to build into
  */
{
  ELog::RegMethod RegA("FishGillTarget","createBeamWindow");
  if (PLine->getVoidCell())
    {
      ModelSupport::objectRegister& OR=
	ModelSupport::objectRegister::Instance();     
      if (!BWPtr)
	{
	  BWPtr=std::shared_ptr<ts1System::BeamWindow>
	    (new ts1System::BeamWindow("BWindow"));
	  OR.addObject(BWPtr);
	}      
      BWPtr->addBoundarySurf(PLine->getCompContainer());
      BWPtr->setInsertCell(PLine->getVoidCell());
      BWPtr->createAll(System,*this,6);   // realtive front face
    }
  
  return;
}

void
FishGillTarget::addProtonLine(Simulation& ,
			     const attachSystem::FixedComp& ,
			     const long int )
  /*!
    Add a proton void cell
    \param System :: Simualation
    \param refFC :: reflector
    \param index :: Index of line
   */
{
  ELog::RegMethod RegA("FishGillTarget","addProtonLine");

  //  PLine->createAll(System,*PressVObj,-7,refFC,index);
  //  createBeamWindow(System);
  
  return;
}

void
FishGillTarget::createAll(Simulation& System,
		       const attachSystem::FixedComp& FC)
  /*!
    Global creation of the hutch
    \param System :: Simulation to add vessel to
    \param FC :: FixedComp for origin [World Origin]
  */
{
  ELog::RegMethod RegA("FishGillTarget","createAll");

  //  PlateTarObj->setInsertCell(this->getInsertCells());
  PlateTarObj->createAll(System,FC,0);
  
  PressVObj->setMainRadius(PlateTarObj->getMainRadius());
  PressVObj->setInsertCell(this->getInsertCells());
  PressVObj->createAll(System,FC,*PlateTarObj,0);
  
  for(std::shared_ptr<BulletDivider> DPtr : DObj)
    {
      DPtr->setInsertCell(PressVObj->getInnerCells());
      DPtr->createAll(System,*PlateTarObj,*PressVObj);
    }

  return;
}
 

  
}  // NAMESPACE ts1System
