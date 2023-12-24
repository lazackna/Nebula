project(glad LANGUAGES C CXX)

source_group(${PROJECT_NAME} src/glad.c)
add_library(${PROJECT_NAME} include/glad/glad.h include/KHR/khrplatform.h)

target_include_directories(${PROJECT_NAME} PUBLIC include)