#include <TH1.h>
#include <TCanvas.h>
#include <TQObject.h>
#include <iostream>
#include <vector>
#include "TROOT.h"

class SingleContainer
{
public:
  ~SingleContainer();
  void Locate(Int_t event, Int_t x, Int_t y, TObject *selected);
  void SetValue(std::vector<Double_t> *x, std::vector<Double_t> y);
  static SingleContainer& GetInstance()
  {
    static SingleContainer instance;
    return instance;
  }

private:
  SingleContainer();
  SingleContainer(const SingleContainer&);
  SingleContainer& operator=(const SingleContainer&);
  std::vector<Doublt_t> *X;
  std::vector<Doublt_t> *Y;  
};

SingleContainer::SingleContainer()
{}

SingleContainer::SingleContainer(const SingleContainer& singlecontainer)
{}

SingleContainer::~SingleContainer()
{}

void SingleContainer::Locate(Int_t event, Int_t x0, Int_y0, TObject *selected)
{
  TCanvas *c = (TCanvas*)gTQSender;
  Double_t x = x0;
  Double_t y = gPad-GetWh()-y0;
  switch(event){
  case 1:
    if(strcmp(selected->ClassName(), "TH2D")==0){
      TH2D *h = (TH2D*)selected;
      x -= (gPad->GetWw())*(gStyle->GetPadLeftMargin());
      x /= (gPad->GetWw()*(1-gStyle->GetPadRightMargin()-gStyle->GetPadLeftMargin()));
      x *= h->GetXaxis()->GetXmax()-h->GetXaxis()->GetXmin();
      
      y -= (gPad->GetWh())*(gStyle->GetPadBottomMargin());
      y /= (gPad->GetWh()*(1-gStyle->GetPadBottomMargin()-gStyle->GetPadTopMargin()));
      y *= h->GetYaxis()->GetXmax()-h->GetYaxis()->GetXmin();
      X->push_back(x);
      Y->push_back(y);
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

void Locate(Int_t event, Int_t x, Int_t y, TObject *selected)
{
  SingleContainer::GetInstance().Locate(event, x, y, selected);
}

void click_pos(TCanvas *c1, std::vector<Double_t> &X, std::vector<Double_t> &Y)
{
  gROOT->GetListOfGlobalFunctions()->Delete();
  c1->Update();
  SingleContainer::GetInstance().SetValue(&X, &Y);
  c1->Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)", 0, 0,
	      "Locate(Int_t, Int_t, Int_t, TObject*)");
}
