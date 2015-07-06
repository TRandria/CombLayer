/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuild/LOKI.cxx
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

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
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
#include "TwinComp.h"
#include "LayerComp.h"
#include "CellMap.h"
#include "World.h"
#include "AttachSupport.h"
#include "GuideItem.h"
#include "Jaws.h"
#include "GuideLine.h"
#include "DiskChopper.h"
#include "Bunker.h"
#include "BunkerInsert.h"
#include "ChopperPit.h"
#include "Hut.h"
#include "HoleShape.h"
#include "RotaryCollimator.h"
#include "PinHole.h"
#include "RentrantBS.h"
#include "LOKI.h"

namespace essSystem
{

LOKI::LOKI() :
  lokiAxis(new attachSystem::FixedComp("lokiAxis",2)),
  BendA(new beamlineSystem::GuideLine("lokiBA"))
 /*!
    Constructor
 */
{
  ELog::RegMethod RegA("LOKI","LOKI");

  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  // This necessary:
  OR.cell("lokiAxis");
  
  OR.addObject(BendA);
  OR.addObject(lokiAxis);
}



LOKI::~LOKI()
  /*!
    Destructor
  */
{}

void
LOKI::setBeamAxis(const GuideItem& GItem)
  /*!
    Set the primary direction object
   */
{
  ELog::RegMethod RegA("LOKI","setBeamAxis");

  lokiAxis->createUnitVector(GItem);
  lokiAxis->setLinkCopy(0,GItem.getKey("Main"),0);
  lokiAxis->setLinkCopy(1,GItem.getKey("Main"),1);

  return;
}
  
void 
LOKI::build(Simulation& System,
	    const GuideItem& GItem,
	    const Bunker& bunkerObj,
	    const int voidCell)
  /*!
    Carry out the full build
    \param System :: Simulation system
    \param GItem :: Guide Item 
    \param BunkerObj :: Bunker component [for inserts]
    \param voidCell :: Void cell
   */
{
  // For output stream
  ELog::RegMethod RegA("LOKI","build");
  ELog::EM<<"Building LOKI on : "<<GItem.getKeyName()<<ELog::endDiag;

  setBeamAxis(GItem);
  
  BendA->addInsertCell(GItem.getCell("Void"));
  BendA->addEndCut(GItem.getKey("Beam").getSignedLinkString(-2));
  BendA->createAll(System,GItem.getKey("Beam"),-1,
		   GItem.getKey("Beam"),-1);

  Geometry::Vec3D A=BendA->getKey("Guide0").getSignedLinkAxis(-1);
  Geometry::Vec3D B=BendA->getKey("Guide0").getSignedLinkAxis(2);

  ELog::EM<<"BendA START DIR == "<<A<<ELog::endDiag;
  ELog::EM<<"BendA END DIR == "<<B<<ELog::endDiag;
  ELog::EM<<"BendA Cos == "<<A.dotProd(B)<<ELog::endDiag;


  
  return;
}


}   // NAMESPACE essSystem
