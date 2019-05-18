cd $(dirname ${BASH_SOURCE[0]})

mkdir -p build

cd build

main_dir=..
lib_dir=$main_dir/lib
code_dir=$main_dir/src/code

$CXX -std=c++17 \
$code_dir/glyph_cache.cpp \
$code_dir/mp3.cpp \
$code_dir/png.cpp \
$code_dir/texture_atlas.cpp \
-I $code_dir \
-I $lib_dir/opengl-wrapper/include \
-I $lib_dir/glm \
-I $lib_dir/freetype-wrapper/include \
-I $lib_dir/freetype/git/include \
-I $lib_dir/minimp3 \
-I $lib_dir/lodepng