/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/trex/TREX.cxx
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

#include "TREX.h"

namespace essSystem
{
  
TREX::TREX(const std::string& keyName):
  attachSystem::CopiedComp("trex",keyName),
  nC(10),nF(8),stopPoint(0),
  trexAxis(new attachSystem::FixedOffset(newName+"Axis",4)),

  FocusMono(new beamlineSystem::GuideLine(newName+"FMono")),
  VPipeBridge(new constructSystem::VacuumPipe(newName+"PipeBridge")),
  FocusBridge(new beamlineSystem::GuideLine(newName+"FBridge")),
  
  VPipeInA(new constructSystem::VacuumPipe(newName+"PipeInA")),
  BendInA(new beamlineSystem::GuideLine(newName+"BInA")),
  VPipeInB(new constructSystem::VacuumPipe(newName+"PipeInB")),
  BendInB(new beamlineSystem::GuideLine(newName+"BInB")),
  VPipeInC(new constructSystem::VacuumPipe(newName+"PipeInC")),
  BendInC(new beamlineSystem::GuideLine(newName+"BInC")),
  VPipeInD(new constructSystem::VacuumPipe(newName+"PipeInD")),
  BendInD(new beamlineSystem::GuideLine(newName+"BInD")),
  
  VPipeInE(new constructSystem::VacuumPipe(newName+"PipeInE")),
  BendInE(new beamlineSystem::GuideLine(newName+"BInE")),

  BInsertA(new CompBInsert(newName+"BInsertA")),
  FocusWallA(new beamlineSystem::GuideLine(newName+"FWallA")),

  BInsertB(new CompBInsert(newName+"BInsertB")),
  FocusWallB(new beamlineSystem::GuideLine(newName+"FWallB")),

  PitA(new constructSystem::ChopperPit(newName+"PitA")),
  PitACutFront(new constructSystem::HoleShape(newName+"PitACutFront")),
  PitACutBack(new constructSystem::HoleShape(newName+"PitACutBack")),
  ShieldA(new constructSystem::LineShield(newName+"ShieldA")),
  VPipeOutA(new constructSystem::VacuumPipe(newName+"PipeOutA")),
  BendOutA(new beamlineSystem::GuideLine(newName+"BOutA")),
  
  PitB(new constructSystem::ChopperPit(newName+"PitB")),
  PitBCutFront(new constructSystem::HoleShape(newName+"PitBCutFront")),
  PitBCutBack(new constructSystem::HoleShape(newName+"PitBCutBack")),
  ShieldB(new constructSystem::LineShield(newName+"ShieldB")),
  VPipeOutB1(new constructSystem::VacuumPipe(newName+"PipeOutB1")),
  BendOutB1(new beamlineSystem::GuideLine(newName+"BOutB1")),
  VPipeOutB2(new constructSystem::VacuumPipe(newName+"PipeOutB2")),
  BendOutB2(new beamlineSystem::GuideLine(newName+"BOutB2")),

  PitC(new constructSystem::ChopperPit(newName+"PitC")),
  PitCCutFront(new constructSystem::HoleShape(newName+"PitCCutFront")),
  PitCCutBack(new constructSystem::HoleShape(newName+"PitCCutBack")),

  ShieldD(new constructSystem::LineShield(newName+"ShieldD")),
  VPipeOutD(new constructSystem::VacuumPipe(newName+"PipeOutD")),
  BendOutD(new beamlineSystem::GuideLine(newName+"BOutD")),

  PitE(new constructSystem::ChopperPit(newName+"PitE")),
  PitECutFront(new constructSystem::HoleShape(newName+"PitECutFront")),
  PitECutBack(new constructSystem::HoleShape(newName+"PitECutBack")),
  ShieldE(new constructSystem::LineShield(newName+"ShieldE")),
  VPipeOutE(new constructSystem::VacuumPipe(newName+"PipeOutE")),
  GuideOutE(new beamlineSystem::GuideLine(newName+"GOutE")),

  PitF(new constructSystem::ChopperPit(newName+"PitF")),
  PitFCutFront(new constructSystem::HoleShape(newName+"PitFCutFront")),
  PitFCutBack(new constructSystem::HoleShape(newName+"PitFCutBack")),
  ShieldF(new constructSystem::LineShield(newName+"ShieldF")),

  PitG(new constructSystem::ChopperPit(newName+"PitG")),
  PitGCutFront(new constructSystem::HoleShape(newName+"PitGCutFront")),
  PitGCutBack(new constructSystem::HoleShape(newName+"PitGCutBack")),
  ShieldG(new constructSystem::LineShield(newName+"ShieldG")),
  VPipeOutG(new constructSystem::VacuumPipe(newName+"PipeOutG")),
  GuideOutG(new beamlineSystem::GuideLine(newName+"GOutG")),

  ShieldH(new constructSystem::LineShield(newName+"ShieldH")),
  VPipeOutH(new constructSystem::VacuumPipe(newName+"PipeOutH")),
  GuideOutH(new beamlineSystem::GuideLine(newName+"GOutH"))  
{
  ELog::RegMethod RegA("TREX","TREX");
  
  ModelSupport::objectRegister& OR = ModelSupport::objectRegister::Instance();
  OR.cell(newName+"Axis");

  OR.addObject(trexAxis);
  
  OR.addObject(FocusMono);

  OR.addObject(VPipeBridge);
  OR.addObject(FocusBridge);
  
  OR.addObject(VPipeInA);
  OR.addObject(BendInA);
  OR.addObject(VPipeInB);
  OR.addObject(BendInB);
  OR.addObject(VPipeInC);
  OR.addObject(BendInC);
  OR.addObject(VPipeInD);
  OR.addObject(BendInD);

  OR.addObject(VPipeInE);
  OR.addObject(BendInE);

  OR.addObject(BInsertA);
  OR.addObject(FocusWallA);

  OR.addObject(BInsertB);
  OR.addObject(FocusWallB);

  OR.addObject(PitA);
  OR.addObject(PitACutFront);
  OR.addObject(PitACutBack);
  OR.addObject(ShieldA);
  OR.addObject(VPipeOutA);
  OR.addObject(BendOutA);
  
  OR.addObject(PitB);
  OR.addObject(PitBCutFront);
  OR.addObject(PitBCutBack);
  OR.addObject(ShieldB);
  OR.addObject(VPipeOutB1);
  OR.addObject(BendOutB1);
  OR.addObject(VPipeOutB2);
  OR.addObject(BendOutB2);

  
  OR.addObject(PitC);
  OR.addObject(PitCCutFront);
  OR.addObject(PitCCutBack);
  for(size_t i=0;i<nC;i++)
    {
      const std::string strNum(StrFunc::makeString(i));

      ShieldCs[i]=std::shared_ptr<constructSystem::LineShield>
     	(new constructSystem::LineShield(newName+"ShieldC"+strNum));

      VPipeOutCs[i]=std::shared_ptr<constructSystem::VacuumPipe>
	(new constructSystem::VacuumPipe(newName+"PipeOutC"+strNum));

      BendOutCs[i]=std::shared_ptr<beamlineSystem::GuideLine>
	(new beamlineSystem::GuideLine(newName+"BOutC"+strNum));

      OR.addObject(ShieldCs[i]);
      OR.addObject(VPipeOutCs[i]);
      OR.addObject(BendOutCs[i]);
    }
  
  OR.addObject(ShieldD);
  OR.addObject(VPipeOutD);
  OR.addObject(BendOutD);
  
  OR.addObject(PitE);
  OR.addObject(PitECutFront);
  OR.addObject(PitECutBack);
  OR.addObject(ShieldE);
  OR.addObject(VPipeOutE);
  OR.addObject(GuideOutE);

  OR.addObject(PitF);
  OR.addObject(PitFCutFront);
  OR.addObject(PitFCutBack);
  OR.addObject(ShieldF);

  for(size_t i=0;i<nF;i++)
    {
      const std::string strNum(StrFunc::makeString(i));

      VPipeOutFs[i]=std::shared_ptr<constructSystem::VacuumPipe>
	(new constructSystem::VacuumPipe(newName+"PipeOutF"+strNum));

      GuideOutFs[i]=std::shared_ptr<beamlineSystem::GuideLine>
	(new beamlineSystem::GuideLine(newName+"GOutF"+strNum));

      OR.addObject(VPipeOutFs[i]);
      OR.addObject(GuideOutFs[i]);
    }

  OR.addObject(PitG);
  OR.addObject(PitGCutFront);
  OR.addObject(PitGCutBack);
  OR.addObject(ShieldG);
  OR.addObject(VPipeOutG);
  OR.addObject(GuideOutG);

  OR.addObject(ShieldH);
  OR.addObject(VPipeOutH);
  OR.addObject(GuideOutH);
}


TREX::~TREX()
{}

void
TREX::setBeamAxis(const FuncDataBase& Control,
		  const GuideItem& GItem,
		  const bool reverseZ)
  /*!
    Set the primary direction object
    \param Control :: Database of variables
    \param GItem :: Guide Item to 
    \param reverseZ :: Reverse axis
   */
{
  ELog::RegMethod RegA("TREX","setBeamAxis");
  
  trexAxis->populate(Control);
  trexAxis->createUnitVector(GItem);
  trexAxis->setLinkCopy(0,GItem.getKey("Main"),0);
  trexAxis->setLinkCopy(1,GItem.getKey("Main"),1);
  trexAxis->setLinkCopy(2,GItem.getKey("Beam"),0);
  trexAxis->setLinkCopy(3,GItem.getKey("Beam"),1);
  
  trexAxis->linkShift(3);
  trexAxis->linkShift(4);
  trexAxis->linkAngleRotate(3);
  trexAxis->linkAngleRotate(4);

  if (reverseZ)
    trexAxis->reverseZ();
}


void
TREX::build(Simulation& System,
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
  ELog::RegMethod RegA("TREX", "build");
  
  ELog::EM<<"\n Building TREX on:"<<GItem.getKeyName()<<ELog::endDiag;
  
  const FuncDataBase& Control=System.getDataBase();
  CopiedComp::process(System.getDataBase());
  stopPoint=Control.EvalDefVar<int>(newName+"StopPoint",0);
  
  setBeamAxis(Control,GItem,1);
  
  /// Inside the Monolith
  FocusMono->addInsertCell(GItem.getCells("Void"));
  FocusMono->setFront(GItem.getKey("Beam"),-1);
  FocusMono->setBack(GItem.getKey("Beam"),-2);
  FocusMono->createAll(System,*trexAxis,-3,*trexAxis,-3);
  
  if (stopPoint==1) return;                      // STOP At monolith

  /// Brigde Guide 
  VPipeBridge->addInsertCell(bunkerObj.getCell("MainVoid")); 
  VPipeBridge->createAll(System,GItem.getKey("Beam"),2);
  FocusBridge->addInsertCell(VPipeBridge->getCells("Void"));
  FocusBridge->createAll(System,*VPipeBridge,0,*VPipeBridge,0);
  /// End Brigde

  /// Start Curve
  VPipeInA->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInA->createAll(System,FocusBridge->getKey("Guide0"),2);
  BendInA->addInsertCell(VPipeInA->getCells("Void"));
  BendInA->createAll(System,*VPipeInA,0,*VPipeInA,0);

  VPipeInB->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInB->setFront(*VPipeInA,2,true);
  VPipeInB->createAll(System,BendInA->getKey("Guide0"),2);
  BendInB->addInsertCell(VPipeInB->getCells("Void"));
  BendInB->createAll(System,*VPipeInB,0,*VPipeInB,0);

  VPipeInC->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInC->setFront(*VPipeInB,2,true);
  VPipeInC->createAll(System,BendInB->getKey("Guide0"),2);
  BendInC->addInsertCell(VPipeInC->getCells("Void"));
  BendInC->createAll(System,*VPipeInC,0,*VPipeInC,0);

  VPipeInD->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInD->setFront(*VPipeInC,2,true);
  VPipeInD->createAll(System,BendInC->getKey("Guide0"),2);
  BendInD->addInsertCell(VPipeInD->getCells("Void"));
  BendInD->createAll(System,*VPipeInD,0,*VPipeInD,0);

  VPipeInE->addInsertCell(bunkerObj.getCell("MainVoid"));
  VPipeInE->createAll(System,BendInD->getKey("Guide0"),2);
  BendInE->addInsertCell(VPipeInE->getCells("Void"));
  BendInE->createAll(System,*VPipeInE,0,*VPipeInE,0);

  if (stopPoint==2) return;       // STOP at the bunker edge
  
  BInsertA->addInsertCell(bunkerObj.getCell("MainVoid"));
  BInsertA->addInsertCell(voidCell);
  BInsertA->createAll(System,*VPipeInE,2,bunkerObj);
  attachSystem::addToInsertSurfCtrl(System,bunkerObj,"frontWall",*BInsertA);

  FocusWallA->addInsertCell(BInsertA->getCells("Item"));
  FocusWallA->createAll(System,*BInsertA,0,*BInsertA,0);

  BInsertB->addInsertCell(bunkerObj.getCell("MainVoid"));
  BInsertB->addInsertCell(voidCell);
  BInsertB->createAll(System,*BInsertA,2,bunkerObj);
  attachSystem::addToInsertSurfCtrl(System,bunkerObj,"frontWall",*BInsertB);

  FocusWallB->addInsertCell(BInsertB->getCells("Item"));
  FocusWallB->createAll(System,*BInsertB,0,*BInsertB,0);

  PitA->addInsertCell(voidCell);  // First pit wrt bunker insert
  PitA->createAll(System,*BInsertB,2); 
  
  ShieldA->addInsertCell(voidCell);
  ShieldA->setFront(*BInsertB,2);
  ShieldA->addInsertCell(PitA->getCells("Outer"));
  ShieldA->addInsertCell(PitA->getCells("MidLayer"));
  ShieldA->setBack(PitA->getKey("Mid"),1);
  ShieldA->createAll(System,*BInsertB,2);

  VPipeOutA->addInsertCell(ShieldA->getCell("Void"));
  VPipeOutA->addInsertCell(PitA->getCells("MidLayer"));
  VPipeOutA->setBack(PitA->getKey("Mid"),1);
  VPipeOutA->createAll(System,FocusWallB->getKey("Guide0"),2);
  BendOutA->addInsertCell(VPipeOutA->getCells("Void"));
  BendOutA->createAll(System,*VPipeOutA,0,*VPipeOutA,0);
  
  if (stopPoint==3) return;    // Up to BW1 Chopper pit
  
  PitB->addInsertCell(voidCell);
  PitB->createAll(System,BendOutA->getKey("Guide0"),2);

  ShieldB->addInsertCell(voidCell);
  ShieldB->setFront(PitA->getKey("Mid"),2);
  ShieldB->addInsertCell(PitA->getCells("Outer"));
  ShieldB->addInsertCell(PitA->getCells("MidLayer"));
  ShieldB->addInsertCell(PitB->getCells("Outer"));
  ShieldB->addInsertCell(PitB->getCells("MidLayer"));
  ShieldB->setBack(PitB->getKey("Mid"),1);
  ShieldB->createAll(System,BendOutA->getKey("Guide0"),2);

  VPipeOutB1->addInsertCell(ShieldB->getCell("Void"));
  VPipeOutB1->addInsertCell(PitA->getCells("MidLayer"));
  VPipeOutB1->setFront(PitA->getKey("Mid"),2);
  VPipeOutB1->createAll(System,*ShieldB,-1);
  BendOutB1->addInsertCell(VPipeOutB1->getCells("Void"));
  BendOutB1->createAll(System,*VPipeOutB1,0,*VPipeOutB1,0);
  
  PitACutFront->addInsertCell(PitA->getCells("MidLayerFront"));
  PitACutFront->setFaces(PitA->getKey("Mid").getSignedFullRule(-1),
			 PitA->getKey("Inner").getSignedFullRule(1));
  PitACutFront->createAll(System,BendOutA->getKey("Guide0"),2);
  PitACutBack->addInsertCell(PitA->getCells("MidLayerBack"));
  PitACutBack->addInsertCell(PitA->getCells("Collet"));  
  PitACutBack->setFaces(PitA->getKey("Inner").getSignedFullRule(2),
			 PitA->getKey("Mid").getSignedFullRule(-2));
  PitACutBack->createAll(System,BendOutB1->getKey("Guide0"),1);
  
  VPipeOutB2->addInsertCell(ShieldB->getCell("Void"));
  VPipeOutB2->setFront(*VPipeOutB1,2,true);
  VPipeOutB2->addInsertCell(PitB->getCells("Outer"));
  VPipeOutB2->addInsertCell(PitB->getCells("MidLayer"));
  VPipeOutB2->setBack(PitB->getKey("Mid"),1);
  VPipeOutB2->createAll(System,BendOutB1->getKey("Guide0"),2);
  BendOutB2->addInsertCell(VPipeOutB2->getCells("Void"));
  BendOutB2->createAll(System,*VPipeOutB2,0,*VPipeOutB2,0);

  if (stopPoint==4) return; // Up to BW2 Chopper Pit
    
  ShieldCs[0]->addInsertCell(voidCell);
  ShieldCs[0]->addInsertCell(PitB->getCells("Outer"));
  ShieldCs[0]->addInsertCell(PitB->getCells("MidLayer"));
  ShieldCs[0]->setFront(PitB->getKey("Mid"),2);
  ShieldCs[0]->createAll(System,BendOutB2->getKey("Guide0"),2);
  VPipeOutCs[0]->addInsertCell(ShieldCs[0]->getCell("Void"));
  VPipeOutCs[0]->addInsertCell(PitB->getCells("MidLayer"));
  VPipeOutCs[0]->setFront(PitB->getKey("Mid"),2);
  VPipeOutCs[0]->setBack(*ShieldCs[0],-2);
  VPipeOutCs[0]->createAll(System,*ShieldCs[0],-1);
  BendOutCs[0]->addInsertCell(VPipeOutCs[0]->getCells("Void"));
  BendOutCs[0]->createAll(System,*VPipeOutCs[0],0,*VPipeOutCs[0],0);

  PitBCutFront->addInsertCell(PitB->getCells("MidLayerFront"));
  PitBCutFront->setFaces(PitB->getKey("Mid").getSignedFullRule(-1),
			 PitB->getKey("Inner").getSignedFullRule(1));
  PitBCutFront->createAll(System,BendOutB2->getKey("Guide0"),2);
  PitBCutBack->addInsertCell(PitB->getCells("MidLayerBack"));
  PitBCutBack->addInsertCell(PitB->getCells("Collet"));  
  PitBCutBack->setFaces(PitB->getKey("Inner").getSignedFullRule(2),
			 PitB->getKey("Mid").getSignedFullRule(-2));
  PitBCutBack->createAll(System,BendOutCs[0]->getKey("Guide0"),1);
 
  const attachSystem::FixedComp* LinkPtr= &BendOutCs[0]->getKey("Guide0");
      
  for(size_t i=1;i<nC;i++)
    {
      ShieldCs[i]->addInsertCell(voidCell);
      ShieldCs[i]->setFront(*ShieldCs[i-1],2);
      if(i==9)
     	{	  
      	  PitC->addInsertCell(voidCell);
      	  PitC->createAll(System,*LinkPtr,2);
      	  ShieldCs[i]->addInsertCell(PitC->getCells("Outer"));
      	  ShieldCs[i]->addInsertCell(PitC->getCells("MidLayer"));
      	}
	
      ShieldCs[i]->createAll(System,*LinkPtr,2);
      
      VPipeOutCs[i]->addInsertCell(ShieldCs[i]->getCell("Void"));
      VPipeOutCs[i]->setFront(*ShieldCs[i],-1,true);
      VPipeOutCs[i]->setBack(*ShieldCs[i],-2);
      VPipeOutCs[i]->createAll(System,*ShieldCs[i],-1);
      
      BendOutCs[i]->addInsertCell(VPipeOutCs[i]->getCells("Void"));
      BendOutCs[i]->createAll(System,*VPipeOutCs[i],0,*VPipeOutCs[i],0);

      LinkPtr= &BendOutCs[i]->getKey("Guide0");
    }

      
  PitCCutFront->addInsertCell(PitC->getCells("MidLayerFront"));
  PitCCutFront->setFaces(PitC->getKey("Mid").getSignedFullRule(-1),
			 PitC->getKey("Inner").getSignedFullRule(1));
  PitCCutFront->createAll(System,*LinkPtr,2);
  
  ShieldD->addInsertCell(voidCell);
  ShieldD->addInsertCell(PitC->getCells("Outer"));
  ShieldD->addInsertCell(PitC->getCells("MidLayer"));
  ShieldD->setFront(PitC->getKey("Mid"),2);
  ShieldD->createAll(System,*LinkPtr,2);
  VPipeOutD->addInsertCell(ShieldD->getCell("Void"));
  VPipeOutD->setFront(*ShieldD,-1,true); 
  VPipeOutD->setBack(*ShieldD,-2);
  VPipeOutD->createAll(System,*ShieldD,-1);
  BendOutD->addInsertCell(VPipeOutD->getCells("Void"));
  BendOutD->createAll(System,*VPipeOutD,0,*VPipeOutD,0);

  PitCCutBack->addInsertCell(PitC->getCells("MidLayerBack"));
  PitCCutBack->addInsertCell(PitC->getCells("Collet"));  
  PitCCutBack->setFaces(PitC->getKey("Inner").getSignedFullRule(2),
			 PitC->getKey("Mid").getSignedFullRule(-2));
  PitCCutBack->createAll(System,BendOutD->getKey("Guide0"),1);
  
  if (stopPoint==5) return; // END of LOS

  /// End  Curve
  
  /// Start straight up to the next chopper pit
  PitE->addInsertCell(voidCell);
  PitE->createAll(System,BendOutD->getKey("Guide0"),2);
  PitECutFront->addInsertCell(PitE->getCells("MidLayerFront"));
  PitECutFront->setFaces(PitE->getKey("Mid").getSignedFullRule(-1),
			 PitE->getKey("Inner").getSignedFullRule(1));
  PitECutFront->createAll(System,PitE->getKey("Inner"),-1);
  PitECutBack->addInsertCell(PitE->getCells("MidLayerBack"));
  PitECutBack->addInsertCell(PitE->getCells("Collet"));  
  PitECutBack->setFaces(PitE->getKey("Inner").getSignedFullRule(2),
			 PitE->getKey("Mid").getSignedFullRule(-2));
  PitECutBack->createAll(System,PitE->getKey("Inner"),2);
  
  ShieldE->addInsertCell(voidCell);
  ShieldE->setFront(*ShieldD,2);
  ShieldE->addInsertCell(PitE->getCells("Outer"));
  ShieldE->addInsertCell(PitE->getCells("MidLayer"));
  ShieldE->setBack(PitE->getKey("Mid"),1);
  ShieldE->createAll(System,BendOutD->getKey("Guide0"),2);
  VPipeOutE->addInsertCell(ShieldE->getCell("Void"));
  VPipeOutE->createAll(System,*ShieldE,-1);
  GuideOutE->addInsertCell(VPipeOutE->getCells("Void"));
  GuideOutE->createAll(System,*VPipeOutE,0,*VPipeOutE,0);

  PitF->addInsertCell(voidCell);
  PitF->createAll(System,GuideOutE->getKey("Guide0"),2);
  PitFCutFront->addInsertCell(PitF->getCells("MidLayerFront"));
  PitFCutFront->setFaces(PitF->getKey("Mid").getSignedFullRule(-1),
			 PitF->getKey("Inner").getSignedFullRule(1));
  PitFCutFront->createAll(System,PitF->getKey("Inner"),-1);
  PitFCutBack->addInsertCell(PitF->getCells("MidLayerBack"));
  PitFCutBack->addInsertCell(PitF->getCells("Collet"));  
  PitFCutBack->setFaces(PitF->getKey("Inner").getSignedFullRule(2),
			 PitF->getKey("Mid").getSignedFullRule(-2));
  PitFCutBack->createAll(System,PitF->getKey("Inner"),2);

  ShieldF->addInsertCell(voidCell);
  ShieldF->addInsertCell(PitE->getCells("Outer"));
  ShieldF->addInsertCell(PitE->getCells("MidLayer"));
  ShieldF->setFront(PitE->getKey("Mid"),2);
  ShieldF->addInsertCell(PitF->getCells("Outer"));
  ShieldF->addInsertCell(PitF->getCells("MidLayer"));
  ShieldF->setBack(PitF->getKey("Mid"),1);
  ShieldF->createAll(System,GuideOutE->getKey("Guide0"),2);

  LinkPtr= &GuideOutE->getKey("Guide0");
  for(size_t i=0;i<nF;i++)
    {
      VPipeOutFs[i]->addInsertCell(ShieldF->getCell("Void"));
      VPipeOutFs[i]->createAll(System,*LinkPtr,2);
      
      GuideOutFs[i]->addInsertCell(VPipeOutFs[i]->getCells("Void"));
      GuideOutFs[i]->createAll(System,*VPipeOutFs[i],0,*VPipeOutFs[i],0);

      LinkPtr= &GuideOutFs[i]->getKey("Guide0");
    }

  PitG->addInsertCell(voidCell);
  PitG->createAll(System,*LinkPtr,2);
  PitGCutFront->addInsertCell(PitG->getCells("MidLayerFront"));
  PitGCutFront->setFaces(PitG->getKey("Mid").getSignedFullRule(-1),
			 PitG->getKey("Inner").getSignedFullRule(1));
  PitGCutFront->createAll(System,PitG->getKey("Inner"),-1);
  PitGCutBack->addInsertCell(PitG->getCells("MidLayerBack"));
  PitGCutBack->addInsertCell(PitG->getCells("Collet"));  
  PitGCutBack->setFaces(PitG->getKey("Inner").getSignedFullRule(2),
			 PitG->getKey("Mid").getSignedFullRule(-2));
  PitGCutBack->createAll(System,PitG->getKey("Inner"),2);

  ShieldG->addInsertCell(voidCell);
  ShieldG->addInsertCell(PitF->getCells("Outer"));
  ShieldG->addInsertCell(PitF->getCells("MidLayer"));
  ShieldG->setFront(PitF->getKey("Mid"),2);
  ShieldG->addInsertCell(PitG->getCells("Outer"));
  ShieldG->addInsertCell(PitG->getCells("MidLayer"));
  ShieldG->setBack(PitG->getKey("Mid"),1);
  ShieldG->createAll(System,*LinkPtr,2);
  VPipeOutG->addInsertCell(ShieldG->getCell("Void"));
  VPipeOutG->createAll(System,*ShieldG,-1);
  GuideOutG->addInsertCell(VPipeOutG->getCells("Void"));
  GuideOutG->createAll(System,*VPipeOutG,0,*VPipeOutG,0);

  ShieldH->addInsertCell(voidCell);
  ShieldH->addInsertCell(PitG->getCells("Outer"));
  ShieldH->addInsertCell(PitG->getCells("MidLayer"));
  ShieldH->setFront(PitG->getKey("Mid"),2);
  ShieldH->createAll(System,GuideOutG->getKey("Guide0"),2);
  VPipeOutH->addInsertCell(ShieldH->getCell("Void"));
  VPipeOutH->createAll(System,*ShieldH,-1);
  GuideOutH->addInsertCell(VPipeOutH->getCells("Void"));
  GuideOutH->createAll(System,*VPipeOutH,0,*VPipeOutH,0);
  
  return;  
}

} // NAMESPACE essSystem

