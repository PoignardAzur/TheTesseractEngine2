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
  src/Inputs.cpp
  src/GameScene.cpp
  src/GameWorld.cpp
  src/GameWorldDisplayer.cpp
  src/PosRange.cpp
  src/WorldArea.cpp
  src/WorldAreaDisplayer.cpp
)
set(HDRS
  src/Inputs.hpp
  src/GameScene.hpp
  src/GameWorld.hpp
  src/GameWorldDisplayer.hpp
  src/PosRange.hpp
  src/Scene.hpp
  src/WorldArea.hpp
  src/WorldAreaDisplayer.hpp
)

include_directories(${Boost_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
add_executable(TTE_2 ${SRCS} ${HDRS})
target_link_libraries(TTE_2 ${OGRE_LIBRARIES} ${SFML_LIBRARIES})
