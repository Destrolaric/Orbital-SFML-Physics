cmake_minimum_required( VERSION 3.13 )
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" )
project( PhysicsSimulationStuff)
find_package(SFML 2 COMPONENTS system window graphics CONFIG REQUIRED)

set( CMAKE_CXX_STANDARD 14 )

add_executable( PhysicsSimulationStuff main.cpp Planet.cpp Planet.h OrbitalCalculator.cpp OrbitalCalculator.h )
target_link_libraries(PhysicsSimulationStuff PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(PhysicsSimulationStuff PRIVATE sfml-main)

