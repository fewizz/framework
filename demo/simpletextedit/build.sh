cd $(dirname ${BASH_SOURCE[0]})
main_dir=../..
lib_dir=$main_dir/lib

pushd $lib_dir/glfw
bash build.sh
popd

pushd $lib_dir/freetype
bash build.sh
popd

#pushd $lib_dir/freetype-wrapper
#make CXX=$CXX CXXARGS=c++17
#popd

#pushd $lib_dir/opengl-wrapper
#bash build.sh
#popd

$CXX -std=c++17 \
-I $main_dir/src/code \
-I $lib_dir/glm \
-I $lib_dir/utfcpp/source \
-I $lib_dir/glfw/git/include \
-I $lib_dir/glfw-wrapper/include \
-I $lib_dir/freetype/git/include \
-I $lib_dir/freetype-wrapper/include \
-D GL_INCLUDE \
-I $lib_dir/opengl-wrapper/include \
-I $lib_dir/opengl-wrapper/src \
main.cpp \
$lib_dir/glfw/build/src/libglfw3.a \
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