#include "GroupBox.hpp"
#include <TGWindow.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGLabel.h>
#include <TGCanvas.h>
#include <TGTextEntry.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include "decode.hpp"
#include <iostream>
#include <fstream>
#include <string>

ClassImp(GroupBox);

const std::string UserFileName = "UserNameList.txt";

GroupBox::GroupBox()
{
}

GroupBox::GroupBox(const TGWindow *p, const char *name, const char *title):
  TGGroupFrame(p, name), ifile(nullptr), UserId(0), EventNo(0), UserNum(0), Login(kFALSE)//, Map()
{
  // create GUI frames
  TGHorizontalFrame *horz = new TGHorizontalFrame(this, 500, 500, kFixedWidth); // make hori frame
  
  ///// create user id selecting tab /////
  TGVerticalFrame *fVL = new TGVerticalFrame(this, 100, 100);
  TGHorizontalFrame *fHL = new TGHorizontalFrame(fVL, 100, 40);
  // create popup menu
  fIdPopMenu = new TGPopupMenu(gClient->GetRoot());
  fIdPopMenu->AddEntry("Please select", UserNum);
  InitUser();
  fIdButton = new TGSplitButton(fHL, new TGHotString("Please select"),
				fIdPopMenu);
  // create login button
  fLogin = new TGTextButton(fHL, "Login");
  fLogin->Connect("Clicked()", "GroupBox", this, "ChangeLoginState()");
  // create textentry to add user
  fEntry = new TGTextEntry(fHL);
  fAdd = new TGTextButton(fHL, "Add user");
  fAdd->Connect("Clicked()", "GroupBox", this, "AddUser()");
  // set parts to frame of upside window
  fHL->AddFrame(fIdButton, new TGLayoutHints(kLHintsCenterX, 0, 0, 0, 0));
  fHL->AddFrame(fLogin, new TGLayoutHints(kLHintsCenterX, 0, 100, 0, 0));
  fHL->AddFrame(fEntry, new TGLayoutHints(kLHintsExpandX));
  fHL->AddFrame(fAdd, new TGLayoutHints(kLHintsCenterX));
  fVL->AddFrame(fHL, new TGLayoutHints(kLHintsCenterX));
  AddFrame(fVL, new TGLayoutHints(kLHintsCenterX));
  
  
  ///// create canvas //////
  canvas = new TRootEmbeddedCanvas("glec", horz, 500, 500); // make canvas
  horz->AddFrame(canvas, new TGLayoutHints(kLHintsLeft | kLHintsExpandY, 5, 5)); // set canvas to frame
  AddFrame(horz, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY)); // set frame to box
  
  TGVerticalFrame *vert = new TGVerticalFrame(this, 170, 50, kFixedWidth); // make vert frame
  AddFrame(vert, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set frame to box
  TGLabel *label = new TGLabel(vert, title); // make label
  vert->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set label to vert frame
  
  // create 2D-histograms
  track_a = new TH2D("track_a", "anode", 256, 0, 256, 1024, 0, 1024);
  track_c = new TH2D("track_c", "cathode", 256, 0, 256, 1024, 0, 1024);
}

void GroupBox::Update()
{
  canvas->GetCanvas()->Clear();
  //  canvas->GetCanvas()->Divide(2,1);
  
  ///// draw in canvas here /////
  track_a->Reset();
  track_c->Reset();
  tree->GetEntry(EventNo);
  decode(Map, track_a, track_c);
  canvas->GetCanvas()->Divide(2, 1);
  canvas->GetCanvas()->cd(1);
  track_a->SetStats(0);
  track_a->Draw();
  canvas->GetCanvas()->cd(2);
  track_c->SetStats(0);
  track_c->Draw();
  
  canvas->GetCanvas()->cd(0);
  canvas->GetCanvas()->Update();
}

void GroupBox::SetRunNo(const int runNo) // set run No.
{
  if(ifile!=nullptr){
    if(ifile->IsOpen()){
      ifile->Close();
    }
  }
  TString filename;
  filename.Form("%04d.root", runNo);
  ifile = TFile::Open(filename);
}

void GroupBox::LogIn(const int UID) // set user ID
{
  if(ofile.is_open()){
    ofile.close();
  }
  TString filename;
  UserId = UID;
  filename.Form("ID%02d.dat", UserId);
  ofile.open(filename, std::ios_base::app);
}

void GroupBox::LogOut()
{
  if(ifile->IsOpen()){
    ifile->Close();
  }
  if(ofile.is_open()){
    ofile.close();
  }
}

void GroupBox::SetBranchAddress()
{
  tree = (TTree*)ifile->Get("tree");
  tree->SetBranchAddress("Map", Map);
}

void GroupBox::InitUser()
{
  std::ifstream userfile(UserFileName);
  std::string username;
  while(getline(userfile, username)){
    fIdPopMenu->AddEntry(username.c_str(), ++UserNum);
  }
  userfile.close();
}

void GroupBox::AddUser()
{
  std::string username(fEntry->GetText());
  ++UserNum;
  fIdPopMenu->AddEntry(username.c_str(), UserNum);
  fEntry->Clear();
  std::ofstream userfile(UserFileName, std::ios_base::app);
  userfile << username << std::endl;
  userfile.close();
}

void GroupBox::ChangeLoginState()
{
  fLogin->SetState(kButtonDown);
  if(!Login){
    fLogin->SetText("Logout");
    fIdButton->SetState(kButtonDisabled);
    Login = kTRUE;
  }else{
    fLogin->SetText("Login");
    fIdButton->SetState(kButtonUp);
    Login = kFALSE;
  }
  fLogin->SetState(kButtonUp);
}
