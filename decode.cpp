#include "decode.hpp"

void decode(UInt_t Map[2][256][32], TH2D *track_a, TH2D *track_c)
{
  for(int ac=0;ac!=2;++ac){
    for(int strp=0;strp!=256;++strp){
      for(int clk=0;clk!=1024;++clk){
	if((Map[ac][strp][clk/32])&((UInt_t)1<<(clk%32))){
	  switch(ac){
	  case 0:
	    track_a->Fill(strp, clk);
	    break;
	  case 1:
	    track_c->Fill(strp, clk);
	    break;
	  }
	}
      }
    }
  }

  return;
}
