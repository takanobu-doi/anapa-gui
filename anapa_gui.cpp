#include <iostream>
#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include "GUIWindow.hpp"

int main(int argc, char *argv[])
{
  int h = 500;
  int w = 500;
  if(argc==3){
    h = atoi(argv[1]);
    w = atoi(argv[2]);
  }
  TApplication app("app", &argc, argv);
  new GUIWindow(h, w);
  app.Run();

  return 0;
}
