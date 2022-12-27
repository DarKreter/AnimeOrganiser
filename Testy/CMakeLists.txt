set(DEPENDENCIES_LIST FilesManagment StringManagment Menu EpisodeSubtitleManagment Threads::Threads)

add_executable(firmware main.cpp)

target_include_directories(firmware PUBLIC .)

find_package(Threads REQUIRED)
add_dependencies(firmware ${DEPENDENCIES_LIST})
target_link_libraries(firmware PUBLIC ${DEPENDENCIES_LIST})
