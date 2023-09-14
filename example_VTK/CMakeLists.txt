cmake_minimum_required(VERSION 3.24)

get_filename_component(current_dir "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
string(REPLACE " " "" current_dir "${current_dir}")
string(REPLACE "-" "_" current_dir "${current_dir}")

message("CMake start \n\t directory name: ${current_dir}")

project("${current_dir}" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB subdirectories LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*")

set(file_to_find "CMakeLists.txt")
foreach(subdir ${subdirectories})
    if(IS_DIRECTORY "${subdir}")
        # message("Found subdir: ${subdir}")

        set(files)

        file(GLOB files_in_directory LIST_FILES "${subdir}/*")
        # message("files_in_directory: ${files_in_directory}")

        foreach(fin ${files_in_directory})
            get_filename_component(file "${fin}" NAME ABSOLUTE)
            list(APPEND files ${file})
        endforeach()

        list(FIND files "${file_to_find}" file_index)

        if(${file_index} EQUAL -1)
            message("${file_to_find} not found in the directory: ${subdir}")
        else()
            message("${file_to_find} found in the directory: ${subdir}")
            add_subdirectory("${subdir}")
        endif()

    endif()
endforeach()

get_property(subdirectories DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY SUBDIRECTORIES)

message("\n Found subdirectory: \n")
foreach(subdir ${subdirectories})
    message("\t\t${subdir}")
endforeach()

message("\n\n")
