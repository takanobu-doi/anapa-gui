#ifndef _GROUPBOX_HPP_
#define _GROUPBOX_HPP_

#include <TROOT.h>
#include <TGWindow.h>
#include <TGFrame.h>
#include <TGCanvas.h>
#include <TCanvas.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGMenu.h>
#include <TGTextEntry.h>
#include <TGLabel.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TTree.h>
#include <fstream>
#include <map>

////////// main part to treat data //////////

class GroupBox: public TGGroupFrame{
private:
  ///// parts of GUI /////
  TRootEmbeddedCanvas *canvas;
  TGSplitButton *fIdButton; // select user id
  TGPopupMenu *fIdPopMenu; // will be attached to fIDButton
  TGTextButton *fLogin; // login button
  TGSplitButton *fRunButton; // select run no
  TGPopupMenu *fRunPopMenu; // will be attached to fRunButton
  TGTextButton *fStart; // start button
  TGTextButton *fAdd; // add user
  TGTextEntry *fEntry;
  TGButtonGroup *fEventSelect;
  TGTextButton *fSelect;
  TGTextButton *fNext;
  TGTextButton *fCancel;
  TGLabel *label;
  TGLabel *message;
  TGTextButton *fAnode;
  TGTextButton *fCathode;
  
  ///// files /////
  TFile *ifile;
  std::ofstream ofile;

  ///// parameters of system control
  int UserNum; // registered user number
  int RunNum; // registered run number
  Bool_t Login; // status of login
  Bool_t AnaState; // status of analysis
  Bool_t Click; // status of ClickPos
  Bool_t AnodeClicked;
  Bool_t CathodeClicked;
  Bool_t Selected;
  
  ///// parameters to handle analysis /////
  int UserId; // current user id
  std::map<int, int> Progress;
  int RunNo;
  int EventNo; // current event No
  int MaxEventNo; // max event number in current run
  int EventId; // selected event id
  std::vector<Double_t> pos;
  std::vector<Double_t> X_anode;
  std::vector<Double_t> Y_anode;
  std::vector<Double_t> X_cathode;
  std::vector<Double_t> Y_cathode;

  ///// parts to draw histograms /////
  TTree *tree;
  TH2D *track_a;
  TH2D *track_c;
  UInt_t Map[2][256][32];
  
public:
  GroupBox();
  GroupBox(const TGWindow *p, const char *name, const int H, const int W);
  void StartStopAnalysis();
  void Update();
  void AnodeUpdate();
  void CathodeUpdate();
  void SetUserId(Int_t UID);
  void SetRunNo(Int_t runNo);
  int OpenRootFile();
  void LogIn();
  void LogOut();
  void SetBranchAddress();
  void InitUser();
  void LoadRun();
  void AddUser();
  void ChangeLoginState();
  void SetEvent(Int_t Id);
  int GetEvent();
  void Anode();
  void Cathode();
  void Next();
  void Cancel();
  void Init();
  void Reset();
  void OutputData();
  void EndOfFile();
  void Exit();
  void ClickPos(TCanvas *c1, std::vector<Double_t> &X, std::vector<Double_t> &Y, int click_num);
  void Locate(Int_t event, Int_t x, Int_t y, TObject *selected);
  void StopClickPos();
  void ReadProgress();
  void WriteProgress();

  ClassDef(GroupBox, 0)
};

#endif
