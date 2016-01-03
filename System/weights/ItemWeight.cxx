/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   weight/ItemWeight.cxx
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
#include <cmath>
#include <complex> 
#include <vector>
#include <list>
#include <set>
#include <map> 
#include <string>
#include <algorithm>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "mathSupport.h"
#include "support.h"
#include "MapSupport.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "WForm.h"
#include "WItem.h"
#include "WCells.h"
#include "WeightMesh.h"
#include "WWG.h"
#include "weightManager.h"

#include "ItemWeight.h"

#include "debugMethod.h"

namespace WeightSystem
{

std::ostream&
operator<<(std::ostream& OX,const ItemWeight& A)
  /*!
    Write out to a stream
    \param OX :: Output stream
    \param A :: ItemWeight to write
    \return Stream
  */
{
  A.write(OX);
  return OX;
}

ItemWeight::ItemWeight()  :
  sigmaScale(0.06914),scaleFactor(1.0),
  minWeight(1e-7)
  /*! 
    Constructor 
  */
{}

ItemWeight::ItemWeight(const ItemWeight& A)  :
  sigmaScale(A.sigmaScale),Cells(A.Cells)
  /*! 
    Copy Constructor 
    \param A :: ItemWeight to copy
  */
{}

ItemWeight&
ItemWeight::operator=(const ItemWeight& A)
  /*! 
    Assignment operator
    \param A :: ItemWeight to copy
    \return *this
  */
{
  if (this!=&A)
    {
      Cells=A.Cells;
    }
  return *this;
}
  
void
ItemWeight::addTracks(const int cN,const double value)
  /*!
    Adds an average track contribution
    \param cN :: cell number
    \param value :: vlaue of weight
  */
{
  ELog::RegMethod RegA("ItemWeight","addTracks");
  
  std::map<long int,CellItem>::iterator mc=Cells.find(cN);
  if (mc==Cells.end())
    Cells.emplace(cN,CellItem(value));
  else
    {
      mc->second.weight+=value;
      mc->second.number+=1.0;
    }
  return;
}

void
ItemWeight::updateWM(const double eCut) const
  /*!
    Update WM
    \param eCut :: Energy cut [-ve to scale below ] 
  */
{
  ELog::RegMethod RegA("ItemWeight","updateWM");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();  

  WeightSystem::WForm* WF=WM.getParticle('n');
  if (!WF)
    throw ColErr::InContainerError<std::string>("n","neutron has no WForm");

  // quick way to get length of array
  const std::vector<double> EVec=WF->getEnergy();
  std::vector<double> DVec=EVec;
  std::fill(DVec.begin(),DVec.end(),1.0);
  
  double maxW(0.0);
  double minW(1e38);
  double aveW(0.0);
  int cnt(0);
  for(const std::map<int,CellItem>::value_type& cv : Cells)
    {
      const double W=(exp(-cv.second.weight*sigmaScale*scaleFactor));
      if (W>maxW) maxW=W;
      if (W<minW && minW>1e-38) minW=W;
      aveW+=W;
      cnt++;
    }
  aveW/=cnt;
  // Work on minW first:
  const double factor=(minW>minWeight) ?
    log(minWeight)/log(minW) : 1.0;

  for(const std::map<int,CellItem>::value_type& cv : Cells)
    {
      const double W=(exp(-cv.second.weight*sigmaScale*scaleFactor*factor));
      for(size_t i=0;i<EVec.size();i++)
	{
	  if (eCut<-1e-10 && EVec[i] <= -eCut)
	    DVec[i]=W;
	  else if (EVec[i]>=eCut)
	    DVec[i]=W;
	}
      WF->scaleWeights(cv.first,DVec);
    }
  return;
}
  

void
ItemWeight::write(std::ostream& OX) const
  /*!
    Write out the track
    \param OX :: Output stream
  */
{
  for(const std::map<long int,CellItem>::value_type& cv : Cells)
    OX<<cv.first<<" "<<cv.second.weight<<" "<<cv.second.number<<std::endl;
  return;
} 

  
} // Namespace WeightSystem
