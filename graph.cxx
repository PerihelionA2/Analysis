
#include<iostream> 
#include "TGraphErrors.h"


void graph()
{
	gROOT -> SetStyle("Plain");
	TCanvas *c1 = new TCanvas();
	c1 -> SetGrid();
	TGraphErrors data("data-carb-all.txt", "%lg %lg %lg");
	//TGraphErrors data("data.txt", "%lg %lg %lg");
	data.SetTitle("Frozen Spin Target Polarization/Asymmetry ;time [days]; #Sigma P_{#gamma}");
	data.SetMarkerStyle(kCircle);
	data.SetFillColor(0);
	data.SetLineColor(56);
	data.Fit("pol1","","",1,8);
	data.DrawClone();
	c1->Print("Fit.png", "png"); 

	TFile f("data.root","recreate"); //Open file, then write histo to it.
  	data.Write();
}
	
