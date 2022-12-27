cmake_minimum_required(VERSION 3.10)

project(AnimeOrganiser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# In case of emergency add this debugging flag do compiler option: ||-ggdb3||
set(CPU_OPTIONS -Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -Ofast)
add_compile_options(${CPU_OPTIONS})

add_subdirectory(Entertainment)
add_subdirectory(StringManagment)
add_subdirectory(FilesManagment)
add_subdirectory(Testy)
# add_subdirectory(Menu)
# add_subdirectory(EpisodeSubtitleManagment)
# add_subdirectory(Anime Organiser HQ)
