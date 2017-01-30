/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/skadiInc/SKADI.h
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
#ifndef essSystem_SKADI_h
#define essSystem_SKADI_h

class Simulation;


namespace attachSystem
{
  class FixedComp;
  class TwinComp;
  class CellMap;
}

namespace constuctSystem
{
  class Jaws;
  class DiskChopper;
  class ChopperPit;
  class ChopperHousing;
  class ChopperUnit;
  class RotaryCollimator;
  class VacuumBox;
  class VacuumPipe;
  class PipeCollimator;
  class LineShield;
  class HoleShape;
  class Aperture;
}

namespace essSystem
{
  class CompBInsert;
  class GuideItem;
  
  /*!
    \class TREX
    \version 1.0
    \author T. Randriamalala
    \date October 2016
    \brief TREX beamline constructor for the ESS
  */



class SKADI : public attachSystem::CopiedComp
{
 private:

   /// Stop at [0:Complete / 1:Mono Wall / 2:Inner Bunker / 3:Outer Bunker ]
  int stopPoint;  

  /// Main Beam Axis
  std::shared_ptr<attachSystem::FixedOffset> skadiAxis;
  
  /// Monolith guideline
  std::shared_ptr<beamlineSystem::GuideLine> BendA;

  /// Bridge guide in the light shutter
  std::shared_ptr<constructSystem::VacuumPipe> VPipeB;
  std::shared_ptr<beamlineSystem::GuideLine> BendB;

  /// Benders inside Bunker
  std::shared_ptr<constructSystem::VacuumPipe> VPipeInA;
  std::shared_ptr<beamlineSystem::GuideLine> BendInA;

  std::shared_ptr<constructSystem::VacuumPipe> VPipeInB;
  std::shared_ptr<beamlineSystem::GuideLine> BendInB;

  std::shared_ptr<constructSystem::VacuumPipe> VPipeInC;
  std::shared_ptr<beamlineSystem::GuideLine> GuideInC;
  
  /// Bunker Insert
  std::shared_ptr<essSystem::CompBInsert> BInsert;
  std::shared_ptr<beamlineSystem::GuideLine> FocusWall;
  std::shared_ptr<essSystem::CompBInsert> CInsert;
  std::shared_ptr<beamlineSystem::GuideLine> FocusShutter;

  /// Structure Up to the First Chopper I  Pit

  std::shared_ptr<constructSystem::ChopperPit> PitA;
  std::shared_ptr<constructSystem::HoleShape> PitACutBack;

  std::shared_ptr<constructSystem::LineShield> ShieldAB;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutA;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutA;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutB;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutB;

  /// Structure Up to the First Chopper II  Pit

  std::shared_ptr<constructSystem::ChopperPit> PitC;
  std::shared_ptr<constructSystem::HoleShape> PitCCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitCCutBack;

  std::shared_ptr<constructSystem::LineShield> ShieldC;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutC;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutC;

  /// Structure Up to the First Chopper III  Pit

  std::shared_ptr<constructSystem::ChopperPit> PitD;
  std::shared_ptr<constructSystem::HoleShape> PitDCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitDCutBack;

  std::shared_ptr<constructSystem::LineShield> ShieldD;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutD;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutD;
  
  void setBeamAxis(const FuncDataBase&,const GuideItem&,const bool);
    
 public:
  
  SKADI(const std::string&);
  SKADI(const SKADI&);
  SKADI& operator=(const SKADI&);
  ~SKADI();
  
  void build(Simulation&,const GuideItem&,const Bunker&,const int);
  
};

}

#endif

