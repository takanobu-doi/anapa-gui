#include "ClickPos.hpp"
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TQObject.h>
#include <TStyle.h>
#include <iostream>
#include <vector>
#include "TROOT.h"

SingleContainer::SingleContainer()
{}

SingleContainer::SingleContainer(const SingleContainer& singlecontainer)
{}

SingleContainer::~SingleContainer()
{}

void SingleContainer::Locate(Int_t event, Int_t x0, Int_t y0, TObject *selected)
{
  TCanvas *c = (TCanvas*)gTQSender;
  Double_t x = x0;
  Double_t y = gPad->GetWh()-y0;
  switch(event){
  case 1:
    if(strcmp(selected->ClassName(), "TH2D")==0){
      TH2D *h = (TH2D*)selected;
      std::cout << h->GetName() << std::endl;
      x -= (gPad->GetWw())*(gStyle->GetPadLeftMargin());
      x /= (gPad->GetWw()*(1-gStyle->GetPadRightMargin()-gStyle->GetPadLeftMargin()));
      x *= h->GetXaxis()->GetXmax()-h->GetXaxis()->GetXmin();
      x += h->GetXaxis()->GetXmin();
      
      y -= (gPad->GetWh())*(gStyle->GetPadBottomMargin());
      y /= (gPad->GetWh()*(1-gStyle->GetPadBottomMargin()-gStyle->GetPadTopMargin()));
      y *= h->GetYaxis()->GetXmax()-h->GetYaxis()->GetXmin();
      X->push_back(x);
      Y->push_back(y);
      std::cout << x << " " << y << std::endl;
    }
    if((--ClickNum)==0){
      c->Disconnect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", 0,
		    "Locate(Int_t, Int_t, Int_t, TObject*)");
      return;
    }
    break;
  case 61:
    c->Disconnect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", 0,
		  "Locate(Int_t, Int_t, Int_t, TObject*)");
    return;
    break;
  default:
    break;
  }
}

void SingleContainer::SetValue(std::vector<Double_t> *x, std::vector<Double_t> *y)
{
  X = x;
  Y = y;
}

void SingleContainer::SetClickNum(int click_num)
{
  ClickNum = click_num;
}
