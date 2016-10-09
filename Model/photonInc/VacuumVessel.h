/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   photonInc/VacuumVessel.h
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
#ifndef photonSystem_VacuumVessel_h
#define photonSystem_VacuumVessel_h

class Simulation;

namespace constructSystem
{
  class RingSeal;
  class RingFlange;
}

namespace photonSystem
{
  
/*!
  \class VacuumVessel
  \author S. Ansell
  \version 1.0
  \date October 2016
  \brief Specialized for a vacuum vessel

  Cylindrical with semi-spherical front/back Doors
*/

class VacuumVessel : public attachSystem::ContainedComp,
  public attachSystem::FixedOffset,
  public attachSystem::CellMap
{
 private:

  const int vacIndex;         ///< Index of surface offset
  int cellIndex;                ///< Cell index

  double length;               ///< length of object
  double radius;               ///< radius [inneer]
  double thick;                ///< Outer thickenss

  double backThick;            ///< Back thicnkess
  double doorStep;             ///< Door out step
  double doorThick;            ///< Door out step

  int voidMat;                 ///< inner material
  int mat;                     ///< Outer material

  void populate(const FuncDataBase&);
  void createUnitVector(const attachSystem::FixedComp&,
			const long int);

  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();

  
 public:

  VacuumVessel(const std::string&);
  VacuumVessel(const VacuumVessel&);
  VacuumVessel& operator=(const VacuumVessel&);
  virtual ~VacuumVessel();
  virtual VacuumVessel* clone() const;
  
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);
};

}

#endif
 