cmake_minimum_required(VERSION 3.0)

project(GravitySimulation VERSION 1.0)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

add_executable(Gravity main.cpp
	mymath.cpp
	PhysicsHandler.cpp
	Renderer.cpp
	StatisticsTracker.cpp
	Universe.cpp
	UserInterface.cpp)
#target_link_libraries(Gravity PUBLIC SFML::Graphics SFML::Window SFML::System) # For SFML version 3
target_link_libraries(Gravity PUBLIC sfml-graphics sfml-window sfml-system) # For SFML version 2