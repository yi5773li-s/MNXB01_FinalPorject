#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <vector>
#include <TGraphErrors.h>
#include <TLegend.h>
/*
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
*/
Int_t n=365;
Double_t outputMS[2];

Double_t* oneDayMDI(string filePath, Int_t month, Int_t day, Int_t plot=0)
{
	// create a histogram
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
	hist->SetFillColor(kRed + 1);
	
	Double_t yeart;
	Double_t montht;
	Double_t dayt;
	Double_t tempt;
	
	vector<Double_t> y;
	vector<Double_t> t;
	vector<Double_t> average;
	
	// open data file
	ifstream datafile(filePath);
	
	
	while (datafile >> yeart >> montht >> dayt >> tempt)
	{
		
		if (montht == month and dayt == day)
		{
			y.push_back(yeart);
			t.push_back(tempt);
		}
	}
	
	Int_t size = y.size();
	
	for (Int_t i = 0; i < size; i++)
	{
		Double_t temp = t[i];
		Double_t test = y[i];
		Int_t counter = 1;
		
		for (Int_t j = i+1; j < size; j++)
		{
			if (test == y[j])
			{
				temp += t[j];
				counter++;
				i++;
			}
		}
		
		//average.push_back(temp/counter);
		hist->Fill(temp/counter);
	}
		
	// close the file
	datafile.close();
	
	if (plot==1)
	{
		hist->Draw();
	}
	else
	{
		 outputMS[0] = hist->GetMean();
	     outputMS[1] = hist->GetRMS();
	
		 return outputMS;
	}	
}

Double_t* oneDay(string filePath, Int_t dayNo, Int_t plot=0)
{
	int days_in_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	Int_t month=0;
	Int_t date=0;
	
	for (Int_t i = 0; i < 13; i++)
	{
		if (dayNo <= days_in_month[i+1])
		{
			date = dayNo;
			month = i+1;
			break;
		}
		
		else
		{
			dayNo -= days_in_month[i+1];
		}
	}
	
	return oneDayMDI(filePath, month, date, plot);
}


void everyDay(string filePath="../clean_data/upsala_clean.dat", Int_t plot=0){
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
		TCanvas* c1 = new TCanvas("c1", "every day graph one location", 900, 600);
		/*
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
		*/
		TGraphErrors* g1 = new TGraphErrors(n,days,daysMean,zeros,daysStaDev);
		g1->SetTitle("Temperatures over the year for one location");
		g1->GetXaxis()->SetTitle("Days");
		g1->GetYaxis()->SetTitle("Temperature [#circC]");
		g1->SetMaximum(500);
		g1->SetMinimum(-100);
		g1->SetFillColor(2);
		g1->SetFillStyle(3000);
		g1->Draw("a4 ");
		TGraphErrors* g1l = new TGraphErrors(n,days,daysMean,zeros,zeros);
		g1l->SetLineColor(1);
		g1l->SetLineWidth(2);
		g1l->Draw("l");
		
		c1->SaveAs("every_day_graph_one_location.jpg");
		
		TCanvas* c4 = new TCanvas("c1", "every day graph one location histogram", 900, 600);
		
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
		
		
		TH1I* histED = new TH1I("histED", "Temperature;Day of the year;Temperature[#circC]", 365, 1, 365);
		for(int bin = 1; bin <= histED->GetNbinsX(); ++bin) {
			histED->SetBinContent(bin, daysMean[bin-1]);
			histED->SetBinError(bin, daysStaDev[bin-1]);
		}
		histED->SetLineColor(2);
		histED->Draw("E L");
		TH1I* histEDl = new TH1I("histED", "Temperature;Day of the year;Temperature[#circC]", 365, 1, 365);
		for(int bin = 1; bin <= histEDl->GetNbinsX(); ++bin) {
			histEDl->SetBinContent(bin, daysMean[bin-1]);
		}
		histEDl->SetLineColor(1);
		histEDl->SetLineWidth(2);
		histEDl->Draw("L same");
		
		c4->SaveAs("every_day_graph_one_location_histogram.jpg");
	}
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
	Double_t t0daysMean[n],t0daysStaDev[n],t1daysMean[n],t1daysStaDev[n],t2daysMean[n],t2daysStaDev[n];
	/*
	Double_t *lundP, *visbyP, *upsalaP, *umeaP, *luleuP;
	Double_t lundM[n], visbyM[n], upsalaM[n], umeaM[n], luleuM[n];
	Double_t lundS[n], visbyS[n], upsalaS[n], umeaS[n], luleuS[n];
	*/
	for(Int_t i = 0; i < n; i++){
		days[i]=i+1;
		zeros[i]=0;
		t0 = oneDay("test0",i,0);
		t0daysMean[i]=t0[0];
		t0daysStaDev[i]=t0[1];
		t1 = oneDay("test1",i,0);
		t1daysMean[i]=t1[0];
		t1daysStaDev[i]=t1[1];
		t2 = oneDay("test2",i,0);
		t2daysMean[i]=t2[0];
		t2daysStaDev[i]=t2[1];
		/*
		lundP = oneDay("../clean_data/lund_clean.dat",i,0);
		lundM[i]=lundP[0];
		lundS[i]=lundP[1];
		visbyP = oneDay("../clean_data/visby_clean.dat",i,0);
		visbyM[i]=visbyP[0];
		visbyS[i]=visbyP[1];
		upsalaP = oneDay("../clean_data/upsala_clean.dat",i,0);
		upsalaM[i]=upsalaP[0];
		upsalaS[i]=upsalaP[1];
		umeaP = oneDay("../clean_data/umea_clean.dat",i,0);
		umeaM[i]=umeaP[0];
		umeaS[i]=umeaP[1];
		luleuP = oneDay("../clean_data/luleu_clean.dat",i,0);
		luleuM[i]=luleuP[0];
		luleuS[i]=luleuP[1];
		*/
	}
	
	TCanvas* c2 = new TCanvas("c2", "every day graph multiple locations standard deviation included", 900, 600);
	
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
	
	Int_t lw1 = 2;
	
	TGraphErrors* t0p = new TGraphErrors(n,days,t0daysMean,zeros,t0daysStaDev);
	t0p->SetTitle("Temperatures over the year for different Lattitudes");
	t0p->GetXaxis()->SetTitle("Days");
  	t0p->GetYaxis()->SetTitle("Temperature [#circC]");
	t0p->SetMaximum(500);
	t0p->SetMinimum(-100);
	t0p->SetFillColor(2);
 	t0p->SetFillStyle(3004);
	t0p->Draw("a4 ");
	
	TGraphErrors* t1p = new TGraphErrors(n,days,t1daysMean,zeros,t1daysStaDev);
	t1p->SetFillColor(3);
	t1p->SetFillStyle(3005);
	t1p->Draw("4 ");
	
	TGraphErrors* t2p = new TGraphErrors(n,days,t2daysMean,zeros,t2daysStaDev);
	t2p->SetFillColor(4);
	t2p->SetFillStyle(3006);
	t2p->Draw("4 ");
	
	TGraphErrors* t0pl = new TGraphErrors(n,days,t0daysMean,zeros,zeros);
	t0pl->SetLineColor(2);
	t0pl->SetLineWidth(lw1);
	t0pl->Draw("l");
	TGraphErrors* t1pl = new TGraphErrors(n,days,t1daysMean,zeros,zeros);
	t1pl->SetLineColor(3);
	t1pl->SetLineWidth(lw1);
	t1pl->Draw("l");
	TGraphErrors* t2pl = new TGraphErrors(n,days,t2daysMean,zeros,zeros);
	t2pl->SetLineColor(4);
	t2pl->SetLineWidth(lw1);
	t2pl->Draw("l");

	/*
	TGraphErrors* lundG = new TGraphErrors(n,days,lundM,zeros,lundS);
	lundG->SetTitle("Temperatures over the year for different Lattitudes");
	lundG->GetXaxis()->SetTitle("Days");
  	lundG->GetYaxis()->SetTitle("Temperature [Celsius]");
	lundG->SetMaximum(20);
	lundG->SetMinimum(-4);
	lundG->SetFillColor(2);
	lundG->SetFillStyle(3001)
	lundG->Draw("a4")
	
	TGraphErrors* visbyG = new TGraphErrors(n,days,visbyM,zeros,visbyS);
	visbyG->SetFillColor(3);
	visbyG->SetFillStyle(3004)
	visbyG->Draw("4")
	
	TGraphErrors* upsalaG = new TGraphErrors(n,days,upsalaM,zeros,upsalaS);
	upsalaG->SetFillColor(4);
	upsalaG->SetFillStyle(3005)
	upsalaG->Draw("4")
	
	TGraphErrors* umeaG = new TGraphErrors(n,days,umeaM,zeros,umeaS);
	umeaG->SetFillColor(6);
	umeaG->SetFillStyle(3006)
	umeaG->Draw("4")
	
	TGraphErrors* luleuG = new TGraphErrors(n,days,luleuM,zeros,luleuS);
	luleuG->SetFillColor(28);
	luleuG->SetFillStyle(3007)
	luleuG->Draw("4")
	
	TGraphErrors* lundGl = new TGraphErrors(n,days,lundM,zeros,zeros);
	lundGl->SetLineColor(4);
	lundGl->SetLineWidth(lw1);
	lundGl->Draw("l");
	TGraphErrors* visbyGl = new TGraphErrors(n,days,visbyM,zeros,zeros);
	visbyGl->SetLineColor(4);
	visbyGl->SetLineWidth(lw1);
	visbyGl->Draw("l");
	TGraphErrors* upsalaGl = new TGraphErrors(n,days,upsalaM,zeros,zeros);
	upsalaGl->SetLineColor(4);
	upsalaGl->SetLineWidth(lw1);
	upsalaGl->Draw("l");
	TGraphErrors* umeaGl = new TGraphErrors(n,days,umeaM,zeros,zeros);
	umeaGl->SetLineColor(4);
	umeaGl->SetLineWidth(lw1);
	umeaGl->Draw("l");
	TGraphErrors* luleuGl = new TGraphErrors(n,days,luleuM,zeros,zeros);
	luleuGl->SetLineColor(4);
	luleuGl->SetLineWidth(lw1);
	luleuGl->Draw("l");
	*/

	
	TLegend* testL = new TLegend(0.1,0.7,0.48,0.9);
  	testL->AddEntry(t0p,"test0","f");
  	testL->AddEntry(t1p,"test1","f");
  	testL->AddEntry(t2p,"test2","f");
  	testL->Draw();
	

	/*
	auto Legend = new TLegend(0.1,0.7,0.48,0.9);
 	Legend->AddEntry(lundG,"Values from lund Latitude = 55.7#circ","f");
  	Legend->AddEntry(visbyG,"Values from Visby Latitude = 57.7#circ","f");
  	Legend->AddEntry(upsalaG,"Values from Upsala Latitude = 59.9#circ","f");
	Legend->AddEntry(umeaG,"Values from Umea Latitude = 63.8#circ","f");
	Legend->AddEntry(luleuG,"Values from Luleu Latitude = 65.5#circ","f");
 	Legend->Draw();
	*/

	c2->SaveAs("every_day_graph_multiple_locations_standard_deviations_included.jpg");
	
	
	
	
	
	
	TCanvas* c3 = new TCanvas("c3", "every day graph multiple locations just means", 900, 600);
	
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
	

	TGraphErrors* t0p2 = new TGraphErrors(n,days,t0daysMean,zeros,zeros);
	Int_t lw2 = 2;
	t0p2->SetMaximum(400);
	t0p2->SetMinimum(0);
	t0p2->SetLineColor(2);
   	t0p2->SetLineWidth(lw2);
	t0p2->Draw("AL");
	TGraphErrors* t1p2 = new TGraphErrors(n,days,t1daysMean,zeros,zeros);
	t1p2->SetLineColor(3);
   	t1p2->SetLineWidth(lw2);
	t1p2->Draw("L");
	TGraphErrors* t2p2 = new TGraphErrors(n,days,t2daysMean,zeros,zeros);
	t2p2->SetLineColor(4);
   	t2p2->SetLineWidth(lw2);
	t2p2->Draw("L");
	
	/*
	TGraphErrors* lundG2 = new TGraphErrors(n,days,lundM,zeros,zeros);
	lundG2->SetTitle("Temperatures over the year for different Lattitudes");
	lundG2->GetXaxis()->SetTitle("Days");
  	lundG2->GetYaxis()->SetTitle("Temperature [Celsius]");
	lundG2->SetMaximum(20);
	lundG2->SetMinimum(-4);
	lundG2->SetLineColor(2);
   	lundG2->SetLineWidth(lw);
	lundG2->Draw("AL");
	
	TGraphErrors* visbyG2 = new TGraphErrors(n,days,visbyM,zeros,visbyS);
	visbyG2->SetLineColor(3);
   	visbyG2->SetLineWidth(lw);
	visbyG2->Draw("L");
	
	TGraphErrors* upsalaG2 = new TGraphErrors(n,days,upsalaM,zeros,upsalaS);
	upsalaG2->SetLineColor(4);
   	upsalaG2->SetLineWidth(lw);
	upsalaG2->Draw("L");
	
	TGraphErrors* umeaG2 = new TGraphErrors(n,days,umeaM,zeros,umeaS);
	umeaG2->SetLineColor(6);
   	umeaG2->SetLineWidth(lw);
	umeaG2->Draw("L");
	
	TGraphErrors* luleuG2 = new TGraphErrors(n,days,luleuM,zeros,luleuS);
	luleuG2->SetLineColor(28);
   	luleuG2->SetLineWidth(lw);
	luleuG2->Draw("L");
	*/
	
	TLegend * testL2 = new TLegend(0.1,0.7,0.48,0.9);
  	testL2->AddEntry(t0p2,"test0","l");
  	testL2->AddEntry(t1p2,"test1","l");
  	testL2->AddEntry(t2p2,"test2","l");
  	testL2->Draw();
	
	/*
	auto Legend2 = new TLegend(0.1,0.7,0.48,0.9);
 	Legend2->AddEntry(lundG2,"Values from lund Latitude = 55.7","l");
  	Legend2->AddEntry(visbyG2,"Values from Visby Latitude = 57.7","l");
  	Legend2->AddEntry(upsalaG2,"Values from Upsala Latitude = 59.9","l");
	Legend2->AddEntry(umeaG2,"Values from Umea Latitude = 63.8","l");
	Legend2->AddEntry(luleuG2,"Values from Luleu Latitude = 65.5","l");
 	Legend2->Draw();
	*/

	c3->SaveAs("every_day_graph_multiple_locations_just_means.jpg");

}
