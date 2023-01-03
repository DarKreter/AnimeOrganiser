set(HEADER_LIST inc/StringManagment.hpp)
set(SRC_LIST src/StringManagment.cpp)

add_library(StringManagment STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(StringManagment PUBLIC . inc src)
