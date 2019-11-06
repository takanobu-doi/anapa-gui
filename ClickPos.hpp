#ifndef _CLICKPOS_HPP_
#define _CLICKPOS_HPP_

#include <TROOT.h>
#include <TObject.h>
#include <TCanvas.h>
#include <vector>

class SingleContainer
{
public:
  ~SingleContainer();
  void Locate(Int_t event, Int_t x, Int_t y, TObject *selected);
  void SetValue(std::vector<Double_t> *x, std::vector<Double_t> *y);
  void SetClickNum(int click_num);
  static SingleContainer& GetInstance()
  {
    static SingleContainer instance;
    return instance;
  }

private:
  SingleContainer();
  SingleContainer(const SingleContainer&);
  SingleContainer& operator=(const SingleContainer&);
  std::vector<Double_t> *X;
  std::vector<Double_t> *Y;
  int ClickNum;
};

void Locate(Int_t event, Int_t x, Int_t y, TObject *selected);
void ClickPos(TCanvas *c1, std::vector<Double_t> &X, std::vector<Double_t> &Y, int click_num);
void StopClickPos();

#endif
