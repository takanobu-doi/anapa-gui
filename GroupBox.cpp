#include "GroupBox.hpp"
#include <TGWindow.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGLabel.h>
#include <TGCanvas.h>
#include <TH1.h>

GroupBox::GroupBox(const TGWindow *p, const char *name, const char *title, const int runNo):
  TGGroupFrame(p, name)
{
  TGHorizontalFrame *horz = new TGHorizontalFrame(this, 500, 500, kFixedWidth); // make hori frame
  canvas = new TRootEmbeddedCanvas("glec", horz, 500, 500); // make canvas
  horz->AddFrame(canvas, new TGLayoutHints(kLHintsLeft | kLHintsExpandY, 5, 5)); // set canvas to frame
  AddFrame(horz, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY)); // set frame to box
  
  TGVerticalFrame *vert = new TGVerticalFrame(this, 170, 50, kFixedWidth); // make vert frame
  AddFrame(vert, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set frame to box
  TGLabel *label = new TGLabel(vert, title); // make label
  vert->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set label to frame

  Update();
}

void GroupBox::Update()
{
  canvas->GetCanvas()->Clear();
//  canvas->GetCanvas()->Divide(2,1);

  ///// draw in canvas here /////
  TH1D *h = new TH1D("h", "h", 100, -10, 10);
  h->FillRandom("gaus", 10000);
//  canvas->GetCanvas()->cd(1);
//  h->Draw();
//  canvas->GetCanvas()->cd(2);
  h->Draw();

  canvas->GetCanvas()->cd(0);
  canvas->GetCanvas()->Update();
}
