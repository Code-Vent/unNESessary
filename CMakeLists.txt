cmake_minimum_required(VERSION 3.25)
project(NES)

set(CMAKE_CXX_STANDARD 23)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
            )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add SDL3 support
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.0)
else()
    message(STATUS "Using local SDL3")
endif()

add_executable(NES main.cpp peripheral.h peripheral.cpp bus.cpp bus.h memory.cpp memory.h nes.cpp nes.h cpu6502.cpp cpu6502.h cartridge.cpp cartridge.h mapper.h ppu2C02.cpp ppu2C02.h nrom.h nrom.h)

# set the include directory
target_include_directories(NES PUBLIC ${SDL3_INCLUDE_DIRS})

target_compile_definitions(NES PRIVATE SDL_MAIN_USE_CALLBACKS)

# link all libraries to the project
target_link_libraries(NES PRIVATE SDL3::SDL3)

if (WIN32)
    add_custom_command(
            TARGET NES POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:NES>"
            VERBATIM
    )
endif()
