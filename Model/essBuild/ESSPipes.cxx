/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuild/ESSPipes.cxx
 *
 * Copyright (c) 2004-2016 by Stuart Ansell
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
#include <array>
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
#include "ContainedComp.h"
#include "LayerComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "SurfMap.h"
#include "World.h"
#include "AttachSupport.h"
#include "pipeUnit.h"
#include "PipeLine.h"
#include "SupplyPipe.h"
#include "ESSPipes.h"

namespace essSystem
{

ESSPipes::ESSPipes() 
 /*!
    Constructor
 */
{
  registerPipes({
      "TSupplyLeftAl","TSupplyLeftConnect","TSupplyLeftInvar",
      "TSupplyRightAl","TSupplyRightConnect","TSupplyRightInvar",
      "TReturnLeftAl","TReturnLeftConnect","TReturnLeftInvar",
      "TReturnRightAl","TReturnRightConnect","TReturnRightInvar",
      "LSupplyLeftAl","LSupplyLeftConnect","LSupplyLeftInvar",
      "LSupplyRightAl","LSupplyRightConnect","LSupplyRightInvar",
      "LReturnLeftAl","LReturnLeftConnect","LReturnLeftInvar",
      "LReturnRightAl","LReturnRightConnect","LReturnRightInvar"});
}

ESSPipes::ESSPipes(const ESSPipes& A) : 
  PipeMap(A.PipeMap)
  /*!
    Copy constructor
    \param A :: ESSPipes to copy
  */
{}

ESSPipes&
ESSPipes::operator=(const ESSPipes& A)
  /*!
    Assignment operator
    \param A :: ESSPipes to copy
    \return *this
  */
{
  if (this!=&A)
    {
      PipeMap=A.PipeMap;
    }
  return *this;
}

  
ESSPipes::PipeTYPE&
ESSPipes::getPipe(const std::string& PName)
  /*!
    Accessor to pipe pointer 
    \param PName :: Pipe name
    \return Pipe Pointer
   */
{
  ELog::RegMethod RegA("ESSPipes","getPipe");
  
  std::map<std::string,PipeTYPE>::iterator mc=
    PipeMap.find(PName);
  if (mc==PipeMap.end())
    throw ColErr::InContainerError<std::string>(PName,"PName in PipeMap");
  return mc->second;
}

void
ESSPipes::registerPipes(const std::vector<std::string>& PNames)
  /*!
    Register a list of pipes via names
    \param PNames :: Name of pipe to register
  */
{
  ELog::RegMethod RegA("ESSPipes","registerPipes");
  
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  for(const std::string& PN : PNames)
    {
      PipeMap.emplace(PN,PipeTYPE(new constructSystem::SupplyPipe(PN)));
      OR.addObject(PipeMap[PN]);
    }
  return;
}

void
ESSPipes::buildH2Pipe(Simulation& System,const std::string& lobeName,
                     const std::string& waterName,
                     const std::string& pipeSpecialization,
                     const std::string& pipeAlName,
                     const std::string& pipeConnectName,
                     const std::string& pipeInvarName)
{
  /*
    Build a pipe connected to a Butterfly lobe
    \param System :: Simulation
    \param lobeName :: Butterfly moderator lobe name
    \param pipeSpecialization :: type of the pipe [currently ignored]
    \param pipeAlName  :: first piece of the pipe
    \param pipeConnectName  :: second piece of the pipe
    \param pipeInvarName  :: third piece of the pipe
    The pieces can be made from different materials.
   */
  ELog::RegMethod RegA("makeESS", "buildH2Pipe");


  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  PipeTYPE& pipeAl=getPipe(pipeAlName);
  PipeTYPE& pipeConnect=getPipe(pipeConnectName);
  PipeTYPE& pipeInvar=getPipe(pipeInvarName);

  
  const attachSystem::FixedComp* lobe=
    OR.getObjectThrow<attachSystem::FixedComp>
    (lobeName,"FixedComp::Lobe");

  const attachSystem::CellMap* waterCM=
    OR.getObjectThrow<attachSystem::CellMap>(waterName,"CellMap::Water");

  System.populateCells();
  System.validateObjSurfMap();

  pipeAl->setAngleSeg(12);
  pipeAl->setOption(pipeSpecialization); 
  // createAll arguments:
  // layer level is depth into the object layers [0=> inner]
  // linkPt is normal link point in fixedcomp [2]
  // layerLevel : linkPoint [2]
  pipeAl->createAll(System,*lobe,0,2,2);

  pipeConnect->setAngleSeg(12);
  pipeConnect->setOption(pipeSpecialization);
  pipeConnect->setStartSurf(pipeAl->getSignedLinkString(2));
  pipeConnect->createAll(System,*pipeAl,2);

  System.populateCells();
  System.validateObjSurfMap();

  pipeInvar->setAngleSeg(12);
  pipeInvar->setOption(pipeSpecialization);
  pipeInvar->setStartSurf(pipeConnect->getSignedLinkString(2));
  pipeInvar->createAll(System,*pipeConnect,2);
  return;
}


void 
ESSPipes::buildTopPipes(Simulation& System,
                        const std::string& pipeUniqName)
  /*!
    Process the upper moderator pipes
    \param System :: Simulation 
    \param pipeUniqName :: pipeUniqName string to add
    infront of keyName
  */
{
  ELog::RegMethod RegA("makeESS","buildTopPipes");


  if (!pipeUniqName.empty() || pipeUniqName!="help")
    {

      buildH2Pipe(System,"TopFlyLeftLobe","TopFlyLeftWater",pipeUniqName,
		  "TSupplyLeftAl","TSupplyLeftConnect", "TSupplyLeftInvar");
      
      buildH2Pipe(System,"TopFlyLeftLobe","TopFlyLeftWater",pipeUniqName,
		  "TReturnLeftAl","TReturnLeftConnect","TReturnLeftInvar");
      
      
      buildH2Pipe(System,"TopFlyRightLobe","TopFlyRightWater",pipeUniqName,
		  "TSupplyRightAl","TSupplyRightConnect","TSupplyRightInvar");
      
      buildH2Pipe(System,"TopFlyRightLobe","TopFlyRightWater",pipeUniqName,
		  "TReturnRightAl","TReturnRightConnect","TReturnRightInvar");
    }
  return;
}

void 
ESSPipes::buildLowPipes(Simulation& System,
                        const std::string& pipeUniqName)
  /*!
    Process the upper moderator pipes
    \param System :: Simulation 
    \param pipeUniqName :: pipeUniqName string to add
    infront of keyName
  */
{
  ELog::RegMethod RegA("makeESS","buildLowPipes");

  if (!pipeUniqName.empty() || pipeUniqName!="help")
    {
      buildH2Pipe(System,"LowFlyLeftLobe","LowFlyLeftWater",pipeUniqName,
                  "LSupplyLeftAl","LSupplyLeftConnect", "LSupplyLeftInvar");

      buildH2Pipe(System,"LowFlyLeftLobe","LowFlyLeftWater",pipeUniqName,
                  "LReturnLeftAl","LReturnLeftConnect","LReturnLeftInvar");
      
      buildH2Pipe(System,"LowFlyRightLobe","LowFlyRightWater",pipeUniqName,
                  "LSupplyRightAl","LSupplyRightConnect","LSupplyRightInvar");
      
      buildH2Pipe(System,"LowFlyRightLobe","LowFlyRightWater",pipeUniqName,
              "LReturnRightAl","LReturnRightConnect","LReturnRightInvar");
    }
  return;
}

  

}   // NAMESPACE essSystem

