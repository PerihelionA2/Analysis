

#include "/home/dylan/Desktop/A2/include/mix2.h"
#include <iostream>
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

// Carbon Backgroun data, used for noise cancellation
TFile Car_3500("Pi0_CBTaggTAPS_3500.root");
TFile Car_3544("Pi0_CBTaggTAPS_3544.root");
TFile Car_3590("Pi0_CBTaggTAPS_3590.root");

///////////////////////////////////////
// Prefixes pretain to target identity.
// Data types ending with _1,_0 refer  
// to relative helicity.	       
///////////////////////

ofstream fout("data-carb-all4.txt");

Int_t mix2()
{
	Int_t n_bin;
	Int_t n_file;

	//initialize ppi0 class object PolPar
	ppi0 PolPar;
	std::cout << "######################################################################" << endl;
	std::cout << "Initializing Carbon data.. " << endl << endl;
	//Call Carbon background subtraction function
	PolPar.Carbon(); 
	std::cout << "Amount of files for analysis : ";
	std::cin >> n_file;
	if (!n_file)     return 0;
	if (n_file == 0) return 0;
	
	// appropiate number of files declared
	else()
	{	
		//Set Theta bin. Bin range is constant.
		std::cout << "Theta bin: ";
		std::cin >> n_bin;
		PolPar.Setn_bin(n_bin);
		if (!n_bin) return 0;
		if (n_bin == 1) std::cout << "This is the underflow bin!, choose again..";
		else ()
		{
			std::cout << endl << "Starting Butanol file input loop..." << endl;
			for(Int_t i = 1; i <= n_file; i++)
			{
				// Asymmetry function for the Butanol data
				PolPar.Asymmetry(i);
			}
			fout.close();
			// Output function for Graph and root files
			PolPar.Graph();
		}
	}
}
// class constuctor
ppi0 :: ppi0() 
{ 
}
// class destructor
ppi0 :: ~ppi0()
{
}
void ppi0 :: Asymmetry(Int_t index)
{

	// File io, 
	FileIn();
	TFile But(run);
	//cout << "bin = " << n_bin << endl;

	// extract Butanol Theta distributions for both helicities
	But.GetObject("Theta_1", BThet_1);
	But.GetObject("Theta_0", BThet_0);	
	
	//integrate over given bin of the Theta distributions
	Byeild_0 = BThet_0 -> GetBinContent(n_bin);
	Byeild_1 = BThet_1 -> GetBinContent(n_bin);
	Cyeild_0 = C3500_0 -> GetBinContent(n_bin);
	Cyeild_1 = C3500_1 -> GetBinContent(n_bin);

	std::cout << Cyeild_0 << " "<< Cyeild_0*Scale() << endl;
		
	// Carbon background subtraction, with scaling function. 
	if(ButaEvnt < 12714948) yeild_0 = Byeild_0 - Cyeild_0*Scale();
	if(ButaEvnt < 12714948) yeild_1 = Byeild_1 - Cyeild_1*Scale();
		
	if(ButaEvnt > 12714948) yeild_0 = Byeild_0*Scale() - Cyeild_0;
	if(ButaEvnt > 12714948) yeild_1 = Byeild_1*Scale() - Cyeild_1;

	//yeild_0 = Byeild_0;
	//yeild_1 = Byeild_1;

	// Strickly positive yeilds 
	if(yeild_0 < 0) yeild_0 = yeild_0*(-1);
	if(yeild_1 < 0) yeild_1 = yeild_1*(-1);
		
	// Asymmetry(and Polarization) calculation using the yeilds of both helicities			
	asym = (yeild_0 - yeild_1)/(yeild_0 + yeild_1);

	// Error calcalution using counting error standard deviation 
	err  = (2./(pow(yeild_0 + yeild_1, 2.)))*sqrt(pow(yeild_0,2.)*yeild_1 
						            + pow(yeild_1,2.)*yeild_0);
	// output data points to external file	
	std::cout << index << " " << asym << " " << err << endl;
	fout << index << " " << asym << " " << err << endl;
		
}
void ppi0 :: Carbon()
{	
	//extract carbon background Theta distributions
	Car_3500.GetObject("Theta_1", C3500_1);
	Car_3500.GetObject("Theta_0", C3500_0);
	Car_3544.GetObject("Theta_1", C3544_1);
	Car_3544.GetObject("Theta_0", C3544_0);
	Car_3590.GetObject("Theta_1", C3590_1);
	Car_3590.GetObject("Theta_0", C3590_0);
	
	//stack the carbon data (better statistics) 
	C3500_1 -> Add(C3544_1, 1);
	C3500_1 -> Add(C3590_1, 1);

	C3500_0 -> Add(C3544_0, 1);
	C3500_0 -> Add(C3590_0, 1);
}
void ppi0 :: FileIn()
{
	
	std::cout << "#########################################################################" << endl;
	std::cout << "Input file name: ";
	std::cin >> run;
	std::cout << endl << "Input compressed raw data acqu entries: ";
	std::cin >> ButaEvnt;
}
void ppi0 :: Graph()
{
	gROOT -> SetStyle("Plain");
	
	//Canvas parameters 
	TCanvas *c1 = new TCanvas();
	c1 -> SetGrid();
	
	TGraphErrors data("data-carb-all4.txt", "%lg %lg %lg");
	//TGraphErrors data("data.txt", "%lg %lg %lg");
	
	// Graph Settings
	data.SetTitle("Frozen Spin Target Polarization/Asymmetry ;time [days]; #Sigma P_{#gamma}");
	data.SetMarkerStyle(kCircle);
	data.SetFillColor(0);
	data.SetLineColor(56);
	data.Fit("pol1","","",1,8);
	data.DrawClone();

	// Print as PNG
	c1->Print("Fit4.png", "png"); 

	//Write into root file
	TFile f("data4.root","recreate");
  	data.Write();
}
