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
	static Double_t store[365];
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
		if (plot == 0){
			store[i] = daysMean[i];
			
		}
		if (plot == 2){
			store[i] = daysStaDev[i];
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
		return store;
	}	
}


void LattDiff(){
	Int_t n=365;
	Double_t days[365];
	Double_t zeros[365];
	/*
	Double_t *lund, *visby, *upsala, *umea, *luleu;
	lund = everyDay("../clean_data/lund_clean.dat",0);
	visby = everyDay("../clean_data/visby_clean.dat",0);
	upsala = everyDay("../clean_data/upsala_clean.dat",0);
	umea = everyDay("../clean_data/umea_clean.dat",0);
	luleu = everyDay("../clean_data/luleu_clean.dat",0);
	Double_t lundM[n],lundS[n];
	Double_t visbyM[n],visbyS[n];
	Double_t upsalaM[n],upsalaS[n];
	Double_t umeaM[n],umeaS[n];
	Double_t luleuM[n],luleuS[n];
	*/
	Double_t *test01, *test02, *test1, *test2;
	test01 = everyDay("test0",0);
	test02 = everyDay("test0",2);
	test1 = everyDay("test1",0);
	test2 = everyDay("test2",0);
	Double_t test0M[365],test0S[365],test1M[n],test1S[n],test2M[n],test2S[n];
	for (Int_t i=0; i < 364; i++){
		days[i]=i+1;
		zeros[i]=0;		
		
		test0M[i] = test01[i];
		test0S[i] = test02[i];
		/*
		test1M[i] = test1[0][i];
		test1S[i] = test1[1][i];
		test2M[i] = test2[0][i];
		test2S[i] = test2[1][i];
		
		lundM[i] = lund[0][i];
		lundS[i] = lund[1][i];
		visbyM[i] = visby[0][i];
		visbyS[i] = visby[1][i];
		upsalaM[i] = upsala[0][i];
		upsalaS[i] = upsala[1][i];
		umeaM[i] = umea[0][i];
		umeaS[i] = umea[1][i];
		luleuM[i] = luleu[0][i];
		luleuS[i] = luleu[1][i];
		*/
	}
	//TCanvas* c2 = new TCanvas("c2", "every day graph multiple locations", 900, 600);
	TGraphErrors* t0 = new TGraphErrors(n,days,test0M,zeros,test0S);
	t0->Draw("AL");
	//TGraphErrors* t1 = new TGraphErrors(n,days,test1M,zeros,test1S);
	//t1->Draw("L");
	//TGraphErrors* t2 = new TGraphErrors(n,days,test2M,zeros,test2S);
	//t2->Draw("L");
	
	
	
	
	
	//c2->SaveAs("every_day_graph_multiple_locations.jpg");

}
