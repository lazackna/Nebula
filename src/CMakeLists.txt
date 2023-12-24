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

LIST(APPEND ../lib)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC "${LIBRARIES}")
#target_link_libraries(${PROJECT_NAME} libs)