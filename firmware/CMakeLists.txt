set(DEPENDENCIES_LIST   FilesManagment StringManagment Menu 
                        EpSubManagment Threads::Threads)

add_executable(AnimeOrganiserHQ AnimeOrganiserHQ.cpp)
add_executable(AnimeOrganiserLQ AnimeOrganiserLQ.cpp)


find_package(Threads REQUIRED)


target_include_directories(AnimeOrganiserLQ PUBLIC .)
add_dependencies(AnimeOrganiserLQ ${DEPENDENCIES_LIST})
target_link_libraries(AnimeOrganiserLQ PUBLIC ${DEPENDENCIES_LIST})

target_include_directories(AnimeOrganiserHQ PUBLIC .)
add_dependencies(AnimeOrganiserHQ ${DEPENDENCIES_LIST})
target_link_libraries(AnimeOrganiserHQ PUBLIC ${DEPENDENCIES_LIST})
