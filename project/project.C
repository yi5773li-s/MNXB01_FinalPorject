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
#include <TMultiGraph.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <string.h>

using std::string;
using std::vector;
using std::ifstream;

Int_t n=365;
Double_t outputMS[2];

Double_t* oneDayMDI(string filePath="../clean_data/lund_clean.dat", Int_t month=1, Int_t day=1, Int_t plot=0)
{
	Double_t yeart;
	Double_t montht;
	Double_t dayt;
	Double_t tempt;

	vector<Double_t> y;
	vector<Double_t> t;
	vector<Double_t> average;

	// open data file
	ifstream datafile(filePath.c_str());


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
			else
			{
				break;
			}
		}

		average.push_back(temp/counter);
	}

	// close the datafile
	datafile.close();

	Int_t asize = average.size();
	if (plot==1)
	{
		TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
		hist->SetFillColor(kRed + 1);
		for (Int_t i = 0; i < asize; i++)
		{
			hist->Fill(average[i]);
		}
		hist->Draw();
	}

	else
	{
		Double_t mean = 0.;
		for (Int_t i = 0; i < asize; i++)
		{
		mean += average[i];
		}
		mean = mean/asize;
		Double_t STD = 0.;
		for (Int_t i = 0; i < asize; i++)
		{
			STD += (average[i]-mean)*(average[i]-mean);
		}
		STD /= asize;
		STD = TMath::Sqrt(STD);
		outputMS[0] = mean;
		outputMS[1] = STD;

		return outputMS;
	}

        //since the function has to return double*, in case of plot == 1 we return zero
        outputMS[0] = 0.0;
        outputMS[1] = 0.0;

        return outputMS;
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



Double_t oneDayProb(string filePath="../clean_data/lund_clean.dat", Int_t month=1, Int_t day=1,Double_t temp=20,Double_t errorRange=2)
{
	Double_t * pointer =oneDayMDI(filePath, month, day, 0);
	TF1* normal = new TF1("normal","gaus", -20.,40.);
	normal->SetParameters(1.0/(pointer[1]*TMath::Sqrt(2.0*TMath::Pi())),pointer[0],pointer[1]);
	return normal->Integral(temp-errorRange/2,temp+errorRange/2);
}






void WarmColdDay(string filePath="../clean_data/uppsala_clean.dat")

#define LULEA_CLEAN "../clean_data/lulea_clean.dat"
#define LUND_CLEAN "../clean_data/lund_clean.dat"
#define UMEA_CLEAN "../clean_data/umea_clean.dat"
#define UPPSALA_CLEAN "../clean_data/uppsala_clean.dat"
#define VISBY_CLEAN "../clean_data/visby_clean.dat"

int WarmColdDay(string loc = "uppsala")

{
    transform(loc.begin(), loc.end(), loc.begin(), [](unsigned char chr){return std::tolower(chr);});
    char fileName[1024];
    if (loc == "lund")
    {
        strcpy(fileName, LUND_CLEAN);
    }
    else if (loc == "lulea")
    {
        strcpy(fileName, LULEA_CLEAN);
    }
    else if (loc == "umea")
    {
        strcpy(fileName, UMEA_CLEAN);
    }
    else if (loc == "uppsala")
    {
        strcpy(fileName, UPPSALA_CLEAN);
    }
    else if (loc == "visby")
    {
        strcpy(fileName, VISBY_CLEAN);
    }
    else
    {
        return -1;
    }
	TH1D* warm = new TH1D("temperature", ";Day of year;Entries", 3*365, -365, 730);
	warm->SetFillColor(kRed + 1);

	TH1D* cold = new TH1D("temperature", "Coldest;Day of year;Entries", 730, 1, 2*365);
	cold->SetFillColor(kBlue + 1);
	TH1D* cold_copy = new TH1D("temperature", "Coldest;Day of year;Entries", 730, -365, 365);
	cold_copy->SetFillColor(kBlue + 1);


	int days_in_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	Double_t yeart;
	Double_t montht;
	Double_t dayt;
	Double_t tempt;

	vector<Double_t> y;
	vector<Double_t> m;
	vector<Double_t> d;
	vector<Double_t> t;
	vector<Double_t> average;

	// open data file
	ifstream datafile(fileName);

	while (datafile >> yeart >> montht >> dayt >> tempt)
	{
		y.push_back(yeart);
		m.push_back(montht);
		d.push_back(dayt);
		t.push_back(tempt);
	}

	Int_t size = y.size();

	vector<Double_t> ty,tm,td;

	for (Int_t i = 0; i < size; i++)
	{
		ty.push_back(t[i]);
		tm.push_back(m[i]);
		td.push_back(d[i]);

		Double_t test = y[i];

		for (Int_t j = i+1; j < size; j++)
		{
			if (test == y[j])
			{
				ty.push_back(t[j]);
				tm.push_back(m[j]);
				td.push_back(d[j]);
				i++;
			}
			else
			{
				break;
			}
		}
		//Int_t indexMax = ty.size() - 1;
		//Int_t indexMin = ty.min_e;

		double tMax = -1.0e100;
		double tMin = 1.0e100;
		int indexMax = 0;
		int indexMin = 0;

		for (int i = 0; i < (int)ty.size(); i++)
		{
			if (ty[i] < tMin)
			{
				tMin = ty[i];
				indexMin = i;
			}
			if (ty[i] > tMax)
			{
				tMax = ty[i];
				indexMax = i;
			}
		}

		Int_t date = td[indexMax];
		if (tm[indexMax]==2 && td[indexMax] ==29)
		{
		}
		else
		{
			for (Int_t s = tm[indexMax]; s>0; s--)
			{
				date += days_in_month[s-1];
			}
			warm->Fill(date);
		}
		
		

		date = td[indexMin];
		if (tm[indexMin] == 2 && td[indexMin] == 29)
		{
		}
                else
                {
			for (Int_t s = tm[indexMin]; s>0; s--)
			{
				date += days_in_month[s-1];
			}
                        if (date < 180)
                        {
		            cold->Fill(date + 365);
		            cold_copy->Fill(date);
                        }
                        else
                        {
                            cold->Fill(date);
		            cold_copy->Fill(date - 365);
                        }
                }

                ty.clear();
                tm.clear();
                td.clear();
	}

        TF1* gaus_cold1 = new TF1("gaus_cold1", "gaus", 180, 180 + 365);
        TF1* gaus_cold2 = new TF1("gaus_cold2", "gaus", -180, -180 + 365);
        TF1* gaus_warm = new TF1("gaus_warm", "gaus", 0, 365);

        gaus_warm->SetLineColor(kBlue);
        gaus_cold1->SetLineColor(kRed);
        gaus_cold2->SetLineColor(kRed);

        warm->Fit("gaus_warm", "R");
        cold->Fit("gaus_cold1", "R");
        cold_copy->Fit("gaus_cold2", "R");

        TCanvas* cnCold = new TCanvas("cnCold", "cnCold", 900, 600);
        TCanvas* cnWarmCold = new TCanvas("cnWarmCold", "cnWarmCold", 900, 600);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1110);

        cnCold->cd();
	cold_copy->Draw();
        cnCold->Update();

        cnWarmCold->cd();
        warm->Draw();
	cold->Draw("same");
	cold_copy->Draw("same");

        warm->GetXaxis()->CenterTitle();
        warm->GetYaxis()->CenterTitle();
        warm->GetXaxis()->SetRangeUser(0, 365);
        warm->GetYaxis()->SetRangeUser(0, 1.5*TMath::Max(warm->GetMaximum(), cold_copy->GetMaximum()));

        cnWarmCold->Modified();
        cnWarmCold->Update();
    
        TPaveStats* stats1 = (TPaveStats*)(warm->FindObject("stats"));
        stats1->SetX1NDC(.1);
        stats1->SetX2NDC(.4);
        stats1->SetY1NDC(.75);
        stats1->SetY2NDC(.9);
        stats1->SetTextColor(kBlue);
        cnWarmCold->Modified();

        TPaveStats* stats2 = (TPaveStats*)(cold_copy->FindObject("stats"));
        stats2->SetX1NDC(.6);
        stats2->SetX2NDC(.9);
        stats2->SetY1NDC(.75);
        stats2->SetY2NDC(.9);
        stats2->SetTextColor(kRed);
        cnWarmCold->Modified();

        char pdfName[128];
        sprintf(pdfName, "cold_warm_day_%s.pdf", loc.c_str());
        cnWarmCold->SaveAs(pdfName);
        
        return 0;
}

void everyDay(string filePath="../clean_data/uppsala_clean.dat"){
	Double_t *p;
	Double_t daysMean[n],daysStaDev[n],days[n],zeros[n];
	for(Int_t i = 0; i < n; i++){
		p = oneDay(filePath,i,0);
		daysMean[i]=p[0];
		daysStaDev[i]=p[1];
		days[i]=i+1;
		zeros[i]=0;
	}
	
	TCanvas* c1 = new TCanvas("c1", "every day graph one location", 900, 600);

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

	TGraphErrors* g1 = new TGraphErrors(n,days,daysMean,zeros,daysStaDev);
	g1->SetTitle("Temperatures over the year for one location");
	g1->GetXaxis()->SetTitle("Days");
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->SetTitle("Temperature [#circC]");
	g1->GetYaxis()->CenterTitle();
	g1->SetMaximum(20);
	g1->SetMinimum(-10);
	g1->SetFillColor(4);
	g1->SetFillStyle(3000);
	g1->Draw("a4 ");
	TGraphErrors* g1l = new TGraphErrors(n,days,daysMean,zeros,zeros);
	g1l->SetLineColor(1);
	g1l->SetLineWidth(2);
	g1l->Draw("l");

	c1->SaveAs("every_day_graph_one_location.pdf");
	

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


	TH1D* histED = new TH1D("histED", "Temperature;Day of the year;Temperature[#circC]", 365, 1, 365);
	for(int bin = 1; bin <= histED->GetNbinsX(); ++bin) {
		histED->SetBinContent(bin, daysMean[bin-1]);
		histED->SetBinError(bin, daysStaDev[bin-1]);
	}
	histED->SetLineColor(4);
	histED->GetXaxis()->CenterTitle();
	histED->GetYaxis()->CenterTitle();
	histED->Draw("E L");
	TH1I* histEDl = new TH1I("histED", "Temperature;Day of the year;Temperature[#circC]", 365, 1, 365);
	for(int bin = 1; bin <= histEDl->GetNbinsX(); ++bin) {
		histEDl->SetBinContent(bin, daysMean[bin-1]);
	}
	histEDl->SetLineColor(1);
	histEDl->SetLineWidth(2);
	histEDl->Draw("L same");

	c4->SaveAs("every_day_graph_one_location_histogram.pdf");

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

	Double_t *lundP, *visbyP, *upsalaP, *umeaP, *luleuP;
	Double_t lundM[n], visbyM[n], upsalaM[n], umeaM[n], luleuM[n];
	Double_t lundS[n], visbyS[n], upsalaS[n], umeaS[n], luleuS[n];

	for(Int_t i = 0; i < n; i++){
		days[i]=i+1;
		zeros[i]=0;

		lundP = oneDay("../clean_data/lund_clean.dat",i+1,0);
		lundM[i]=lundP[0];
		lundS[i]=lundP[1];
		visbyP = oneDay("../clean_data/visby_clean.dat",i+1,0);
		visbyM[i]=visbyP[0];
		visbyS[i]=visbyP[1];
		upsalaP = oneDay("../clean_data/uppsala_clean.dat",i+1,0);
		upsalaM[i]=upsalaP[0];
		upsalaS[i]=upsalaP[1];
		umeaP = oneDay("../clean_data/umea_clean.dat",i+1,0);
		umeaM[i]=umeaP[0];
		umeaS[i]=umeaP[1];
		luleuP = oneDay("../clean_data/lulea_clean.dat",i+1,0);
		luleuM[i]=luleuP[0];
		luleuS[i]=luleuP[1];
	}

	Int_t lw = 2;
	Int_t lw1 = 2;



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


	TGraphErrors* lundG = new TGraphErrors(n,days,lundM,zeros,lundS);

	lundG->SetTitle("Temperatures over the year for different Lattitudes");
	lundG->GetXaxis()->SetTitle("Days");
	lundG->GetXaxis()->CenterTitle();
	lundG->GetYaxis()->SetTitle("Temperature [Celsius]");
	lundG->GetYaxis()->CenterTitle();
	lundG->SetMaximum(25);
	lundG->SetMinimum(-20);
	lundG->SetLineColor(2);
	lundG->SetFillColor(2);
	lundG->Draw("al");

	TGraphErrors* visbyG = new TGraphErrors(n,days,visbyM,zeros,visbyS);
	visbyG->SetLineColor(3);
	visbyG->SetFillColor(3);
	visbyG->Draw("l");

	TGraphErrors* upsalaG = new TGraphErrors(n,days,upsalaM,zeros,upsalaS);
	upsalaG->SetLineColor(4);
	upsalaG->SetFillColor(4);
	upsalaG->Draw("l");

	TGraphErrors* umeaG = new TGraphErrors(n,days,umeaM,zeros,umeaS);
	umeaG->SetLineColor(6);
	umeaG->SetFillColor(6);
	umeaG->Draw("l");

	TGraphErrors* luleuG = new TGraphErrors(n,days,luleuM,zeros,luleuS);
	luleuG->SetLineColor(28);
	luleuG->SetFillColor(28);
	luleuG->Draw("l");

	TGraphErrors* lundGl = new TGraphErrors(n,days,lundM,zeros,zeros);
	lundGl->SetLineColor(2);
	lundGl->SetLineWidth(lw1);
	lundGl->Draw("l");
	TGraphErrors* visbyGl = new TGraphErrors(n,days,visbyM,zeros,zeros);
	visbyGl->SetLineColor(3);
	visbyGl->SetLineWidth(lw1);
	visbyGl->Draw("l");
	TGraphErrors* upsalaGl = new TGraphErrors(n,days,upsalaM,zeros,zeros);
	upsalaGl->SetLineColor(4);
	upsalaGl->SetLineWidth(lw1);
	upsalaGl->Draw("l");
	TGraphErrors* umeaGl = new TGraphErrors(n,days,umeaM,zeros,zeros);
	umeaGl->SetLineColor(6);
	umeaGl->SetLineWidth(lw1);
	umeaGl->Draw("l");
	TGraphErrors* luleuGl = new TGraphErrors(n,days,luleuM,zeros,zeros);
	luleuGl->SetLineColor(1);
	luleuGl->SetLineWidth(lw1);
	luleuGl->Draw("l");



	TLegend* Legend = new TLegend(0.1,0.7,0.48,0.9);
	Legend->SetFillStyle(0);
	Legend->SetBorderSize(0);
 	Legend->AddEntry(lundG,"Values from lund Latitude = 55.7#circ","f");
  	Legend->AddEntry(visbyG,"Values from Visby Latitude = 57.7#circ","f");
  	Legend->AddEntry(upsalaG,"Values from Upsala Latitude = 59.9#circ","f");
	Legend->AddEntry(umeaG,"Values from Umea Latitude = 63.8#circ","f");
	Legend->AddEntry(luleuG,"Values from Luleu Latitude = 65.5#circ","f");
 	Legend->Draw();


	c2->SaveAs("every_day_graph_multiple_locations_standard_deviations_included.pdf");



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

	TGraphErrors* lundG2 = new TGraphErrors(n,days,lundM,zeros,zeros);
	lundG2->SetTitle("Temperatures over the year for different Lattitudes");
	lundG2->GetXaxis()->SetTitle("Days");
	lundG2->GetXaxis()->CenterTitle();
	lundG2->GetYaxis()->SetTitle("Temperature [#circC]");
	lundG2->GetYaxis()->CenterTitle();
	lundG2->SetMaximum(20);
	lundG2->SetMinimum(-15);
	lundG2->SetLineWidth(lw);
	lundG2->SetLineColor(2);
   	//mult2->Add(lundG2);
	lundG2->Draw("AL");
	//mult2->Add(lundG2,"l");

	TGraphErrors* visbyG2 = new TGraphErrors(n,days,visbyM,zeros,zeros);
	visbyG2->SetLineColor(3);
	visbyG2->SetLineWidth(lw);
   	//mult2->Add(visbyG2);
	visbyG2->Draw("L");
	//mult2->Add(visbyG2,"l");

	TGraphErrors* upsalaG2 = new TGraphErrors(n,days,upsalaM,zeros,zeros);
	upsalaG2->SetLineColor(4);
	upsalaG2->SetLineWidth(lw);
   	//mult2->Add(upsalaG2);
	upsalaG2->Draw("L");
	//mult2->Add(upsalaG2,"l");

	TGraphErrors* umeaG2 = new TGraphErrors(n,days,umeaM,zeros,zeros);
	umeaG2->SetLineColor(6);
	umeaG2->SetLineWidth(lw);
   	//mult2->Add(umeaG2);
	umeaG2->Draw("L");
	//mult2->Add(umeaG2,"l");

	TGraphErrors* luleuG2 = new TGraphErrors(n,days,luleuM,zeros,zeros);
	luleuG2->SetLineColor(28);
	luleuG2->SetLineWidth(lw);
   	//mult2->Add(luleuG2);
	luleuG2->Draw("L");
	//mult2->Add(luleuG2,"l");


	TLegend* Legend2 = new TLegend(0.1,0.7,0.48,0.9);
	Legend2->SetFillStyle(0);
	Legend2->SetBorderSize(0);
 	Legend2->AddEntry(lundG2,"Values from lund Latitude = 55.7","l");
	Legend2->AddEntry(visbyG2,"Values from Visby Latitude = 57.7","l");
	Legend2->AddEntry(upsalaG2,"Values from Upsala Latitude = 59.9","l");
	Legend2->AddEntry(umeaG2,"Values from Umea Latitude = 63.8","l");
	Legend2->AddEntry(luleuG2,"Values from Luleu Latitude = 65.5","l");
 	Legend2->Draw();


	c3->SaveAs("every_day_graph_multiple_locations_just_means.pdf");


}


#include <string.h>



#include <stdio.h>
#include <TDatime.h>

#define BORAS "../MNXB01-project/datasets/smhi-opendata_Boras.csv"
#define FALSTERBO "../MNXB01-project/datasets/smhi-opendata_Falsterbo.csv"
#define FALUN "../MNXB01-project/datasets/smhi-opendata_Falun.csv"
#define KARLSTAD "../MNXB01-project/datasets/smhi-openda_Karlstad.csv"
#define LULEA "../MNXB01-project/datasets/smhi-opendata_Lulea.csv"
#define LUND "../MNXB01-project/datasets/smhi-opendata_Lund.csv"
#define SODERARM "../MNXB01-project/datasets/smhi-opendata_Soderarm.csv"
#define UMEA "../MNXB01-project/datasets/smhi-opendata_Umea.csv"
#define UPPSALA "../MNXB01-project/datasets/uppsala_tm_1722-2013.dat"
#define VISBY "../MNXB01-project/datasets/smhi-opendata_Visby.csv"

#define Y2S 31556952

using std::transform;

int getTemperature(string loc = "lund")
{
    transform(loc.begin(), loc.end(), loc.begin(), [](unsigned char chr){return std::tolower(chr);});
    char fileName[1024];
    if (loc == "lund")
    {
        strcpy(fileName, LUND);
    }
    else if (loc == "boras")
    {
        strcpy(fileName, BORAS);
    }
    else if (loc == "falsterbo")
    {
        strcpy(fileName, FALSTERBO);
    }
    else if (loc == "falun")
    {
        strcpy(fileName, FALUN);
    }
    else if (loc == "karlstad")
    {
        strcpy(fileName, KARLSTAD);
    }
    else if (loc == "lulea")
    {
        strcpy(fileName, LULEA);
    }
    else if (loc == "soderarm")
    {
        strcpy(fileName, SODERARM);
    }
    else if (loc == "umea")
    {
        strcpy(fileName, UMEA);
    }
    else if (loc == "uppsala")
    {
        strcpy(fileName, UPPSALA);
    }
    else if (loc == "visby")
    {
        strcpy(fileName, VISBY);
    }
    else
    {
        return -1;
    }
    int year, month, day, hour;
    double tempr;

    FILE* inputFile = fopen(fileName, "r");
    char line[1024];
    int lineNumber = 0;
    vector<double> vDate;
    vector<double> vTempr;
    while (fgets(line, sizeof(line), inputFile))
    {
        if(loc != "uppsala")
        {
            if (lineNumber < 15)
            {
                printf("%2i:%s\n", lineNumber, line);
            }
            if (lineNumber > 11)
            {
                sscanf(line, "%4d-%2d-%2d;%2d:%*2d:%*2d;%lf", &year, &month, &day, &hour, &tempr);
                if (lineNumber%1000 == 0)
                {
                    printf("%d-%d-%d %d:%d:%d > %f\n", year, month, day, hour, 0, 0, tempr);
                }
                //TDatime dateBuffer(year, month, day, hour, 0, 0);
                double dateBuffer = Y2S*(double)(year - 1970) + Y2S*(double)month/12.0
                    + Y2S*(double)day/365.2425 + Y2S*(double)hour/8765.82;
                vDate.push_back(dateBuffer);
                vTempr.push_back(tempr);
            }
        }
        else if (loc == "uppsala")
        {
            {
                sscanf(line, "%d %d %d %*f %lf", &year, &month, &day, &tempr);
                double dateBuffer = Y2S*(double)(year - 1970) + Y2S*(double)month/12.0
                    + Y2S*(double)day/365.2425;
                vDate.push_back(dateBuffer);
                vTempr.push_back(tempr);
            }
        }
        lineNumber++;
    }

    TGraph* grTempr = new TGraph((int)vTempr.size(), &vDate[0], &vTempr[0]);
    grTempr->SetLineColor(kBlue);
    grTempr->SetTitle("");
    grTempr->SetName("grTempr");

    TCanvas* cnTempr = new TCanvas("cnTempr", "cnTempr", 900, 600);
    cnTempr->cd();
    grTempr->Draw("AL");

    grTempr->GetXaxis()->SetTimeDisplay(1);
    grTempr->GetXaxis()->SetNdivisions(503);
    grTempr->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    grTempr->GetXaxis()->SetTimeOffset(0, "gmt");
    grTempr->GetYaxis()->SetTitle("Temperature, #circC");
    grTempr->GetXaxis()->SetTitle("Date, YYYY-MM-DD hh:mm");
    grTempr->GetYaxis()->CenterTitle();
    grTempr->GetXaxis()->CenterTitle();
    cnTempr->Modified();

    gStyle->SetOptFit(1110);
    TF1* fitPol1 = new TF1("fitPol1", "[0] + [1]*x", vDate[0], vDate[vDate.size() - 1]);
    grTempr->Fit("fitPol1", "R");
    double pol0 = fitPol1->GetParameter(0);
    double pol1 = fitPol1->GetParameter(1);
    fitPol1->SetParameter(0, pol0);
    fitPol1->SetParameter(1, pol1);
    fitPol1->SetLineColor(kRed);
    fitPol1->SetLineWidth(2);
    cnTempr->Update();

    char dataName[128];
    sprintf(dataName, "Temperature in the %s area", loc.c_str());
    TLegend* aLegend = new TLegend(0.1, 0.7, 0.4, 0.9);
    aLegend->AddEntry("grTempr", dataName);
    aLegend->AddEntry("fitPol1", "Linear fit");
    aLegend->Draw();

    TPaveStats* fitStats = (TPaveStats*)(grTempr->FindObject("stats"));
    fitStats->SetX1NDC(0.6);
    fitStats->SetY1NDC(0.7);
    fitStats->SetX2NDC(0.9);
    fitStats->SetY2NDC(0.9);

    grTempr->GetYaxis()->SetRangeUser(-35, 60);

    cnTempr->Modified();


    char pdfName[128];
    sprintf(pdfName, "temperature_%s.pdf", loc.c_str());
    cnTempr->SaveAs(pdfName);

    grTempr->GetXaxis()->SetRangeUser(vDate[(int)(0.4*vDate.size())], vDate[(int)(0.5*vDate.size())]);
    char pdfNameZoomed[128];
    sprintf(pdfNameZoomed, "temperature_%s_zoomed.pdf", loc.c_str());
    cnTempr->SaveAs(pdfNameZoomed);

    return 0;
}

