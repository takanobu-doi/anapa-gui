#ifndef _GUIWINDOW_HPP_
#define _GUIWINDOW_HPP_

#include "GroupBox.hpp"
#include <TGFrame.h>

class GUIWindow{
protected:
  TGMainFrame *fMain; // main frame
  GroupBox *fSelector; // echo mode (echo, password, no echo)
public:
  GUIWindow(int runNo);
  virtual ~GUIWindow() { delete fMain;}
//  void ChangeStrings();
//  ClassDef(GUIWindow, 0);
};

#endif
