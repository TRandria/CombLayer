/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   t1Upgrade/makeGamma.cxx
 *
 * Copyright (c) 2004-2015 by Stuart Ansell
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
#include <iterator>
#include <memory>

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
#include "Object.h"
#include "Qhull.h"
#include "insertInfo.h"
#include "insertBaseInfo.h"
#include "Simulation.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "LayerComp.h"
#include "CellMap.h"
#include "ModBase.h"
#include "ConicInfo.h"
#include "BlockMod.h"
#include "voidCylVolume.h"
#include "World.h"
#include "AttachSupport.h"
#include "NordBall.h"
#include "makeGamma.h"

#include "Debug.h"

namespace gammaSystem
{

makeGamma::makeGamma() :
  brick(new constructSystem::BlockMod("Brick")),
  tallyVol(new constructSystem::voidCylVolume("VoidTally")),
  NDet(0)
  /*!
    Constructor
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(brick);
  OR.addObject(tallyVol);
}

makeGamma::~makeGamma()
  /*!
    Destructor
   */
{}

void
makeGamma::makeDetectors(Simulation& System)
  /*!
    Construct all the detectors
    \param System :: Simulation 
  */
{
  ELog::RegMethod RegA("makeGamma","createDetectors");

  const int voidCell(74123);
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();


  const FuncDataBase& Control=System.getDataBase();
  NDet=Control.EvalVar<size_t>("gammaSetupNDet");
  for(size_t i=0;i<NDet;i++)
    {
      std::shared_ptr<NordBall> NBPtr(new NordBall(i,"Nord"));
      NBPtr->addInsertCell(voidCell);
      NBPtr->createAll(System,World::masterOrigin());
      
      OR.addObject(NBPtr);
      
    }
}
			  

void 
makeGamma::build(Simulation* SimPtr,
		 const mainSystem::inputParam& IParam)
  /*!
    Carry out the full build
    \param SimPtr :: Simulation system
    \param IParam :: Input parameters
   */
{
  // For output stream
  ELog::RegMethod RControl("makeGamma","build");

  const int voidCell(74123);
  
  brick->addInsertCell(voidCell);
  brick->createAll(*SimPtr,World::masterOrigin());

  tallyVol->addInsertCell(voidCell);
  tallyVol->createAll(*SimPtr,*brick);
  makeDetectors(*SimPtr);

  return;
}


}   // NAMESPACE gammaSystem
