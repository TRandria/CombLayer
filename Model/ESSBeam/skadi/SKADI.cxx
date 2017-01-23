/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/skadi/SKADI.cxx
 *
 * Copyright (c) 2004-2017 by Tsitohaina Randriamalala/Stuart Ansell
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
  
  PitA(new constructSystem::ChopperPit(newName+"PitA")),
  PitACutBack(new constructSystem::HoleShape(newName+"PitACutBack")),

  ShieldAB(new constructSystem::LineShield(newName+"ShieldAB")),
  VPipeOutA(new constructSystem::VacuumPipe(newName+"PipeOutA")),
  GuideOutA(new beamlineSystem::GuideLine(newName+"GOutA")),
  VPipeOutB(new constructSystem::VacuumPipe(newName+"PipeOutB")),
  GuideOutB(new beamlineSystem::GuideLine(newName+"GOutB")),
  
  PitC(new constructSystem::ChopperPit(newName+"PitC")),
  PitCCutFront(new
  constructSystem::HoleShape(newName+"PitCCutFront")),
  PitCCutBack(new constructSystem::HoleShape(newName+"PitCCutBack")),

  ShieldC(new constructSystem::LineShield(newName+"ShieldC")),
  VPipeOutC(new constructSystem::VacuumPipe(newName+"PipeOutC")),
  GuideOutC(new beamlineSystem::GuideLine(newName+"GOutC")),

  PitD(new constructSystem::ChopperPit(newName+"PitD")),
  PitDCutFront(new
  constructSystem::HoleShape(newName+"PitDCutFront")),
  PitDCutBack(new constructSystem::HoleShape(newName+"PitDCutBack")),

  ShieldD(new constructSystem::LineShield(newName+"ShieldD")),
  VPipeOutD(new constructSystem::VacuumPipe(newName+"PipeOutD")),
  GuideOutD(new beamlineSystem::GuideLine(newName+"GOutD"))
  
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
  OR.addObject(PitACutBack);

  OR.addObject(ShieldAB);
  OR.addObject(VPipeOutA);
  OR.addObject(GuideOutA);
  OR.addObject(VPipeOutB);
  OR.addObject(GuideOutB);

  OR.addObject(PitC);
  OR.addObject(PitCCutFront);
  OR.addObject(PitCCutBack);

  OR.addObject(ShieldC);
  OR.addObject(VPipeOutC);
  OR.addObject(GuideOutC);

  OR.addObject(PitD);
  OR.addObject(PitDCutFront);
  OR.addObject(PitDCutBack);

  OR.addObject(ShieldD);
  OR.addObject(VPipeOutD);
  OR.addObject(GuideOutD);  

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

  return;
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
  
  ELog::EM<<"\n Building SKADI on:"<<GItem.getKeyName()<<ELog::endDiag;
  
  const FuncDataBase& Control=System.getDataBase();
  CopiedComp::process(System.getDataBase());

  stopPoint=Control.EvalDefVar<int>(newName+"StopPoint",0);
  
  setBeamAxis(Control,GItem,0);
  
  /// Inside the Monolith
  BendA->addInsertCell(GItem.getCells("Void"));
  BendA->setFront(GItem.getKey("Beam"),-1);
  BendA->setBack(GItem.getKey("Beam"),-2);
  BendA->createAll(System,*skadiAxis,-3,*skadiAxis,-3);

  if (stopPoint==1) return;          // Stop at Monolith

  /// Pipe+Guide at Light shutter position
  VPipeB->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeB->createAll(System,BendA->getKey("Guide0"),2);
  BendB->addInsertCell(VPipeB->getCells("Void"));
  BendB->createAll(System,*VPipeB,0,*VPipeB,0);
  
  VPipeInA->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInA->createAll(System,BendB->getKey("Guide0"),2);
  BendInA->addInsertCell(VPipeInA->getCells("Void"));
  BendInA->createAll(System,*VPipeInA,0,*VPipeInA,0);
  
  VPipeInB->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInB->createAll(System,BendInA->getKey("Guide0"),2);
  BendInB->addInsertCell(VPipeInB->getCells("Void"));
  BendInB->createAll(System,BendInA->getKey("Guide0"),2,
		     BendInA->getKey("Guide0"),2);
   
  VPipeInC->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInC->createAll(System,BendInB->getKey("Guide0"),2);
  GuideInC->addInsertCell(VPipeInC->getCells("Void"));
  GuideInC->createAll(System,*VPipeInC,0,*VPipeInC,0);
 
  if (stopPoint==2) return;         // Stop at last pipe in Bunker
  
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

  PitA->addInsertCell(voidCell); //Chopper I pit
  PitA->addFrontWall(bunkerObj,2);
  PitA->createAll(System,FocusShutterB->getKey("Guide0"),2);

  PitACutBack->addInsertCell(PitA->getCells("MidLayerBack"));
  PitACutBack->addInsertCell(PitA->getCells("Collet"));
  PitACutBack->setFaces(PitA->getKey("Mid").getSignedFullRule(-2),
			 PitA->getKey("Inner").getSignedFullRule(2));
  //  PitACutBack->createAll(System,GuideOutA->getKey("Guide0"),1);
  PitACutBack->createAll(System,PitA->getKey("Inner"),2);
  
  PitC->addInsertCell(voidCell); //Chopper II pit
  PitC->createAll(System,PitA->getKey("Outer"),2);
  PitCCutFront->addInsertCell(PitC->getCells("MidLayerFront"));
  PitCCutFront->setFaces(PitC->getKey("Mid").getSignedFullRule(-1),
			 PitC->getKey("Inner").getSignedFullRule(1));
  PitCCutFront->createAll(System,PitC->getKey("Inner"),-1);

  PitCCutBack->addInsertCell(PitC->getCells("MidLayerBack"));
  PitCCutBack->addInsertCell(PitC->getCells("Collet"));
  PitCCutBack->setFaces(PitC->getKey("Mid").getSignedFullRule(-2),
			 PitC->getKey("Inner").getSignedFullRule(2));
  PitCCutBack->createAll(System,PitC->getKey("Inner"),2);
  
  PitD->addInsertCell(voidCell); //Chopper III & IV pit
  PitD->createAll(System,PitC->getKey("Outer"),2);
  PitDCutFront->addInsertCell(PitD->getCells("MidLayerFront"));
  PitDCutFront->setFaces(PitD->getKey("Mid").getSignedFullRule(-1),
			 PitD->getKey("Inner").getSignedFullRule(1));
  PitDCutFront->createAll(System,PitD->getKey("Inner"),-1);

  PitDCutBack->addInsertCell(PitD->getCells("MidLayerBack"));
  PitDCutBack->addInsertCell(PitD->getCells("Collet"));
  PitDCutBack->setFaces(PitD->getKey("Mid").getSignedFullRule(-2),
			 PitD->getKey("Inner").getSignedFullRule(2));
  PitDCutBack->createAll(System,PitD->getKey("Inner"),2);
  

  ShieldAB->addInsertCell(voidCell);
  ShieldAB->addInsertCell(PitA->getCells("Outer"));
  ShieldAB->addInsertCell(PitA->getCells("MidLayer"));
  ShieldAB->setFront(PitA->getKey("Mid"),2);
  ShieldAB->addInsertCell(PitC->getCells("Outer"));
  ShieldAB->addInsertCell(PitC->getCells("MidLayer"));
  ShieldAB->setBack(PitC->getKey("Mid"),1);  
  ShieldAB->createAll(System,FocusShutterB->getKey("Guide0"),2);

  VPipeOutA->addInsertCell(ShieldAB->getCell("Void"));
  VPipeOutA->createAll(System,*ShieldAB,-1);
  GuideOutA->addInsertCell(VPipeOutA->getCells("Void"));
  GuideOutA->createAll(System,*VPipeOutA,0,*VPipeOutA,0);
    
  VPipeOutB->addInsertCell(ShieldAB->getCell("Void"));
  //  VPipeOutB->setBack(PitC->getKey("Mid"),1);
  VPipeOutB->createAll(System,*VPipeOutA,2);
  GuideOutB->addInsertCell(VPipeOutB->getCells("Void"));
  GuideOutB->createAll(System,*VPipeOutB,0,*VPipeOutB,0);
  
  ShieldC->addInsertCell(voidCell);
  ShieldC->addInsertCell(PitC->getCells("Outer"));
  ShieldC->addInsertCell(PitC->getCells("MidLayer"));
  ShieldC->setFront(PitC->getKey("Mid"),2);
  ShieldC->addInsertCell(PitD->getCells("Outer"));
  ShieldC->addInsertCell(PitD->getCells("MidLayer"));
  ShieldC->setBack(PitD->getKey("Mid"),1);  
  ShieldC->createAll(System,PitC->getKey("Mid"),2);

  VPipeOutC->addInsertCell(ShieldC->getCell("Void"));
  VPipeOutC->createAll(System,*ShieldC,-1);
  GuideOutC->addInsertCell(VPipeOutC->getCells("Void"));
  GuideOutC->createAll(System,*VPipeOutC,0,*VPipeOutC,0);

  ShieldD->addInsertCell(voidCell);
  ShieldD->addInsertCell(PitD->getCells("Outer"));
  ShieldD->addInsertCell(PitD->getCells("MidLayer"));
  ShieldD->setFront(PitD->getKey("Mid"),2);
  ShieldD->createAll(System,PitD->getKey("Mid"),2);

  VPipeOutD->addInsertCell(ShieldD->getCell("Void"));
  VPipeOutD->createAll(System,*ShieldD,-1);
  GuideOutD->addInsertCell(VPipeOutD->getCells("Void"));
  GuideOutD->createAll(System,*VPipeOutD,0,*VPipeOutD,0);
  

  return;  
}

} // NAMESPACE essSystem

