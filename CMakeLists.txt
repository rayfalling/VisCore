cmake_minimum_required(VERSION 3.20)
project(VisCore)

include(GenerateExportHeader)

# Make codecvt work for c++17
add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

# Set Cmake build output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary/Library)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)

set("VIS_CORE_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${VIS_CORE_INCLUDE_DIR}/)
set("VIS_CORE_CLASSES_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Classes)
include_directories(${VIS_CORE_CLASSES_DIR}/)
file(GLOB_RECURSE VIS_CORE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/* ${CMAKE_CURRENT_SOURCE_DIR}/Classes/*)
aux_source_directory(Source VIS_CORE_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${VIS_CORE_INCLUDE} ${VIS_CORE_SOURCE})

# set build option
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
mark_as_advanced(BUILD_SHARED_LIBS)

set(LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
    # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
    set(LIB_TYPE SHARED)
endif (BUILD_SHARED_LIBS)

add_library(VisCore SHARED ${VIS_CORE_INCLUDE} ${VIS_CORE_SOURCE})

if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE VIS_CORE_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME VIS_CORE
            EXPORT_MACRO_NAME VIS_CORE_EXPORTS
            EXPORT_FILE_NAME ${VIS_CORE_INCLUDE_DIR}/VisCoreExport.generate.h
            STATIC_DEFINE VIS_CORE_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER VisCore/Core)

