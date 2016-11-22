/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   weightsInc/MarkovProcess.h
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
#ifndef WeightSystem_MarkovProcess_h
#define WeightSystem_MarkovProcess_h

///\file 

class Simulation;
namespace Geometry
{
  class Plane;
}

/*!
  \namespace WeightSystem
  \brief Adds a layer of shutters to the Target/Reflect/Moderatr
  \author S. Ansell
  \version 1.0
  \date April 2009
*/

namespace WeightSystem
{
  class ItemWeight;
  class CellWeight;
  class WWGWeight;
  
  /*!
    \class MarkovProcess
    \version 1.0
    \author S. Ansell
    \date October 2015
    \brief Input to Weights controller
  */
  
class MarkovProcess
{
 private:

 public:

  MarkovProcess();
  MarkovProcess(const MarkovProcess&);
  MarkovProcess& operator=(const MarkovProcess&);
  ~MarkovProcess();

  
    
};

}


#endif
 