cd $(dirname ${BASH_SOURCE[0]})
lib_dir=../../lib

pushd $lib_dir/glfw
bash build.sh
popd

pushd $lib_dir/freetype
bash build.sh
popd

pushd $lib_dir/freetype-wrapper
make CXX=$CXX CXXARGS=c++17
popd

#pushd $lib_dir/opengl-wrapper
#bash build.sh
#popd

$CXX --std=c++17 \
-I$lib_dir/glfw/git/include \
-I$lib_dir/glfw-wrapper/include \
-I$lib_dir/freetype/git/include \
-I$lib_dir/freetype-wrapper/include \
-DGL_INCLUDE \
-I$lib_dir/opengl-wrapper/include \
-I$lib_dir/opengl-wrapper/src \
main.cpp \
$lib_dir/glfw/build/src/libglfw3.a \
$lib_dir/freetype-wrapper/libfreetype-wrapper.a \
$lib_dir/freetype/build/libfreetype.a \
-lOpenGL \
-lz \
-lpng \
-lm \
-pthread \
-lrt \
-ldl \
-lX11 \
-o build/simpletextedit
