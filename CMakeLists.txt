cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(aws-lambda-cpp-common VERSION 1.0.0 LANGUAGES CXX)

find_package(ZLIB REQUIRED)
find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

add_library(${PROJECT_NAME} STATIC
  "src/logger.cpp"
  "src/string_utils.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
  "include/aws-lambda-cpp"
  "include")

target_link_libraries(${PROJECT_NAME} PUBLIC
  AWS::aws-lambda-runtime
  ${AWSSDK_LINK_LIBRARIES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib64)

install(DIRECTORY "include" DESTINATION ".")

