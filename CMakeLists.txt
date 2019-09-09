cmake_minimum_required(VERSION 3.0)
project("F247-demo" C CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(TGT_NAME "${PROJECT_NAME}")

find_package(PkgConfig REQUIRED)

pkg_search_module(PORTAUDIO REQUIRED portaudio-2.0)
foreach(OPT ${PORTAUDIO_CFLAGS})
set(PORTAUDIO_CFLAGS_str "${PORTAUDIO_CFLAGS_str} ${OPT}")
endforeach()
foreach(OPT ${PORTAUDIO_LDFLAGS})
set(PORTAUDIO_LFLAGS_str "${PORTAUDIO_LFLAGS_str} ${OPT}")
endforeach()

pkg_search_module(SDL2 REQUIRED sdl2)
foreach(OPT ${SDL2_CFLAGS})
set(SDL2_CFLAGS_str "${SDL2_CFLAGS_str} ${OPT}")
endforeach()
foreach(OPT ${SDL2_LDFLAGS})
set(SDL2_LFLAGS_str "${SDL2_LFLAGS_str} ${OPT}")
endforeach()

pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)
foreach(OPT ${SDL2TTF_CFLAGS})
set(SDL2TTF_CFLAGS_str "${SDL2TTF_CFLAGS_str} ${OPT}")
endforeach()
foreach(OPT ${SDL2TTF_LDFLAGS})
set(SDL2TTF_LFLAGS_str "${SDL2TTF_LFLAGS_str} ${OPT}")
endforeach()


set(CCOMMON_FLAGS           "")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -funsigned-bitfields")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -O2")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -DLINUX")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -D__GNU__")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -Wall")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -Werror")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -Wextra")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -Wno-unused-parameter")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -Wno-unused-value")
#set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -I$(DIR_PGLIB)")
#set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -I./")
#set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} `pkg-config sdl2 --cflags`")
#set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} `pkg-config SDL2_ttf --cflags`")


set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} ${PORTAUDIO_CFLAGS_str}")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} ${SDL2_CFLAGS_str}")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} ${SDL2TTF_CFLAGS_str}")
set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} ")

set(CCOMMON_FLAGS           "${CCOMMON_FLAGS} -g")

set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} ${CCOMMON_FLAGS}")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wstrict-prototypes")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -ffunction-sections")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -fdata-sections")

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${CCOMMON_FLAGS}")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wundef")

#set(CMAKE_EXE_LINKER_FLAGS  "")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lasound")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -ldl") #required by sqlite3
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${PORTAUDIO_LFLAGS_str}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${SDL2_LFLAGS_str}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${SDL2TTF_LFLAGS_str}")
#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} `pkg-config sdl2 --libs`")
#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} `pkg-config SDL2_ttf --libs`")

set(SOURCE_FILES "")

include(
    "${CMAKE_CURRENT_LIST_DIR}/APP_IMPORT/CMakeLists.txt"
    )

include(
    "${CMAKE_CURRENT_LIST_DIR}/APP_LOCAL/CMakeLists.txt"
    )

include(
    "${CMAKE_CURRENT_LIST_DIR}/LIB_IMPORT/CMakeLists.txt"
    )

include(
    "${CMAKE_CURRENT_LIST_DIR}/LIB_LOCAL/CMakeLists.txt"
    )

add_executable(
    ${TGT_NAME}
    ${SOURCE_FILES}
    )

message("***CMakeLists.txt at: ${CMAKE_CURRENT_LIST_DIR}")
message("   TGT_NAME=${TGT_NAME}")
message("   SOURCE_FILES=${SOURCE_FILES}")
message("   CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
message("   CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message("   CMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS}")

