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
  PipeGen.setWindow(-2.0,0.5);
  PipeGen.setFlange(-4.0,1.0);

  SGen.addWall(1,60.0,"CastIron");
  SGen.addRoof(1,60.0,"CastIron");
  SGen.addFloor(1,20.0,"CastIron");
  SGen.addFloorMat(5,"Concrete");
  SGen.addRoofMat(5,"Concrete");
  SGen.addWallMat(5,"Concrete");

  // extent of beamline
  Control.addVariable("skadiStopPoint",0);
  Control.addVariable("skadiAxisXYAngle",0.0);   // rotation
  Control.addVariable("skadiAxisZAngle",0.0);   // rotation
  Control.addVariable("skadiAxisZStep",0.0);   // +/- height

  FGen.setGuideMat("Aluminium");
  FGen.setThickness(0.8,0.5);
  
  const double w=3.0;
  // Vertical bender
  FGen.setYOffset(0.0);
  FGen.generateBender(Control,"skadiBA",350.0,w,w,w,w,8400.0,90.0);
  
  //  Gamma blocker 
  FGen.setYOffset(1.5);
  PipeGen.generatePipe(Control,"skadiPipeB",0.5,49.0);
  Control.addVariable("skadiPipeBZStep",-7.5);
  FGen.generateBender(Control,"skadiBB",47.0,w,w,w,w,8400.0,90.0);
  
  FGen.setYOffset(2.5);
  PipeGen.generatePipe(Control,"skadiPipeInA",0.5,49.0);
  Control.addVariable("skadiPipeInAZStep",-2.5);
  FGen.generateBender(Control,"skadiBInA",47.0,w,w,w,w,8400.0,90.0);

  PipeGen.generatePipe(Control,"skadiPipeInB",0.5,449.0);
  Control.addVariable("skadiPipeInBZAngle",-2.0);
  FGen.generateBender(Control,"skadiBInB",446.5,w,w,w,w,8400.0,-90.0);

  FGen.clearYOffset();
  PipeGen.generatePipe(Control,"skadiPipeInC",2.5,49.5);
  FGen.generateRectangle(Control,"skadiGInC",46.5,w,w);

  //Beam Insert
  Control.addVariable("skadiBInsertNBox",3);
  Control.addVariable("skadiBInsertYStep",1.0);
  Control.addVariable("skadiBInsertHeight",30.0);
  Control.addVariable("skadiBInsertWidth",48.0);
  Control.addVariable("skadiBInsertHeight1",152.0);
  Control.addVariable("skadiBInsertWidth1",152.0);
  Control.addVariable("skadiBInsertHeight2",230.0);
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

  FGen.clearYOffset();
  PipeGen.generatePipe(Control,"skadiPipeOutA",1.0,45.0);
  FGen.generateRectangle(Control,"skadiGOutA",43.0,w,w);

  PGen.setFeLayer(6.0);
  PGen.setConcLayer(10.0);
  PGen.generatePit(Control,"skadiPitA",46.0,200.0,220.0,210.0,40.0);
  Control.addVariable("skadiPitACutFrontShape","Square");
  Control.addVariable("skadiPitACutFrontRadius",5.0);
  Control.addVariable("skadiPitACutBackShape","Square");
  Control.addVariable("skadiPitACutBackRadius",5.0);

  FGen.setYOffset(5.0);
  FGen.generateRectangle(Control,"skadiGOutB",43.0,w,w);
  FGen.setYOffset(1.0);
  FGen.generateRectangle(Control,"skadiGOutC",150.0,10,10);

  FGen.clearYOffset();
  SGen.generateShield(Control,"skadiShieldD",516.0,120.0,120.0,48.6,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutD",1.0, 514.0);
  FGen.generateRectangle(Control,"skadiGOutD",512.0,10.0,10.0);

  PGen.generatePit(Control,"skadiPitD",506.0,20.0,220.0,210.0,40.0);
  Control.addVariable("skadiPitDCutFrontShape","Square");
  Control.addVariable("skadiPitDCutFrontRadius",5.0);
  Control.addVariable("skadiPitDCutBackShape","Square");
  Control.addVariable("skadiPitDCutBackRadius",5.0);

  SGen.generateShield(Control,"skadiShieldE",321.0,40.0,40.0,40.0,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutE",1.0,319.0);
  FGen.generateRectangle(Control,"skadiGOutE",317.0,10.0,10.0);

  PGen.generatePit(Control,"skadiPitE",311.0,40.0,220.0,210.0,40.0);
  Control.addVariable("skadiPitECutFrontShape","Square");
  Control.addVariable("skadiPitECutFrontRadius",5.0);
  Control.addVariable("skadiPitECutBackShape","Square");
  Control.addVariable("skadiPitECutBackRadius",5.0);
  /*
  SGen.generateShield(Control,"skadiShieldF",913.0,40.0,40.0,40.0,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutF",1.0,912.0);
  FGen.setYOffset(1.0);
  FGen.generateRectangle(Control,"skadiGOutF",912.0,10.0,10.0);
  */
  SGen.generateShield(Control,"skadiShieldF",713.0,40.0,40.0,40.0,4,8);
  PipeGen.generatePipe(Control,"skadiPipeOutF",0.5,712.0);
  FGen.setYOffset(1.0);
  FGen.generateRectangle(Control,"skadiGOutF",710.0,10.0,10.0);

  FGen.setYOffset(2.0);
  FGen.generateRectangle(Control,"skadiGOutG",200.0,10.0,10.0);

  FGen.clearYOffset();
  SGen.generateShield(Control,"skadiShieldH",2000.0,40.0,40.0,40.0,4,8);
  Control.addVariable("skadiShieldHYStep",404.0);
  PipeGen.generatePipe(Control,"skadiPipeOutH",0.5,2000.0);
  FGen.generateRectangle(Control,"skadiGOutH",1999.0,10.0,10.0);
  return;
}
  
}//NAMESPACE setVariable
