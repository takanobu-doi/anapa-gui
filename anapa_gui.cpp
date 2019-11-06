#include <iostream>
#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include "GUIWindow.hpp"

int main(int argc, char *argv[])
{
  int runNo = 97;
  TApplication app("app", &argc, argv);
  new GUIWindow(runNo);
  app.Run();

  return 0;
}
