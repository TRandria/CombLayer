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
  setVariable::PitGenerator PGen;
  setVariable::PipeGenerator PipeGen;
  setVariable::BladeGenerator BGen;

  PipeGen.setPipe(12.0,0.5);
  PipeGen.setWindow(-2.0,0.3);
  PipeGen.setFlange(-4.0,1.0);

  SGen.addWall(1,30.0,"CastIron");
  SGen.addRoof(1,30.0,"CastIron");
  SGen.addFloor(1,50.0,"CastIron");
  SGen.addFloorMat(5,"Concrete");
  SGen.addRoofMat(5,"Concrete");
  SGen.addWallMat(5,"Concrete");

  // extent of beamline
  Control.addVariable("skadiStopPoint",0);
  Control.addVariable("skadiAxisXYAngle",0.0);   // rotation
  Control.addVariable("skadiAxisZAngle",0.0);   // rotation
  //  Control.addVariable("skadiAxisZStep",0.0);   // +/- height

  FGen.setGuideMat("Aluminium");
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
  PipeGen.generatePipe(Control,"skadiPipeInC",2.0,50.0);
  FGen.clearYOffset();
  FGen.generateRectangle(Control,"skadiGInC",48.0,w,w);

  //Beam Insert
  Control.addVariable("skadiBInsertNBox",3);
  Control.addVariable("skadiBInsertYStep",1.0);
  Control.addVariable("skadiBInsertHeight",30.0);
  Control.addVariable("skadiBInsertWidth",48.0);
  Control.addVariable("skadiBInsertHeight1",152.0);
  Control.addVariable("skadiBInsertWidth1",152.0);
  Control.addVariable("skadiBInsertHeight2",218.0);
  Control.addVariable("skadiBInsertWidth2",202.0);
  Control.addVariable("skadiBInsertLength0",100.0);
  Control.addVariable("skadiBInsertLength1",180.0);
  Control.addVariable("skadiBInsertLength2",70.0);
  Control.addVariable("skadiBInsertMat0","Void");
  Control.addVariable("skadiBInsertMat1","Void");
  Control.addVariable("skadiBInsertMat2","Void");

  Control.addVariable("skadiBInsertNWall",1);
  Control.addVariable("skadiBInsertWallThick0",1.0);
  Control.addVariable("skadiBInsertWallMat0","Nickel");
  Control.addVariable("skadiBInsertWallThick1",2.0);
  Control.addVariable("skadiBInsertWallMat1","Void");

  FGen.setYOffset(1.0);
  FGen.generateRectangle(Control,"skadiFWall",98.0,w,w);
  FGen.setYOffset(2.0);
  FGen.generateRectangle(Control,"skadiFSA",178.0,w,w);
  FGen.generateRectangle(Control,"skadiFSB",68.0,w,w);


  PGen.setFeLayer(6.0);
  PGen.setConcLayer(10.0);
  PGen.generatePit(Control,"skadiPitA",0.0,30.0,180.0,180.0,30.0);
  Control.addVariable("skadiPitACutBackShape","Square");
  Control.addVariable("skadiPitACutBackRadius",5.0);

  SGen.generateShield(Control,"skadiShieldAB",718.0,40.0,40.0,60.0,4,8);
  Control.addVariable("skadiShieldABYStep",63.0);
  FGen.clearYOffset();
  PipeGen.generatePipe(Control,"skadiPipeOutA",0.5,47.0);
  FGen.generateRectangle(Control,"skadiGOutA",45.0,w,w);
  
  PipeGen.generatePipe(Control,"skadiPipeOutB",1.0,670.0);
  FGen.generateRectangle(Control,"skadiGOutB",668.0,10.0,10.0);

  PGen.generatePit(Control,"skadiPitC",709.0,30.0,180.0,180.0,30.0);
  Control.addVariable("skadiPitCCutFrontShape","Square");
  Control.addVariable("skadiPitCCutFrontRadius",12.0);
  Control.addVariable("skadiPitCCutBackShape","Square");
  Control.addVariable("skadiPitCCutBackRadius",12.0);

  SGen.generateShield(Control,"skadiShieldC",300.0,40.0,40.0,60.0,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutC",1.0,298.0);
  FGen.generateRectangle(Control,"skadiGOutC",296.0,10.0,10.0);
  
  PGen.generatePit(Control,"skadiPitD",290.0,60.0,180.0,180.0,30.0);
  Control.addVariable("skadiPitDCutFrontShape","Square");
  Control.addVariable("skadiPitDCutFrontRadius",12.0);
  Control.addVariable("skadiPitDCutBackShape","Square");
  Control.addVariable("skadiPitDCutBackRadius",12.0);

  SGen.generateShield(Control,"skadiShieldD",917.0,40.0,40.0,60.0,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutD",1.0,916.0);
  FGen.generateRectangle(Control,"skadiGOutD",914.0,10.0,10.0);
  
    
  return;
}
  
}//NAMESPACE setVariable
