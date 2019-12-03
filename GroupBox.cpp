#include "GroupBox.hpp"
#include "ClickPos.hpp"
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
#include <TStyle.h>
#include <TROOT.h>
#include "decode.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

ClassImp(GroupBox);

const std::string UserFileName = ".UserNameList.txt";
const std::string RunFileName = ".RunNumberList.txt";
const std::string ProgressFileName = ".ProgressID";

GroupBox::GroupBox()
{
}

GroupBox::GroupBox(const TGWindow *p, const char *name, const int H, const int W):
  TGGroupFrame(p, name), ifile(nullptr), UserId(0), EventNo(0), UserNum(0), RunNum(0), Login(kFALSE), AnaState(kFALSE), Selected(kFALSE)//, Map()
{  
  const Int_t Height = H;
  const Int_t Width = W;
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
  LoadRun();
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
  fEventSelect = new TGButtonGroup(horz2, "Track Number", kChildFrame | kVerticalFrame);
  new TGRadioButton(fEventSelect, "1", 1);
  new TGRadioButton(fEventSelect, "2", 2);
  new TGRadioButton(fEventSelect, "3", 3);
  new TGRadioButton(fEventSelect, "4~", 4);
  fEventSelect->Connect("Pressed(Int_t)", "GroupBox", this, "SetEvent(Int_t)");
  fEventSelect->SetButton(0);
  fSelect = new TGTextButton(horz2, "Select");
  fSelect->SetState(kButtonDisabled);
  fSelect->Connect("Clicked()", "GroupBox", this, "GetEvent()");
  message = new TGLabel(horz2, "                                                      \n\n");
  horz2->AddFrame(fEventSelect, new TGLayoutHints(kLHintsLeft, 20, 0, 0, 0)); // set radio button to horz2 frame
  horz2->AddFrame(fSelect, new TGLayoutHints(kLHintsLeft | kLHintsCenterY)); // set select button to horz2 frame
  horz2->AddFrame(message, new TGLayoutHints(kLHintsNormal));

  // create anode & cathode button
  fAnode = new TGTextButton(horz2, "Anode");
  fAnode->Connect("Clicked()", "GroupBox", this, "Anode()");
  fAnode->SetState(kButtonDisabled);
  fCathode = new TGTextButton(horz2, "Cathode");
  fCathode->Connect("Clicked()", "GroupBox", this, "Cathode()");
  fCathode->SetState(kButtonDisabled);
  horz2->AddFrame(fAnode, new TGLayoutHints(kLHintsCenterY));
  horz2->AddFrame(fCathode, new TGLayoutHints(kLHintsCenterY));

  // create next & cancel button
  fNext = new TGTextButton(horz2, "Next");
  fNext->Connect("Clicked()", "GroupBox", this, "Next()");
  fNext->SetState(kButtonDisabled);
  fCancel = new TGTextButton(horz2, "Cancel");
  fCancel->Connect("Clicked()", "GroupBox", this, "Cancel()");
  fCancel->SetState(kButtonDisabled);
  horz2->AddFrame(fCancel, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
  horz2->AddFrame(fNext, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 0, 10, 0, 0));
  
  // create 2D-histograms
  track_a = new TH2D("track_a", "anode", 256, 0, 256, 1024, 0, 1024);
  track_c = new TH2D("track_c", "cathode", 256, 0, 256, 1024, 0, 1024);
  gStyle->SetPalette(56);
}

void GroupBox::AnodeUpdate()
{
  canvas->GetCanvas()->SetEditable(kTRUE);
  canvas->GetCanvas()->Clear();
  canvas->GetCanvas()->cd(0);
  track_a->SetStats(0);
  track_a->GetXaxis()->SetTickLength(0);
  track_a->GetYaxis()->SetTickLength(0);
  track_a->Draw("col");
  gPad->SetGrid(1);
  
  canvas->GetCanvas()->Update();
  canvas->GetCanvas()->SetEditable(kFALSE);
}

void GroupBox::CathodeUpdate()
{
  canvas->GetCanvas()->SetEditable(kTRUE);
  canvas->GetCanvas()->Clear();
  canvas->GetCanvas()->cd(0);
  track_c->SetStats(0);
  track_c->GetXaxis()->SetTickLength(0);
  track_c->GetYaxis()->SetTickLength(0);
  track_c->Draw("col");
  gPad->SetGrid(1);
  
  canvas->GetCanvas()->Update();
  canvas->GetCanvas()->SetEditable(kFALSE);
}

void GroupBox::Update() // Unlock all selector and update images
{
  canvas->GetCanvas()->SetEditable(kTRUE);
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
  track_a->GetXaxis()->SetTickLength(0);
  track_a->GetYaxis()->SetTickLength(0);
  track_a->Draw("col");
  gPad->SetGrid(1);
  canvas->GetCanvas()->cd(2);
  track_c->SetStats(0);
  track_c->GetXaxis()->SetTickLength(0);
  track_c->GetYaxis()->SetTickLength(0);
  track_c->Draw("col");
  gPad->SetGrid(1);
  
  canvas->GetCanvas()->cd(0);
  canvas->GetCanvas()->Update();
  canvas->GetCanvas()->SetEditable(kFALSE);

  WriteProgress();
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
    ReadProgress();
    LoadRun();
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
  WriteProgress();

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

void GroupBox::LoadRun()
{
  std::ifstream runfile(RunFileName);
  std::string runnumber;
  int runtemp = 0;
  while(getline(runfile, runnumber)){
    if(runtemp==RunNum){
      fRunPopMenu->AddEntry(runnumber.c_str(), stoi(runnumber));
      RunNum++;
    }
    runtemp++;
  }
  runfile.close();
}

void GroupBox::AddUser()
{
  std::string username(fEntry->GetText());
  if(username.size()==0){
    return;
  }
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
  if(Id!=0 && AnaState && !Selected){
    fSelect->SetState(kButtonUp);
    Selected = kTRUE;
  }
}

int GroupBox::GetEvent()
{
//  fNext->SetState(kButtonUp);
  fSelect->SetState(kButtonDisabled);
  std::string str;
  if(EventId<4){
//    std::cout << EventId << std::endl;
    str = "Please click " + std::to_string(EventId+1) + " point(s) in each image.\n Then go next.";
    fAnode->SetState(kButtonUp);
    fCathode->SetState(kButtonUp);
  }else{
    str = "Go Next!! GOGO!!";
  }
  message->SetText(str.c_str());
  return EventId;
}
void GroupBox::Anode()
{
  fAnode->SetState(kButtonDisabled);
  AnodeUpdate();
  ClickPos(canvas->GetCanvas(), X_anode, Y_anode, EventId+1);
  AnodeClicked = kTRUE;
  if(CathodeClicked){
    fNext->SetState(kButtonUp);
  }
}

void GroupBox::Cathode()
{
  fCathode->SetState(kButtonDisabled);
  CathodeUpdate();
  ClickPos(canvas->GetCanvas(), X_cathode, Y_cathode, EventId+1); 
  CathodeClicked = kTRUE;
  if(AnodeClicked){
    fNext->SetState(kButtonUp);
  }
}

void GroupBox::Next()
{
  OutputData();
  Progress[RunNo] = (++EventNo);
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
//  if(Click){
//    StopClickPos();
//    Click = kFALSE;
//  }
}

void GroupBox::Init()
{
  MaxEventNo = tree->GetEntries();
  EventNo = Progress[RunNo];
  Reset();
}

void GroupBox::OutputData()
{
  ofile << RunNo << " " << EventNo << " " << std::flush;
  ofile << EventId << " " << std::flush;
  for(int i=0;i!=EventId+1;++i){
    ofile << X_anode.at(i) << " " << Y_anode.at(i) << " "
	  << X_cathode.at(i) << " " << Y_cathode.at(i) << " " << std::flush;
  }
  ofile << std::endl;
}

void GroupBox::Reset()
{
  EventId = 0;
  AnodeClicked = kFALSE;
  CathodeClicked = kFALSE;
  pos.clear();
  X_anode.clear();
  Y_anode.clear();
  X_cathode.clear();
  Y_cathode.clear();
  fEventSelect->SetButton(0);
  fNext->SetState(kButtonDisabled);
  fSelect->SetState(kButtonDisabled);
  fAnode->SetState(kButtonDisabled);
  fCathode->SetState(kButtonDisabled);
  message->SetText("Please select track number.");
  Selected = kFALSE;
  Update();
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
    fCancel->SetState(kButtonDisabled);
    AnaState = kFALSE;
  }else{
    if(OpenRootFile()){
      SetBranchAddress();
      if(Progress.count(RunNo)==0){
	Progress[RunNo] = 0;
      }
      Update();
      Init();
      fRunButton->SetState(kButtonDisabled);
      fLogin->SetState(kButtonDisabled);
      fStart->SetText("Stop");
      fCancel->SetState(kButtonUp);
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

void GroupBox::ClickPos(TCanvas *c1, std::vector<Double_t> &X, std::vector<Double_t> &Y, int click_num)
{
  SingleContainer::GetInstance().SetValue(&X, &Y);
  SingleContainer::GetInstance().SetClickNum(click_num);
  c1->Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", "GroupBox", this,
	      "Locate(Int_t, Int_t, Int_t, TObject*)");
}

void GroupBox::Locate(Int_t event, Int_t x, Int_t y, TObject *selected)
{
  SingleContainer::GetInstance().Locate(event, x, y ,selected);
}

void GroupBox::StopClickPos()
{
  TCanvas *c = (TCanvas*)gTQSender;
  c->Disconnect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", 0,
		"Locate(Int_t, Int_t, Int_t, TObject*)");
}

void GroupBox::ReadProgress()
{
  TString filename;
  std::ifstream progfile;
  filename.Form("%s%02d.txt", ProgressFileName.c_str(), UserId);
  progfile.open(filename);
  Progress.clear();
  std::string line;
  while(getline(progfile, line)){
    std::stringstream stream;
    stream << line;
    int runno, prog;
    stream >> runno >> prog;
//    std::cout << runno << " " << prog << std::endl;
    Progress[runno] = prog;
  }
}

void GroupBox::WriteProgress()
{
  TString filename;
  std::ofstream progfile;
  filename.Form("%s%02d.txt", ProgressFileName.c_str(), UserId);
  progfile.open(filename);
  for(auto itr=Progress.begin();itr!=Progress.end();++itr){
    progfile << itr->first << " " << itr->second << std::endl;
  }
  progfile.close();
}
