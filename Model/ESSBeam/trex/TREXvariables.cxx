/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/trex/TREXvariables.cxx
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
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "ShieldGenerator.h"
#include "FocusGenerator.h"
#include "ChopperGenerator.h"
#include "PitGenerator.h"
#include "PipeGenerator.h"
#include "BladeGenerator.h"
#include "essVariables.h"


namespace setVariable
{
void TREXvariables(FuncDataBase& Control)
{
  ELog::RegMethod RegA("TREXvariables[F]","TREXvariables");

  setVariable::ChopperGenerator CGen;
  setVariable::FocusGenerator FGen;
  setVariable::ShieldGenerator SGen;
  setVariable::PitGenerator PGen;
  setVariable::PipeGenerator PipeGen;
  setVariable::BladeGenerator BGen;

  PipeGen.setPipe(10.0,0.5);
  PipeGen.setWindow(-2.0,0.5);
  PipeGen.setFlange(-4.0,1.0);

  // extent of beamline
  Control.addVariable("trexStopPoint",0);
  Control.addVariable("trexAxisXYAngle",0.0);   // rotation
  Control.addVariable("trexAxisZAngle",0.0);   // rotation
  Control.addVariable("trexAxisZStep",0.0);   // +/- height

  FGen.setGuideMat("Aluminium","CastIron");
  FGen.setThickness(0.8,0.5,0.5);
  FGen.clearYOffset();

  FGen.generateTaper(Control,"trexFMono",350.0,9.0,6.38,3.0,4.43);

  //  Gamma blocker 
  PipeGen.generatePipe(Control,"trexPipeBridge",7.0,41.0);
  FGen.generateTaper(Control,"trexFBridge",39.0,6.38,6.0,4.43,4.59);

  //   Vac pipe +  horizontal bender (Inside Bunker)
  PipeGen.generatePipe(Control,"trexPipeInA",1.5,447.5);
  Control.addVariable("trexPipeInAXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInA",445.5,6.0,6.0,4.59,5.75,
                      1900000.0,0.0);

  Control.addVariable("trexCollimAYStep",27.0);
  Control.addVariable("trexCollimALength",50.0);
  Control.addVariable("trexCollimAMat","Copper"); 
  
  //FGen.setYOffset(2.0);
  PipeGen.generatePipe(Control,"trexPipeInB",1.0,400.0);
  Control.addVariable("trexPipeInBXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInB",398.0,6.0,6.0,5.75,6.51,
                      1900000.0,0.0);

  PipeGen.generatePipe(Control,"trexPipeInC",1.0,400.0);
  Control.addVariable("trexPipeInCXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInC",398.0,6.0,6.0,6.51,7.11,
		      1900000.0,0.0);

  Control.addVariable("trexCollimBYStep",58.0);
  Control.addVariable("trexCollimBLength",50.0);
  Control.addVariable("trexCollimBMat","Copper");

  PipeGen.generatePipe(Control,"trexPipeInD",1.0,366.0);
  Control.addVariable("trexPipeInDXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInD",364.0,6.0,6.0,7.11,7.57,
		      1900000.0,0.0);

  // FGen.clearYOffset();
  PipeGen.generatePipe(Control,"trexPipeInE",1.5,200.0);
  FGen.generateBender(Control,"trexBInE",198.0,6.0,6.0,7.57,7.72,
		      1900000.0,0.0);

  Control.addVariable("trexCollimCYStep",173.0);
  Control.addVariable("trexCollimCLength",50.0);
  Control.addVariable("trexCollimCMat","Copper");

  // BEAM INSERT
  Control.addVariable("trexBInsertANBox",1);
  Control.addVariable("trexBInsertAHeight",27.0);
  Control.addVariable("trexBInsertAWidth",25.7);
  Control.addVariable("trexBInsertALength",204.4);
  Control.addVariable("trexBInsertAMat","Void");
  Control.addVariable("trexBInsertANWall",1);
  Control.addVariable("trexBInsertAWallThick",0.35);
  Control.addVariable("trexBInsertAWallMat","Stainless304");

  FGen.setYOffset(0.0);
  FGen.generateBender(Control,"trexFWallA",204.4,6.0,6.0,7.72,7.89,
		      1900000.0,0.0);
  Control.setVariable("trexFWallANShapeLayers",5); 
  Control.addVariable("trexFWallALayerThick1",0.8);
  Control.addVariable("trexFWallALayerThick2",0.2);
  Control.addVariable("trexFWallALayerThick3",5.0);
  Control.addVariable("trexFWallALayerThick4",3.5); 
  Control.addVariable("trexFWallALayerMat1","Copper");
  Control.addVariable("trexFWallALayerMat2","Void");
  Control.addVariable("trexFWallALayerMat3","Steel71");
  Control.addVariable("trexFWallALayerMat4","Stainless304");

  Control.addVariable("trexBInsertBNBox",1);
  Control.addVariable("trexBInsertBHeight",44.0);
  Control.addVariable("trexBInsertBWidth",42.4);
  Control.addVariable("trexBInsertBLength",195.6);
  Control.addVariable("trexBInsertBMat","Void");
  Control.addVariable("trexBInsertBNWall",1);
  Control.addVariable("trexBInsertBWallThick",0.35);
  Control.addVariable("trexBInsertBWallMat","Stainless304");
    
  FGen.generateBender(Control,"trexFWallB",195.6,6.0,6.0,7.89,8.04,
		      1900000.0,0.0);
  Control.setVariable("trexFWallBNShapeLayers",5); 
  Control.addVariable("trexFWallBLayerThick1",3.8);
  Control.addVariable("trexFWallBLayerThick2",0.2);
  Control.addVariable("trexFWallBLayerThick3",10.35);
  Control.addVariable("trexFWallBLayerThick4",3.5); 
  Control.addVariable("trexFWallBLayerMat1","Copper");
  Control.addVariable("trexFWallBLayerMat2","Void");
  Control.addVariable("trexFWallBLayerMat3","Steel71");
  Control.addVariable("trexFWallBLayerMat4","Stainless304");

  //Out of bunker
  PGen.setFeLayer(6.0);
  PGen.setConcLayer(10.0);
  PGen.generatePit(Control,"trexPitA",369.0,25.0,160.0,100.0,66.0);
  Control.addVariable("trexPitACutFrontShape","Square");
  Control.addVariable("trexPitACutFrontRadius",5.0);
  Control.addVariable("trexPitACutBackShape","Square");
  Control.addVariable("trexPitACutBackRadius",5.0);

  CGen.setMainRadius(38.122);
  CGen.setFrame(86.5,86.5);
  CGen.generateChopper(Control,"trexChopperA",0.0,12.0,6.55);

  BGen.setMaterials("Copper","B4C");
  BGen.setThick({0.2});
  BGen.addPhase({95},{60});
  BGen.generateBlades(Control,"trexADisk",0.0,25.0,35.0);


  const double s_matThickness = 60.0;
  const double s_voidDimension = 18.0;
  const double s_HW = s_matThickness + s_voidDimension;
  SGen.addWall(1,s_voidDimension,"CastIron");
  SGen.addRoof(1,s_voidDimension,"CastIron");
  SGen.addFloor(1,s_voidDimension,"Concrete");
  SGen.addFloorMat(5,"Concrete");
  SGen.addRoofMat(5,"Concrete");
  SGen.addWallMat(5,"Concrete");
  SGen.setRFLayers(3,8);

  SGen.generateShield(Control,"trexShieldA",405.5,s_HW,s_HW,s_HW,2,8);
  PipeGen.generatePipe(Control,"trexPipeOutA",0.5,368.0);
  Control.addVariable("trexPipeOutAXYAngle",-0.1);
 
  FGen.setGuideMat("Borosilicate","CastIron");
  FGen.setThickness(0.5,0.5,0.5);
  FGen.clearYOffset();
  FGen.generateBender(Control,"trexBOutA",366.0,6.0,6.0,8.07,8.27,
		      1900000.0,0.0);

  PGen.generatePit(Control,"trexPitB",801.25,25.0,160.0,100.0,66.0);
  Control.addVariable("trexPitBCutFrontShape","Square");
  Control.addVariable("trexPitBCutFrontRadius",5.0);
  Control.addVariable("trexPitBCutBackShape","Square");
  Control.addVariable("trexPitBCutBackRadius",5.0);
  CGen.generateChopper(Control,"trexChopperB",0.0,12.0,6.55);
  BGen.generateBlades(Control,"trexBDisk",0.0,25.0,35.0);

  SGen.generateShield(Control,"trexShieldB",762.25,s_HW,s_HW,s_HW,4,8);
  Control.addVariable("trexShieldBXYAngle",-0.1);
  Control.addVariable("trexShieldBYStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutB1",0.5,380.75);
  Control.addVariable("trexPipeOutB1XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutB1",378.75,6.0,6.0,8.27,8.42,
 		      1900000.0,0.0);
  PipeGen.generatePipe(Control,"trexPipeOutB2",1.0,380.75);
  Control.addVariable("trexPipeOutB2XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutB2",378.75,6.0,6.0,8.42,8.49,
		      1900000.0,0.0);

  /// After BW2 Chopper pit
  PGen.generatePit(Control,"trexPitC",4961.0,35.0,160.0,100.0,66.0);
  Control.addVariable("trexPitCXStep",85.25);
  Control.addVariable("trexPitCXYAngle",-2.0);
  Control.addVariable("trexPitCCutFrontShape","Square");
  Control.addVariable("trexPitCCutFrontRadius",5.0);
  Control.addVariable("trexPitCCutBackShape","Square");
  Control.addVariable("trexPitCCutBackRadius",5.0);

  CGen.generateChopper(Control,"trexChopperC",0.0,20.0,10.0);
  setVariable::BladeGenerator BGen1;
  BGen1.setMaterials("Copper","B4C");
  BGen1.setThick({7.0});
  BGen1.addPhase({95},{60});
  BGen1.generateBlades(Control,"trexCDisk",3.5,20.0,30.0);
  
  /// array section
  FGen.clearYOffset();
 
  SGen.generateShield(Control,"trexShieldC0",497.0,s_HW,s_HW,s_HW,3,8);
  Control.addVariable("trexShieldC0XYAngle",-0.1);
  Control.addVariable("trexShieldC0YStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutC0",0.5,496.25);
  Control.addVariable("trexPipeOutC0XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutC0",494.25,6.0,6.0,8.50,8.50,
		      1900000.0,0.0);
  
  for(size_t i=1;i<9;i++)
    {
      const std::string strNum(StrFunc::makeString(i));
      SGen.generateShield(Control,"trexShieldC"+strNum,497.25,s_HW,s_HW,
            		  s_HW,3,8);
      Control.addVariable("trexShieldC"+strNum+"XYAngle",-0.1); 
      PipeGen.generatePipe(Control,"trexPipeOutC"+strNum,0.0,496.25);
      Control.addVariable("trexPipeOutC"+strNum+"XYAngle",-0.1);
      FGen.generateBender(Control,"trexBOutC"+strNum,494.25,6.0,6.0,8.50,
			  8.50,1900000.0,0.0);
    }
  
  SGen.generateShield(Control,"trexShieldC9",496.0,s_HW,s_HW,s_HW,3,8);
  Control.addVariable("trexShieldC9XYAngle",-0.1);
  PipeGen.generatePipe(Control,"trexPipeOutC9",0.0,495.25);
  Control.addVariable("trexPipeOutC9XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutC9",493.25,6.0,6.0,8.50,8.50,
		      1900000.0,0.0);

  SGen.generateShield(Control,"trexShieldD",576.5,s_HW,s_HW,s_HW,4,8);
  Control.addVariable("trexShieldDXYAngle",-0.1);
  Control.addVariable("trexShieldDYStep",48.5);
  PipeGen.generatePipe(Control,"trexPipeOutD",0.0,577.0);
  FGen.generateBender(Control,"trexBOutD",575.0,6.0,6.0,8.50,8.50,
		      1900000.0,0.0);

  // End LOS
  
  PGen.generatePit(Control,"trexPitE",1946.25,45.0,160.0,100.0,66.0);
  Control.addVariable("trexPitECutFrontShape","Square");
  Control.addVariable("trexPitECutFrontRadius",5.0);
  Control.addVariable("trexPitECutBackShape","Square");
  Control.addVariable("trexPitECutBackRadius",5.0);
  CGen.generateChopper(Control,"trexChopperE",0.0,35.0,25.0);
  BGen.generateBlades(Control,"trexE1Disk",-10.0,20.0,30.0);
  BGen.generateBlades(Control,"trexE2Disk",10.0,20.0,30.0);

  SGen.generateShield(Control,"trexShieldE",1369.5,s_HW,s_HW,s_HW,10,8);
  PipeGen.generatePipe(Control,"trexPipeOutE",0.0,1369.0);
  FGen.generateRectangle(Control,"trexGOutE",1367.0,6.0,8.50);

  SGen.generateShield(Control,"trexShieldF",5014.0,s_HW,s_HW,s_HW,10,8);
  Control.addVariable("trexShieldFYStep",58.5);
  double FVS[8]={8.50,8.50,8.50,8.48,8.29,7.92,7.29,6.28};
  double FVE[8]={8.50,8.50,8.48,8.29,7.92,7.29,6.28,4.76};
  double FHS[8]={6.0,6.28,6.78,7.01,6.98,6.74,6.19,5.28};
  double FHE[8]={6.28,6.78,7.01,6.98,6.74,6.19,5.28,3.73};
  for(size_t i=0;i<7;i++)
    {
      const std::string strNum(StrFunc::makeString(i));
      const double yOffsetF = (i==0) ? 58.5 : 1.0;
      PipeGen.generatePipe(Control,"trexPipeOutF"+strNum,yOffsetF,626.72);
      FGen.generateTaper(Control,"trexGOutF"+strNum,624.72,FHS[i],FHE[i],
			 FVS[i],FVE[i]);
    }
  
  PipeGen.generatePipe(Control,"trexPipeOutF7",1.0,627.0);
  FGen.generateTaper(Control,"trexGOutF7",625.0,FHS[7],FHE[7],
			 FVS[7],FVE[7]);

  PipeGen.generatePipe(Control,"trexPipeOutG",1.5,313.75);
  FGen.generateTaper(Control,"trexGOutG",311.75,3.73,2.94,4.76,4.06);
  CGen.generateChopper(Control,"trexChopperG",6.0,12.0,6.55);
  BGen.generateBlades(Control,"trexGDisk",0.0,25.0,35.0);

  PipeGen.generatePipe(Control,"trexPipeOutH",0.0,138.0);
  FGen.generateTaper(Control,"trexGOutH",136.0,2.77,2.22,3.91,3.49);
  CGen.generateChopper(Control,"trexChopperH",8.0,16.0,8.0);
  BGen.generateBlades(Control,"trexH1Disk",-1.0,25.0,35.0);
  BGen.generateBlades(Control,"trexH2Disk",1.0,25.0,35.0);

  FGen.setYOffset(0.0);
  FGen.generateTaper(Control,"trexGOutI",91.0,2.21,1.5,3.48,3.0);

  // TREXHUT:
  
  Control.addVariable("trexCaveYStep",5085.0);
  Control.addVariable("trexCaveXStep",0.0);
  Control.addVariable("trexCaveVoidFront",60.0);
  Control.addVariable("trexCaveVoidHeight",600.0);
  Control.addVariable("trexCaveVoidDepth",150.0);
  Control.addVariable("trexCaveVoidWidth",1000.0);
  Control.addVariable("trexCaveVoidLength",1000.0);

  Control.addVariable("trexCaveL1Front",0.5);
  Control.addVariable("trexCaveL1LeftWall",0.5);
  Control.addVariable("trexCaveL1RightWall",0.5);
  Control.addVariable("trexCaveL1Roof",0.5);
  Control.addVariable("trexCaveL1Floor",0.5);
  Control.addVariable("trexCaveL1Back",0.5);

  Control.addVariable("trexCaveL2Front",60.5);
  Control.addVariable("trexCaveL2LeftWall",60.5);
  Control.addVariable("trexCaveL2RightWall",60.5);
  Control.addVariable("trexCaveL2Roof",60.5);
  Control.addVariable("trexCaveL2Floor",60.5);
  Control.addVariable("trexCaveL2Back",60.5);

  Control.addVariable("trexCaveL3Front",70.5);
  Control.addVariable("trexCaveL3LeftWall",70.5);
  Control.addVariable("trexCaveL3RightWall",70.5);
  Control.addVariable("trexCaveL3Roof",70.5);
  Control.addVariable("trexCaveL3Floor",70.5);
  Control.addVariable("trexCaveL3Back",70.5);

  Control.addVariable("trexCaveL3Mat","Concrete");
  Control.addVariable("trexCaveL2Mat","Concrete");
  Control.addVariable("trexCaveL1Mat","Void");

  Control.addVariable("trexCaveFrontCutShape","Circle");
  Control.addVariable("trexCaveFrontCutRadius",18.0);

  return;
}
  
}//NAMESPACE setVariable
