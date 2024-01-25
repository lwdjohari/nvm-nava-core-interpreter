cmake_minimum_required(VERSION 3.10)
project(nava.core.interpreter-v2 CXX)

message( "NVM::NAVA::CORE::INTERPRETERS PLUGINS v2")
message( "-----------------------------")
message(STATUS "NVM::NAVA2_CORE_INTERPRETERS LIB DIR:${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_ROLE "PROJECT")
message(STATUS "Current CMake role: ${CMAKE_ROLE}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(ABSL_PROPAGATE_CXX_STD ON)

option(LIB_NAVA2_CORE_INTERPRETERS_BUILD_DOC "Build documentation" OFF)
option(LIB_NAVA2_CORE_INTERPRETERS_SANITIZE_ADDRESS "SANITIZE ADDRESS" OFF)
option(LIB_NAVA2_CORE_INTERPRETERS_USE_CATCH ON)
option(LIB_NAVA2_CORE_INTERPRETERS_USE_LIB ON)
option(LIB_NAVA2_CORE_INTERPRETERS_USE_TEST OFF)

set(LIB_NAVA2_CORE_INTERPRETERS_SANITIZE_ADDRESS OFF)

# Add ASAN
if(LIB_NAVA2_CORE_INTERPRETERS_SANITIZE_ADDRESS)
    set(SANITIZE_ADDRESS ON)
endif(LIB_NAVA2_CORE_INTERPRETERS_SANITIZE_ADDRESS)

#  make ourself sanitize and sane well.
if(NOT Sanitizers_FOUND)
 find_package(Sanitizers)
endif()

# Add Doxygen
if(LIB_NAVA2_CORE_INTERPRETERS_BUILD_DOC)
    if(NOT DOXYGEN_FOUND)
        find_package(Doxygen)
    endif()

    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/generated/docs-cached/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

         # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_coreinterpreters ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated/docs-cached/
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(LIB_NAVA2_CORE_INTERPRETERS_BUILD_DOC)

# Add Unit Test Lib Catch2
if(LIB_NAVA2_CORE_INTERPRETERS_USE_CATCH)
 message(STATUS  "CATCH2::ADD_LIB.")
 find_package(Catch2 3 REQUIRED)
endif()

# Add dependencies source code
add_subdirectory(deps/pegtl-3.2.7 build-pegtl)

# Add Python, we will embed the python

# find_package (Python3 REQUIRED COMPONENTS Development )
# message(STATUS "Found Python: ${Python3_FOUND} ${Python3_INTERPRETER_ID} ${Python3_EXECUTABLE}")
# message(STATUS "Found Python3_LIBRARIES: ${Python3_LIBRARIES}")
# message(STATUS "Found Python3_Development_FOUND: ${Python3_Development_FOUND}")
# if (Python3_Development_FOUND)
#     include_directories(${Python3_INCLUDE_DIRS})
# else()
#     message(FATAL_ERROR "Python dev C headers required (python-dev package)" )
# endif()

find_package(Python3 COMPONENTS Interpreter Development.Embed REQUIRED)
add_subdirectory(deps/pybind11 build/pybind11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/navascript/helo-python.py
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/navascript/)

# Main headers and sources
file(GLOB_RECURSE SOURCES_NAVA2_CORE_INTERPRETERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)

add_library(${PROJECT_NAME} ${SOURCES_NAVA2_CORE_INTERPRETERS} )
target_link_libraries(${PROJECT_NAME} 
    nvm-core
    pybind11::embed
    utf8cpp
    taocpp::pegtl
    )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        inc/

)



add_executable(${PROJECT_NAME}-test main.cc)
# if(Sanitizers_FOUND AND LIB_NAVA2_CORE_INTERPRETERS_SANITIZE_ADDRESS )
#     add_sanitizers("${PROJECT_NAME}-test")
#     message(STATUS "${PROJECT_NAME}-test_LIB::ASAN:ON.")
# endif()

target_link_libraries(${PROJECT_NAME}-test PRIVATE  ${PROJECT_NAME} )
target_include_directories("${PROJECT_NAME}-test"
    PUBLIC
        inc/
)
        

if(LIB_NAVA2_CORE_INTERPRETERS_USE_TEST)
    message(STATUS "TEST::ADD_UNIT_TEST.")
    add_subdirectory(tests)
endif()       

message(STATUS "Nava::Core LIB Configuration Done!\n")
set(nava2_core_pinterpreters_FOUND  ON)