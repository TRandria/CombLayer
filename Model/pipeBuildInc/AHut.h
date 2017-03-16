#ifndef pipeSystem_AHut_h
#define pipeSystem_AHut_h

class Simulation;

namespace pipeSystem
{
class AHut :
  public attachSystem::FixedOffsetGroup,
  public attachSystem::ContainedComp,
  public attachSystem::CellMap
  
{
 private:
  
  const int hutIndex;           ///< Index of surface offset
  int cellIndex;                ///< Cell index  


  double voidHeight;            ///< void height [top only]
  double voidWidth;             ///< void width [total]
  double voidDepth;             ///< void depth [low only]
  double voidLength;            ///< void length [total]

  double L1Front;               ///< Front extension
  double L1LeftWall;            ///< Left wall
  double L1RightWall;           ///< Right wall
  double L1Roof;                ///< Roof
  double L1Floor;               ///< Token floor depth
  double L1Back;                ///< Back steel extension

  double L2Front;               ///< Front extension
  double L2LeftWall;            ///< Left wall
  double L2RightWall;           ///< Right wall
  double L2Roof;                ///< Roof
  double L2Floor;               ///< Token floor depth
  double L2Back;                ///< Back length

  double L3Front;               ///< Front extension
  double L3LeftWall;            ///< Left wall
  double L3RightWall;           ///< Right wall
  double L3Roof;                ///< Roof
  double L3Floor;               ///< Token floor depth
  double L3Back;                ///< Back length
  
  int L1Mat;                  ///< First layer material 
  int L2Mat;                ///< Second layer material
  int L3Mat;                ///< Third layer material

  double pipeRadius;
  double pipeLength;
  double L1PipeThick;
  double L2PipeThick;	  
  int L1PipeMat; 
  int L2PipeMat;

  void populate(const FuncDataBase&);
  void createUnitVector(const attachSystem::FixedComp&,const long int);
  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();

 public:

  AHut(const std::string&);
  AHut(const AHut&);
  AHut& operator=(const AHut&);
  virtual ~AHut();

  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};
}

#endif
 
