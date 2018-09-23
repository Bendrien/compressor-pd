cmake_minimum_required(VERSION 3.10)
project(compressor C)

set(CMAKE_C_STANDARD 99)

add_library(compressor SHARED
        m_pd.h
        library.h
        library.c
    )

set_target_properties(compressor PROPERTIES PREFIX "")
set_target_properties(compressor PROPERTIES SUFFIX ".pd_linux")