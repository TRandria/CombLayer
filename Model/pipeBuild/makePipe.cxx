/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   pipeBuild/makePipe.cxx
 *
 * Copyright (c) 2004-2017 by Stuart Ansell
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
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "FrontBackCut.h"
#include "LayerComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "GroupOrigin.h"
#include "World.h"
#include "AttachSupport.h"
#include "pipeTube.h"
#include "SurfMap.h"

/// needed fro chopper and Co
#include "FixedGroup.h"
#include "FixedOffsetGroup.h"
#include "DiskChopper.h"
#include "ChopperPit.h"
#include "ChopperUnit.h"
#include "ChopperHousing.h"
#include "HoleShape.h"
#include "LineShield.h"
#include "PipeCollimator.h"
#include "Aperture.h"

/// Pipe and GL
#include "VacuumPipe.h"
#include "GuideLine.h"

#include "makePipe.h"

#include "AHut.h"

namespace pipeSystem
{

makePipe::makePipe() :
  ATube(new pipeSystem::pipeTube("ATube")),
  BTube(new pipeSystem::pipeTube("BTube")),
  CTube(new pipeSystem::pipeTube("CTube")),
  ChopperA(new constructSystem::ChopperUnit("ChopperA")),
  BandADisk(new constructSystem::DiskChopper("BandADisk")),
  PipeA(new constructSystem::VacuumPipe("PipeA")),
  GuideA(new beamlineSystem::GuideLine("GuideA")),
  PipeB(new constructSystem::VacuumPipe("PipeB")),
  GuideB(new beamlineSystem::GuideLine("GuideB")),
  PipeC(new constructSystem::VacuumPipe("PipeC")),
  GuideC(new beamlineSystem::GuideLine("GuideC")),
  PitA(new constructSystem::ChopperPit("PitA")),
  CutFrontA(new constructSystem::HoleShape("CutFrontA")),
  CutBackA(new constructSystem::HoleShape("CutBackA")),
  ShieldA(new constructSystem::LineShield("ShieldA")),
  ShieldB(new constructSystem::LineShield("ShieldB")),
  
  Cave(new pipeSystem::AHut("Cave")),
  AppA(new constructSystem::Aperture("AppA")),
  CollimA(new constructSystem::PipeCollimator("CollimA"))
  /*!
    Constructor
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(ATube);
  OR.addObject(BTube);
  OR.addObject(CTube);

  OR.addObject(ChopperA);
  OR.addObject(BandADisk);

  OR.addObject(PipeA);
  OR.addObject(GuideA);

  OR.addObject(PipeB);
  OR.addObject(GuideB);

  OR.addObject(PipeC);
  OR.addObject(GuideC);

  OR.addObject(PitA);

  OR.addObject(CutFrontA);
  OR.addObject(CutBackA);
    
  OR.addObject(ShieldA);
  OR.addObject(ShieldB);

  OR.addObject(Cave);
  OR.addObject(AppA);
  OR.addObject(CollimA);
}

makePipe::makePipe(const makePipe& A) : 
  ATube(new pipeSystem::pipeTube(*(A.ATube))),
  BTube(new pipeSystem::pipeTube(*(A.BTube))),
  CTube(new pipeSystem::pipeTube(*(A.CTube)))
  /*!
    Copy constructor
    \param A :: makePipe to copy
  */
{}

makePipe&
makePipe::operator=(const makePipe& A)
  /*!
    Assignment operator
    \param A :: makePipe to copy
    \return *this
  */
{
  if (this!=&A)
    {
      *ATube=*A.ATube;
      *BTube=*A.BTube;
      *CTube=*A.CTube;
    }
  return *this;
}

makePipe::~makePipe()
  /*!
    Destructor
   */
{}

void 
makePipe::build(Simulation* SimPtr,
		       const mainSystem::inputParam&)
/*!
  Carry out the full build
  \param SimPtr :: Simulation system
  \param :: Input parameters
*/
{
  // For output stream
  ELog::RegMethod RControl("makePipe","build");

  int voidCell(74123);
  /*
  ATube->addInsertCell(voidCell);
  ATube->createAll(*SimPtr,World::masterOrigin(),0);
  
  BTube->addInsertCell(voidCell);
  BTube->createAll(*SimPtr,*ATube,2);
 
  CTube->addInsertCell(voidCell);
  CTube->createAll(*SimPtr,*BTube,2);
  */
  /*
  PitA->addInsertCell(voidCell);
  //  PitA->createAll(*SimPtr,*CTube,2);
  PitA->createAll(*SimPtr,World::masterOrigin(),0);

  ChopperA->addInsertCell(PitA->getCell("Void"));
  ChopperA->createAll(*SimPtr,*PitA,0);

  BandADisk->addInsertCell(ChopperA->getCell("Void"));
  BandADisk->setCentreFlag(3);
  BandADisk->setOffsetFlag(1);
  BandADisk->createAll(*SimPtr,ChopperA->getKey("Beam"),0);
*/

  
  //  PipeB->addInsertCell(voidCell);
  //  PipeB->addInsertCell(PitA->getCells("Outer"));
  //  PipeB->setBack(PitA->getKey("Mid"),1);
  //  PipeB->createAll(*SimPtr,GuideA->getKey("Guide0"),2);
  
  PipeA->addInsertCell(voidCell);
  //  PipeA->createAll(*SimPtr,ChopperA->getKey("Beam"),2);
  PipeA->createAll(*SimPtr,World::masterOrigin(),0);
  GuideA->addInsertCell(PipeA->getCells("Void"));
  //  GuideA->addInsertCell(voidCell);
  GuideA->createAll(*SimPtr,*PipeA,0,*PipeA,0);
  
  // GuideB->addInsertCell(PipeB->getCells("Void"));
  //GuideB->createAll(*SimPtr,*PipeB,0,*PipeB,0);

  //  CutFrontA->addInsertCell(PitA->getCells("MidLayerFront"));
  //  CutFrontA->setFaces(PitA->getKey("Mid").getSignedFullRule(-1),
  //		      PitA->getKey("Inner").getSignedFullRule(1));
  //  CutFrontA->createAll(*SimPtr,GuideB->getKey("Guide0"),2);
  //
  //  CutBackA->addInsertCell(PitA->getCells("MidLayerBack"));
  //  CutBackA->addInsertCell(PitA->getCells("Collet"));
  //  CutBackA->setFaces(PitA->getKey("Mid").getSignedFullRule(-2),
  //		      PitA->getKey("Inner").getSignedFullRule(2));
  //  CutBackA->createAll(*SimPtr,GuideB->getKey("Guide0"),2);
  //  
  //
  //  ShieldA->addInsertCell(voidCell);
  //  ShieldA->createAll(*SimPtr,World::masterOrigin(),0);
  //
  //  ShieldB->addInsertCell(ShieldA->getCell("Void"));
  //  ShieldB->createAll(*SimPtr,*ShieldA,-1);

  //  Cave->addInsertCell(voidCell);
  //  Cave->createAll(*SimPtr,World::masterOrigin(),0);
  //AppA->addInsertCell(voidCell);
  //AppA->createAll(*SimPtr,World::masterOrigin(),0);
   
  CollimA->setOuter(PipeA->getSignedFullRule(-6));
 
  CollimA->setInner(GuideA->getXSection(0,0));
   //   CollimA->setInnerExclude(GuideA->getSignedFullRule(3));

  CollimA->addInsertCell(PipeA->getCells("Void"));
  
  CollimA->createAll(*SimPtr,*PipeA,0);
  std::cout<<PipeA->NConnect()<<std::endl;
  std::cout<<GuideA->nGroups()<<std::endl;

  return;

}
  
}   // NAMESPACE pipeSystem

