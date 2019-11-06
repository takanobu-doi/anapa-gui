#ifndef _GROUPBOX_HPP_
#define _GROUPBOX_HPP_

#include <TROOT.h>
#include <TGWindow.h>
#include <TGFrame.h>
#include <TGCanvas.h>
#include <TCanvas.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButton.h>
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
  TGTextButton *fAdd; // add user
  TGTextEntry *fEntry;
  
  ///// files /////
  TFile *ifile;
  std::ofstream ofile;

  ///// parameters to handle analysis /////
  int UserId; // current user id
  int EventNo; // current event No
  int UserNum; // registered user number 
  Bool_t Login; // status of login

  ///// parts to draw histograms /////
  TTree *tree;
  TH2D *track_a;
  TH2D *track_c;
  ULong64_t Map[2][256][16];
  
public:
  GroupBox();
  GroupBox(const TGWindow *p, const char *name, const char *title);
  void Update();
  void SetRunNo(const int runNo);
  void LogIn(const int UID);
  void LogOut();
  void SetBranchAddress();
  void InitUser();
  void AddUser();
  void ChangeLoginState();

  ClassDef(GroupBox, 0)
};

#endif
