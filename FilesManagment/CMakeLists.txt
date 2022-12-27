set(HEADER_LIST inc/FilesManagment.hpp fml/FilesManagment.tpp)
set(SRC_LIST src/FilesManagment.cpp)
set(DEPENDENCIES_LIST StringManagment)

add_library(FilesManagment STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(FilesManagment PUBLIC . inc src fml)

add_dependencies(FilesManagment ${DEPENDENCIES_LIST})
target_link_libraries(FilesManagment PUBLIC ${DEPENDENCIES_LIST})
