mkdir -p build

cd build

#cmake -DCMAKE_C_COMPILER=$CC ../git
#cmake --build .

src_files0=\
'base/ftsystem '\
'base/ftinit '\
'base/ftdebug '\
'base/ftbase '\
\
'base/ftbbox '\
'base/ftglyph '\
'base/ftbitmap '\
\
'sfnt/sfnt '\
'truetype/truetype '\
\
'raster/raster '\
'smooth/smooth '\
\
'psnames/psnames '

for x in ${src_files0}; do src_files="${src_files} ../git/src/${x}.c"; done

${CC} -c \
	${src_files} \
	-I../git/include \
	-DFT2_BUILD_LIBRARY

ar -rs libfreetype.a `find *.o` 
