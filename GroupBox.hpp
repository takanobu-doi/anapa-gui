#ifndef _GROUPBOX_HPP_
#define _GROUPBOX_HPP_

#include <TGWindow.h>
#include <TGFrame.h>
#include <TGCanvas.h>
#include <TCanvas.h>
#include <TRootEmbeddedCanvas.h>

////////// main part to treat data //////////

class GroupBox: public TGGroupFrame{
private:
  TRootEmbeddedCanvas *canvas;
  
public:
  GroupBox(const TGWindow *p, const char *name, const char *title, const int runNo);
  void Update();
};

#endif
