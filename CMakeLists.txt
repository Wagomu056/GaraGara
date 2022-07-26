cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)

add_subdirectory(src/core)

add_definitions(-DENABLE_LOG)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if (NOT ${ENVSDK} STREQUAL "")
	# Convert path from Windows
	file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
	execute_process(
			COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
			COMMAND head -n 1
			COMMAND cut -c9-
			OUTPUT_VARIABLE SDK
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

if (NOT EXISTS ${SDK})
	message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
	return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

# Game Name Customization
set(PLAYDATE_GAME_NAME garagara)
set(PLAYDATE_GAME_DEVICE garagara_DEVICE)

project(${PLAYDATE_GAME_NAME} C ASM)

file(GLOB IMAGES
		"Source/images/*"
		"Source/font/*"
)

if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE} ${SDK}/C_API/buildsupport/setup.c
			src/main.c
			src/cutin_drawer.c src/name_drawer.c src/pd_util.c src/gara.c)
	target_link_libraries(${PLAYDATE_GAME_DEVICE} core)
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED ${IMAGES}
			src/main.c
			src/cutin_drawer.c src/name_drawer.c src/pd_util.c src/gara.c)
	target_link_libraries(${PLAYDATE_GAME_NAME} core)
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)
