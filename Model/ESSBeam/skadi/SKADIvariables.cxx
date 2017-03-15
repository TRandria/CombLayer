/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/skadi/SKADIvariables.cxx
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
void SKADIvariables(FuncDataBase& Control)
{
  ELog::RegMethod RegA("SKADIvariables[F]","SKADIvariables");

  setVariable::ChopperGenerator CGen;
  setVariable::FocusGenerator FGen;
  setVariable::ShieldGenerator SGen;
  setVariable::ShieldGenerator SGen1;
  setVariable::PitGenerator PGen;
  setVariable::PipeGenerator PipeGen;
  setVariable::BladeGenerator BGen;

  PipeGen.setPipe(7.5,0.5);
  PipeGen.setWindow(-2.0,0.3);
  PipeGen.setFlange(-4.0,1.0);

  // extent of beamline
  Control.addVariable("skadiStopPoint",0);
  Control.addVariable("skadiAxisXYAngle",0.0);   // rotation
  Control.addVariable("skadiAxisZAngle",0.0);   // rotation
  //  Control.addVariable("skadiAxisZStep",0.0);   // +/- height

  FGen.setGuideMat("Copper");
  FGen.setThickness(0.8,0.5);
  
  const double w=3.0;
  // Vertical bender
  FGen.setYOffset(0.0);
  FGen.generateBender(Control,"skadiBA",350.0,w,w,w,w,8400.0,90.0);
  
  //  Gamma shield , and S
  PipeGen.generatePipe(Control,"skadiPipeB",7.0,42.0);
  FGen.clearYOffset();
  FGen.generateBender(Control,"skadiBB",40.0,w,w,w,w,8400.0,90.0);

  PipeGen.generatePipe(Control,"skadiPipeInA",2.0,48);
  FGen.generateBender(Control,"skadiBInA",46,w,w,w,w,8400.0,90.0);

  // Second part of the S
  PipeGen.generatePipe(Control,"skadiPipeInB",2.0,449.0);
  Control.addVariable("skadiPipeInBZAngle",1.5);
  FGen.setYOffset(3.0);
  FGen.generateBender(Control,"skadiBInB",447.0,w,w,w,w,8400.0,270.0);
  
  // Heavy Shutter !!
  PipeGen.generatePipe(Control,"skadiPipeInC",2.0,20.0);
  FGen.clearYOffset();
  FGen.generateRectangle(Control,"skadiGInC",18.0,w,w);

  //Beam Insert
  Control.addVariable("skadiBInsertNBox",1);
  Control.addVariable("skadiBInsertYStep",1.0);
  Control.addVariable("skadiBInsertLength",200.0);
  Control.addVariable("skadiBInsertHeight",16.0);
  Control.addVariable("skadiBInsertWidth",16.0);
  Control.addVariable("skadiBInsertMat","Void");
  Control.addVariable("skadiBInsertNWall",1);
  Control.addVariable("skadiBInsertWallThick",1.0);
  Control.addVariable("skadiBInsertWallMat","Steel71");

  FGen.setYOffset(0.0);
  FGen.generateRectangle(Control,"skadiFWall",200.0,w,w);

  Control.addVariable("skadiCInsertNBox",2);
  Control.addVariable("skadiCInsertHeight",61.0);
  Control.addVariable("skadiCInsertWidth",61.0);
  Control.addVariable("skadiCInsertZStep",-15.25);
  Control.addVariable("skadiCInsertHeight1",81.0);
  Control.addVariable("skadiCInsertWidth1",81.0);
  Control.addVariable("skadiCInsertLength0",124.0);
  Control.addVariable("skadiCInsertLength1",56.0);
  //  Control.addVariable("skadiCInsertZStep1",-35.0);
  Control.addVariable("skadiCInsertMat0","Concrete");
  Control.addVariable("skadiCInsertMat1","Concrete");
  Control.addVariable("skadiCInsertNWall",2);
  Control.addVariable("skadiCInsertWallThick0",24.5);
  Control.addVariable("skadiCInsertWallMat0","Steel71");
  Control.addVariable("skadiCInsertWallThick1",20.0);
  Control.addVariable("skadiCInsertWallMat1","Concrete");

  FGen.generateRectangle(Control,"skadiFShutter",180.0,w,w);
  Control.addVariable("skadiFShutterZStep",15.25);

  const double s_matThickness = 70.0;
  const double s_voidDimension = 12.3;
  const double s_HW = s_matThickness + s_voidDimension;
  SGen.addWall(1,s_voidDimension,"Concrete");
  SGen.addRoof(1,s_voidDimension,"Concrete");
  SGen.addFloor(1,1.5*s_voidDimension,"Concrete");
  SGen.addFloorMat(7,"Steel71");
  SGen.addRoofMat(7,"Steel71");
  SGen.addWallMat(7,"Steel71");
  SGen.setRFLayers(3,8);

  SGen1.addWall(1,s_voidDimension-0.5,"B4C");
  SGen1.addRoof(1,s_voidDimension-0.5,"B4C");
  SGen1.addFloor(1,s_voidDimension-0.5,"B4C");

  SGen.generateShield(Control,"skadiShieldA",32.0,s_HW,s_HW,s_HW,1,8);
  Control.addVariable("skadiShieldAYStep",0.25);
  SGen1.generateShield(Control,"skadiShieldA1",32.0,s_voidDimension,
		       s_voidDimension,s_voidDimension,1,2);
  FGen.clearYOffset();
  PipeGen.generatePipe(Control,"skadiPipeOutA",0.5,31.0);
  FGen.generateRectangle(Control,"skadiGOutA",29.0,w,w);

  PGen.setFeLayer(6.0);
  PGen.setConcLayer(10.0);
  PGen.generatePit(Control,"skadiPitA",32.0,25.0,160.0,100.0,66.0);
  Control.addVariable("skadiPitACutFrontShape","Square");
  Control.addVariable("skadiPitACutFrontRadius",5.0);
  Control.addVariable("skadiPitACutBackShape","Square");
  Control.addVariable("skadiPitACutBackRadius",5.0);

  CGen.setMainRadius(38.122);
  CGen.setFrame(86.5,86.5);
  CGen.generateChopper(Control,"skadiChopperA",0.0,12.0,6.55);

  BGen.setMaterials("Copper","B4C");
  BGen.setThick({0.2});
  BGen.addPhase({95},{60});
  BGen.generateBlades(Control,"skadiADisk",0.0,25.0,35.0);

  PGen.generatePit(Control,"skadiPitB",688.0,25.0,160.0,100.0,66.0);
  Control.addVariable("skadiPitBCutFrontShape","Square");
  Control.addVariable("skadiPitBCutFrontRadius",5.0);
  Control.addVariable("skadiPitBCutBackShape","Square");
  Control.addVariable("skadiPitBCutBackRadius",5.0);
  CGen.generateChopper(Control,"skadiChopperB",0.0,12.0,6.55);
  BGen.generateBlades(Control,"skadiBDisk",0.0,25.0,35.0);
  SGen.generateShield(Control,"skadiShieldB",688.0,s_HW,s_HW,s_HW,4,8);
  SGen1.generateShield(Control,"skadiShieldB1",688.0,s_voidDimension,
		       s_voidDimension,s_voidDimension,4,2);
  PipeGen.generatePipe(Control,"skadiPipeOutB",0.5,697.0);
  FGen.generateRectangle(Control,"skadiGOutB",695.0,w,w);

  PGen.generatePit(Control,"skadiPitC",298.0,55.0,160.0,100.0,66.0);
  Control.addVariable("skadiPitCCutFrontShape","Square");
  Control.addVariable("skadiPitCCutFrontRadius",5.0);
  Control.addVariable("skadiPitCCutBackShape","Square");
  Control.addVariable("skadiPitCCutBackRadius",5.0);
  SGen.generateShield(Control,"skadiShieldC",297.0,s_HW,s_HW,s_HW,2,8);
  SGen1.generateShield(Control,"skadiShieldC1",297.0,s_voidDimension,
		       s_voidDimension,s_voidDimension,2,2);
  PipeGen.generatePipe(Control,"skadiPipeOutC",0.5,307.0);
  FGen.generateRectangle(Control,"skadiGOutC",305.0,w,w);

  CGen.generateChopper(Control,"skadiChopperC1",-15.0,12.0,6.55);
  BGen.generateBlades(Control,"skadiC1Disk",0.0,25.0,35.0);
  CGen.generateChopper(Control,"skadiChopperC2",15.0,12.0,6.55);
  BGen.generateBlades(Control,"skadiC2Disk",0.0,25.0,35.0);

  SGen.generateShield(Control,"skadiShieldD",761.0,s_HW,s_HW,s_HW,5,8);
  SGen1.generateShield(Control,"skadiShieldD1",761.0,s_voidDimension,
		       s_voidDimension,s_voidDimension,5,2);
  PipeGen.generatePipe(Control,"skadiPipeOutD",0.5,692.0);
  FGen.generateRectangle(Control,"skadiGOutD",690.0,w,w);

  // SKADIHUT:
  
  Control.addVariable("skadiCaveYStep",357.5);
  Control.addVariable("skadiCaveXStep",0.0);
  Control.addVariable("skadiCaveVoidFront",60.0);
  Control.addVariable("skadiCaveVoidHeight",240.3);
  Control.addVariable("skadiCaveVoidDepth",189.7);
  Control.addVariable("skadiCaveVoidWidth",250.0);
  Control.addVariable("skadiCaveVoidLength",250.0);

  Control.addVariable("skadiCaveL1Front",0.5);
  Control.addVariable("skadiCaveL1LeftWall",0.5);
  Control.addVariable("skadiCaveL1RightWall",0.5);
  Control.addVariable("skadiCaveL1Roof",0.5);
  Control.addVariable("skadiCaveL1Floor",0.5);
  Control.addVariable("skadiCaveL1Back",0.5);

  Control.addVariable("skadiCaveL2Front",60.5);
  Control.addVariable("skadiCaveL2LeftWall",60.5);
  Control.addVariable("skadiCaveL2RightWall",60.5);
  Control.addVariable("skadiCaveL2Roof",60.5);
  Control.addVariable("skadiCaveL2Floor",60.5);
  Control.addVariable("skadiCaveL2Back",60.5);

  Control.addVariable("skadiCaveL3Front",70.5);
  Control.addVariable("skadiCaveL3LeftWall",70.5);
  Control.addVariable("skadiCaveL3RightWall",70.5);
  Control.addVariable("skadiCaveL3Roof",70.5);
  Control.addVariable("skadiCaveL3Floor",70.5);
  Control.addVariable("skadiCaveL3Back",70.5);

  Control.addVariable("skadiCaveL3Mat","Stainless304");
  Control.addVariable("skadiCaveL2Mat","Concrete");
  Control.addVariable("skadiCaveL1Mat","B4C");
  
  Control.addVariable("skadiCavepipeL2Mat","Aluminium");
  Control.addVariable("skadiCavepipeL1Mat","B4C");
  
  Control.addVariable("skadiCavepipeL1Thick",1.0);
  Control.addVariable("skadiCavepipeL2Thick",1.0);
  Control.addVariable("skadiCavepipeRadius",100.0);
  Control.addVariable("skadiCavepipeLength",2195.0); //lenght+voidLength

  FGen.setYOffset(0.0);
  FGen.generateRectangle(Control,"skadiGOutE",480.0,w,w);

  Control.addVariable("skadiCaveFrontCutShape","Square");
  Control.addVariable("skadiCaveFrontCutRadius",3.1);

  setVariable::ShieldGenerator SGen2;
  SGen2.addWall(1,110.0,"Concrete");
  SGen2.addRoof(1,110.0,"Concrete");
  SGen2.addFloor(1,120.0,"Concrete");
  SGen2.generateShield(Control,"skadiShieldF",2201.4,
		      170.0,170.0,190.0,5,8);
  Control.addVariable("skadiShieldFYStep",678.0);
  return;
}
  
}//NAMESPACE setVariable
