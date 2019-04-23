mkdir -p build

$CXX --std=c++17 \
-Iinclude \
src/glyph_cache.cpp \
src/mp3.cpp \
src/png.cpp \
src/texture_atlas.cpp \

