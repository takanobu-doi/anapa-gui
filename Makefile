CXX = g++
TARGET = anapa_gui
OBJ = anapa_gui.o GUIWindow.o GroupBox.o decode.o MyClassDict.o
SOURCE = anapa_gui.cpp GUIWindow.cpp GroupBox.cpp decode.cpp MyClassDict.cpp
INC = GUIWindow.hpp GroupBox.hpp decode.hpp
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
