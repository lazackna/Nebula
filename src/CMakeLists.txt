cmake_minimum_required(VERSION 3.10.2)
project(nebula LANGUAGES C CXX)

file(GLOB_RECURSE nebula_src
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_SOURCE_DIR}/src/*.tpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.hpp"
        "${CMAKE_SOURCE_DIR}/src/**/*.tpp"
)

source_group(${PROJECT_NAME} ${nebula_src})
add_library(${PROJECT_NAME} ${nebula_src})
set(INCLUDE_DIRS "")
set(LIBRARIES "")

find_package(glad CONFIG REQUIRED)
list(APPEND LIBRARIES glad::glad)
list(APPEND INCLUDE_DIRS ${GLAD_INCLUDE_DIRS})

find_package(glfw3 CONFIG REQUIRED)
list(APPEND LIBRARIES glfw)
list(APPEND INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})

find_package(glm CONFIG REQUIRED)
list(APPEND LIBRARIES glm::glm)
list(APPEND INCLUDE_DIRS ${GLM_INCLUDE_DIRS})

find_package(nlohmann_json CONFIG REQUIRED)
list(APPEND LIBRARIES nlohmann_json::nlohmann_json)
list(APPEND INCLUDE_DIRS ${NLOHMANN_INCLUDE_DIRS})

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")
message(${TINYGLTF_INCLUDE_DIRS})
list(APPEND INCLUDE_DIRS ${TINYGLTF_INCLUDE_DIRS})

list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libIncludes)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE "${LIBRARIES}")