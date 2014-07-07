
#include<iostream> 
#include "TGraphErrors.h"


void graph()
{
	TCanvas *c1 = new TCanvas();
	TGraphErrors data("data_bin8.txt", "%lg %lg %lg");
	data.DrawClone();

	//c1 -> Print("ESP");
}
	
