mkdir -p build

cd build

rm *

#cmake -DCMAKE_C_COMPILER=$CC ../git
#cmake --build .

src_files=\
'base/ftsystem '\
'base/ftinit '\
'base/ftdebug '\
'base/ftbase '\
'base/ftobjs '\
\
'base/ftbbox '\
'base/ftglyph '\
'base/ftbitmap '\
\
'cff/cff '\
'sfnt/sfnt '\
'truetype/truetype '\
\
'raster/raster '\
'smooth/smooth '\
\
'gzip/ftgzip '\
'autofit/autofit '\
'psaux/psaux '\
'pshinter/pshinter '\
'psnames/psnames '

$CC $CFLAGS -c \
	`echo ${src_files} | sed 's/[^ ]\+/..\/git\/src\/&.c /g'` \
	-I../git/include \
	-I../ \
	-D FT2_BUILD_LIBRARY \
	-D FT_CONFIG_OPTIONS_H=\"ftoption.h\" \
	-D FT_CONFIG_MODULES_H=\"ftmodule.h\"

ar -rs libfreetype.a `ls | sed 's/*.o/&/g'`