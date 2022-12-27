set(HEADER_LIST inc/Menu.hpp)
set(SRC_LIST src/Menu.cpp)
set(DEPENDENCIES_LIST Entertainment)

add_library(Menu STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(Menu PUBLIC . inc src)

add_dependencies(Menu ${DEPENDENCIES_LIST})
target_link_libraries(Menu PUBLIC ${DEPENDENCIES_LIST})
