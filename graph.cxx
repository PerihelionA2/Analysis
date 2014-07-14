
#include<iostream> 
#include "TGraphErrors.h"


void graph()
{
	gROOT -> SetStyle("Plain");
	TCanvas *c1 = new TCanvas();
	c1 -> SetGrid();
	TGraphErrors data("Pi0P_DMT_E_300.txt","%lg %lg %lg");
	//TGraphErrors data("data-carb-all2.txt", "%lg %lg %lg");
	data.SetTitle("Frozen Spin Target Polarization/Asymmetry ;time [days]; #Sigma P_{#gamma}");
	data.SetMarkerStyle(kCircle);
	data.SetFillColor(0);
	data.SetLineColor(56);
	data.Fit("pol1","","",1,8);
	data.DrawClone();
	c1->Print("new.png", "png"); 

	TFile f("new.root","recreate"); //Open file, then write histo to it.
  	data.Write();
}
	
