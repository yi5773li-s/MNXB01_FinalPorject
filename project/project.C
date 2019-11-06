#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <vector>

Double_t * oneDay(string filePath, Int_t day, Int_t plot=1){
	
	
	
	
	
	static Double_t result[2];
	if (filePath == "test"){
		Double_t tday = (Double_t)day;
		result[0]=tday+2.2;
		result[1]=tday/3;
		return result;
	}
}

void everyDay(string filePath){
	Double_t *p;
	vector<Double_t> daysMean;
	vector<Double_t> daysStaDev;
	vector<Int_t> days;
	for(Int_t i = 1; i <= 365; i++){
		p = oneDay(filePath,i,0);
		daysMean.push_back(p[0]);
		daysStaDev.push_back(p[1]);
		days.push_back(i);
	}
	
	



}


void LattDiff(){





}
