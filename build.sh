cd $(dirname ${BASH_SOURCE[0]})

mkdir -p build

cd build

rm *

main_dir=..
lib_dir=$main_dir/lib
code_dir=$main_dir/src/code

echo -e "\e[92mBuilding Freetype\e[0m"

pushd $lib_dir/freetype
bash build.sh
popd

echo -e "\e[92mBuilding GLFW\e[0m"

pushd $lib_dir/glfw
bash build.sh
popd

echo -e "\e[92mBuilding Framework\e[0m"

$CXX $CXXFLAGS -std=c++17 -c \
-I $code_dir \
-I $lib_dir/opengl-wrapper/code \
-I $lib_dir/glm \
-I $lib_dir/freetype-wrapper/include \
-I $lib_dir/freetype/git/include \
-I $lib_dir/minimp3 \
-I $lib_dir/lodepng \
-D GL_INCLUDE \
$code_dir/fwk/texture_atlas.cpp \
$code_dir/fwk/glyph_cache.cpp \
$code_dir/fwk/mp3.cpp \
$code_dir/fwk/png.cpp \
$lib_dir/lodepng/lodepng.cpp

ar -rs libframework.a `ls | sed 's/*.o/&/g'`