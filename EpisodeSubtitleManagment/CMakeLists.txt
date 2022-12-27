set(HEADER_LIST inc/Episode.hpp inc/Subtitle.hpp inc/File.hpp)
set(SRC_LIST src/Episode.cpp src/Subtitle.cpp src/File.cpp)
set(DEPENDENCIES_LIST StringManagment FilesManagment Entertainment)

add_library(EpisodeSubtitleManagment STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(EpisodeSubtitleManagment PUBLIC . inc src)

add_dependencies(EpisodeSubtitleManagment ${DEPENDENCIES_LIST})
target_link_libraries(EpisodeSubtitleManagment PUBLIC ${DEPENDENCIES_LIST})
