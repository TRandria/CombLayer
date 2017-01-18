/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/skadi/SKADI.cxx
 *
 * Copyright (c) 2004-2016 by Tsitohaina Randriamalala/Stuart Ansell
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
#include <array>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
#include "debugMethod.h"
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
#include "FixedOffset.h"
#include "FixedGroup.h"
#include "FixedOffsetGroup.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "SecondTrack.h"
#include "CopiedComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "SurfMap.h"
#include "FrontBackCut.h"
#include "World.h"
#include "AttachSupport.h"
#include "GuideItem.h"
#include "Jaws.h"
#include "GuideLine.h"
#include "DiskChopper.h"
#include "VacuumBox.h"
#include "VacuumPipe.h"
#include "ChopperHousing.h"
#include "ChopperUnit.h"
#include "Bunker.h"
#include "BunkerInsert.h"
#include "CompBInsert.h"
#include "ChopperPit.h"
#include "HoleShape.h"
#include "LineShield.h"
#include "PipeCollimator.h"
#include "Aperture.h"

#include "SKADI.h"

namespace essSystem
{
  
SKADI::SKADI(const std::string& keyName):
  attachSystem::CopiedComp("skadi",keyName),
  stopPoint(0),
  skadiAxis(new attachSystem::FixedOffset(newName+"Axis",4)),
  BendA(new beamlineSystem::GuideLine(newName+"BA")),
  VPipeB(new constructSystem::VacuumPipe(newName+"PipeB")),
  BendB(new beamlineSystem::GuideLine(newName+"BB")),
  VPipeInA(new constructSystem::VacuumPipe(newName+"PipeInA")),
  BendInA(new beamlineSystem::GuideLine(newName+"BInA")),
  VPipeInB(new constructSystem::VacuumPipe(newName+"PipeInB")),
  BendInB(new beamlineSystem::GuideLine(newName+"BInB")),
  VPipeInC(new constructSystem::VacuumPipe(newName+"PipeInC")),
  GuideInC(new beamlineSystem::GuideLine(newName+"GInC")),

  BInsert(new CompBInsert(newName+"BInsert")),
  FocusWall(new beamlineSystem::GuideLine(newName+"FWall")),
  FocusShutterA(new beamlineSystem::GuideLine(newName+"FSA")),
  FocusShutterB(new beamlineSystem::GuideLine(newName+"FSB")),

  VPipeOutA(new constructSystem::VacuumPipe(newName+"PipeOutA")),
  GuideOutA(new beamlineSystem::GuideLine(newName+"GOutA")),
  
  PitA(new constructSystem::ChopperPit(newName+"PitA")),
  PitACutFront(new
  constructSystem::HoleShape(newName+"PitACutFront")),
  PitACutBack(new constructSystem::HoleShape(newName+"PitACutBack")),

  GuideOutB(new beamlineSystem::GuideLine(newName+"GOutB")),
  GuideOutC(new beamlineSystem::GuideLine(newName+"GOutC")),

  ShieldD(new constructSystem::LineShield(newName+"ShieldD")),
  VPipeOutD(new constructSystem::VacuumPipe(newName+"PipeOutD")),
  GuideOutD(new beamlineSystem::GuideLine(newName+"GOutD")),

  PitD(new constructSystem::ChopperPit(newName+"PitD")),
  PitDCutFront(new
  constructSystem::HoleShape(newName+"PitDCutFront")),
  PitDCutBack(new constructSystem::HoleShape(newName+"PitDCutBack")),
  
  PitE(new constructSystem::ChopperPit(newName+"PitE")),
  PitECutFront(new
  constructSystem::HoleShape(newName+"PitECutFront")),
  PitECutBack(new constructSystem::HoleShape(newName+"PitECutBack")),
  ShieldE(new constructSystem::LineShield(newName+"ShieldE")),
  VPipeOutE(new constructSystem::VacuumPipe(newName+"PipeOutE")),
  GuideOutE(new beamlineSystem::GuideLine(newName+"GOutE")),
  
  ShieldF(new constructSystem::LineShield(newName+"ShieldF")),
  VPipeOutF(new constructSystem::VacuumPipe(newName+"PipeOutF")),
  GuideOutF(new beamlineSystem::GuideLine(newName+"GOutF")),
  
  GuideOutG(new beamlineSystem::GuideLine(newName+"GOutG")),

  ShieldH(new constructSystem::LineShield(newName+"ShieldH")),
  VPipeOutH(new constructSystem::VacuumPipe(newName+"PipeOutH")),
  GuideOutH(new beamlineSystem::GuideLine(newName+"GOutH"))

{
  ELog::RegMethod RegA("SKADI","SKADI");
  
  ModelSupport::objectRegister& OR = ModelSupport::objectRegister::Instance();
  OR.cell(newName+"Axis");

  OR.addObject(skadiAxis);

  OR.addObject(BendA);
  OR.addObject(VPipeB);
  OR.addObject(BendB);
  OR.addObject(VPipeInA);
  OR.addObject(BendInA);
  OR.addObject(VPipeInB);
  OR.addObject(BendInB);  
  OR.addObject(VPipeInC);
  OR.addObject(GuideInC);

  OR.addObject(BInsert);
  OR.addObject(FocusWall);
  OR.addObject(FocusShutterA);
  OR.addObject(FocusShutterB);

  OR.addObject(PitA);
  OR.addObject(PitACutFront);
  OR.addObject(PitACutBack);
  OR.addObject(VPipeOutA);
  OR.addObject(GuideOutA);

  OR.addObject(GuideOutB);
  OR.addObject(GuideOutC);

  OR.addObject(ShieldD);
  OR.addObject(VPipeOutD);
  OR.addObject(GuideOutD);

  OR.addObject(PitD);
  OR.addObject(PitDCutFront);
  OR.addObject(PitDCutBack);

  OR.addObject(PitE);
  OR.addObject(PitECutFront);
  OR.addObject(PitECutBack);
  OR.addObject(ShieldE);
  OR.addObject(VPipeOutE);
  OR.addObject(GuideOutE);

  OR.addObject(ShieldF);
  OR.addObject(VPipeOutF);
  OR.addObject(GuideOutF);

  OR.addObject(GuideOutG);
  
  OR.addObject(ShieldH);
  OR.addObject(VPipeOutH);
  OR.addObject(GuideOutH);  
}


SKADI::~SKADI()
{}

void
SKADI::setBeamAxis(const FuncDataBase& Control,
		  const GuideItem& GItem,
		  const bool reverseZ)
  /*!
    Set the primary direction object
    \param Control :: Database of variables
    \param GItem :: Guide Item to 
    \param reverseZ :: Reverse axis
   */
{
  ELog::RegMethod RegA("SKADI","setBeamAxis");
  
  skadiAxis->populate(Control);
  skadiAxis->createUnitVector(GItem);
  skadiAxis->setLinkCopy(0,GItem.getKey("Main"),0);
  skadiAxis->setLinkCopy(1,GItem.getKey("Main"),1);
  skadiAxis->setLinkCopy(2,GItem.getKey("Beam"),0);
  skadiAxis->setLinkCopy(3,GItem.getKey("Beam"),1);
  
  skadiAxis->linkShift(3);
  skadiAxis->linkShift(4);
  skadiAxis->linkAngleRotate(3);
  skadiAxis->linkAngleRotate(4);

  if (reverseZ)
    skadiAxis->reverseZ();
}


void
SKADI::build(Simulation& System,
	    const GuideItem& GItem,
	    const Bunker& bunkerObj,
	    const int voidCell)
  /*!
    Carry out the full build
    \param System :: Simulation system
    \param GItem :: Guide Item 
    \param bunkerObj :: Bunker component [for inserts]
    \param voidCell :: Void cell
   */
{
  ELog::RegMethod RegA("SKADI", "build");
  
  ELog::EM<<"\n Building TREX on:"<<GItem.getKeyName()<<ELog::endDiag;
  
  const FuncDataBase& Control=System.getDataBase();
  CopiedComp::process(System.getDataBase());
  stopPoint=Control.EvalDefVar<int>(newName+"StopPoint",0);
  
  setBeamAxis(Control,GItem,1);
  
  /// Inside the Monolith
  BendA->addInsertCell(GItem.getCells("Void"));
  BendA->setFront(GItem.getKey("Beam"),-1);
  BendA->setBack(GItem.getKey("Beam"),-2);
  BendA->createAll(System,GItem.getKey("Beam"),-1,GItem.getKey("Beam"),-1);

  if (stopPoint==1) return;          // Stop at Monolith

  /// Pipe+Guide at Light shutter position
  VPipeB->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeB->createAll(System,GItem.getKey("Beam"),2);
  BendB->addInsertCell(VPipeB->getCells("Void"));
  BendB->createAll(System,BendA->getKey("Guide0"),2,
		   BendA->getKey("Guide0"),2);

  VPipeInA->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInA->createAll(System,*VPipeB,2);
  BendInA->addInsertCell(VPipeInA->getCells("Void"));
  BendInA->createAll(System,BendB->getKey("Guide0"),2,
		   BendB->getKey("Guide0"),2);
  
  VPipeInB->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInB->setFront(*VPipeInA,2,true);
  VPipeInB->createAll(System,*VPipeInA,2);
  BendInB->addInsertCell(VPipeInB->getCells("Void"));
  BendInB->createAll(System,BendInA->getKey("Guide0"),2,
		   BendInA->getKey("Guide0"),2);

  VPipeInC->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInC->createAll(System,BendInB->getKey("Guide0"),2);
  GuideInC->addInsertCell(VPipeInC->getCells("Void"));
  GuideInC->createAll(System,*VPipeInC,0,*VPipeInC,0);
  
  if (stopPoint==2) return;         // Stop at Bunker exit

  BInsert->addInsertCell(bunkerObj.getCell("MainVoid"));
  BInsert->addInsertCell(voidCell);
  BInsert->createAll(System,*VPipeInC,2,bunkerObj);
  attachSystem::addToInsertSurfCtrl(System,bunkerObj,"frontWall",*BInsert);
  FocusWall->addInsertCell(BInsert->getCells("Item"));
  FocusWall->createAll(System,*BInsert,-1,*BInsert,-1);
  FocusShutterA->addInsertCell(BInsert->getCells("Item"));
  FocusShutterA->createAll(System,FocusWall->getKey("Guide0"),2,
			   FocusWall->getKey("Guide0"),2);
  FocusShutterB->addInsertCell(BInsert->getCells("Item"));
  FocusShutterB->createAll(System,FocusShutterA->getKey("Guide0"),2,
  			  FocusShutterA->getKey("Guide0"),2);

  if (stopPoint==3) return;
  
  PitA->addInsertCell(voidCell); //Chopper and Polarization pit
  PitA->createAll(System,*BInsert,2);

  VPipeOutA->addInsertCell(voidCell);
  VPipeOutA->addInsertCell(PitA->getCells("Outer"));
  VPipeOutA->addInsertCell(PitA->getCells("MidLayer"));
  VPipeOutA->setBack(PitA->getKey("Mid"),1);
  VPipeOutA->createAll(System,*BInsert,2);
  GuideOutA->addInsertCell(VPipeOutA->getCells("Void"));
  GuideOutA->createAll(System,*VPipeOutA,0,*VPipeOutA,0);

  GuideOutB->addInsertCell(PitA->getCell("Void"));
  GuideOutB->createAll(System,PitA->getKey("Inner"),-1,
		       PitA->getKey("Inner"),-1);
  GuideOutC->addInsertCell(PitA->getCell("Void"));
  GuideOutC->createAll(System,GuideOutB->getKey("Guide0"),2,
		       GuideOutB->getKey("Guide0"),2);

  PitD->addInsertCell(voidCell); //Chopper II  pit
  PitD->createAll(System,PitA->getKey("Outer"),2);
  
  ShieldD->addInsertCell(voidCell);
  ShieldD->addInsertCell(PitA->getCells("Outer"));
  ShieldD->addInsertCell(PitA->getCells("MidLayer"));
  ShieldD->setFront(PitA->getKey("Mid"),2);
  ShieldD->addInsertCell(PitD->getCells("Outer"));
  ShieldD->addInsertCell(PitD->getCells("MidLayer"));
  ShieldD->setBack(PitD->getKey("Mid"),1);  
  ShieldD->createAll(System,PitA->getKey("Mid"),2);
  VPipeOutD->addInsertCell(ShieldD->getCell("Void"));
  VPipeOutD->createAll(System,*ShieldD,-1);
  GuideOutD->addInsertCell(VPipeOutD->getCells("Void"));
  GuideOutD->createAll(System,*VPipeOutD,0,*VPipeOutD,0);

  return;  
}

} // NAMESPACE essSystem

