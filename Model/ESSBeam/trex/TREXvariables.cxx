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

  PipeGen.setPipe(12.0,0.5);
  PipeGen.setWindow(-2.0,0.5);
  PipeGen.setFlange(-4.0,1.0);

  SGen.addWall(1,20.0,"CastIron");
  SGen.addRoof(1,20.0,"CastIron");
  SGen.addFloor(1,20.0,"CastIron");
  SGen.addFloorMat(5,"Concrete");
  SGen.addRoofMat(5,"Concrete");
  SGen.addWallMat(5,"Concrete");

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
  
  //FGen.setYOffset(2.0);
  PipeGen.generatePipe(Control,"trexPipeInB",1.0,400.0);
  Control.addVariable("trexPipeInBXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInB",398.0,6.0,6.0,5.75,6.51,
                      1900000.0,0.0);

  PipeGen.generatePipe(Control,"trexPipeInC",1.0,400.0);
  Control.addVariable("trexPipeInCXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInC",398.0,6.0,6.0,6.51,7.11,
		      1900000.0,0.0);
  
  PipeGen.generatePipe(Control,"trexPipeInD",1.0,366.0);
  Control.addVariable("trexPipeInDXYAngle",-0.1);
  FGen.generateBender(Control,"trexBInD",364.0,6.0,6.0,7.11,7.57,
		      1900000.0,0.0);

  // FGen.clearYOffset();
  PipeGen.generatePipe(Control,"trexPipeInE",1.5,200.0);
  FGen.generateBender(Control,"trexBInE",198.0,6.0,6.0,7.57,7.72,
		      1900000.0,0.0);
 
  // BEAM INSERT
  Control.addVariable("trexBInsertANBox",1);
  Control.addVariable("trexBInsertAHeight",25.7);
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
  Control.addVariable("trexBInsertBHeight",42.4);
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
  PGen.generatePit(Control,"trexPitA",333.0,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitACutFrontShape","Square");
  Control.addVariable("trexPitACutFrontRadius",5.0);
  Control.addVariable("trexPitACutBackShape","Square");
  Control.addVariable("trexPitACutBackRadius",5.0);
  
  SGen.generateShield(Control,"trexShieldA",366.5,40.0,40.0,40.0,4,8);
  PipeGen.generatePipe(Control,"trexPipeOutA",1.5,331.5);
  Control.addVariable("trexPipeOutAXYAngle",-0.1);
 
  FGen.setGuideMat("Borosilicate","CastIron");
  FGen.setThickness(0.5,0.5,0.5);
  FGen.clearYOffset();
  FGen.generateBender(Control,"trexBOutA",329.5,6.0,6.0,8.07,8.27,
		      1900000.0,0.0);

  PGen.generatePit(Control,"trexPitB",800.0,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitBCutFrontShape","Square");
  Control.addVariable("trexPitBCutFrontRadius",5.0);
  Control.addVariable("trexPitBCutBackShape","Square");
  Control.addVariable("trexPitBCutBackRadius",5.0);
  
  SGen.generateShield(Control,"trexShieldB",761.0,40.0,40.0,40.0,4,8);
  Control.addVariable("trexShieldBXYAngle",-0.1);
  Control.addVariable("trexShieldBYStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutB1",0.0,380.5);
  Control.addVariable("trexPipeOutB1XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutB1",378.5,6.0,6.0,8.27,8.42,
 		      1900000.0,0.0);
  PipeGen.generatePipe(Control,"trexPipeOutB2",1.0,380.5);
  Control.addVariable("trexPipeOutB2XYAngle",-0.1);
  FGen.generateBender(Control,"trexBOutB2",378.5,6.0,6.0,8.42,8.49,
		      1900000.0,0.0);

  /// After BW2 Chopper pit
  //  PGen.generatePit(Control,"trexOutPitC",4995.0,25.0,220.0,210.0,40.0);
  PGen.generatePit(Control,"trexPitC",497.1,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitCCutFrontShape","Square");
  Control.addVariable("trexPitCCutFrontRadius",5.0);
  Control.addVariable("trexPitCCutBackShape","Square");
  Control.addVariable("trexPitCCutBackRadius",5.0);
  
  /// array section
  FGen.clearYOffset();
  for(size_t i=0;i<10;i++)
    {
      const std::string strNum(StrFunc::makeString(i));

      double ShieldYOffset = (i==0) ? 38.5 : 1.5;
      SGen.generateShield(Control,"trexShieldC"+strNum,495.5,40.0,40.0,
            		  40.0,4,8);
      Control.addVariable("trexShieldC"+strNum+"XYAngle",-0.1);
      Control.addVariable("trexShieldC"+strNum+"YStep",ShieldYOffset);
      
      PipeGen.generatePipe(Control,"trexPipeOutC"+strNum,0.5,495.5);
      Control.addVariable("trexPipeOutC"+strNum+"XYAngle",-0.1);

      FGen.generateBender(Control,"trexBOutC"+strNum,493.5,6.0,6.0,8.50,
			  8.50,1900000.0,0.0);
    }
  
  SGen.generateShield(Control,"trexShieldD",581.5,40.0,40.0,40.0,4,8);
  Control.addVariable("trexShieldDXYAngle",-0.1);
  Control.addVariable("trexShieldDYStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutD",0.5,581.5);
  FGen.generateBender(Control,"trexBOutD",579.5,6.0,6.0,8.50,8.50,
		      1900000.0,0.0);

  // End LOS

  PGen.generatePit(Control,"trexPitE",1321.5,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitECutFrontShape","Square");
  Control.addVariable("trexPitECutFrontRadius",5.0);
  Control.addVariable("trexPitECutBackShape","Square");
  Control.addVariable("trexPitECutBackRadius",5.0);
  
  SGen.generateShield(Control,"trexShieldE",1321.5,40.0,40.0,40.0,4,8);
  PipeGen.generatePipe(Control,"trexPipeOutE",0.5,1320.0);
  FGen.generateRectangle(Control,"trexGOutE",1318.0,6.0,8.50);
  
  PGen.generatePit(Control,"trexPitF",5183.0,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitFCutFrontShape","Square");
  Control.addVariable("trexPitFCutFrontRadius",4.0);
  Control.addVariable("trexPitFCutBackShape","Square");
  Control.addVariable("trexPitFCutBackRadius",4.0);

  SGen.generateShield(Control,"trexShieldF",5144.5,40.0,40.0,40.0,4,8);
  Control.addVariable("trexShieldFYStep",38.5);
  double FVS[8]={8.50,8.50,8.50,8.48,8.29,7.92,7.29,6.28};
  double FVE[8]={8.50,8.50,8.48,8.29,7.92,7.29,6.28,4.76};
  double FHS[8]={6.0,6.28,6.78,7.01,6.98,6.74,6.19,5.28};
  double FHE[8]={6.28,6.78,7.01,6.98,6.74,6.19,5.28,3.73};
  for(size_t i=0;i<8;i++)
    {
      const std::string strNum(StrFunc::makeString(i));
      const double yOffsetF = (i==0) ? 39.0 : 1.0;
      PipeGen.generatePipe(Control,"trexPipeOutF"+strNum,yOffsetF,643.0);
      FGen.generateTaper(Control,"trexGOutF"+strNum,641.0,FHS[i],FHE[i],FVS[i],
			  FVE[i]);
    }

  PGen.generatePit(Control,"trexPitG",299.0,25.0,220.0,210.0,40.0);
  Control.addVariable("trexPitGCutFrontShape","Square");
  Control.addVariable("trexPitGCutFrontRadius",3.0);
  Control.addVariable("trexPitGCutBackShape","Square");
  Control.addVariable("trexPitGCutBackRadius",3.0);

  SGen.generateShield(Control,"trexShieldG",260.5,40.0,40.0,40.0,4,8);
  Control.addVariable("trexShieldGYStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutG",0.5,259.5);
  FGen.generateTaper(Control,"trexGOutG",257.5,3.39,2.52,4.45,3.71);

  SGen.generateShield(Control,"trexShieldH",60.5,40.0,40.0,40.0,4,8);
  Control.addVariable("trexShieldHYStep",38.5);
  PipeGen.generatePipe(Control,"trexPipeOutH",0.5,59.5);
  FGen.generateTaper(Control,"trexGOutH",57.5,2.21,1.50,3.48,3.0);
  
  return;
}
  
}//NAMESPACE setVariable
