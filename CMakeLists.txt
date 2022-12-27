cmake_minimum_required(VERSION 3.10)

project(AnimeOrganiser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# In case of emergency add this debugging flag do compiler option: ||-ggdb3||
IF(!WIN32)
    set(CPU_OPTIONS -Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -Ofast)
ENDIF()

add_compile_options(${CPU_OPTIONS})

add_subdirectory(Entertainment)
add_subdirectory(Menu)

add_subdirectory(StringManagment)
add_subdirectory(FilesManagment)

add_subdirectory(EpSubManagment)

add_subdirectory(firmware)
