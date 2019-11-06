#include "GroupBox.hpp"
#include <TApplication.h>
#include <TGWindow.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGLabel.h>
#include <TGCanvas.h>
#include <TGTextEntry.h>
#include <TGButtonGroup.h>
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
const std::string RunFileName = "RunNumberList.txt";
const Int_t Width = 600;
const Int_t Height = 600;

GroupBox::GroupBox()
{
}

GroupBox::GroupBox(const TGWindow *p, const char *name):
  TGGroupFrame(p, name), ifile(nullptr), UserId(0), EventNo(0), UserNum(0), Login(kFALSE), AnaState(kFALSE)//, Map()
{
  // create GUI frames
  TGHorizontalFrame *horz = new TGHorizontalFrame(this, Width, Height, kFixedWidth); // make hori frame

  TGHorizontalFrame *fHL = new TGHorizontalFrame(this, Width, 40);
  TGVerticalFrame *fVL = new TGVerticalFrame(fHL, 300, 40);
  ///// create user id selecting area /////
  TGHorizontalFrame *fHL1 = new TGHorizontalFrame(fVL, Width/2, 40);
  // create popup menu
  fIdPopMenu = new TGPopupMenu(gClient->GetRoot());
  fIdPopMenu->AddEntry("Please select", UserNum);
  fIdPopMenu->Connect("Activated(Int_t)", "GroupBox", this, "SetUserId(Int_t)");
  InitUser();
  fIdButton = new TGSplitButton(fHL1, new TGHotString("Please select"),
				fIdPopMenu);
  TGLabel *userlabel = new TGLabel(fHL1, "User: ");
  // create login button
  fLogin = new TGTextButton(fHL1, "Login");
  fLogin->Connect("Clicked()", "GroupBox", this, "ChangeLoginState()");
  // create textentry to add user
  fEntry = new TGTextEntry(fHL1);
  fAdd = new TGTextButton(fHL1, "Add user");
  fAdd->Connect("Clicked()", "GroupBox", this, "AddUser()");

  ///// create run number selecting area /////
  TGHorizontalFrame *fHL2 = new TGHorizontalFrame(fVL, Width/2,40);
  TGLabel *runlabel = new TGLabel(fHL2, "Run#: ");
  // create popup menu for runNo
  fRunPopMenu = new TGPopupMenu(gClient->GetRoot());
  fRunPopMenu->AddEntry("Please select", RunNum);
  fRunPopMenu->Connect("Activated(Int_t)", "GroupBox", this, "SetRunNo(Int_t)");
  InitRun();
  fRunButton = new TGSplitButton(fHL2, new TGHotString("Please select"),
				 fRunPopMenu);
  fRunButton->SetState(kButtonDisabled);
  // create start button
  fStart = new TGTextButton(fHL, "Start");
  fStart->SetState(kButtonDisabled);
  fStart->Connect("Clicked()", "GroupBox", this, "StartStopAnalysis()");
  //create exit button
  TGTextButton *fExit = new TGTextButton(fHL, "Exit");
  fExit->Connect("Clicked()", "GroupBox", this, "Exit()");
  
  // set parts to frame of upside window
  fHL1->AddFrame(userlabel, new TGLayoutHints(kLHintsNormal));
  fHL1->AddFrame(fIdButton, new TGLayoutHints(kLHintsNormal));
  fHL1->AddFrame(fLogin, new TGLayoutHints(kLHintsNormal));
  fHL1->AddFrame(fEntry, new TGLayoutHints(kLHintsExpandX));
  fHL1->AddFrame(fAdd, new TGLayoutHints(kLHintsNormal));
  fHL2->AddFrame(runlabel, new TGLayoutHints(kLHintsNormal));
  fHL2->AddFrame(fRunButton, new TGLayoutHints(kLHintsNormal));
  fVL->AddFrame(fHL1, new TGLayoutHints(kLHintsNormal));
  fVL->AddFrame(fHL2, new TGLayoutHints(kLHintsNormal));
  fHL->AddFrame(fVL, new TGLayoutHints(kLHintsLeft));
  fHL->AddFrame(fStart, new TGLayoutHints(kLHintsCenterY, 20, 0, 0, 0));
  fHL->AddFrame(fExit, new TGLayoutHints(kLHintsCenterY, 20, 0, 0, 0));
  AddFrame(fHL, new TGLayoutHints(kLHintsLeft));
  
  
  ///// create canvas //////
  canvas = new TRootEmbeddedCanvas("glec", horz, Width, Height); // make canvas
  horz->AddFrame(canvas, new TGLayoutHints(kLHintsLeft | kLHintsExpandY, 5, 5)); // set canvas to frame
  AddFrame(horz, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY)); // set frame to box

  ///// create analysis space /////
  TGVerticalFrame *vert = new TGVerticalFrame(this, Width, 50, kFixedWidth); // make vert frame
  AddFrame(vert, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set frame to box
  label = new TGLabel(vert, "Event No.              "); // make label
  vert->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 20, 0, 0, 0)); // set label to vert frame
  TGHorizontalFrame *horz2 = new TGHorizontalFrame(vert, Width, 50, kFixedWidth); // make horz frame
  vert->AddFrame(horz2, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set horz2 to vert frame
  // create radio button & select button
  fEventSelect = new TGButtonGroup(horz2, "Track Number", kChildFrame | kHorizontalFrame);
  new TGRadioButton(fEventSelect, "1", 1);
  new TGRadioButton(fEventSelect, "2", 2);
  new TGRadioButton(fEventSelect, "3", 3);
  new TGRadioButton(fEventSelect, "4<", 4);
  fEventSelect->Connect("Pressed(Int_t)", "GroupBox", this, "SetEvent(Int_t)");
  fEventSelect->SetButton(1);
  fSelect = new TGTextButton(horz2, "Select");
  fSelect->SetState(kButtonDisabled);
  fSelect->Connect("Clicked()", "GroupBox", this, "GetEvent()");
  message = new TGLabel(horz2, "                                                               \n\n");
  horz2->AddFrame(fEventSelect, new TGLayoutHints(kLHintsLeft)); // set radio button to horz2 frame
  horz2->AddFrame(fSelect, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set select button to horz2 frame
  horz2->AddFrame(message, new TGLayoutHints(kLHintsNormal));

  // create next & cancel button
  fNext = new TGTextButton(horz2, "Next");
  fNext->Connect("Clicked()", "GroupBox", this, "Next()");
  fNext->SetState(kButtonDisabled);
  fCancel = new TGTextButton(horz2, "Cancel");
  fCancel->Connect("Clicked()", "GroupBox", this, "Cancel()");
  horz2->AddFrame(fCancel, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
  horz2->AddFrame(fNext, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 0, 10, 0, 0));
  
  // create 2D-histograms
  track_a = new TH2D("track_a", "anode", 256, 0, 256, 1024, 0, 1024);
  track_c = new TH2D("track_c", "cathode", 256, 0, 256, 1024, 0, 1024);
}

void GroupBox::Update() // Unlock all selector and update images
{
  canvas->GetCanvas()->Clear();
  std::string label_str = "Event No. " + std::to_string(EventNo);
  label->SetText(label_str.c_str());
  
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

void GroupBox::SetUserId(Int_t UID)
{
  UserId = UID;
}

void GroupBox::SetRunNo(Int_t runNo) // set run No.
{
  RunNo = runNo;
}

int GroupBox::OpenRootFile(){
  if(ifile!=nullptr){
    if(ifile->IsOpen()){
      ifile->Close();
    }
  }
  TString filename;
  filename.Form("%04d.root", RunNo);
  ifile = TFile::Open(filename);
  if(ifile!=nullptr){
    if(ifile->IsOpen()){
      return 1;
    }
  }
  return 0;
}

void GroupBox::ChangeLoginState()
{
  if(!Login){
    LogIn();
  }else{
    LogOut();
  }
}

void GroupBox::LogIn() // set user ID
{
  if(UserId!=0){
    if(ofile.is_open()){
      ofile.close();
    }
    TString filename;
    filename.Form("ID%02d.dat", UserId);
    ofile.open(filename, std::ios_base::app);
    fLogin->SetText("Logout");
    fIdButton->SetState(kButtonDisabled);
    fAdd->SetState(kButtonDisabled);
    fRunButton->SetState(kButtonUp);
    fStart->SetState(kButtonUp);
    Login = kTRUE;
  }else{
    fIdButton->SetState(kButtonUp);
    fRunButton->SetState(kButtonDisabled);
  }
}

void GroupBox::LogOut()
{
  if(ifile!=nullptr){
    if(ifile->IsOpen()){
      ifile->Close();
    }
  }
  if(ofile.is_open()){
    ofile.close();
  }
  fIdButton->SetState(kButtonUp);
  fLogin->SetText("Login");
  fAdd->SetState(kButtonUp);
  fRunButton->SetState(kButtonDisabled);
  fStart->SetState(kButtonDisabled);
  Login = kFALSE;
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

void GroupBox::InitRun()
{
  std::ifstream runfile(RunFileName);
  std::string runnumber;
  while(getline(runfile, runnumber)){
    fRunPopMenu->AddEntry(runnumber.c_str(), stoi(runnumber));
  }
  runfile.close();
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

void GroupBox::SetEvent(Int_t Id)
{
  EventId = Id;
}

int GroupBox::GetEvent()
{
  fNext->SetState(kButtonUp);
  fSelect->SetState(kButtonDisabled);
  std::string str;
  if(EventId<4){
    str = "Please click " + std::to_string(EventId) + "points.\n Then go next.";
  }else{
    str = "Go Next";
  }
  message->SetText(str.c_str());
  return EventId;
}

void GroupBox::Next()
{
  EventNo++;
  Reset();
  if(EventNo<MaxEventNo){
    Update();
  }else{
    EndOfFile();
  }
}

void GroupBox::Cancel()
{
  Reset();
}

void GroupBox::Init()
{
  MaxEventNo = tree->GetEntries();
  EventNo = 0;
  Reset();
}

void GroupBox::Reset()
{
  EventId = 0;
  pos.clear();
  fEventSelect->SetButton(1);
  fNext->SetState(kButtonDisabled);
  fSelect->SetState(kButtonUp);
  message->SetText("Please select event type");
}

void GroupBox::EndOfFile()
{
  fRunButton->SetState(kButtonUp);
  fLogin->SetState(kButtonUp);
  fStart->SetText("Start");
  AnaState = kFALSE;
}

void GroupBox::StartStopAnalysis()
{
  if(AnaState){
    fRunButton->SetState(kButtonUp);
    fLogin->SetState(kButtonUp);
    fStart->SetText("Start");
    AnaState = kFALSE;
  }else{
    if(OpenRootFile()){
      SetBranchAddress();
      Update();
      Init();
      fRunButton->SetState(kButtonDisabled);
      fLogin->SetState(kButtonDisabled);
      fStart->SetText("Stop");
      AnaState = kTRUE;
    }else{
      fRunButton->SetState(kButtonUp);
      fStart->SetText("Start");
      AnaState = kFALSE;
    }
  }
}

void GroupBox::Exit()
{
  LogOut();
  gApplication->Terminate();
}
