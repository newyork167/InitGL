# Project definition
cmake_minimum_required(VERSION 3.1)
project(InitGL)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES "${SRC_DIR}/main.cpp" source/Lesson1/Lesson1.cpp source/Lesson1/Lesson1.h source/ShaderReader/ShaderReader.cpp source/ShaderReader/ShaderReader.h)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADERS_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# Add Boost
find_package(Boost 1.69 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

## Add Shader and Fragment files
#include_directories("${SRC_DIR}/Lesson1")
#set(SHADERS_DIR "${SRC_DIR}/shaders")
#set(CHAPTERS ${SRC_DIR}/Lesson1)
#
#foreach(CHAPTER ${CHAPTERS})
#    file(GLOB SOURCE
#            "${SRC_DIR}/${CHAPTER}/*.h"
#            "${SRC_DIR}/${CHAPTER}/*.cpp"
#            "${SRC_DIR}/${CHAPTER}/*.vert"
#            "${SRC_DIR}/${CHAPTER}/*.frag"
#            )
#    set(NAME "${CHAPTER}")
#    add_executable(${PROJECT_NAME} ${SOURCE})
#    target_link_libraries(${NAME} ${LIBS})
#    if(WIN32)
#        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CHAPTER}")
#    elseif(UNIX AND NOT APPLE)
#        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}")
#    elseif(APPLE)
#        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}")
#        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}")
#        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}")
#    endif(WIN32)
#
#    file(GLOB SHADERS
#            "${SRC_DIR}/${CHAPTER}/*.vert"
#            "${SRC_DIR}/${CHAPTER}/*.frag"
#            )
#    foreach(SHADER ${SHADERS})
#        if(WIN32)
#            # configure_file(${SHADER} "test")
#            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
#        elseif(UNIX AND NOT APPLE)
#            file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
#        elseif(APPLE)
#            # create symbolic link for *.vs *.fs *.gs
#            get_filename_component(SHADERNAME ${SHADER} NAME)
#            makeLink(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}/${SHADERNAME} ${NAME})
#        endif(WIN32)
#    endforeach(SHADER)
#endforeach(CHAPTER)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
