cmake_minimum_required(VERSION 3.12) 
set(CMAKE_CXX_STANDARD 20) 
project(demo LANGUAGES CXX) 
find_package(aws-lambda-runtime) 
find_package(AWSSDK COMPONENTS core) 
find_package(mongocxx REQUIRED) 
find_package(bsoncxx REQUIRED) 

include_directories(${LIBMONGOCXX_INCLUDE_DIR}) 
include_directories(${LIBBSONCXX_INCLUDE_DIR}) 

add_executable(${PROJECT_NAME} "main.cpp" "helper.cpp" "mongoDbHelper.cpp") 
target_link_libraries(${PROJECT_NAME} PRIVATE AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES}) 
target_link_libraries(${PROJECT_NAME} PRIVATE mongo::bsoncxx_shared) 
target_link_libraries(${PROJECT_NAME} PRIVATE mongo::mongocxx_shared) 
 
target_compile_features(${PROJECT_NAME} PRIVATE "cxx_std_20") 
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-O3" "-mavx2") 

aws_lambda_package_target(${PROJECT_NAME}) 