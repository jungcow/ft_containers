include .Makefile.googletest.env

CXX = c++
CXXFLAGS =
INCLUDES = -I.
LIBS = -lgtest -lgtest_main -lpthread

sample10:
	cd samples
	$(CXX) $(CXXFLAGS) ./samples/*.cc -o sample10 $(INCLUDES) $(LIBS)
