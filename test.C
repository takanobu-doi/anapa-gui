// Mainframe macro generated from application: /usr/local/bin/root.exe
// By ROOT version 6.18/04 on 2019-11-03 15:12:08

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TRootContextMenu
#include "TRootContextMenu.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif

#include "Riostream.h"

void test()
{

   // main frame
   TGMainFrame *fMainFrame1086 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
   fMainFrame1086->SetName("fMainFrame1086");
   fMainFrame1086->SetLayoutBroken(kTRUE);
   TGTextButton *fTextButton640 = new TGTextButton(fMainFrame1086,"fTextButton640",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton640->SetTextJustify(36);
   fTextButton640->SetMargins(0,0,0,0);
   fTextButton640->SetWrapLength(-1);
   fTextButton640->Resize(92,24);
   fMainFrame1086->AddFrame(fTextButton640, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton640->MoveResize(544,40,92,24);
   TGTextButton *fTextButton649 = new TGTextButton(fMainFrame1086,"fTextButton649",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton649->SetTextJustify(36);
   fTextButton649->SetMargins(0,0,0,0);
   fTextButton649->SetWrapLength(-1);
   fTextButton649->Resize(92,24);
   fMainFrame1086->AddFrame(fTextButton649, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton649->MoveResize(544,80,92,24);
   TGTextButton *fTextButton658 = new TGTextButton(fMainFrame1086,"fTextButton658",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton658->SetTextJustify(36);
   fTextButton658->SetMargins(0,0,0,0);
   fTextButton658->SetWrapLength(-1);
   fTextButton658->Resize(92,24);
   fMainFrame1086->AddFrame(fTextButton658, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton658->MoveResize(544,120,92,24);

   TGFont *ufont;         // will reflect user font changes
   ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   TGGC   *uGC;           // will reflect user GC changes
   // graphics context changes
   GCValues_t valEntry667;
   valEntry667.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry667.fForeground);
   gClient->GetColorByName("#e8e8e8",valEntry667.fBackground);
   valEntry667.fFillStyle = kFillSolid;
   valEntry667.fFont = ufont->GetFontHandle();
   valEntry667.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry667, kTRUE);
   TGTextEntry *fTextEntry667 = new TGTextEntry(fMainFrame1086, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fTextEntry667->SetMaxLength(4096);
   fTextEntry667->SetAlignment(kTextLeft);
   fTextEntry667->SetText("fTextEntry667");
   fTextEntry667->Resize(86,fTextEntry667->GetDefaultHeight());
   fMainFrame1086->AddFrame(fTextEntry667, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextEntry667->MoveResize(24,8,86,22);
   TGTextButton *fTextButton680 = new TGTextButton(fMainFrame1086,"fTextButton680",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton680->SetTextJustify(36);
   fTextButton680->SetMargins(0,0,0,0);
   fTextButton680->SetWrapLength(-1);
   fTextButton680->Resize(92,24);
   fMainFrame1086->AddFrame(fTextButton680, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton680->MoveResize(120,8,92,24);

   // embedded canvas
   TRootEmbeddedCanvas *fRootEmbeddedCanvas702 = new TRootEmbeddedCanvas(0,fMainFrame1086,496,272,kSunkenFrame);
   fRootEmbeddedCanvas702->SetName("fRootEmbeddedCanvas702");
   Int_t wfRootEmbeddedCanvas702 = fRootEmbeddedCanvas702->GetCanvasWindowId();
   TCanvas *c123 = new TCanvas("c123", 10, 10, wfRootEmbeddedCanvas702);
   fRootEmbeddedCanvas702->AdoptCanvas(c123);
   fMainFrame1086->AddFrame(fRootEmbeddedCanvas702, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fRootEmbeddedCanvas702->MoveResize(16,56,496,272);

   fMainFrame1086->SetMWMHints(kMWMDecorAll,
                        kMWMFuncAll,
                        kMWMInputModeless);
   fMainFrame1086->MapSubwindows();

   fMainFrame1086->Resize(fMainFrame1086->GetDefaultSize());
   fMainFrame1086->MapWindow();
   fMainFrame1086->Resize(644,507);
}  
