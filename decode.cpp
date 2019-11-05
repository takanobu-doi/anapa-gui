void decode(UDouble64_t Map[2][256][16])
{
  TH2F *track_a = new TH2F("track_a", "track_a",
			   256, 0, 256, 1024, 0, 1024);
  TH2F *track_c = new TH2F("track_a", "track_a",
			   256, 0, 256, 1024, 0, 1024);

  for(int ac=0;ac!=2;++ac){
    for(int strp=0;strp!=256;++strp){
      for(int clk=0;clk!=1024;++clk){
	if((Map[ac][strp][clk/64])&((ULong64_t)1<<(clk%64))){
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
