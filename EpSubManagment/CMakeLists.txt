set(HEADER_LIST inc/Episode.hpp inc/Subtitle.hpp inc/File.hpp)
set(SRC_LIST src/Subtitle.cpp src/File.cpp)
set(DEPENDENCIES_LIST StringManagment FilesManagment Entertainment)

add_library(EpSubManagment STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(EpSubManagment PUBLIC . inc src)

add_dependencies(EpSubManagment ${DEPENDENCIES_LIST})
target_link_libraries(EpSubManagment PUBLIC ${DEPENDENCIES_LIST})
