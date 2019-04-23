mkdir -p build
cd build
cmake \
-D CMAKE_C_COMPILER=$CC \
-D GLFW_BUILD_DOCS=OFF \
-D GLFW_BUILD_EXAMPLES=OFF \
-D GLFW_BUILD_TESTS=OFF \
-D GLFW_INSTALL=OFF \
../git
cmake --build .
