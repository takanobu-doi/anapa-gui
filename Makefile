CXX = g++
TARGET = anapa_gui
OBJ = anapa_gui.o GUIWindow.o GroupBox.o
SOURCE = anapa_gui.cpp GUIWindow.cpp GroupBox.cpp
INC = GUIWindow.hpp GroupBox.hpp
ROOT_LIBS = $(shell root-config --glibs)
ROOT_FLAGS = $(shell root-config --cflags)
CFLAGS = -O4 -Wall $(ROOT_FLAGS)
LIBS = $(ROOT_LIBS)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(CFLAGS) $(LIBS)
.cpp.o:
	$(CXX) -c $< $(CFLAGS)
clean:
	$(RM) *.o $(TARGET) *~
reflesh:
	$(RM) *.o *=
