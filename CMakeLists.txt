cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-fPIC -Wconversion -W -Wall -Wextra -Wno-comment -fexceptions -std=c++11 -O2 ")
set(CMAKE_CXX_RELEASE_FLAGS "-fPIC -Wconversion -W -Wall -Wextra -Wno-comment -fexceptions -std=c++11 -O2 ")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

set(BOOST_ROOT "/usr/local")
FIND_PACKAGE(Boost ${Boost_VERSION} REQUIRED COMPONENTS regex system filesystem )

if(Boost_FOUND)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
endif()
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/beamlineInc")
include_directories("${PROJECT_SOURCE_DIR}/globalInc")
include_directories("${PROJECT_SOURCE_DIR}/instrumentInc")
include_directories("${PROJECT_SOURCE_DIR}/scatMatInc")
include_directories("${PROJECT_SOURCE_DIR}/specialInc")
include_directories("${PROJECT_SOURCE_DIR}/transportInc")
include_directories("${PROJECT_SOURCE_DIR}/testInclude")
include_directories("${PROJECT_SOURCE_DIR}/System/attachCompInc")
include_directories("${PROJECT_SOURCE_DIR}/System/compWeightsInc")
include_directories("${PROJECT_SOURCE_DIR}/System/constructInc")
include_directories("${PROJECT_SOURCE_DIR}/System/crystalInc")
include_directories("${PROJECT_SOURCE_DIR}/System/endfInc")
include_directories("${PROJECT_SOURCE_DIR}/System/funcBaseInc")
include_directories("${PROJECT_SOURCE_DIR}/System/geomInc")
include_directories("${PROJECT_SOURCE_DIR}/System/inputInc")
include_directories("${PROJECT_SOURCE_DIR}/System/logInc")
include_directories("${PROJECT_SOURCE_DIR}/System/md5Inc")
include_directories("${PROJECT_SOURCE_DIR}/System/mersenneInc")
include_directories("${PROJECT_SOURCE_DIR}/System/monteInc")
include_directories("${PROJECT_SOURCE_DIR}/System/physicsInc")
include_directories("${PROJECT_SOURCE_DIR}/System/polyInc")
include_directories("${PROJECT_SOURCE_DIR}/System/processInc")
include_directories("${PROJECT_SOURCE_DIR}/System/simMCInc")
include_directories("${PROJECT_SOURCE_DIR}/System/sourceInc")
include_directories("${PROJECT_SOURCE_DIR}/System/supportInc")
include_directories("${PROJECT_SOURCE_DIR}/System/tallyInc")
include_directories("${PROJECT_SOURCE_DIR}/System/visitInc")
include_directories("${PROJECT_SOURCE_DIR}/System/weightsInc")
include_directories("${PROJECT_SOURCE_DIR}/System/workInc")
include_directories("${PROJECT_SOURCE_DIR}/System/worldInc")
include_directories("${PROJECT_SOURCE_DIR}/System/xmlInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/bibBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/bnctBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/buildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/chipInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/cuBlockInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/d4cModelInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/delftInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/epbBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/essBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/essLinacInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/filterInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/gammaBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/imatInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/lensModelInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/moderatorInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/muonInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/photonInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/pipeBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/sinbadBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/singleItemBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/snsBuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/t1BuildInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/t1EngineerInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/t1UpgradeInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/t3ModelInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/zoomInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/beerInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/bifrostInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/commonVarInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/cspecInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/dreamInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/estiaInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/freiaInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/lokiInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/longLokiInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/magicInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/miraclesInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/nmxInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/nnbarInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/odinInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortDreamInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortNmxInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortOdinInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/simpleItemInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/skadiInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/testBeamInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/trexInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/vespaInc")
include_directories("${PROJECT_SOURCE_DIR}/Model/ESSBeam/vorInc")
## END INCLUDES 

## GLOBS 
file(GLOB input "${PROJECT_SOURCE_DIR}/System/input/*.cxx")
add_library(libinput SHARED ${input})
file(GLOB t1Upgrade "${PROJECT_SOURCE_DIR}/Model/t1Upgrade/*.cxx")
add_library(libt1Upgrade SHARED ${t1Upgrade})
file(GLOB vespa "${PROJECT_SOURCE_DIR}/Model/ESSBeam/vespa/*.cxx")
add_library(libvespa SHARED ${vespa})
file(GLOB bnctBuild "${PROJECT_SOURCE_DIR}/Model/bnctBuild/*.cxx")
add_library(libbnctBuild SHARED ${bnctBuild})
file(GLOB commonVar "${PROJECT_SOURCE_DIR}/Model/ESSBeam/commonVar/*.cxx")
add_library(libcommonVar SHARED ${commonVar})
file(GLOB cspec "${PROJECT_SOURCE_DIR}/Model/ESSBeam/cspec/*.cxx")
add_library(libcspec SHARED ${cspec})
file(GLOB t1Engineer "${PROJECT_SOURCE_DIR}/Model/t1Engineer/*.cxx")
add_library(libt1Engineer SHARED ${t1Engineer})
file(GLOB magic "${PROJECT_SOURCE_DIR}/Model/ESSBeam/magic/*.cxx")
add_library(libmagic SHARED ${magic})
file(GLOB imat "${PROJECT_SOURCE_DIR}/Model/imat/*.cxx")
add_library(libimat SHARED ${imat})
file(GLOB miracles "${PROJECT_SOURCE_DIR}/Model/ESSBeam/miracles/*.cxx")
add_library(libmiracles SHARED ${miracles})
file(GLOB estia "${PROJECT_SOURCE_DIR}/Model/ESSBeam/estia/*.cxx")
add_library(libestia SHARED ${estia})
file(GLOB snsBuild "${PROJECT_SOURCE_DIR}/Model/snsBuild/*.cxx")
add_library(libsnsBuild SHARED ${snsBuild})
file(GLOB testBeam "${PROJECT_SOURCE_DIR}/Model/ESSBeam/testBeam/*.cxx")
add_library(libtestBeam SHARED ${testBeam})
file(GLOB odin "${PROJECT_SOURCE_DIR}/Model/ESSBeam/odin/*.cxx")
add_library(libodin SHARED ${odin})
file(GLOB source "${PROJECT_SOURCE_DIR}/System/source/*.cxx")
add_library(libsource SHARED ${source})
file(GLOB transport "${PROJECT_SOURCE_DIR}/transport/*.cxx")
add_library(libtransport SHARED ${transport})
file(GLOB simpleItem "${PROJECT_SOURCE_DIR}/Model/ESSBeam/simpleItem/*.cxx")
add_library(libsimpleItem SHARED ${simpleItem})
file(GLOB weights "${PROJECT_SOURCE_DIR}/System/weights/*.cxx")
add_library(libweights SHARED ${weights})
file(GLOB visit "${PROJECT_SOURCE_DIR}/System/visit/*.cxx")
add_library(libvisit SHARED ${visit})
file(GLOB cuBlock "${PROJECT_SOURCE_DIR}/Model/cuBlock/*.cxx")
add_library(libcuBlock SHARED ${cuBlock})
file(GLOB longLoki "${PROJECT_SOURCE_DIR}/Model/ESSBeam/longLoki/*.cxx")
add_library(liblongLoki SHARED ${longLoki})
file(GLOB muon "${PROJECT_SOURCE_DIR}/Model/muon/*.cxx")
add_library(libmuon SHARED ${muon})
file(GLOB beamline "${PROJECT_SOURCE_DIR}/beamline/*.cxx")
add_library(libbeamline SHARED ${beamline})
file(GLOB nnbar "${PROJECT_SOURCE_DIR}/Model/ESSBeam/nnbar/*.cxx")
add_library(libnnbar SHARED ${nnbar})
file(GLOB physics "${PROJECT_SOURCE_DIR}/System/physics/*.cxx")
add_library(libphysics SHARED ${physics})
file(GLOB gammaBuild "${PROJECT_SOURCE_DIR}/Model/gammaBuild/*.cxx")
add_library(libgammaBuild SHARED ${gammaBuild})
file(GLOB t1Build "${PROJECT_SOURCE_DIR}/Model/t1Build/*.cxx")
add_library(libt1Build SHARED ${t1Build})
file(GLOB essLinac "${PROJECT_SOURCE_DIR}/Model/essLinac/*.cxx")
add_library(libessLinac SHARED ${essLinac})
file(GLOB loki "${PROJECT_SOURCE_DIR}/Model/ESSBeam/loki/*.cxx")
add_library(libloki SHARED ${loki})
file(GLOB filter "${PROJECT_SOURCE_DIR}/Model/filter/*.cxx")
add_library(libfilter SHARED ${filter})
file(GLOB d4cModel "${PROJECT_SOURCE_DIR}/Model/d4cModel/*.cxx")
add_library(libd4cModel SHARED ${d4cModel})
file(GLOB instrument "${PROJECT_SOURCE_DIR}/instrument/*.cxx")
add_library(libinstrument SHARED ${instrument})
file(GLOB work "${PROJECT_SOURCE_DIR}/System/work/*.cxx")
add_library(libwork SHARED ${work})
file(GLOB essBuild "${PROJECT_SOURCE_DIR}/Model/essBuild/*.cxx")
add_library(libessBuild SHARED ${essBuild})
file(GLOB build "${PROJECT_SOURCE_DIR}/Model/build/*.cxx")
add_library(libbuild SHARED ${build})
file(GLOB epbBuild "${PROJECT_SOURCE_DIR}/Model/epbBuild/*.cxx")
add_library(libepbBuild SHARED ${epbBuild})
file(GLOB shortDream "${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortDream/*.cxx")
add_library(libshortDream SHARED ${shortDream})
file(GLOB bifrost "${PROJECT_SOURCE_DIR}/Model/ESSBeam/bifrost/*.cxx")
add_library(libbifrost SHARED ${bifrost})
file(GLOB scatMat "${PROJECT_SOURCE_DIR}/scatMat/*.cxx")
add_library(libscatMat SHARED ${scatMat})
file(GLOB sinbadBuild "${PROJECT_SOURCE_DIR}/Model/sinbadBuild/*.cxx")
add_library(libsinbadBuild SHARED ${sinbadBuild})
file(GLOB tally "${PROJECT_SOURCE_DIR}/System/tally/*.cxx")
add_library(libtally SHARED ${tally})
file(GLOB test "${PROJECT_SOURCE_DIR}/test/*.cxx")
add_library(libtest SHARED ${test})
file(GLOB trex "${PROJECT_SOURCE_DIR}/Model/ESSBeam/trex/*.cxx")
add_library(libtrex SHARED ${trex})
file(GLOB bibBuild "${PROJECT_SOURCE_DIR}/Model/bibBuild/*.cxx")
add_library(libbibBuild SHARED ${bibBuild})
file(GLOB shortOdin "${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortOdin/*.cxx")
add_library(libshortOdin SHARED ${shortOdin})
file(GLOB freia "${PROJECT_SOURCE_DIR}/Model/ESSBeam/freia/*.cxx")
add_library(libfreia SHARED ${freia})
file(GLOB delft "${PROJECT_SOURCE_DIR}/Model/delft/*.cxx")
add_library(libdelft SHARED ${delft})
file(GLOB t3Model "${PROJECT_SOURCE_DIR}/Model/t3Model/*.cxx")
add_library(libt3Model SHARED ${t3Model})
file(GLOB special "${PROJECT_SOURCE_DIR}/special/*.cxx")
add_library(libspecial SHARED ${special})
file(GLOB construct "${PROJECT_SOURCE_DIR}/System/construct/*.cxx")
add_library(libconstruct SHARED ${construct})
file(GLOB dream "${PROJECT_SOURCE_DIR}/Model/ESSBeam/dream/*.cxx")
add_library(libdream SHARED ${dream})
file(GLOB xml "${PROJECT_SOURCE_DIR}/System/xml/*.cxx")
add_library(libxml SHARED ${xml})
file(GLOB geometry "${PROJECT_SOURCE_DIR}/System/geometry/*.cxx")
add_library(libgeometry SHARED ${geometry})
file(GLOB attachComp "${PROJECT_SOURCE_DIR}/System/attachComp/*.cxx")
add_library(libattachComp SHARED ${attachComp})
file(GLOB monte "${PROJECT_SOURCE_DIR}/System/monte/*.cxx")
add_library(libmonte SHARED ${monte})
file(GLOB src "${PROJECT_SOURCE_DIR}/src/*.cxx")
add_library(libsrc SHARED ${src})
file(GLOB nmx "${PROJECT_SOURCE_DIR}/Model/ESSBeam/nmx/*.cxx")
add_library(libnmx SHARED ${nmx})
file(GLOB process "${PROJECT_SOURCE_DIR}/System/process/*.cxx")
add_library(libprocess SHARED ${process})
file(GLOB vor "${PROJECT_SOURCE_DIR}/Model/ESSBeam/vor/*.cxx")
add_library(libvor SHARED ${vor})
file(GLOB moderator "${PROJECT_SOURCE_DIR}/Model/moderator/*.cxx")
add_library(libmoderator SHARED ${moderator})
file(GLOB chip "${PROJECT_SOURCE_DIR}/Model/chip/*.cxx")
add_library(libchip SHARED ${chip})
file(GLOB skadi "${PROJECT_SOURCE_DIR}/Model/ESSBeam/skadi/*.cxx")
add_library(libskadi SHARED ${skadi})
file(GLOB pipeBuild "${PROJECT_SOURCE_DIR}/Model/pipeBuild/*.cxx")
add_library(libpipeBuild SHARED ${pipeBuild})
file(GLOB mersenne "${PROJECT_SOURCE_DIR}/System/mersenne/*.cxx")
add_library(libmersenne SHARED ${mersenne})
file(GLOB md5 "${PROJECT_SOURCE_DIR}/System/md5/*.cxx")
add_library(libmd5 SHARED ${md5})
file(GLOB endf "${PROJECT_SOURCE_DIR}/System/endf/*.cxx")
add_library(libendf SHARED ${endf})
file(GLOB lensModel "${PROJECT_SOURCE_DIR}/Model/lensModel/*.cxx")
add_library(liblensModel SHARED ${lensModel})
file(GLOB support "${PROJECT_SOURCE_DIR}/System/support/*.cxx")
add_library(libsupport SHARED ${support})
file(GLOB simMC "${PROJECT_SOURCE_DIR}/System/simMC/*.cxx")
add_library(libsimMC SHARED ${simMC})
file(GLOB world "${PROJECT_SOURCE_DIR}/System/world/*.cxx")
add_library(libworld SHARED ${world})
file(GLOB shortNmx "${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortNmx/*.cxx")
add_library(libshortNmx SHARED ${shortNmx})
file(GLOB beer "${PROJECT_SOURCE_DIR}/Model/ESSBeam/beer/*.cxx")
add_library(libbeer SHARED ${beer})
file(GLOB funcBase "${PROJECT_SOURCE_DIR}/System/funcBase/*.cxx")
add_library(libfuncBase SHARED ${funcBase})
file(GLOB singleItemBuild "${PROJECT_SOURCE_DIR}/Model/singleItemBuild/*.cxx")
add_library(libsingleItemBuild SHARED ${singleItemBuild})
file(GLOB crystal "${PROJECT_SOURCE_DIR}/System/crystal/*.cxx")
add_library(libcrystal SHARED ${crystal})
file(GLOB log "${PROJECT_SOURCE_DIR}/System/log/*.cxx")
add_library(liblog SHARED ${log})
file(GLOB poly "${PROJECT_SOURCE_DIR}/System/poly/*.cxx")
add_library(libpoly SHARED ${poly})
file(GLOB global "${PROJECT_SOURCE_DIR}/global/*.cxx")
add_library(libglobal SHARED ${global})
file(GLOB zoom "${PROJECT_SOURCE_DIR}/Model/zoom/*.cxx")
add_library(libzoom SHARED ${zoom})
file(GLOB compWeights "${PROJECT_SOURCE_DIR}/System/compWeights/*.cxx")
add_library(libcompWeights SHARED ${compWeights})
file(GLOB photon "${PROJECT_SOURCE_DIR}/Model/photon/*.cxx")
add_library(libphoton SHARED ${photon})
## END GLOBS 

## EXECUTABLES 
add_executable(fullBuild ${PROJECT_SOURCE_DIR}/Main/fullBuild)
target_link_libraries(fullBuild  libbuild)
target_link_libraries(fullBuild  libvisit)
target_link_libraries(fullBuild  libchip)
target_link_libraries(fullBuild  libmoderator)
target_link_libraries(fullBuild  libbuild)
target_link_libraries(fullBuild  libzoom)
target_link_libraries(fullBuild  libimat)
target_link_libraries(fullBuild  libsrc)
target_link_libraries(fullBuild  libsimMC)
target_link_libraries(fullBuild  libphysics)
target_link_libraries(fullBuild  libconstruct)
target_link_libraries(fullBuild  libtransport)
target_link_libraries(fullBuild  libscatMat)
target_link_libraries(fullBuild  libcrystal)
target_link_libraries(fullBuild  libendf)
target_link_libraries(fullBuild  libinput)
target_link_libraries(fullBuild  libsource)
target_link_libraries(fullBuild  libmonte)
target_link_libraries(fullBuild  libfuncBase)
target_link_libraries(fullBuild  liblog)
target_link_libraries(fullBuild  libprocess)
target_link_libraries(fullBuild  libtally)
target_link_libraries(fullBuild  libworld)
target_link_libraries(fullBuild  libmonte)
target_link_libraries(fullBuild  libgeometry)
target_link_libraries(fullBuild  libmersenne)
target_link_libraries(fullBuild  libsrc)
target_link_libraries(fullBuild  libwork)
target_link_libraries(fullBuild  libxml)
target_link_libraries(fullBuild  libpoly)
target_link_libraries(fullBuild  libsupport)
target_link_libraries(fullBuild  libweights)
target_link_libraries(fullBuild  libmd5)
target_link_libraries(fullBuild  libglobal)
target_link_libraries(fullBuild  libattachComp)
target_link_libraries(fullBuild  libvisit)
target_link_libraries(fullBuild ${Boost_LIBRARIES})
target_link_libraries(fullBuild stdc++)
target_link_libraries(fullBuild gsl)
target_link_libraries(fullBuild gslcblas)
target_link_libraries(fullBuild m)
add_executable(ess ${PROJECT_SOURCE_DIR}/Main/ess)
target_link_libraries(ess  libessBuild)
target_link_libraries(ess  libvisit)
target_link_libraries(ess  libsrc)
target_link_libraries(ess  libsimMC)
target_link_libraries(ess  libbeamline)
target_link_libraries(ess  libphysics)
target_link_libraries(ess  libsupport)
target_link_libraries(ess  libinput)
target_link_libraries(ess  libinstrument)
target_link_libraries(ess  libsource)
target_link_libraries(ess  libmonte)
target_link_libraries(ess  libfuncBase)
target_link_libraries(ess  liblog)
target_link_libraries(ess  libtally)
target_link_libraries(ess  libconstruct)
target_link_libraries(ess  libcrystal)
target_link_libraries(ess  libtransport)
target_link_libraries(ess  libscatMat)
target_link_libraries(ess  libmd5)
target_link_libraries(ess  libendf)
target_link_libraries(ess  libprocess)
target_link_libraries(ess  libworld)
target_link_libraries(ess  libwork)
target_link_libraries(ess  libmonte)
target_link_libraries(ess  libgeometry)
target_link_libraries(ess  libmersenne)
target_link_libraries(ess  libsrc)
target_link_libraries(ess  libxml)
target_link_libraries(ess  libpoly)
target_link_libraries(ess  libweights)
target_link_libraries(ess  libglobal)
target_link_libraries(ess  libattachComp)
target_link_libraries(ess  libvisit)
target_link_libraries(ess  libbeer)
target_link_libraries(ess  libbifrost)
target_link_libraries(ess  libcspec)
target_link_libraries(ess  libdream)
target_link_libraries(ess  libestia)
target_link_libraries(ess  libfreia)
target_link_libraries(ess  libloki)
target_link_libraries(ess  libmagic)
target_link_libraries(ess  libmiracles)
target_link_libraries(ess  libnmx)
target_link_libraries(ess  libnnbar)
target_link_libraries(ess  libodin)
target_link_libraries(ess  libtestBeam)
target_link_libraries(ess  libtrex)
target_link_libraries(ess  libvor)
target_link_libraries(ess  libvespa)
target_link_libraries(ess  libshortDream)
target_link_libraries(ess  libshortNmx)
target_link_libraries(ess  libshortOdin)
target_link_libraries(ess  liblongLoki)
target_link_libraries(ess  libcommonVar)
target_link_libraries(ess  libsimpleItem)
target_link_libraries(ess  libskadi)
target_link_libraries(ess ${Boost_LIBRARIES})
target_link_libraries(ess stdc++)
target_link_libraries(ess gsl)
target_link_libraries(ess gslcblas)
target_link_libraries(ess m)
add_executable(muBeam ${PROJECT_SOURCE_DIR}/Main/muBeam)
target_link_libraries(muBeam  libmuon)
target_link_libraries(muBeam  libvisit)
target_link_libraries(muBeam  libsrc)
target_link_libraries(muBeam  libphysics)
target_link_libraries(muBeam  libsimMC)
target_link_libraries(muBeam  libinput)
target_link_libraries(muBeam  libsource)
target_link_libraries(muBeam  libmonte)
target_link_libraries(muBeam  libfuncBase)
target_link_libraries(muBeam  liblog)
target_link_libraries(muBeam  libtally)
target_link_libraries(muBeam  libconstruct)
target_link_libraries(muBeam  libcrystal)
target_link_libraries(muBeam  libtransport)
target_link_libraries(muBeam  libscatMat)
target_link_libraries(muBeam  libmd5)
target_link_libraries(muBeam  libendf)
target_link_libraries(muBeam  libprocess)
target_link_libraries(muBeam  libworld)
target_link_libraries(muBeam  libwork)
target_link_libraries(muBeam  libmonte)
target_link_libraries(muBeam  libgeometry)
target_link_libraries(muBeam  libmersenne)
target_link_libraries(muBeam  libsrc)
target_link_libraries(muBeam  libxml)
target_link_libraries(muBeam  libpoly)
target_link_libraries(muBeam  libsupport)
target_link_libraries(muBeam  libweights)
target_link_libraries(muBeam  libglobal)
target_link_libraries(muBeam  libattachComp)
target_link_libraries(muBeam  libvisit)
target_link_libraries(muBeam ${Boost_LIBRARIES})
target_link_libraries(muBeam stdc++)
target_link_libraries(muBeam gsl)
target_link_libraries(muBeam gslcblas)
target_link_libraries(muBeam m)
add_executable(pipe ${PROJECT_SOURCE_DIR}/Main/pipe)
target_link_libraries(pipe  libpipeBuild)
target_link_libraries(pipe  libvisit)
target_link_libraries(pipe  libsrc)
target_link_libraries(pipe  libsimMC)
target_link_libraries(pipe  libconstruct)
target_link_libraries(pipe  libphysics)
target_link_libraries(pipe  libinput)
target_link_libraries(pipe  libprocess)
target_link_libraries(pipe  libtransport)
target_link_libraries(pipe  libscatMat)
target_link_libraries(pipe  libendf)
target_link_libraries(pipe  libcrystal)
target_link_libraries(pipe  libsource)
target_link_libraries(pipe  libmonte)
target_link_libraries(pipe  libfuncBase)
target_link_libraries(pipe  liblog)
target_link_libraries(pipe  libmonte)
target_link_libraries(pipe  libtally)
target_link_libraries(pipe  libgeometry)
target_link_libraries(pipe  libmersenne)
target_link_libraries(pipe  libsrc)
target_link_libraries(pipe  libworld)
target_link_libraries(pipe  libattachComp)
target_link_libraries(pipe  libbeamline)
target_link_libraries(pipe  libsupport)
target_link_libraries(pipe  libcommonVar)
target_link_libraries(pipe  libwork)
target_link_libraries(pipe  libxml)
target_link_libraries(pipe  libpoly)
target_link_libraries(pipe  libsupport)
target_link_libraries(pipe  libweights)
target_link_libraries(pipe  libmd5)
target_link_libraries(pipe  libglobal)
target_link_libraries(pipe  libattachComp)
target_link_libraries(pipe  libvisit)
target_link_libraries(pipe  libpoly)
target_link_libraries(pipe ${Boost_LIBRARIES})
target_link_libraries(pipe stdc++)
target_link_libraries(pipe gsl)
target_link_libraries(pipe gslcblas)
target_link_libraries(pipe m)
add_executable(photonMod2 ${PROJECT_SOURCE_DIR}/Main/photonMod2)
target_link_libraries(photonMod2  libphoton)
target_link_libraries(photonMod2  libvisit)
target_link_libraries(photonMod2  libsrc)
target_link_libraries(photonMod2  libsimMC)
target_link_libraries(photonMod2  libconstruct)
target_link_libraries(photonMod2  libphysics)
target_link_libraries(photonMod2  libinput)
target_link_libraries(photonMod2  libprocess)
target_link_libraries(photonMod2  libtransport)
target_link_libraries(photonMod2  libscatMat)
target_link_libraries(photonMod2  libendf)
target_link_libraries(photonMod2  libcrystal)
target_link_libraries(photonMod2  libsource)
target_link_libraries(photonMod2  libmonte)
target_link_libraries(photonMod2  libfuncBase)
target_link_libraries(photonMod2  liblog)
target_link_libraries(photonMod2  libmonte)
target_link_libraries(photonMod2  libtally)
target_link_libraries(photonMod2  libgeometry)
target_link_libraries(photonMod2  libmersenne)
target_link_libraries(photonMod2  libsrc)
target_link_libraries(photonMod2  libworld)
target_link_libraries(photonMod2  libwork)
target_link_libraries(photonMod2  libxml)
target_link_libraries(photonMod2  libpoly)
target_link_libraries(photonMod2  libsupport)
target_link_libraries(photonMod2  libweights)
target_link_libraries(photonMod2  libmd5)
target_link_libraries(photonMod2  libglobal)
target_link_libraries(photonMod2  libattachComp)
target_link_libraries(photonMod2  libvisit)
target_link_libraries(photonMod2  libpoly)
target_link_libraries(photonMod2 ${Boost_LIBRARIES})
target_link_libraries(photonMod2 stdc++)
target_link_libraries(photonMod2 gsl)
target_link_libraries(photonMod2 gslcblas)
target_link_libraries(photonMod2 m)
add_executable(t1Real ${PROJECT_SOURCE_DIR}/Main/t1Real)
target_link_libraries(t1Real  libt1Build)
target_link_libraries(t1Real  libimat)
target_link_libraries(t1Real  libchip)
target_link_libraries(t1Real  libbuild)
target_link_libraries(t1Real  libvisit)
target_link_libraries(t1Real  libmoderator)
target_link_libraries(t1Real  libzoom)
target_link_libraries(t1Real  libsrc)
target_link_libraries(t1Real  libsimMC)
target_link_libraries(t1Real  libconstruct)
target_link_libraries(t1Real  libcrystal)
target_link_libraries(t1Real  libtransport)
target_link_libraries(t1Real  libscatMat)
target_link_libraries(t1Real  libendf)
target_link_libraries(t1Real  libphysics)
target_link_libraries(t1Real  libinput)
target_link_libraries(t1Real  libprocess)
target_link_libraries(t1Real  libsource)
target_link_libraries(t1Real  libmonte)
target_link_libraries(t1Real  libfuncBase)
target_link_libraries(t1Real  liblog)
target_link_libraries(t1Real  libmonte)
target_link_libraries(t1Real  libtally)
target_link_libraries(t1Real  libgeometry)
target_link_libraries(t1Real  libmersenne)
target_link_libraries(t1Real  libsrc)
target_link_libraries(t1Real  libworld)
target_link_libraries(t1Real  libwork)
target_link_libraries(t1Real  libxml)
target_link_libraries(t1Real  libpoly)
target_link_libraries(t1Real  libsupport)
target_link_libraries(t1Real  libweights)
target_link_libraries(t1Real  libmd5)
target_link_libraries(t1Real  libglobal)
target_link_libraries(t1Real  libattachComp)
target_link_libraries(t1Real  libvisit)
target_link_libraries(t1Real  libpoly)
target_link_libraries(t1Real ${Boost_LIBRARIES})
target_link_libraries(t1Real stdc++)
target_link_libraries(t1Real gsl)
target_link_libraries(t1Real gslcblas)
target_link_libraries(t1Real m)
add_executable(sns ${PROJECT_SOURCE_DIR}/Main/sns)
target_link_libraries(sns  libsnsBuild)
target_link_libraries(sns  libvisit)
target_link_libraries(sns  libsrc)
target_link_libraries(sns  libsimMC)
target_link_libraries(sns  libphysics)
target_link_libraries(sns  libinput)
target_link_libraries(sns  libsource)
target_link_libraries(sns  libmonte)
target_link_libraries(sns  libfuncBase)
target_link_libraries(sns  liblog)
target_link_libraries(sns  libtally)
target_link_libraries(sns  libconstruct)
target_link_libraries(sns  libcrystal)
target_link_libraries(sns  libtransport)
target_link_libraries(sns  libscatMat)
target_link_libraries(sns  libmd5)
target_link_libraries(sns  libendf)
target_link_libraries(sns  libprocess)
target_link_libraries(sns  libworld)
target_link_libraries(sns  libwork)
target_link_libraries(sns  libmonte)
target_link_libraries(sns  libgeometry)
target_link_libraries(sns  libmersenne)
target_link_libraries(sns  libsrc)
target_link_libraries(sns  libxml)
target_link_libraries(sns  libpoly)
target_link_libraries(sns  libsupport)
target_link_libraries(sns  libweights)
target_link_libraries(sns  libglobal)
target_link_libraries(sns  libattachComp)
target_link_libraries(sns  libvisit)
target_link_libraries(sns ${Boost_LIBRARIES})
target_link_libraries(sns stdc++)
target_link_libraries(sns gsl)
target_link_libraries(sns gslcblas)
target_link_libraries(sns m)
add_executable(reactor ${PROJECT_SOURCE_DIR}/Main/reactor)
target_link_libraries(reactor  libdelft)
target_link_libraries(reactor  libvisit)
target_link_libraries(reactor  libsrc)
target_link_libraries(reactor  libsimMC)
target_link_libraries(reactor  libphysics)
target_link_libraries(reactor  libinput)
target_link_libraries(reactor  libsource)
target_link_libraries(reactor  libmonte)
target_link_libraries(reactor  libfuncBase)
target_link_libraries(reactor  liblog)
target_link_libraries(reactor  libconstruct)
target_link_libraries(reactor  libtransport)
target_link_libraries(reactor  libscatMat)
target_link_libraries(reactor  libcrystal)
target_link_libraries(reactor  libendf)
target_link_libraries(reactor  libprocess)
target_link_libraries(reactor  libtally)
target_link_libraries(reactor  libworld)
target_link_libraries(reactor  libmonte)
target_link_libraries(reactor  libgeometry)
target_link_libraries(reactor  libmersenne)
target_link_libraries(reactor  libsrc)
target_link_libraries(reactor  libxml)
target_link_libraries(reactor  libpoly)
target_link_libraries(reactor  libsupport)
target_link_libraries(reactor  libweights)
target_link_libraries(reactor  libmd5)
target_link_libraries(reactor  libwork)
target_link_libraries(reactor  libglobal)
target_link_libraries(reactor  libattachComp)
target_link_libraries(reactor  libvisit)
target_link_libraries(reactor ${Boost_LIBRARIES})
target_link_libraries(reactor stdc++)
target_link_libraries(reactor gsl)
target_link_libraries(reactor gslcblas)
target_link_libraries(reactor m)
add_executable(t1MarkII ${PROJECT_SOURCE_DIR}/Main/t1MarkII)
target_link_libraries(t1MarkII  libt1Upgrade)
target_link_libraries(t1MarkII  libt1Build)
target_link_libraries(t1MarkII  libimat)
target_link_libraries(t1MarkII  libchip)
target_link_libraries(t1MarkII  libbuild)
target_link_libraries(t1MarkII  libvisit)
target_link_libraries(t1MarkII  libmoderator)
target_link_libraries(t1MarkII  libzoom)
target_link_libraries(t1MarkII  libsrc)
target_link_libraries(t1MarkII  libsimMC)
target_link_libraries(t1MarkII  libconstruct)
target_link_libraries(t1MarkII  libcrystal)
target_link_libraries(t1MarkII  libtransport)
target_link_libraries(t1MarkII  libscatMat)
target_link_libraries(t1MarkII  libendf)
target_link_libraries(t1MarkII  libphysics)
target_link_libraries(t1MarkII  libinput)
target_link_libraries(t1MarkII  libprocess)
target_link_libraries(t1MarkII  libsource)
target_link_libraries(t1MarkII  libmonte)
target_link_libraries(t1MarkII  libfuncBase)
target_link_libraries(t1MarkII  liblog)
target_link_libraries(t1MarkII  libmonte)
target_link_libraries(t1MarkII  libtally)
target_link_libraries(t1MarkII  libgeometry)
target_link_libraries(t1MarkII  libmersenne)
target_link_libraries(t1MarkII  libsrc)
target_link_libraries(t1MarkII  libworld)
target_link_libraries(t1MarkII  libwork)
target_link_libraries(t1MarkII  libxml)
target_link_libraries(t1MarkII  libpoly)
target_link_libraries(t1MarkII  libsupport)
target_link_libraries(t1MarkII  libweights)
target_link_libraries(t1MarkII  libmd5)
target_link_libraries(t1MarkII  libglobal)
target_link_libraries(t1MarkII  libattachComp)
target_link_libraries(t1MarkII  libvisit)
target_link_libraries(t1MarkII  libpoly)
target_link_libraries(t1MarkII ${Boost_LIBRARIES})
target_link_libraries(t1MarkII stdc++)
target_link_libraries(t1MarkII gsl)
target_link_libraries(t1MarkII gslcblas)
target_link_libraries(t1MarkII m)
add_executable(essBeamline ${PROJECT_SOURCE_DIR}/Main/essBeamline)
target_link_libraries(essBeamline  libessBuild)
target_link_libraries(essBeamline  libvisit)
target_link_libraries(essBeamline  libsrc)
target_link_libraries(essBeamline  libsimMC)
target_link_libraries(essBeamline  libbeamline)
target_link_libraries(essBeamline  libphysics)
target_link_libraries(essBeamline  libsupport)
target_link_libraries(essBeamline  libinput)
target_link_libraries(essBeamline  libinstrument)
target_link_libraries(essBeamline  libsource)
target_link_libraries(essBeamline  libmonte)
target_link_libraries(essBeamline  libfuncBase)
target_link_libraries(essBeamline  liblog)
target_link_libraries(essBeamline  libtally)
target_link_libraries(essBeamline  libconstruct)
target_link_libraries(essBeamline  libcrystal)
target_link_libraries(essBeamline  libtransport)
target_link_libraries(essBeamline  libscatMat)
target_link_libraries(essBeamline  libmd5)
target_link_libraries(essBeamline  libendf)
target_link_libraries(essBeamline  libprocess)
target_link_libraries(essBeamline  libworld)
target_link_libraries(essBeamline  libwork)
target_link_libraries(essBeamline  libmonte)
target_link_libraries(essBeamline  libgeometry)
target_link_libraries(essBeamline  libmersenne)
target_link_libraries(essBeamline  libsrc)
target_link_libraries(essBeamline  libxml)
target_link_libraries(essBeamline  libpoly)
target_link_libraries(essBeamline  libweights)
target_link_libraries(essBeamline  libglobal)
target_link_libraries(essBeamline  libattachComp)
target_link_libraries(essBeamline  libvisit)
target_link_libraries(essBeamline  libbeer)
target_link_libraries(essBeamline  libbifrost)
target_link_libraries(essBeamline  libcspec)
target_link_libraries(essBeamline  libdream)
target_link_libraries(essBeamline  libestia)
target_link_libraries(essBeamline  libfreia)
target_link_libraries(essBeamline  libloki)
target_link_libraries(essBeamline  libmagic)
target_link_libraries(essBeamline  libmiracles)
target_link_libraries(essBeamline  libnmx)
target_link_libraries(essBeamline  libnnbar)
target_link_libraries(essBeamline  libodin)
target_link_libraries(essBeamline  libtestBeam)
target_link_libraries(essBeamline  libtrex)
target_link_libraries(essBeamline  libvor)
target_link_libraries(essBeamline  libvespa)
target_link_libraries(essBeamline  libshortDream)
target_link_libraries(essBeamline  libshortNmx)
target_link_libraries(essBeamline  libshortOdin)
target_link_libraries(essBeamline  liblongLoki)
target_link_libraries(essBeamline  libcommonVar)
target_link_libraries(essBeamline  libsimpleItem)
target_link_libraries(essBeamline ${Boost_LIBRARIES})
target_link_libraries(essBeamline stdc++)
target_link_libraries(essBeamline gsl)
target_link_libraries(essBeamline gslcblas)
target_link_libraries(essBeamline m)
add_executable(filter ${PROJECT_SOURCE_DIR}/Main/filter)
target_link_libraries(filter  libfilter)
target_link_libraries(filter  libphoton)
target_link_libraries(filter  libvisit)
target_link_libraries(filter  libsrc)
target_link_libraries(filter  libsimMC)
target_link_libraries(filter  libconstruct)
target_link_libraries(filter  libphysics)
target_link_libraries(filter  libinput)
target_link_libraries(filter  libprocess)
target_link_libraries(filter  libtransport)
target_link_libraries(filter  libscatMat)
target_link_libraries(filter  libendf)
target_link_libraries(filter  libcrystal)
target_link_libraries(filter  libsource)
target_link_libraries(filter  libmonte)
target_link_libraries(filter  libfuncBase)
target_link_libraries(filter  liblog)
target_link_libraries(filter  libmonte)
target_link_libraries(filter  libtally)
target_link_libraries(filter  libgeometry)
target_link_libraries(filter  libmersenne)
target_link_libraries(filter  libsrc)
target_link_libraries(filter  libworld)
target_link_libraries(filter  libwork)
target_link_libraries(filter  libxml)
target_link_libraries(filter  libpoly)
target_link_libraries(filter  libsupport)
target_link_libraries(filter  libweights)
target_link_libraries(filter  libmd5)
target_link_libraries(filter  libglobal)
target_link_libraries(filter  libattachComp)
target_link_libraries(filter  libvisit)
target_link_libraries(filter  libpoly)
target_link_libraries(filter ${Boost_LIBRARIES})
target_link_libraries(filter stdc++)
target_link_libraries(filter gsl)
target_link_libraries(filter gslcblas)
target_link_libraries(filter m)
add_executable(singleItem ${PROJECT_SOURCE_DIR}/Main/singleItem)
target_link_libraries(singleItem  libsingleItemBuild)
target_link_libraries(singleItem  libvisit)
target_link_libraries(singleItem  libsrc)
target_link_libraries(singleItem  libsimMC)
target_link_libraries(singleItem  libconstruct)
target_link_libraries(singleItem  libphysics)
target_link_libraries(singleItem  libinput)
target_link_libraries(singleItem  libprocess)
target_link_libraries(singleItem  libtransport)
target_link_libraries(singleItem  libscatMat)
target_link_libraries(singleItem  libendf)
target_link_libraries(singleItem  libcrystal)
target_link_libraries(singleItem  libsource)
target_link_libraries(singleItem  libmonte)
target_link_libraries(singleItem  libfuncBase)
target_link_libraries(singleItem  liblog)
target_link_libraries(singleItem  libmonte)
target_link_libraries(singleItem  libtally)
target_link_libraries(singleItem  libgeometry)
target_link_libraries(singleItem  libmersenne)
target_link_libraries(singleItem  libsrc)
target_link_libraries(singleItem  libworld)
target_link_libraries(singleItem  libwork)
target_link_libraries(singleItem  libxml)
target_link_libraries(singleItem  libpoly)
target_link_libraries(singleItem  libsupport)
target_link_libraries(singleItem  libweights)
target_link_libraries(singleItem  libmd5)
target_link_libraries(singleItem  libglobal)
target_link_libraries(singleItem  libattachComp)
target_link_libraries(singleItem  libvisit)
target_link_libraries(singleItem  libpoly)
target_link_libraries(singleItem ${Boost_LIBRARIES})
target_link_libraries(singleItem stdc++)
target_link_libraries(singleItem gsl)
target_link_libraries(singleItem gslcblas)
target_link_libraries(singleItem m)
add_executable(testMain ${PROJECT_SOURCE_DIR}/Main/testMain)
target_link_libraries(testMain  libtest)
target_link_libraries(testMain  libbuild)
target_link_libraries(testMain  libvisit)
target_link_libraries(testMain  libchip)
target_link_libraries(testMain  libt1Upgrade)
target_link_libraries(testMain  libimat)
target_link_libraries(testMain  libmoderator)
target_link_libraries(testMain  libbuild)
target_link_libraries(testMain  libzoom)
target_link_libraries(testMain  libconstruct)
target_link_libraries(testMain  libcrystal)
target_link_libraries(testMain  libtransport)
target_link_libraries(testMain  libscatMat)
target_link_libraries(testMain  libendf)
target_link_libraries(testMain  libt1Build)
target_link_libraries(testMain  libsrc)
target_link_libraries(testMain  libsimMC)
target_link_libraries(testMain  libphysics)
target_link_libraries(testMain  libinput)
target_link_libraries(testMain  libprocess)
target_link_libraries(testMain  libsource)
target_link_libraries(testMain  libmonte)
target_link_libraries(testMain  libfuncBase)
target_link_libraries(testMain  liblog)
target_link_libraries(testMain  libgeometry)
target_link_libraries(testMain  libtally)
target_link_libraries(testMain  libmersenne)
target_link_libraries(testMain  libsrc)
target_link_libraries(testMain  libwork)
target_link_libraries(testMain  libxml)
target_link_libraries(testMain  libpoly)
target_link_libraries(testMain  libsupport)
target_link_libraries(testMain  libworld)
target_link_libraries(testMain  libweights)
target_link_libraries(testMain  libmd5)
target_link_libraries(testMain  libglobal)
target_link_libraries(testMain  libattachComp)
target_link_libraries(testMain  libvisit)
target_link_libraries(testMain  libpoly)
target_link_libraries(testMain ${Boost_LIBRARIES})
target_link_libraries(testMain stdc++)
target_link_libraries(testMain gsl)
target_link_libraries(testMain gslcblas)
target_link_libraries(testMain m)
## END EXECUTABLE 

set(ALLCXX 
     ./System/input/*.cxx 
     ./Model/t1Upgrade/*.cxx 
     ./Model/ESSBeam/vespa/*.cxx 
     ./Model/bnctBuild/*.cxx 
     ./Model/ESSBeam/commonVar/*.cxx 
     ./Model/ESSBeam/cspec/*.cxx 
     ./Model/t1Engineer/*.cxx 
     ./Model/ESSBeam/magic/*.cxx 
     ./Model/imat/*.cxx 
     ./Model/ESSBeam/miracles/*.cxx 
     ./Model/ESSBeam/estia/*.cxx 
     ./Model/snsBuild/*.cxx 
     ./Model/ESSBeam/testBeam/*.cxx 
     ./Model/ESSBeam/odin/*.cxx 
     ./System/source/*.cxx 
     ./transport/*.cxx 
     ./Model/ESSBeam/simpleItem/*.cxx 
     ./System/weights/*.cxx 
     ./System/visit/*.cxx 
     ./Model/cuBlock/*.cxx 
     ./Model/ESSBeam/longLoki/*.cxx 
     ./Model/muon/*.cxx 
     ./beamline/*.cxx 
     ./Model/ESSBeam/nnbar/*.cxx 
     ./System/physics/*.cxx 
     ./Model/gammaBuild/*.cxx 
     ./Model/t1Build/*.cxx 
     ./Model/essLinac/*.cxx 
     ./Model/ESSBeam/loki/*.cxx 
     ./Model/filter/*.cxx 
     ./Model/d4cModel/*.cxx 
     ./instrument/*.cxx 
     ./System/work/*.cxx 
     ./Model/essBuild/*.cxx 
     ./Model/build/*.cxx 
     ./Model/epbBuild/*.cxx 
     ./Model/ESSBeam/shortDream/*.cxx 
     ./Model/ESSBeam/bifrost/*.cxx 
     ./scatMat/*.cxx 
     ./Model/sinbadBuild/*.cxx 
     ./System/tally/*.cxx 
     ./test/*.cxx 
     ./Model/ESSBeam/trex/*.cxx 
     ./Model/bibBuild/*.cxx 
     ./Model/ESSBeam/shortOdin/*.cxx 
     ./Model/ESSBeam/freia/*.cxx 
     ./Model/delft/*.cxx 
     ./Model/t3Model/*.cxx 
     ./special/*.cxx 
     ./System/construct/*.cxx 
     ./Model/ESSBeam/dream/*.cxx 
     ./System/xml/*.cxx 
     ./System/geometry/*.cxx 
     ./System/attachComp/*.cxx 
     ./System/monte/*.cxx 
     ./src/*.cxx 
     ./Model/ESSBeam/nmx/*.cxx 
     ./System/process/*.cxx 
     ./Model/ESSBeam/vor/*.cxx 
     ./Model/moderator/*.cxx 
     ./Model/chip/*.cxx 
     ./Model/ESSBeam/skadi/*.cxx 
     ./Model/pipeBuild/*.cxx 
     ./System/mersenne/*.cxx 
     ./System/md5/*.cxx 
     ./System/endf/*.cxx 
     ./Model/lensModel/*.cxx 
     ./System/support/*.cxx 
     ./System/simMC/*.cxx 
     ./System/world/*.cxx 
     ./Model/ESSBeam/shortNmx/*.cxx 
     ./Model/ESSBeam/beer/*.cxx 
     ./System/funcBase/*.cxx 
     ./Model/singleItemBuild/*.cxx 
     ./System/crystal/*.cxx 
     ./System/log/*.cxx 
     ./System/poly/*.cxx 
     ./global/*.cxx 
     ./Model/zoom/*.cxx 
     ./System/compWeights/*.cxx 
     ./Model/photon/*.cxx 
     ./Main/*.cxx )
set(ALLHXX 
     ./include/*.h 
     ./beamlineInc/*.h 
     ./globalInc/*.h 
     ./instrumentInc/*.h 
     ./scatMatInc/*.h 
     ./specialInc/*.h 
     ./transportInc/*.h 
     ./testInclude/*.h 
     ./System/attachCompInc/*.h 
     ./System/compWeightsInc/*.h 
     ./System/constructInc/*.h 
     ./System/crystalInc/*.h 
     ./System/endfInc/*.h 
     ./System/funcBaseInc/*.h 
     ./System/geomInc/*.h 
     ./System/inputInc/*.h 
     ./System/logInc/*.h 
     ./System/md5Inc/*.h 
     ./System/mersenneInc/*.h 
     ./System/monteInc/*.h 
     ./System/physicsInc/*.h 
     ./System/polyInc/*.h 
     ./System/processInc/*.h 
     ./System/simMCInc/*.h 
     ./System/sourceInc/*.h 
     ./System/supportInc/*.h 
     ./System/tallyInc/*.h 
     ./System/visitInc/*.h 
     ./System/weightsInc/*.h 
     ./System/workInc/*.h 
     ./System/worldInc/*.h 
     ./System/xmlInc/*.h 
     ./Model/bibBuildInc/*.h 
     ./Model/bnctBuildInc/*.h 
     ./Model/buildInc/*.h 
     ./Model/chipInc/*.h 
     ./Model/cuBlockInc/*.h 
     ./Model/d4cModelInc/*.h 
     ./Model/delftInc/*.h 
     ./Model/epbBuildInc/*.h 
     ./Model/essBuildInc/*.h 
     ./Model/essLinacInc/*.h 
     ./Model/filterInc/*.h 
     ./Model/gammaBuildInc/*.h 
     ./Model/imatInc/*.h 
     ./Model/lensModelInc/*.h 
     ./Model/moderatorInc/*.h 
     ./Model/muonInc/*.h 
     ./Model/photonInc/*.h 
     ./Model/pipeBuildInc/*.h 
     ./Model/sinbadBuildInc/*.h 
     ./Model/singleItemBuildInc/*.h 
     ./Model/snsBuildInc/*.h 
     ./Model/t1BuildInc/*.h 
     ./Model/t1EngineerInc/*.h 
     ./Model/t1UpgradeInc/*.h 
     ./Model/t3ModelInc/*.h 
     ./Model/zoomInc/*.h 
     ./Model/ESSBeam/beerInc/*.h 
     ./Model/ESSBeam/bifrostInc/*.h 
     ./Model/ESSBeam/commonVarInc/*.h 
     ./Model/ESSBeam/cspecInc/*.h 
     ./Model/ESSBeam/dreamInc/*.h 
     ./Model/ESSBeam/estiaInc/*.h 
     ./Model/ESSBeam/freiaInc/*.h 
     ./Model/ESSBeam/lokiInc/*.h 
     ./Model/ESSBeam/longLokiInc/*.h 
     ./Model/ESSBeam/magicInc/*.h 
     ./Model/ESSBeam/miraclesInc/*.h 
     ./Model/ESSBeam/nmxInc/*.h 
     ./Model/ESSBeam/nnbarInc/*.h 
     ./Model/ESSBeam/odinInc/*.h 
     ./Model/ESSBeam/shortDreamInc/*.h 
     ./Model/ESSBeam/shortNmxInc/*.h 
     ./Model/ESSBeam/shortOdinInc/*.h 
     ./Model/ESSBeam/simpleItemInc/*.h 
     ./Model/ESSBeam/skadiInc/*.h 
     ./Model/ESSBeam/testBeamInc/*.h 
     ./Model/ESSBeam/trexInc/*.h 
     ./Model/ESSBeam/vespaInc/*.h 
     ./Model/ESSBeam/vorInc/*.h 
      )
set(ASRC ${ALLHXX} ${ALLCXX} )
add_custom_target(doxygen  COMMAND  { cat Doxyfile \; echo "INPUT=" ${ASRC} "" \;} | doxygen - )
add_custom_target(sloc  COMMAND sloccount ${ASRC} )
add_custom_target(words  COMMAND grep -v -e '^[[:space:][:cntrl:]]*$$' 
     ./System/input/*.cxx 
     ./Model/t1Upgrade/*.cxx 
     ./Model/ESSBeam/vespa/*.cxx 
     ./Model/bnctBuild/*.cxx 
     ./Model/ESSBeam/commonVar/*.cxx 
     ./Model/ESSBeam/cspec/*.cxx 
     ./Model/t1Engineer/*.cxx 
     ./Model/ESSBeam/magic/*.cxx 
     ./Model/imat/*.cxx 
     ./Model/ESSBeam/miracles/*.cxx 
     ./Model/ESSBeam/estia/*.cxx 
     ./Model/snsBuild/*.cxx 
     ./Model/ESSBeam/testBeam/*.cxx 
     ./Model/ESSBeam/odin/*.cxx 
     ./System/source/*.cxx 
     ./transport/*.cxx 
     ./Model/ESSBeam/simpleItem/*.cxx 
     ./System/weights/*.cxx 
     ./System/visit/*.cxx 
     ./Model/cuBlock/*.cxx 
     ./Model/ESSBeam/longLoki/*.cxx 
     ./Model/muon/*.cxx 
     ./beamline/*.cxx 
     ./Model/ESSBeam/nnbar/*.cxx 
     ./System/physics/*.cxx 
     ./Model/gammaBuild/*.cxx 
     ./Model/t1Build/*.cxx 
     ./Model/essLinac/*.cxx 
     ./Model/ESSBeam/loki/*.cxx 
     ./Model/filter/*.cxx 
     ./Model/d4cModel/*.cxx 
     ./instrument/*.cxx 
     ./System/work/*.cxx 
     ./Model/essBuild/*.cxx 
     ./Model/build/*.cxx 
     ./Model/epbBuild/*.cxx 
     ./Model/ESSBeam/shortDream/*.cxx 
     ./Model/ESSBeam/bifrost/*.cxx 
     ./scatMat/*.cxx 
     ./Model/sinbadBuild/*.cxx 
     ./System/tally/*.cxx 
     ./test/*.cxx 
     ./Model/ESSBeam/trex/*.cxx 
     ./Model/bibBuild/*.cxx 
     ./Model/ESSBeam/shortOdin/*.cxx 
     ./Model/ESSBeam/freia/*.cxx 
     ./Model/delft/*.cxx 
     ./Model/t3Model/*.cxx 
     ./special/*.cxx 
     ./System/construct/*.cxx 
     ./Model/ESSBeam/dream/*.cxx 
     ./System/xml/*.cxx 
     ./System/geometry/*.cxx 
     ./System/attachComp/*.cxx 
     ./System/monte/*.cxx 
     ./src/*.cxx 
     ./Model/ESSBeam/nmx/*.cxx 
     ./System/process/*.cxx 
     ./Model/ESSBeam/vor/*.cxx 
     ./Model/moderator/*.cxx 
     ./Model/chip/*.cxx 
     ./Model/ESSBeam/skadi/*.cxx 
     ./Model/pipeBuild/*.cxx 
     ./System/mersenne/*.cxx 
     ./System/md5/*.cxx 
     ./System/endf/*.cxx 
     ./Model/lensModel/*.cxx 
     ./System/support/*.cxx 
     ./System/simMC/*.cxx 
     ./System/world/*.cxx 
     ./Model/ESSBeam/shortNmx/*.cxx 
     ./Model/ESSBeam/beer/*.cxx 
     ./System/funcBase/*.cxx 
     ./Model/singleItemBuild/*.cxx 
     ./System/crystal/*.cxx 
     ./System/log/*.cxx 
     ./System/poly/*.cxx 
     ./global/*.cxx 
     ./Model/zoom/*.cxx 
     ./System/compWeights/*.cxx 
     ./Model/photon/*.cxx 
     ./include/*.h 
     ./beamlineInc/*.h 
     ./globalInc/*.h 
     ./instrumentInc/*.h 
     ./scatMatInc/*.h 
     ./specialInc/*.h 
     ./transportInc/*.h 
     ./testInclude/*.h 
     ./System/attachCompInc/*.h 
     ./System/compWeightsInc/*.h 
     ./System/constructInc/*.h 
     ./System/crystalInc/*.h 
     ./System/endfInc/*.h 
     ./System/funcBaseInc/*.h 
     ./System/geomInc/*.h 
     ./System/inputInc/*.h 
     ./System/logInc/*.h 
     ./System/md5Inc/*.h 
     ./System/mersenneInc/*.h 
     ./System/monteInc/*.h 
     ./System/physicsInc/*.h 
     ./System/polyInc/*.h 
     ./System/processInc/*.h 
     ./System/simMCInc/*.h 
     ./System/sourceInc/*.h 
     ./System/supportInc/*.h 
     ./System/tallyInc/*.h 
     ./System/visitInc/*.h 
     ./System/weightsInc/*.h 
     ./System/workInc/*.h 
     ./System/worldInc/*.h 
     ./System/xmlInc/*.h 
     ./Model/bibBuildInc/*.h 
     ./Model/bnctBuildInc/*.h 
     ./Model/buildInc/*.h 
     ./Model/chipInc/*.h 
     ./Model/cuBlockInc/*.h 
     ./Model/d4cModelInc/*.h 
     ./Model/delftInc/*.h 
     ./Model/epbBuildInc/*.h 
     ./Model/essBuildInc/*.h 
     ./Model/essLinacInc/*.h 
     ./Model/filterInc/*.h 
     ./Model/gammaBuildInc/*.h 
     ./Model/imatInc/*.h 
     ./Model/lensModelInc/*.h 
     ./Model/moderatorInc/*.h 
     ./Model/muonInc/*.h 
     ./Model/photonInc/*.h 
     ./Model/pipeBuildInc/*.h 
     ./Model/sinbadBuildInc/*.h 
     ./Model/singleItemBuildInc/*.h 
     ./Model/snsBuildInc/*.h 
     ./Model/t1BuildInc/*.h 
     ./Model/t1EngineerInc/*.h 
     ./Model/t1UpgradeInc/*.h 
     ./Model/t3ModelInc/*.h 
     ./Model/zoomInc/*.h 
     ./Model/ESSBeam/beerInc/*.h 
     ./Model/ESSBeam/bifrostInc/*.h 
     ./Model/ESSBeam/commonVarInc/*.h 
     ./Model/ESSBeam/cspecInc/*.h 
     ./Model/ESSBeam/dreamInc/*.h 
     ./Model/ESSBeam/estiaInc/*.h 
     ./Model/ESSBeam/freiaInc/*.h 
     ./Model/ESSBeam/lokiInc/*.h 
     ./Model/ESSBeam/longLokiInc/*.h 
     ./Model/ESSBeam/magicInc/*.h 
     ./Model/ESSBeam/miraclesInc/*.h 
     ./Model/ESSBeam/nmxInc/*.h 
     ./Model/ESSBeam/nnbarInc/*.h 
     ./Model/ESSBeam/odinInc/*.h 
     ./Model/ESSBeam/shortDreamInc/*.h 
     ./Model/ESSBeam/shortNmxInc/*.h 
     ./Model/ESSBeam/shortOdinInc/*.h 
     ./Model/ESSBeam/simpleItemInc/*.h 
     ./Model/ESSBeam/skadiInc/*.h 
     ./Model/ESSBeam/testBeamInc/*.h 
     ./Model/ESSBeam/trexInc/*.h 
     ./Model/ESSBeam/vespaInc/*.h 
     ./Model/ESSBeam/vorInc/*.h 
     ./Main/*.cxx 
     ./CMake.pl  
     .//CMakeList.pm 
 | wc )

add_custom_target(tar  COMMAND tar zcvf ${PROJECT_SOURCE_DIR}/Master.tgz 
     ./System/input/*.cxx 
     ./Model/t1Upgrade/*.cxx 
     ./Model/ESSBeam/vespa/*.cxx 
     ./Model/bnctBuild/*.cxx 
     ./Model/ESSBeam/commonVar/*.cxx 
     ./Model/ESSBeam/cspec/*.cxx 
     ./Model/t1Engineer/*.cxx 
     ./Model/ESSBeam/magic/*.cxx 
     ./Model/imat/*.cxx 
     ./Model/ESSBeam/miracles/*.cxx 
     ./Model/ESSBeam/estia/*.cxx 
     ./Model/snsBuild/*.cxx 
     ./Model/ESSBeam/testBeam/*.cxx 
     ./Model/ESSBeam/odin/*.cxx 
     ./System/source/*.cxx 
     ./transport/*.cxx 
     ./Model/ESSBeam/simpleItem/*.cxx 
     ./System/weights/*.cxx 
     ./System/visit/*.cxx 
     ./Model/cuBlock/*.cxx 
     ./Model/ESSBeam/longLoki/*.cxx 
     ./Model/muon/*.cxx 
     ./beamline/*.cxx 
     ./Model/ESSBeam/nnbar/*.cxx 
     ./System/physics/*.cxx 
     ./Model/gammaBuild/*.cxx 
     ./Model/t1Build/*.cxx 
     ./Model/essLinac/*.cxx 
     ./Model/ESSBeam/loki/*.cxx 
     ./Model/filter/*.cxx 
     ./Model/d4cModel/*.cxx 
     ./instrument/*.cxx 
     ./System/work/*.cxx 
     ./Model/essBuild/*.cxx 
     ./Model/build/*.cxx 
     ./Model/epbBuild/*.cxx 
     ./Model/ESSBeam/shortDream/*.cxx 
     ./Model/ESSBeam/bifrost/*.cxx 
     ./scatMat/*.cxx 
     ./Model/sinbadBuild/*.cxx 
     ./System/tally/*.cxx 
     ./test/*.cxx 
     ./Model/ESSBeam/trex/*.cxx 
     ./Model/bibBuild/*.cxx 
     ./Model/ESSBeam/shortOdin/*.cxx 
     ./Model/ESSBeam/freia/*.cxx 
     ./Model/delft/*.cxx 
     ./Model/t3Model/*.cxx 
     ./special/*.cxx 
     ./System/construct/*.cxx 
     ./Model/ESSBeam/dream/*.cxx 
     ./System/xml/*.cxx 
     ./System/geometry/*.cxx 
     ./System/attachComp/*.cxx 
     ./System/monte/*.cxx 
     ./src/*.cxx 
     ./Model/ESSBeam/nmx/*.cxx 
     ./System/process/*.cxx 
     ./Model/ESSBeam/vor/*.cxx 
     ./Model/moderator/*.cxx 
     ./Model/chip/*.cxx 
     ./Model/ESSBeam/skadi/*.cxx 
     ./Model/pipeBuild/*.cxx 
     ./System/mersenne/*.cxx 
     ./System/md5/*.cxx 
     ./System/endf/*.cxx 
     ./Model/lensModel/*.cxx 
     ./System/support/*.cxx 
     ./System/simMC/*.cxx 
     ./System/world/*.cxx 
     ./Model/ESSBeam/shortNmx/*.cxx 
     ./Model/ESSBeam/beer/*.cxx 
     ./System/funcBase/*.cxx 
     ./Model/singleItemBuild/*.cxx 
     ./System/crystal/*.cxx 
     ./System/log/*.cxx 
     ./System/poly/*.cxx 
     ./global/*.cxx 
     ./Model/zoom/*.cxx 
     ./System/compWeights/*.cxx 
     ./Model/photon/*.cxx 
     ./include/*.h 
     ./beamlineInc/*.h 
     ./globalInc/*.h 
     ./instrumentInc/*.h 
     ./scatMatInc/*.h 
     ./specialInc/*.h 
     ./transportInc/*.h 
     ./testInclude/*.h 
     ./System/attachCompInc/*.h 
     ./System/compWeightsInc/*.h 
     ./System/constructInc/*.h 
     ./System/crystalInc/*.h 
     ./System/endfInc/*.h 
     ./System/funcBaseInc/*.h 
     ./System/geomInc/*.h 
     ./System/inputInc/*.h 
     ./System/logInc/*.h 
     ./System/md5Inc/*.h 
     ./System/mersenneInc/*.h 
     ./System/monteInc/*.h 
     ./System/physicsInc/*.h 
     ./System/polyInc/*.h 
     ./System/processInc/*.h 
     ./System/simMCInc/*.h 
     ./System/sourceInc/*.h 
     ./System/supportInc/*.h 
     ./System/tallyInc/*.h 
     ./System/visitInc/*.h 
     ./System/weightsInc/*.h 
     ./System/workInc/*.h 
     ./System/worldInc/*.h 
     ./System/xmlInc/*.h 
     ./Model/bibBuildInc/*.h 
     ./Model/bnctBuildInc/*.h 
     ./Model/buildInc/*.h 
     ./Model/chipInc/*.h 
     ./Model/cuBlockInc/*.h 
     ./Model/d4cModelInc/*.h 
     ./Model/delftInc/*.h 
     ./Model/epbBuildInc/*.h 
     ./Model/essBuildInc/*.h 
     ./Model/essLinacInc/*.h 
     ./Model/filterInc/*.h 
     ./Model/gammaBuildInc/*.h 
     ./Model/imatInc/*.h 
     ./Model/lensModelInc/*.h 
     ./Model/moderatorInc/*.h 
     ./Model/muonInc/*.h 
     ./Model/photonInc/*.h 
     ./Model/pipeBuildInc/*.h 
     ./Model/sinbadBuildInc/*.h 
     ./Model/singleItemBuildInc/*.h 
     ./Model/snsBuildInc/*.h 
     ./Model/t1BuildInc/*.h 
     ./Model/t1EngineerInc/*.h 
     ./Model/t1UpgradeInc/*.h 
     ./Model/t3ModelInc/*.h 
     ./Model/zoomInc/*.h 
     ./Model/ESSBeam/beerInc/*.h 
     ./Model/ESSBeam/bifrostInc/*.h 
     ./Model/ESSBeam/commonVarInc/*.h 
     ./Model/ESSBeam/cspecInc/*.h 
     ./Model/ESSBeam/dreamInc/*.h 
     ./Model/ESSBeam/estiaInc/*.h 
     ./Model/ESSBeam/freiaInc/*.h 
     ./Model/ESSBeam/lokiInc/*.h 
     ./Model/ESSBeam/longLokiInc/*.h 
     ./Model/ESSBeam/magicInc/*.h 
     ./Model/ESSBeam/miraclesInc/*.h 
     ./Model/ESSBeam/nmxInc/*.h 
     ./Model/ESSBeam/nnbarInc/*.h 
     ./Model/ESSBeam/odinInc/*.h 
     ./Model/ESSBeam/shortDreamInc/*.h 
     ./Model/ESSBeam/shortNmxInc/*.h 
     ./Model/ESSBeam/shortOdinInc/*.h 
     ./Model/ESSBeam/simpleItemInc/*.h 
     ./Model/ESSBeam/skadiInc/*.h 
     ./Model/ESSBeam/testBeamInc/*.h 
     ./Model/ESSBeam/trexInc/*.h 
     ./Model/ESSBeam/vespaInc/*.h 
     ./Model/ESSBeam/vorInc/*.h 
     ./Main/*.cxx 
     ./CMake.pl  
     .//CMakeList.pm 
 )

add_custom_target(tags  COMMAND etags  
     ${PROJECT_SOURCE_DIR}/System/input/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/t1Upgrade/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/vespa/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/bnctBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/commonVar/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/cspec/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/t1Engineer/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/magic/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/imat/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/miracles/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/estia/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/snsBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/testBeam/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/odin/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/source/*.cxx 
     ${PROJECT_SOURCE_DIR}/transport/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/simpleItem/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/weights/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/visit/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/cuBlock/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/longLoki/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/muon/*.cxx 
     ${PROJECT_SOURCE_DIR}/beamline/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/nnbar/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/physics/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/gammaBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/t1Build/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/essLinac/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/loki/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/filter/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/d4cModel/*.cxx 
     ${PROJECT_SOURCE_DIR}/instrument/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/work/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/essBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/build/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/epbBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortDream/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/bifrost/*.cxx 
     ${PROJECT_SOURCE_DIR}/scatMat/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/sinbadBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/tally/*.cxx 
     ${PROJECT_SOURCE_DIR}/test/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/trex/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/bibBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortOdin/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/freia/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/delft/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/t3Model/*.cxx 
     ${PROJECT_SOURCE_DIR}/special/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/construct/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/dream/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/xml/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/geometry/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/attachComp/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/monte/*.cxx 
     ${PROJECT_SOURCE_DIR}/src/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/nmx/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/process/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/vor/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/moderator/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/chip/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/skadi/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/pipeBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/mersenne/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/md5/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/endf/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/lensModel/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/support/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/simMC/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/world/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortNmx/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/beer/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/funcBase/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/singleItemBuild/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/crystal/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/log/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/poly/*.cxx 
     ${PROJECT_SOURCE_DIR}/global/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/zoom/*.cxx 
     ${PROJECT_SOURCE_DIR}/System/compWeights/*.cxx 
     ${PROJECT_SOURCE_DIR}/Model/photon/*.cxx 
     ${PROJECT_SOURCE_DIR}/include/*.h 
     ${PROJECT_SOURCE_DIR}/beamlineInc/*.h 
     ${PROJECT_SOURCE_DIR}/globalInc/*.h 
     ${PROJECT_SOURCE_DIR}/instrumentInc/*.h 
     ${PROJECT_SOURCE_DIR}/scatMatInc/*.h 
     ${PROJECT_SOURCE_DIR}/specialInc/*.h 
     ${PROJECT_SOURCE_DIR}/transportInc/*.h 
     ${PROJECT_SOURCE_DIR}/testInclude/*.h 
     ${PROJECT_SOURCE_DIR}/System/attachCompInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/compWeightsInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/constructInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/crystalInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/endfInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/funcBaseInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/geomInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/inputInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/logInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/md5Inc/*.h 
     ${PROJECT_SOURCE_DIR}/System/mersenneInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/monteInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/physicsInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/polyInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/processInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/simMCInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/sourceInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/supportInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/tallyInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/visitInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/weightsInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/workInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/worldInc/*.h 
     ${PROJECT_SOURCE_DIR}/System/xmlInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/bibBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/bnctBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/buildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/chipInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/cuBlockInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/d4cModelInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/delftInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/epbBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/essBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/essLinacInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/filterInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/gammaBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/imatInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/lensModelInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/moderatorInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/muonInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/photonInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/pipeBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/sinbadBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/singleItemBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/snsBuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/t1BuildInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/t1EngineerInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/t1UpgradeInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/t3ModelInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/zoomInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/beerInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/bifrostInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/commonVarInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/cspecInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/dreamInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/estiaInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/freiaInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/lokiInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/longLokiInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/magicInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/miraclesInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/nmxInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/nnbarInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/odinInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortDreamInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortNmxInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/shortOdinInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/simpleItemInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/skadiInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/testBeamInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/trexInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/vespaInc/*.h 
     ${PROJECT_SOURCE_DIR}/Model/ESSBeam/vorInc/*.h 
 )

