/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   ESSBeam/trexInc/TREX.h
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
#ifndef essSystem_TREX_h
#define essSystem_TREX_h

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



class TREX : public attachSystem::CopiedComp
{
 private:

  const size_t nC;
  const size_t nF;
  
  /// Stop at [0:Complete / 1:Mono Wall / 2:Inner Bunker / 3:Outer Bunker ]
  int stopPoint;  

  /// Main Beam Axis
  std::shared_ptr<attachSystem::FixedOffset> trexAxis;
  
  /// Monolith guideline
  std::shared_ptr<beamlineSystem::GuideLine> FocusMono;

  /// Bridge guide in the light shutter
  std::shared_ptr<constructSystem::VacuumPipe> VPipeBridge;
  std::shared_ptr<beamlineSystem::GuideLine> FocusBridge;

  /// First Bender inside Bunker
  std::shared_ptr<constructSystem::VacuumPipe> VPipeInA;
  std::shared_ptr<beamlineSystem::GuideLine> BendInA;

  std::shared_ptr<constructSystem::VacuumPipe> VPipeInB;
  std::shared_ptr<beamlineSystem::GuideLine> BendInB;

  std::shared_ptr<constructSystem::VacuumPipe> VPipeInC;
  std::shared_ptr<beamlineSystem::GuideLine> BendInC;

  std::shared_ptr<constructSystem::VacuumPipe> VPipeInD;
  std::shared_ptr<beamlineSystem::GuideLine> BendInD;

  /// !! Heavy Shutter !!
  std::shared_ptr<constructSystem::VacuumPipe> VPipeInE;
  std::shared_ptr<beamlineSystem::GuideLine> BendInE;
  
  /// Bunker Insert
  //std::shared_ptr<essSystem::BunkerInsert> BInsert;
  std::shared_ptr<essSystem::CompBInsert> BInsert;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeWall;
  std::shared_ptr<beamlineSystem::GuideLine> FocusWall;

  /// Structure Up to the First Chopper Pit
  std::shared_ptr<constructSystem::ChopperPit> PitA;
  std::shared_ptr<constructSystem::HoleShape> PitACutFront;
  std::shared_ptr<constructSystem::HoleShape> PitACutBack;
  std::shared_ptr<constructSystem::LineShield> ShieldA;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutA;
  std::shared_ptr<beamlineSystem::GuideLine> BendOutA;

  /// Structure Up to the Second Chopper Pit
  std::shared_ptr<constructSystem::ChopperPit> PitB;
  std::shared_ptr<constructSystem::HoleShape> PitBCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitBCutBack;
  std::shared_ptr<constructSystem::LineShield> ShieldB;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutB1;
  std::shared_ptr<beamlineSystem::GuideLine> BendOutB1;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutB2;
  std::shared_ptr<beamlineSystem::GuideLine> BendOutB2;

  /// Structur up to the T0 chopper position
  std::shared_ptr<constructSystem::ChopperPit> PitC;
  std::shared_ptr<constructSystem::HoleShape> PitCCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitCCutBack;
  std::array<std::shared_ptr<constructSystem::LineShield>,10> ShieldCs;
  std::array<std::shared_ptr<constructSystem::VacuumPipe>,10>
  VPipeOutCs;
  std::array<std::shared_ptr<beamlineSystem::GuideLine>,10> BendOutCs;

  /// Last part of the curve part
  std::shared_ptr<constructSystem::LineShield> ShieldD;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutD;
  std::shared_ptr<beamlineSystem::GuideLine> BendOutD;

  /// First Straight Beamline up to the next ChopperPit
  std::shared_ptr<constructSystem::ChopperPit> PitE;
  std::shared_ptr<constructSystem::HoleShape> PitECutFront;
  std::shared_ptr<constructSystem::HoleShape> PitECutBack;
  std::shared_ptr<constructSystem::LineShield> ShieldE;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutE;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutE;

  std::shared_ptr<constructSystem::ChopperPit> PitF;
  std::shared_ptr<constructSystem::HoleShape> PitFCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitFCutBack;
  std::shared_ptr<constructSystem::LineShield> ShieldF;
  std::array<std::shared_ptr<constructSystem::VacuumPipe>,8>
  VPipeOutFs;
  std::array<std::shared_ptr<beamlineSystem::GuideLine>,8> GuideOutFs;

  std::shared_ptr<constructSystem::ChopperPit> PitG;
  std::shared_ptr<constructSystem::HoleShape> PitGCutFront;
  std::shared_ptr<constructSystem::HoleShape> PitGCutBack;
  std::shared_ptr<constructSystem::LineShield> ShieldG;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutG;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutG;

  std::shared_ptr<constructSystem::LineShield> ShieldH;
  std::shared_ptr<constructSystem::VacuumPipe> VPipeOutH;
  std::shared_ptr<beamlineSystem::GuideLine> GuideOutH;
  
  
  void setBeamAxis(const FuncDataBase&,const GuideItem&,
		   const bool);
    
 public:
  
  TREX(const std::string&);
  TREX(const TREX&);
  TREX& operator=(const TREX&);
  ~TREX();
  
  void build(Simulation&,const GuideItem&,const Bunker&,const int);
  
};

}

#endif

