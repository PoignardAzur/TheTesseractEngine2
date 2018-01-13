cmake_minimum_required (VERSION 2.8)
project(OgreTutorialsSample)

# specify which version you need
find_package(OGRE 1.10 REQUIRED)
find_package(SFML 2.4 REQUIRED system window graphics network audio)
find_package(Boost REQUIRED COMPONENTS thread)

# the search paths
include_directories(${OGRE_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})

# copy essential config files next to our binary where OGRE autodiscovers them
file(
  COPY ./dist
  DESTINATION ${CMAKE_BINARY_DIR}
)

set(SRCS
  src/main.cpp
  src/FloatingPlayer.cpp

  src/Inputs/SfmlInputs.cpp
  src/Inputs/DummyInputs.cpp

  src/GameWorld/GameWorld.cpp
  src/GameWorld/PosRange.cpp
  src/GameWorld/WorldArea.cpp

  src/GameWorldDisplayer/GameWorldDisplayer.cpp
  src/GameWorldDisplayer/WorldAreaDisplayer.cpp

  src/Scene/GameScene.cpp
)
set(HDRS
  src/FloatingPlayer.hpp

  src/Inputs/Inputs.hpp
  src/Inputs/SfmlInputs.hpp
  src/Inputs/DummyInputs.hpp

  src/GameWorld/BlockPos.hpp
  src/GameWorld/BlockType.hpp
  src/GameWorld/EntityPos.hpp
  src/GameWorld/EntityOrientation.hpp
  src/GameWorld/GameWorld.hpp
  src/GameWorld/PosRange.hpp
  src/GameWorld/WorldArea.hpp

  src/GameWorldDisplayer/GameWorldDisplayer.hpp
  src/GameWorldDisplayer/WorldAreaDisplayer.hpp

  src/Scene/Scene.hpp
  src/Scene/GameScene.hpp
)

include_directories(
  ${Boost_INCLUDE_DIRS},
  src
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
add_executable(TTE_2 ${SRCS} ${HDRS})
target_link_libraries(TTE_2 ${OGRE_LIBRARIES} ${SFML_LIBRARIES})

if(MSVC)
  target_compile_options(TTE_2 PRIVATE "/W4")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(TTE_2 PRIVATE "-Wall")
  target_compile_options(TTE_2 PRIVATE "-Wextra")
  target_compile_options(TTE_2 PRIVATE "-Wno-unused-parameter")
endif()
