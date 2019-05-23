# Project definition
cmake_minimum_required(VERSION 3.1)
project(InitGL)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
#set(SOURCES "${SRC_DIR}/main.cpp" source/Lesson1/Lesson1.cpp source/Lesson1/Lesson1.h source/ShaderReader/ShaderReader.cpp source/ShaderReader/ShaderReader.h)
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.vert"
    "${SRC_DIR}/*.frag"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# Add Boost
find_package(Boost 1.69 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

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

# Add Shaders
macro(makeLink src dest target)
    add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

file(GLOB_RECURSE SHADERS
        "${SRC_DIR}/*.vert"
        "${SRC_DIR}/*.frag"
        )
foreach(SHADER ${SHADERS})
    message(${SHADER})
    if(WIN32)
        # configure_file(${SHADER} "test")
        add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
    elseif(UNIX AND NOT APPLE)
        file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
    elseif(APPLE)
        # create symbolic link for *.vs *.fs *.gs
        get_filename_component(SHADERNAME ${SHADER} NAME)
        makeLink(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/${SHADERNAME} ${PROJECT_NAME})
    endif(WIN32)
endforeach(SHADER)
