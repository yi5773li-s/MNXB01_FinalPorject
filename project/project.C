#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <vector>
#include <TGraphErrors.h>

Double_t * oneDay(string filePath, Int_t day, Int_t plot=1){
	
	
	
	
	
	static Double_t result[2];
	if (filePath == "test0"){
		Double_t tday = (Double_t)day;
		result[0]=tday+2.2;
		result[1]=tday/3;
		return result;
	}
	if (filePath == "test1"){
		Double_t tday = (Double_t)day;
		result[0]=-tday-2.2;
		result[1]=tday/3;
		return result;
	}
	if (filePath == "test2"){
		Double_t tday = (Double_t)day;
		result[0]=tday+4.2;
		result[1]=tday/2;
		return result;
	}
}

Double_t * everyDay(string filePath="../clean_data/upsala_clean.dat", Int_t plot=1){
	Int_t n=365;
	Double_t *p;
	Double_t daysMean[n],daysStaDev[n],days[n],zeros[n];
	static Double_t store[4][365];
	//vector<Double_t> daysMean;
	//vector<Double_t> daysStaDev;
	//vector<Int_t> days;
	//vector<Int_t> zeros;
	for(Int_t i = 0; i < n; i++){
		p = oneDay(filePath,i+1,0);
		daysMean[i]=p[0];
		daysStaDev[i]=p[1];
		days[i]=i+1;
		zeros[i]=0;
		//daysMean.push_back(p[0]);
		//daysStaDev.push_back(p[1]);
		//days.push_back(i);
		//zeros.push_back(0);
		if (plot == 0){
			store[0][i] = p[0];
			store[1][i] = p[1];
			store[2][i] = i+1;
			store[3][i] = 0;
		}
		
	}
	if (plot == 1){
		gStyle->SetOptStat(0);
		gStyle->SetOptTitle(0);
		gStyle->SetTitleSize(0.05, "x");
		gStyle->SetTitleSize(0.05, "y");
		gStyle->SetLabelSize(0.05, "x");
		gStyle->SetLabelSize(0.05, "y");
		gStyle->SetPadTopMargin(0.05);
		gStyle->SetPadRightMargin(0.05);
		gStyle->SetPadBottomMargin(0.16);
		gStyle->SetPadLeftMargin(0.16);
		TCanvas* c1 = new TCanvas("c1", "every day graph one location", 900, 600);
		TGraphErrors* g1 = new TGraphErrors(n,days,daysMean,zeros,daysStaDev);
		g1->Draw("AL");
		c1->SaveAs("every_day_graph_one_location.jpg");
	}
	if (plot == 0){
		return *store;
	}	
}


void LattDiff(){
	//Double_t *lund, *visby, *upsala, *umea, *luleu;
	//lund = everyDay("../clean_data/lund_clean.dat",0);
	//visby = everyDay("../clean_data/visby_clean.dat",0);
	//upsala = everyDay("../clean_data/upsala_clean.dat",0);
	//umea = everyDay("../clean_data/umea_clean.dat",0);
	//luleu = everyDay("../clean_data/luleu_clean.dat",0);
	Double_t *test0, *test1, *test2;
	test0 = everyDay("test0",0);
	test1 = everyDay("test1",0);
	test2 = everyDay("test2",0);
	
	





}
