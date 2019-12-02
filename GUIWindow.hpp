#ifndef _GUIWINDOW_HPP_
#define _GUIWINDOW_HPP_

#include "GroupBox.hpp"
#include <TGFrame.h>
#include <TGButton.h>
#include <TGMenu.h>
#include <TObject.h>
#include <vector>
#include <string>

class GUIWindow: public TObject{
protected:
  TGMainFrame *fMain; // main frame
  GroupBox *fSelector; // echo mode (echo, password, no echo)
  
public:
  GUIWindow(int H, int W);
  virtual ~GUIWindow() { delete fMain;}
};

#endif
