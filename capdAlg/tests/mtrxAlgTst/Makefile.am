include ${capdMake}/make/common_makefile.mkf

check_PROGRAMS=floatMatrixAlgorithmsTest intMatrixAlgorithmsTest
TESTS=${check_PROGRAMS}

floatMatrixAlgorithmsTest_SOURCES=floatMatrixAlgorithmsTest.cpp
floatMatrixAlgorithmsTest_CXXFLAGS=${capdintervals_CFLAGS}
floatMatrixAlgorithmsTest_libs=${capdintervals_LIBS}
floatMatrixAlgorithmsTest_LDADD=${floatMatrixAlgorithmsTest_libs}
floatMatrixAlgorithmsTest_DEPENDENCIES=${filter %.a %.la,${floatMatrixAlgorithmsTest_libs}}

intMatrixAlgorithmsTest_SOURCES=intMatrixAlgorithmsTest.cpp
intMatrixAlgorithmsTest_CXXFLAGS=${capdintervals_CFLAGS}
intMatrixAlgorithmsTest_libs=${capdintervals_LIBS}
intMatrixAlgorithmsTest_LDADD=${intMatrixAlgorithmsTest_libs}
intMatrixAlgorithmsTest_DEPENDENCIES=${filter %.a %.la,${intMatrixAlgorithmsTest_libs}}

