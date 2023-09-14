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

set(VTK_DIR "C:/PCL 1.13.1/3rdParty/VTK")
set(ITK_DIR "C:/envs/ITK-5.4.0-lib")
set(ITK_CMAKE_DIR "C:/envs/ITK-5.4.0-lib/lib/cmake/ITK-5.4")

set(CMAKE_PREFIX_PATH
    ${CMAKE_PREFIX_PATH}
    ${VTK_DIR}
#    ${VTK_CMAKE_DIR}
    ${ITK_CMAKE_DIR}
)

include_directories(${ITK_DIR}/include/ITK-5.4)

find_package(ITK REQUIRED)
find_package(PCL REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Widgets)


message("PCL_FOUND: ${PCL_FOUND}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

message("QT_VERSION_MAJOR: ${QT_VERSION_MAJOR}")
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${PCL_LIBRARIES}
    ${ITK_LIBRARIES}
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
