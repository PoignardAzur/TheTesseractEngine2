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
  src/FloatingPlayer.cpp

  src/Inputs/SfmlInputs.cpp
  src/Inputs/DummyInputs.cpp

  src/GameWorld/PosRange.cpp
  src/GameWorld/SingleChunk.cpp
  src/GameWorld/WorldChunk.cpp

  src/GameWorldDisplayer/GameWorldDisplayer.cpp
  src/GameWorldDisplayer/WorldChunkDisplayer.cpp

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
  src/GameWorld/SingleChunk.hpp
  src/GameWorld/WorldChunk.hpp

  src/GameWorldDisplayer/GameWorldDisplayer.hpp
  src/GameWorldDisplayer/WorldChunkDisplayer.hpp

  src/Scene/Scene.hpp
  src/Scene/GameScene.hpp
)

set(TESTS
  tests/tests-main.cpp

  tests/GameWorld/tests-PosRange.cpp
  tests/GameWorld/tests-SingleChunk.cpp
  tests/GameWorld/tests-WorldChunk.cpp
)

include_directories(
  ${Boost_INCLUDE_DIRS},
  tests,
  src
)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)

add_executable(TTE_2_tests ${SRCS} ${TESTS} ${HDRS} tests/catch.hpp)
target_link_libraries(TTE_2_tests ${OGRE_LIBRARIES} ${SFML_LIBRARIES})

set_property(TARGET TTE_2_tests PROPERTY CXX_STANDARD_REQUIRED true)
set_property(TARGET TTE_2_tests PROPERTY CXX_STANDARD 17)


add_executable(TTE_2 ${SRCS} ${HDRS} src/main.cpp)
target_link_libraries(TTE_2 ${OGRE_LIBRARIES} ${SFML_LIBRARIES})

set_property(TARGET TTE_2 PROPERTY CXX_STANDARD_REQUIRED true)
set_property(TARGET TTE_2 PROPERTY CXX_STANDARD 17)

if(MSVC)
  target_compile_options(TTE_2 PRIVATE "/W4")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(TTE_2 PRIVATE "-Wall")
  target_compile_options(TTE_2 PRIVATE "-Wextra")
  target_compile_options(TTE_2 PRIVATE "-Wno-unused-parameter")
endif()
