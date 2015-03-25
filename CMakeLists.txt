cmake_minimum_required(VERSION 2.8)

project(arcgen)

set(hdrs
)
source_group("Headers" FILES ${hdrs})

set(srcs
    arcgen.cpp
)

include_directories(
    ${Boost_IOSTREAMS_LIBRARY}
)

add_executable( ${PROJECT_NAME}
    ${srcs}
)

target_link_libraries( ${PROJECT_NAME}
    ${Boost_IOSTREAMS_LIBRARY}
)
