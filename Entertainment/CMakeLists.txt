set(HEADER_LIST inc/Entertainment.hpp)
set(SRC_LIST src/Entertainment.cpp)

add_library(Entertainment STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(Entertainment PUBLIC . inc src)
