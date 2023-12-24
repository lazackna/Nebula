cmake_minimum_required(VERSION 3.10.2)
project(engine LANGUAGES C CXX)

file(GLOB_RECURSE engine_src
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_SOURCE_DIR}/src/*.tpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.hpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.tpp"
)

source_group(${PROJECT_NAME} ${engine_src})
add_library(${PROJECT_NAME} ${engine_src})
set(INCLUDE_DIRS "")
set(LIBRARIES "")

find_package(glad CONFIG REQUIRED)
list(APPEND LIBRARIES glad::glad)

find_package(glfw3 CONFIG REQUIRED)
list(APPEND LIBRARIES glfw)

find_package(glm CONFIG REQUIRED)
list(APPEND LIBRARIES glm::glm)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE "${LIBRARIES}")
#target_link_libraries(${PROJECT_NAME} libs)