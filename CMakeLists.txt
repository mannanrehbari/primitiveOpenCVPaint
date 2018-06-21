project (primitiveOpenCVPaint)
cmake_minimum_required(VERSION 2.8)

# configure OpenCV
find_package(OpenCV REQUIRED)

# create create individual projects
add_executable(primitivePaint primPaint.cpp)
target_link_libraries(primitivePaint ${OpenCV_LIBS})
