set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.22.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()

set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

set( # Required for McuLib, to know the target system
  MCULIB_TARGET MCUXPRESSO CACHE STRING 
  "Select McuLib target: RP2040, MCUXPRESSO or ESP32"
)

# turn variable on for verbose output, useful for build debugging. Or run 'ninja --verbose' in the build folder
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

# set project name which is used as CMake target too
set(PROJECT_NAME  "epp-tinyK22")

# set project name, board files path and languages supported
project(
  ${PROJECT_NAME}                  # project name
  LANGUAGES C CXX ASM              # project languages
)
#set(PROJECT_BOARD_PORT_PATH  "./board") # where are the board files

# set variables for directories
set(PROJECT_ROOT_DIR        "${CMAKE_CURRENT_SOURCE_DIR}")      # project root directory
set(ProjDirPath             "${CMAKE_CURRENT_SOURCE_DIR}")      # variable used by NXP extension and SDK
set(MCULIB_DIR              "${PROJECT_ROOT_DIR}/McuLib")       # common McuLib directory
set(SDK_DIR                 "${PROJECT_ROOT_DIR}/sdk")          # location of NXP MCUXpresso SDK
set(BOARD_DIR               "${PROJECT_ROOT_DIR}/board")        # where the board files are located
set(EXECUTABLE              "${PROJECT_NAME}.elf")              # name oft the executable file
set(MCUX_SDK_PROJECT_NAME   "${PROJECT_NAME}")                  # project name used by NXP SDK

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/build/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

# get MCUXpresso SDK toolchain file
include(${SdkRootDirPath}/tools/cmake_toolchain_files/armgcc.cmake)

# MCUXpresso SDK main CMake file
include(${SdkRootDirPath}/tools/cmake_toolchain_files/mcux_config.cmake)

# include MCUXpresso specific settings
include(./cmake/flags.cmake)
include(./cmake/config.cmake)
include(./cmake/ide_overrides.cmake OPTIONAL)

# 0: do not handle warnings as errors
set(CONFIG_MCUX_PRJSEG_config.arm.warn_as_error 0)

# list of included directories
include_directories(
  "./src"
  ${BOARD_DIR}
)

# set global compiler options, which includes board/SDK related paths for the McuLib
add_compile_options( # these options are *not* used for sources maintained by the SDK, but for example for the McuLib 
  -include "${PROJECT_ROOT_DIR}/src/IncludeMcuLibConfig.h"
  -I${BOARD_DIR}
  -I${SDK_DIR}/CMSIS/Core/Include
  -I${SDK_DIR}/devices/MK22F51212
  -I${SDK_DIR}/devices/MK22F51212/drivers
  -I${SDK_DIR}/devices/MK22F51212/periph20
)
# **************************************************************
# add McuLib libraries
add_subdirectory(${MCULIB_DIR}                      McuLib)
add_subdirectory(${MCULIB_DIR}/rdimon               rdimon)

# add custom source folders with CMakeLists.txt in it
add_subdirectory(./src            src)

# list root folder source files, including board specific files
add_executable(
  ${PROJECT_NAME}
  # "${SDK_DIR}/devices/MK22F51212/gcc/startup_MK22F51212.S"
  ${BOARD_DIR}/board.c
  ${BOARD_DIR}/clock_config.c
  ${BOARD_DIR}/peripherals.c
  ${BOARD_DIR}/pin_mux.c
)

# add libraries to project
target_link_libraries(
  ${PROJECT_NAME}
    PRIVATE 
    srcLib    # library of src folder
    McuLib    # McuLib with common tools and middleware
    rdimonLib # file I/O with semihosting
  )

include(${SdkRootDirPath}/devices/MK22F51212/all_lib_device.cmake)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE} ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O srec ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE} ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.s19)
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE} ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "${PROJECT_NAME}.map;${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin")
set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "${PROJECT_NAME}.map;${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.s19")
set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "${PROJECT_NAME}.map;${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex")
