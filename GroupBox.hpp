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
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TTree.h>
#include <fstream>

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
  
  ///// files /////
  TFile *ifile;
  std::ofstream ofile;

  ///// parameters of system control
  int UserNum; // registered user number
  int RunNum; // registered run number
  Bool_t Login; // status of login
  
  ///// parameters to handle analysis /////
  int UserId; // current user id
  int RunNo;
  int EventNo; // current event No
  int MaxEventNo; // max event number in current run
  int EventId; // selected event id
  std::vector<double> pos;

  ///// parts to draw histograms /////
  TTree *tree;
  TH2D *track_a;
  TH2D *track_c;
  ULong64_t Map[2][256][16];
  
public:
  GroupBox();
  GroupBox(const TGWindow *p, const char *name);
  void StartAnalysis();
  void Update();
  void SetRunNo(const int runNo);
  void LogIn(const int UID);
  void LogOut();
  void SetBranchAddress();
  void InitUser();
  void InitRun();
  void AddUser();
  void ChangeLoginState();
  void SetEvent(Int_t Id);
  int GetEvent();
  void Next();
  void Cancel();
  void Init();
  void Reset();
  void EndOfFile();

  ClassDef(GroupBox, 0)
};

#endif
