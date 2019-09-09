cmake_minimum_required(VERSION 3.0)

include_directories(
    #SYSTEM
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
    #PARENT_SCOPE
    )

message("***CMakeLists.txt at: ${CMAKE_CURRENT_LIST_DIR}")

