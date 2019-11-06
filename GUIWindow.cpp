#include "GUIWindow.hpp"
#include "GroupBox.hpp"
#include <TGTextEntry.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGLabel.h>
#include <TGComboBox.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGButton.h>
#include <TGMenu.h>
#include <TObject.h>
#include <TROOT.h>
#include <TApplication.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

////////// create gui window & set button and textentry //////////
GUIWindow::GUIWindow(int runNo)
{
//  TGTextEntry *entry;
//  TGTextButton *next;
//  TGTextButton *back;

  ///// create main frame /////
  fMain = new TGMainFrame(gClient->GetRoot(), 10, 10, kMainFrame | kVerticalFrame);
  // recusively delete all subframes on exit //
  fMain->SetCleanup(kDeepCleanup);
  
  ///// create group frame //////
  fSelector = new GroupBox(fMain, "Event viewer", "Selector");
  fSelector->SetRunNo(runNo);
  fSelector->SetBranchAddress();
  fSelector->Update();
  fMain->AddFrame(fSelector, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5));

  // terminate ROOT session when window is closed //
  fMain->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  fMain->DontCallClose();
  fMain->MapSubwindows();
  // set minimux width, height //
  fMain->SetWMSizeHints(fMain->GetDefaultWidth(), fMain->GetDefaultHeight(),
			1000, 1000, 0, 0);
  fMain->SetWindowName("Test");
  fMain->MapRaised();

}

