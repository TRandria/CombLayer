/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   pipeBuild/pipeVariables.cxx
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
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "variableSetup.h"

#include "ChopperGenerator.h"
#include "BladeGenerator.h"
#include "PipeGenerator.h"
#include "FocusGenerator.h"
#include "PitGenerator.h"
#include "ShieldGenerator.h"

namespace setVariable
{

  
void
PipeVariables(FuncDataBase& Control)
  /*!
    Create all the beamline variabes
    \param Control :: DataBase
  */
{
  ELog::RegMethod RegA("pipeVariables[F]","PipeVariables");
  
  Control.addVariable("ATubeLength",350.0);
  Control.addVariable("ATubeWidth",100.0);
  Control.addVariable("ATubeHeight",100.0);
  Control.addVariable("ATubeInnerWidth",10.0);
  Control.addVariable("ATubeInnerHeight",10.0);
  Control.addVariable("ATubeWallMat","Stainless304");

  Control.addVariable("ATubeNWallLayers",3);
  Control.addVariable("ATubeWLayerThick0",3.0);
  Control.addVariable("ATubeWLayerThick1",4.0);
  Control.addVariable("ATubeWLayerThick2",5.0);
  Control.addVariable("ATubeWLayerThick3",5.0);

  Control.addVariable("BTubeLength",350.0);
  Control.addVariable("BTubeWidth",100.0);
  Control.addVariable("BTubeHeight",100.0);
  Control.addVariable("BTubeInnerWidth",10.0);
  Control.addVariable("BTubeInnerHeight",10.0);
  Control.addVariable("BTubeWallMat","H2O");

  Control.addVariable("BTubeNWallLayers",3);
  Control.addVariable("BTubeWLayerThick0",3.0);
  Control.addVariable("BTubeWLayerThick1",4.0);
  Control.addVariable("BTubeWLayerThick2",5.0);
  Control.addVariable("BTubeWLayerThick3",5.0);
  

  Control.addVariable("CTubeLength",350.0);
  Control.addVariable("CTubeWidth",100.0);
  Control.addVariable("CTubeHeight",100.0);
  Control.addVariable("CTubeInnerWidth",10.0);
  Control.addVariable("CTubeInnerHeight",10.0);
  Control.addVariable("CTubeWallMat","Stainless304");

  Control.addVariable("CTubeNWallLayers",6);
  Control.addVariable("CTubeWLayerThick0",3.0);
  Control.addVariable("CTubeWLayerThick1",4.0);
  Control.addVariable("CTubeWLayerThick2",5.0);
  Control.addVariable("CTubeWLayerThick3",5.0);
  Control.addVariable("CTubeWLayerThick4",5.0);
  Control.addVariable("CTubeWLayerThick5",5.0);
  
  Control.addVariable("pointSourceXStep",1.0);
  Control.addVariable("diskSourceXStep",0.0);
  Control.addVariable("diskSourceYStep",1.0);
  Control.addVariable("diskSourceZStep",0.0);
  Control.addVariable("diskSourceRadius",0.2);
  Control.addVariable("diskSourceParticleType",1);  // neutron
  Control.addVariable("diskSourceASpread",90.0);
  Control.addVariable("diskSourceEnergy",3.0);
  Control.addVariable("diskSourceEProb",1.0);


  setVariable::ChopperGenerator CGen;
  setVariable::BladeGenerator BGen;
  setVariable::PipeGenerator PGen;
  setVariable::FocusGenerator FGen;
  setVariable::PitGenerator pitGen;

  pitGen.setFeLayer(6.0);
  pitGen.setConcLayer(10.0);
  //  pitGen.generatePit(Control,"PitA",220.0,25.0,220.0,210.0,40.0);
  pitGen.generatePit(Control,"PitA",0.0,25.0,160.0,210.0,40.0);
  
  CGen.setMainRadius(38.122);
  CGen.setFrame(86.5,86.5);
  CGen.generateChopper(Control,"ChopperA",6.0,12.0,6.55);

  BGen.setMaterials("Copper","B4C");
  BGen.setThick({0.2});
  BGen.addPhase({95},{60});
  BGen.generateBlades(Control,"BandADisk",0.0,25.0,35.0);

  PGen.setPipe(8.0,0.5);
  PGen.setWindow(-2.0,0.5);
  PGen.setFlange(-4.0,1.0);
  PGen.generatePipe(Control,"PipeA",1.0,100.0);

  FGen.setGuideMat("Copper","Borosilicate");
  FGen.setThickness(0.8,0.5,0.5);
  FGen.generateBender(Control,"GuideA",98.0,6.0,6.0,6.0,6.0,1550.0,90.0);

  PGen.generatePipe(Control,"PipeB",3.0,100.0);
  FGen.generateBender(Control,"GuideB",98.0,6.0,6.0,6.0,6.0,1550.0,270.0);
  

  Control.addVariable("CutFrontAShape","Square");
  Control.addVariable("CutFrontARadius",5.0);
  
  Control.addVariable("CutBackAShape","Square");
  Control.addVariable("CutBackARadius",15.0);

  setVariable::ShieldGenerator SGen;
  /*
  SGen.addWall(1,30.0,"Concrete");
  SGen.addRoof(1,20.0,"Concrete");
  SGen.addFloor(1,0.0,"Concrete");
  SGen.addWallMat(7,"CastIron");
  SGen.addRoofMat(7,"CastIron");
  
  SGen.generateShield(Control,"ShieldA",100.0,100.0,90.0,20.0,4,8);
  */
  setVariable::ShieldGenerator SGen1;
  SGen1.addWall(1,29.5,"B4C");
  SGen1.addRoof(1,19.5,"B4C");
  SGen1.generateShield(Control,"ShieldB",100.0,30.0,20.0,0.0,4,2);


  // HUT:
  
  Control.addVariable("CaveYStep",0.0);
  Control.addVariable("CaveXStep",0.0);
  Control.addVariable("CaveVoidFront",60.0);
  Control.addVariable("CaveVoidHeight",300.0);
  Control.addVariable("CaveVoidDepth",183.0);
  Control.addVariable("CaveVoidWidth",500.0);
  Control.addVariable("CaveVoidLength",600.0);

  Control.addVariable("CaveL1Front",25.0);
  Control.addVariable("CaveL1LeftWall",15.0);
  Control.addVariable("CaveL1RightWall",15.0);
  Control.addVariable("CaveL1Roof",15.0);
  Control.addVariable("CaveL1Floor",15.0);
  Control.addVariable("CaveL1Back",15.0);

  Control.addVariable("CaveL2Front",35.0);
  Control.addVariable("CaveL2LeftWall",35.0);
  Control.addVariable("CaveL2RightWall",35.0);
  Control.addVariable("CaveL2Roof",35.0);
  Control.addVariable("CaveL2Floor",50.0);
  Control.addVariable("CaveL2Back",35.0);

  Control.addVariable("CaveL3Front",50.0);
  Control.addVariable("CaveL3LeftWall",55.0);
  Control.addVariable("CaveL3RightWall",55.0);
  Control.addVariable("CaveL3Roof",55.0);
  Control.addVariable("CaveL3Floor",60.0);
  Control.addVariable("CaveL3Back",55.0);


  Control.addVariable("CaveL1Mat","Stainless304");
  Control.addVariable("CaveL2Mat","Concrete");
  Control.addVariable("CaveL3Mat","B4C");

  Control.addVariable("CaveL2PipeMat","CastIron");
  Control.addVariable("CaveL1PipeMat","B4C");
  
  Control.addVariable("CaveL1PipeThick",7.5);
  Control.addVariable("CaveL2PipeThick",7.5);
  Control.addVariable("CaveRadius",100.0);
  Control.addVariable("CaveLength",2000.0);


  Control.addVariable("AppAInnerWidth",4.0);
  Control.addVariable("AppAInnerHeight",4.0);
  Control.addVariable("AppAWidth",12.0);
  Control.addVariable("AppAHeight",12.0);
  Control.addVariable("AppADepth",5.0);
  Control.addVariable("AppAYStep",7.0);
  Control.addVariable("AppADefMat","Tungsten");

  SGen.addWall(1,30.0,"Tungsten");
  SGen.addRoof(1,30.0,"Tungsten");
  SGen.addFloor(1,30.0,"Tungsten");
  
  SGen.generateShield(Control,"ShieldA",10.0,31.0,31.0,31.0,1,2);

  Control.addVariable("CollimALength",10.0);
  Control.addVariable("CollimAMat","Copper");

  return;
}

}  // NAMESPACE setVariable
 
