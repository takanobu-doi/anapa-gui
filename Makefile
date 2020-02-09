CXX = g++
TARGET = eyescan
OBJ = eyescan.o MyClassDict.o GUIWindow.o GroupBox.o decode.o ClickPos.o
SOURCE = eyescan.cpp MyClassDict.cpp GUIWindow.cpp GroupBox.cpp decode.cpp ClickPos.cpp
INC = GUIWindow.hpp GroupBox.hpp decode.hpp ClickPos.hpp
ROOT_LIBS = $(shell root-config --glibs)
ROOT_FLAGS = $(shell root-config --cflags)
CFLAGS = -O4 -Wall $(ROOT_FLAGS)
LIBS = $(ROOT_LIBS)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(CFLAGS) $(LIBS)
MyClassDict.cpp: GroupBox.hpp LinkDef.h
	@echo "Generating dictionary ..."
	rootcint -f MyClassDict.cpp -c GroupBox.hpp LinkDef.h
.cpp.o:
	$(CXX) -c $< $(CFLAGS)
clean:
	$(RM) *.o $(TARGET) *~
reflesh:
	$(RM) *.o *=
