cmake_minimum_required(VERSION 3.0)

#include(
#    "${CMAKE_CURRENT_LIST_DIR}/cfg/CMakeLists.txt"
#    )

include_directories(
    "${CMAKE_CURRENT_LIST_DIR}"
    )

file(
    GLOB
    "SRC_${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    )

set(
    SOURCE_FILES
    ${SOURCE_FILES}
    ${SRC_${CMAKE_CURRENT_LIST_DIR}}
    )

message("***CMakeLists.txt at: ${CMAKE_CURRENT_LIST_DIR}")

#rekursja do zerżnięcia
#/MACRO(HEADER_DIRECTORIES return_list)/
#    /    FILE(GLOB_RECURSE new_list *.h)/
#    /    SET(dir_list "")/
#    /    FOREACH(file_path ${new_list})/
#    /        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)/
#    /        SET(dir_list ${dir_list} ${dir_path})/
#    /    ENDFOREACH()/
#    /    LIST(REMOVE_DUPLICATES dir_list)/
#    /    SET(${return_list} ${dir_list})/
#    /ENDMACRO()/


