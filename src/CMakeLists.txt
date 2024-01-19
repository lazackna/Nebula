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

find_package(EnTT CONFIG REQUIRED)
list(APPEND LIBRARIES EnTT::EnTT)
list(APPEND INCLUDE_DIRS ${ENTT_INCLUDE_DIRS})

find_package(assimp CONFIG REQUIRED)
list(APPEND LIBRARIES assimp::assimp)
list(APPEND INCLUDE_DIRS ${ASSIMP_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE "${LIBRARIES}")