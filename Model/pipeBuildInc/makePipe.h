/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   pipeInc/makePipe.h
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
#ifndef pipeSystem_makePipe_h
#define pipeSystem_makePipe_h


/*!
  \namespace pipeSystem
  \brief simple pipemodl
  \version 1.0
  \date May 2015
  \author S. Ansell
*/

namespace constructSystem
{
  class ChopperPit;
  class DiskChopper;
  class ChopperUnit;
  class ChopperHousing;
  class VacuumPipe;
  class HoleShape;
}

namespace beamlineSystem
{
  class GuideLine;
}

namespace pipeSystem
{
  class pipeTube;
  /*!
    \class makePipe
    \version 1.0
    \author S. Ansell
    \date May 2015
    \brief General pipe building system
  */

  class makePipe
  {
  private:


    std::shared_ptr<pipeSystem::pipeTube> ATube;   ///< pre-tube
    std::shared_ptr<pipeSystem::pipeTube> BTube;   ///< Main tube
    std::shared_ptr<pipeSystem::pipeTube> CTube;   ///< collector tube
    
    std::shared_ptr<constructSystem::ChopperUnit> ChopperA;
    std::shared_ptr<constructSystem::DiskChopper> BandADisk;
    
    std::shared_ptr<constructSystem::VacuumPipe> PipeA;
    std::shared_ptr<beamlineSystem::GuideLine> GuideA;

    std::shared_ptr<constructSystem::VacuumPipe> PipeB;
    std::shared_ptr<beamlineSystem::GuideLine> GuideB;

    std::shared_ptr<constructSystem::VacuumPipe> PipeC;
    std::shared_ptr<beamlineSystem::GuideLine> GuideC;

    std::shared_ptr<constructSystem::ChopperPit> PitA;
    std::shared_ptr<constructSystem::HoleShape> CutFrontA;
    std::shared_ptr<constructSystem::HoleShape> CutBackA;
    
    
  public:
    
    makePipe();
    makePipe(const makePipe&);
    makePipe& operator=(const makePipe&);
    ~makePipe();
    
    void build(Simulation*,const mainSystem::inputParam&);
    
  };

}

#endif
