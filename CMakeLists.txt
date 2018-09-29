cmake_minimum_required(VERSION 3.10)
project(compressor C)

set(CMAKE_C_STANDARD 99)

add_library(compressor SHARED
        m_pd.h
        library.h
        library.c
    )

set_target_properties(compressor PROPERTIES PREFIX "")
if (APPLE)
    set_target_properties(compressor PROPERTIES SUFFIX "~.pd_darwin")
elseif(UNIX)
    set_target_properties(compressor PROPERTIES SUFFIX "~.pd_linux")
elseif(WIN32)
    set_target_properties(compressor PROPERTIES SUFFIX "~.dll")
endif (APPLE)
