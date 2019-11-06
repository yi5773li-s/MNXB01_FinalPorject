#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <vector>

Double_t oneDay(string filePath, Int_t day, Int_t plot=1){




}

void everyDay(string filePath){
  vector<Double_t> daysMean;
  vector<Double_t> daysStaDev;
  for(Int_t i = 1, i < 365, i++){
    daysMean.push_back(oneDay(filePath,i,0)[0])
    daysStaDev.push_back(oneDay(filePath,i,0)[1])
  }



}


void LattDiff(){





}
