/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   essBuild/makeESSBL.cxx
 *
 * Copyright (c) 2004-2014 by Stuart Ansell
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
#include <utility>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>
#include <boost/format.hpp>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "stringCombine.h"
#include "inputParam.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Rules.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Simulation.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "LayerComp.h"
#include "FixedGroup.h"
#include "ShapeUnit.h"
#include "GuideLine.h"

#include "beamlineConstructor.h"
#include "makeESSBL.h"

namespace essSystem
{

makeESSBL::makeESSBL(const std::string& SN,
		     const std::string& BName) : 
  beamlineSystem::beamlineConstructor(),
  shutterName(SN),
  RefA(new beamlineSystem::GuideLine(BName))
 /*!
    Constructor
    \param SN :: Shutter name
    \param BName :: Beamline
 */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(RefA);
}

makeESSBL::makeESSBL(const makeESSBL& A) : 
  shutterName(A.shutterName),RefA(A.RefA)
  /*!
    Copy constructor
    \param A :: makeESSBL to copy
  */
{}

makeESSBL&
makeESSBL::operator=(const makeESSBL& A)
  /*!
    Assignment operator
    \param A :: makeESSBL to copy
    \return *this
  */
{
  if (this!=&A)
    {
      RefA=A.RefA;
    }
  return *this;
}


makeESSBL::~makeESSBL()
  /*!
    Destructor
  */
{}

void 
makeESSBL::build(Simulation& System,
		 const mainSystem::inputParam& IParam)
  /*!
    Carry out the full build
    \param SimPtr :: Simulation system
    \param IParam :: Input parameters
   */
{
  // For output stream
  ELog::RegMethod RegA("makeESSBL","build");

  
  const int voidCell(74123);
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  const attachSystem::FixedComp* mainFCPtr=
    OR.getObject<attachSystem::FixedComp>(shutterName);

  if (!mainFCPtr)
    throw ColErr::InContainerError<std::string>(shutterName,"shutterObject");

  RefA->addInsertCell(voidCell);
  RefA->createAll(System,*mainFCPtr,2,*mainFCPtr,2);
  
  
  return;
}


}   // NAMESPACE essSystem

