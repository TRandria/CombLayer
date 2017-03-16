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
#include <memory>
#include <array>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Object.h"
#include "Qhull.h"
#include "Simulation.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "LinkUnit.h"  
#include "FixedComp.h"
#include "FixedGroup.h"
#include "FixedOffset.h"
#include "FixedOffsetGroup.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "CellMap.h"

#include "AHut.h"

namespace pipeSystem
{

AHut::AHut(const std::string& Key) :
  attachSystem::FixedOffsetGroup(Key,"Inner",6,"Mid1",6,"Outer",6),
  attachSystem::ContainedComp(),attachSystem::CellMap(),
  hutIndex(ModelSupport::objectRegister::Instance().cell(Key)),
  cellIndex(hutIndex+1)
{}

AHut::~AHut()
{}

void AHut::populate(const FuncDataBase& Control)
{
  ELog::RegMethod RegA("AHut","populate");

  FixedOffsetGroup::populate(Control);

  voidHeight=Control.EvalVar<double>(keyName+"VoidHeight");
  voidWidth=Control.EvalVar<double>(keyName+"VoidWidth");
  voidDepth=Control.EvalVar<double>(keyName+"VoidDepth");
  voidLength=Control.EvalVar<double>(keyName+"VoidLength");

  L1Front=Control.EvalVar<double>(keyName+"L1Front");
  L1LeftWall=Control.EvalVar<double>(keyName+"L1LeftWall");
  L1RightWall=Control.EvalVar<double>(keyName+"L1RightWall");
  L1Roof=Control.EvalVar<double>(keyName+"L1Roof");
  L1Back=Control.EvalVar<double>(keyName+"L1Back");
  
  L2Front=Control.EvalVar<double>(keyName+"L2Front");
  L2LeftWall=Control.EvalVar<double>(keyName+"L2LeftWall");
  L2RightWall=Control.EvalVar<double>(keyName+"L2RightWall");
  L2Roof=Control.EvalVar<double>(keyName+"L2Roof");
  L2Back=Control.EvalVar<double>(keyName+"L2Back");

  L3Front=Control.EvalVar<double>(keyName+"L3Front");
  L3LeftWall=Control.EvalVar<double>(keyName+"L3LeftWall");
  L3RightWall=Control.EvalVar<double>(keyName+"L3RightWall");
  L3Roof=Control.EvalVar<double>(keyName+"L3Roof");
  L3Back=Control.EvalVar<double>(keyName+"L3Back");

  L1Mat=ModelSupport::EvalMat<int>(Control,keyName+"L1Mat");
  L2Mat=ModelSupport::EvalMat<int>(Control,keyName+"L2Mat");
  L3Mat=ModelSupport::EvalMat<int>(Control,keyName+"L3Mat");

  //Cylinder Det Pipe
  pipeRadius=Control.EvalVar<double>(keyName+"Radius");
  pipeLength=Control.EvalVar<double>(keyName+"Length");
  //  nDivision=Control.EvalDefVar<size_t>(keyName+"NDivision",0);
  //  voidMat=ModelSupport::EvalDefMat<int>(Control,keyName+"VoidMat",0);
  L1PipeThick=Control.EvalVar<double>(keyName+"L1PipeThick");
  L2PipeThick=Control.EvalVar<double>(keyName+"L2PipeThick");
  L1PipeMat=ModelSupport::EvalMat<int>(Control,keyName+"L1PipeMat");
  L2PipeMat=ModelSupport::EvalMat<int>(Control,keyName+"L2PipeMat");

  return;
}

void AHut::createUnitVector(const attachSystem::FixedComp& FC,
			   const long int sideIndex)
{
  ELog::RegMethod RegA("AHut","createUnitVector");
  
  yStep+=voidLength/2.0;
  attachSystem::FixedComp& Outer=getKey("Outer");
  attachSystem::FixedComp& Mid1=getKey("Mid1");
  //  attachSystem::FixedComp& Mid2=getKey("Mid2");
  attachSystem::FixedComp& Inner=getKey("Inner");
  
  Outer.createUnitVector(FC,sideIndex);
  Mid1.createUnitVector(FC,sideIndex);
  //  Mid2.createUnitVector(FC,sideIndex);
  Inner.createUnitVector(FC,sideIndex);
  applyOffset();
  setDefault("Inner");
  return;
}

void AHut::createSurfaces()
{
  ELog::RegMethod RegA("AHut","createSurfaces");

  ModelSupport::buildPlane(SMap,hutIndex+1,Origin-Y*(voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+2,Origin+Y*(voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+3,Origin-X*(voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+4,Origin+X*(voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+5,Origin-Z*voidDepth,Z);
  ModelSupport::buildPlane(SMap,hutIndex+6,Origin+Z*voidHeight,Z); 


  // L1 WALLS:
  ModelSupport::buildPlane(SMap,hutIndex+11,
			   Origin-Y*(L1Front+voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+12,
			   Origin+Y*(L1Back+voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+13,
			   Origin-X*(L1LeftWall+voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+14,
			   Origin+X*(L1RightWall+voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+15,
			   Origin-Z*(L1Floor+voidDepth),Z);  
  ModelSupport::buildPlane(SMap,hutIndex+16,
			   Origin+Z*(L1Roof+voidHeight),Z);

  // L2 WALLS:
  ModelSupport::buildPlane(SMap,hutIndex+21,
			   Origin-Y*(L2Front+voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+22,
			   Origin+Y*(L2Back+voidLength/2.0),Y);
  ModelSupport::buildPlane(SMap,hutIndex+23,
			   Origin-X*(L2LeftWall+voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+24,
			   Origin+X*(L2RightWall+voidWidth/2.0),X);
  ModelSupport::buildPlane(SMap,hutIndex+25,
			   Origin-Z*(L2Floor+voidDepth),Z);  
  ModelSupport::buildPlane(SMap,hutIndex+26,
			   Origin+Z*(L2Roof+voidHeight),Z);

  // L3 WALLS:
   ModelSupport::buildPlane(SMap,hutIndex+31,
			    Origin-Y*(L3Front+voidLength/2.0),Y);
   ModelSupport::buildPlane(SMap,hutIndex+32,
			    Origin+Y*(L3Back+voidLength/2.0),Y);
   ModelSupport::buildPlane(SMap,hutIndex+33,
			    Origin-X*(L3LeftWall+voidWidth/2.0),X);
   ModelSupport::buildPlane(SMap,hutIndex+34,
			    Origin+X*(L3RightWall+voidWidth/2.0),X);
   ModelSupport::buildPlane(SMap,hutIndex+35,
			    Origin-Z*(L3Floor+voidDepth),Z);  
   ModelSupport::buildPlane(SMap,hutIndex+36,
			    Origin+Z*(L3Roof+voidHeight),Z);

   ModelSupport::buildCylinder(SMap,hutIndex+41,Origin,Y,pipeRadius);
   ModelSupport::buildCylinder(SMap,hutIndex+42,Origin,Y,pipeRadius+L1PipeThick);
   ModelSupport::buildCylinder(SMap,hutIndex+43,Origin,Y,pipeRadius+L1PipeThick+L2PipeThick);
   ModelSupport::buildPlane(SMap,hutIndex+51,Origin+Y*(pipeLength/2.0),Y);
 
   return;
}

void AHut::createObjects(Simulation& System)
{
  ELog::RegMethod RegA("AHut","createObjects");

  std::string Out;

  Out=ModelSupport::getComposite(SMap,hutIndex,
				 "(1 -2 3 -4 5 -6) : (2 -41 -51) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,0,0.0,Out));
  setCell("Void",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,"2 -42 41 -51 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L1PipeMat,0.0,Out));
  setCell("L1Pipe",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,"2 -43 42 -51 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L2PipeMat,0.0,Out));
  setCell("L2Pipe",cellIndex-1);
  
  Out=ModelSupport::getComposite(SMap,hutIndex,
				 "1 -12 13 -14 15 -16 43 (2:-3:4:-5:6) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L1Mat,0.0,Out));
  setCell("L1",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex," -1 11 13 -14 15 -16 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L1Mat,0.0,Out));
  setCell("FrontWall",cellIndex-1);
  setCell("L1Front",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,
		 "11 -22 23 -24 25 -26 43 (12:-13:14:-15:16) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L2Mat,0.0,Out));
  setCell("L2",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,"-11 21 23 -24 25 -26 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L2Mat,0.0,Out));
  addCell("FrontWall",cellIndex-1);
  setCell("L2Front",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,
		 "21 -32 33 -34 35 -36 43 (22:-23:24:-25:26) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L3Mat,0.0,Out));
  setCell("L3",cellIndex-1);

  Out=ModelSupport::getComposite(SMap,hutIndex,"-21 31 33 -34 35 -36 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,L3Mat,0.0,Out));
  addCell("FrontWall",cellIndex-1);
  setCell("L3Front",cellIndex-1); 
  
  // Exclude:
  Out=ModelSupport::getComposite(SMap,hutIndex,
				 " (31 -32 33 -34  35 -36) : (32 -43 -51) ");
  addOuterSurf(Out);      
  
  //Out=ModelSupport::getComposite(SMap,hutIndex,
  //				 " (1 -2 3 -4  5 -6) : (2 -43 -51) ");
  //addOuterSurf(Out); 

  return;
}
void
AHut::createLinks()
  /*!
    Determines the link point on the outgoing plane.
    It must follow the beamline, but exit at the plane
  */
{
  ELog::RegMethod RegA("AHut","createLinks");

  attachSystem::FixedComp& innerFC=FixedGroup::getKey("Inner");
  attachSystem::FixedComp& mid1FC=FixedGroup::getKey("Mid1");
  //  attachSystem::FixedComp& mid2FC=FixedGroup::getKey("Mid2");
  attachSystem::FixedComp& outerFC=FixedGroup::getKey("Outer");

  innerFC.setConnect(0,Origin-Y*(voidLength/2.0),-Y);
  innerFC.setConnect(1,Origin+Y*(voidLength/2.0),Y);
  innerFC.setConnect(2,Origin-X*(voidWidth/2.0),-X);
  innerFC.setConnect(3,Origin+X*(voidWidth/2.0),X);
  innerFC.setConnect(4,Origin-Z*voidDepth,-Z);
  innerFC.setConnect(5,Origin+Z*voidHeight,Z);  

  innerFC.setLinkSurf(0,-SMap.realSurf(hutIndex+1));
  innerFC.setLinkSurf(1,SMap.realSurf(hutIndex+2));
  innerFC.setLinkSurf(2,-SMap.realSurf(hutIndex+3));
  innerFC.setLinkSurf(3,SMap.realSurf(hutIndex+4));
  innerFC.setLinkSurf(4,-SMap.realSurf(hutIndex+5));
  innerFC.setLinkSurf(5,SMap.realSurf(hutIndex+6));

  
  mid1FC.setConnect(0,Origin-Y*(L1Front+voidLength/2.0),-Y);
  mid1FC.setConnect(1,Origin+Y*(L1Back+voidLength/2.0),Y);
  mid1FC.setConnect(2,Origin-X*(L1LeftWall+voidWidth/2.0),-X);
  mid1FC.setConnect(3,Origin+X*(L1RightWall+voidWidth/2.0),X);
  mid1FC.setConnect(4,Origin-Z*(L1Floor+voidDepth),-Z);
  mid1FC.setConnect(5,Origin+Z*(L1Roof+voidHeight),Z);  

  mid1FC.setLinkSurf(0,-SMap.realSurf(hutIndex+11));
  mid1FC.setLinkSurf(1,SMap.realSurf(hutIndex+12));
  mid1FC.setLinkSurf(2,-SMap.realSurf(hutIndex+13));
  mid1FC.setLinkSurf(3,SMap.realSurf(hutIndex+14));
  mid1FC.setLinkSurf(4,-SMap.realSurf(hutIndex+15));
  mid1FC.setLinkSurf(5,SMap.realSurf(hutIndex+16));

  /* 
  mid2FC.setConnect(0,Origin-Y*(L1Front+L2Front+voidLength/2.0),-Y);
  mid2FC.setConnect(1,Origin+Y*(L1Back+L2Back+voidLength/2.0),Y);
  mid2FC.setConnect(2,Origin-X*(L1LeftWall+L2LeftWall+voidWidth/2.0),-X);
  mid2FC.setConnect(3,Origin+X*(L1RightWall+L2RightWall+voidWidth/2.0),X);
  mid2FC.setConnect(4,Origin-Z*(L1Floor+L2Floor+voidDepth),-Z);
  mid2FC.setConnect(5,Origin+Z*(L1Roof+L2Roof+voidHeight),Z);  

  mid2FC.setLinkSurf(0,-SMap.realSurf(hutIndex+21));
  mid2FC.setLinkSurf(1,SMap.realSurf(hutIndex+22));
  mid2FC.setLinkSurf(2,-SMap.realSurf(hutIndex+23));
  mid2FC.setLinkSurf(3,SMap.realSurf(hutIndex+24));
  mid2FC.setLinkSurf(4,-SMap.realSurf(hutIndex+25));
  mid2FC.setLinkSurf(5,SMap.realSurf(hutIndex+26));
  */
  outerFC.setConnect(0,Origin-Y*(L1Front+L2Front+L3Front+voidLength/2.0),-Y);
  outerFC.setConnect(1,Origin+Y*(L1Back+L2Back+L3Back+voidLength/2.0),Y);
  outerFC.setConnect(2,Origin-X*(L1LeftWall+L2LeftWall+L3LeftWall+voidWidth/2.0),-X);
  outerFC.setConnect(3,Origin+X*(L1RightWall+L2RightWall+L3RightWall+voidWidth/2.0),X);
  outerFC.setConnect(4,Origin-Z*(L1Floor+L2Floor+L3Floor+voidDepth),-Z);
  outerFC.setConnect(5,Origin+Z*(L1Roof+L2Roof+L3Floor+voidHeight),Z);  

  outerFC.setLinkSurf(0,-SMap.realSurf(hutIndex+31));
  outerFC.setLinkSurf(1,SMap.realSurf(hutIndex+32));
  outerFC.setLinkSurf(2,-SMap.realSurf(hutIndex+33));
  outerFC.setLinkSurf(3,SMap.realSurf(hutIndex+34));
  outerFC.setLinkSurf(4,-SMap.realSurf(hutIndex+35));
  outerFC.setLinkSurf(5,SMap.realSurf(hutIndex+36));

  return;
}

void
AHut::createAll(Simulation& System,
		   const attachSystem::FixedComp& FC,
		   const long int FIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: FixedComp
    \param FIndex :: Fixed Index
  */
{
  ELog::RegMethod RegA("AHut","createAll(FC)");

  populate(System.getDataBase());
  createUnitVector(FC,FIndex);
  
  createSurfaces();    
  createObjects(System);
  
  createLinks();
  insertObjects(System);   
  
  return;
}
}
