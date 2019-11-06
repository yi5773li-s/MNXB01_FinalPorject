#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <vector>
#include <TGraphErrors.h>

Int_t n=365;
Double_t outputMS[2];

Double_t * oneDay(string filePath, Int_t day, Int_t plot=0){
	
	if (filePath == "test0"){
		Double_t tday = (Double_t)day;
		outputMS[0]=tday+2.2;
		outputMS[1]=tday/3;
		return outputMS;
	}
	else if (filePath == "test1"){
		Double_t tday = (Double_t)day;
		outputMS[0]=-tday+8.2;
		outputMS[1]=tday/3;
		return outputMS;
	}
	else if (filePath == "test2"){
		Double_t tday = (Double_t)day;
		outputMS[0]=tday+4.2;
		outputMS[1]=tday/2;
		return outputMS;
	}
}

Double_t * everyDay(string filePath="../clean_data/upsala_clean.dat", Int_t plot=0){
	Double_t *p;
	Double_t daysMean[n],daysStaDev[n],days[n],zeros[n];
	//vector<Double_t> daysMean;
	//vector<Double_t> daysStaDev;
	//vector<Int_t> days;
	//vector<Int_t> zeros;
	for(Int_t i = 0; i < n; i++){
		p = oneDay(filePath,i,0);
		daysMean[i]=p[0];
		daysStaDev[i]=p[1];
		days[i]=i+1;
		zeros[i]=0;
		//daysMean.push_back(p[0]);
		//daysStaDev.push_back(p[1]);
		//days.push_back(i);
		//zeros.push_back(0);
		/*
		if (plot == 1){
			outputBigM[i] = daysMean[i];
		}
		if (plot == 2){
			outputBigS[i] = daysStaDev[i];
		}
		*/
	}
	if (plot == 0){
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
	/*
	if (plot == 0){
		return outputBigM;
	}	
	if (plot == 2){
		return outputBigS;
	}
	*/
}


void LattDiff(){
	Double_t days[365];
	Double_t zeros[365];
	/*
	Double_t *lundM, *visbyM, *upsalaM, *umeaM, *luleuM;
	lundM = everyDay("../clean_data/lund_clean.dat",0);
	visbyM = everyDay("../clean_data/visby_clean.dat",0);
	upsalaM = everyDay("../clean_data/upsala_clean.dat",0);
	umeaM = everyDay("../clean_data/umea_clean.dat",0);
	luleuM = everyDay("../clean_data/luleu_clean.dat",0);
	
	Double_t *lundS, *visbyS, *upsalaS, *umeaS, *luleuS;
	lundS = everyDay("../clean_data/lund_clean.dat",0);
	visbyS = everyDay("../clean_data/visby_clean.dat",0);
	upsalaS = everyDay("../clean_data/upsala_clean.dat",0);
	umeaS = everyDay("../clean_data/umea_clean.dat",0);
	luleuS = everyDay("../clean_data/luleu_clean.dat",0);
	
	Double_t *test0M, *test0S, *test1M, *test1S, *test2M, *test2S;
	test0M = everyDay("test0",1);
	test0S = everyDay("test0",2);
	test1M = everyDay("test1",1);
	test1S = everyDay("test1",2);
	test2M = everyDay("test2",1);
	test2S = everyDay("test2",2);
	*/
	Double_t *t0, *t1, *t2;
	Double_t t0daysMean[n],t0daysStaDev[n],t1daysMean[n],t1daysStaDev[n];
	for(Int_t i = 0; i < n; i++){
		days[i]=i+1;
		zeros[i]=0;
		t0 = oneDay("test0",i,0);
		t0daysMean[i]=t0[0];
		t0daysStaDev[i]=t0[1];
		t1 = oneDay("test1",i,0);
		t1daysMean[i]=t1[0];
		t1daysStaDev[i]=t1[1];
	}
	
	
	
	
	for (Int_t i=0; i < 365; i++){
		cout << t0daysMean[i] << endl;
		cout << t1daysMean[i] << endl;
		
	}
	TCanvas* c2 = new TCanvas("c2", "every day graph multiple locations", 900, 600);
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
	TGraphErrors* t0p = new TGraphErrors(n,days,t0daysMean,zeros,t0daysStaDev);
	t0p->SetMaximum(400);
	t0p->SetMinimum(-400);
	t0p->Draw("AL");
	TGraphErrors* t1p = new TGraphErrors(n,days,t1daysMean,zeros,t1daysStaDev);
	t1p->Draw("L");
	//TGraphErrors* t2 = new TGraphErrors(n,days,test2M,zeros,test2S);
	//t2->Draw("L");
	
	
	
	
	
	c2->SaveAs("every_day_graph_multiple_locations.jpg");

}

