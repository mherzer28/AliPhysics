#ifndef ALIJCORRECTIONMAPTASK_H
#define ALIJCORRECTIONMAPTASK_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */
//______________________________________________________________________________
// Analysis task : Providing Correction Maps 
// Track cuts are applied
// author:  D.J. Kim (dong.jo.kim@cern.ch)
// ALICE Group University of Jyvaskyla, Finland
// Note: Adapted for AliAnalysisTaskSE
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "AliAnalysisTaskSE.h"

//==============================================================

using namespace std;
class TFile;
class TH1D;
class TH2D;
class TAxis;
class TGraphErrors;
class TList;
class AliJCorrectionMapTask : public AliAnalysisTaskSE {
public:
	AliJCorrectionMapTask();
	AliJCorrectionMapTask(const char *name);
	AliJCorrectionMapTask(const AliJCorrectionMapTask& ap);
	AliJCorrectionMapTask& operator = (const AliJCorrectionMapTask& ap);
	virtual ~AliJCorrectionMapTask();

	// methods to fill from AliAnalysisTaskSE
	virtual void UserCreateOutputObjects();
	virtual void Init();
	virtual void LocalInit() { Init(); }
	virtual void UserExec(Option_t *option);
	virtual void Terminate(Option_t* opt="");

	//inline void DEBUG(int level, TString msg){ if(level < fDebugLevel){ std::cout<< level << "\t" << msg << endl;};}
	// Getters for other analysis tasks
	void SetDebugLevel(int debuglevel) const{}
		//fDebugLevel = debuglevel; cout <<"setting Debug Level = " << fDebugLevel << endl;}

	UInt_t ConnectInputContainer(const TString &, const TString &);
	void EnablePhiCorrection(UInt_t, const TString &); //it efficiency filter bit
	void EnableCentFlattening(const TString &);
	void EnableEffCorrection(const TString &);
	void EnableEffCorrection2(const TString &);
	enum EFF2_LABEL{
		EFF2_LABEL_GLOBAL8,
		EFF2_LABEL_GLOBALSDD8,
		EFF2_LABEL_HYBRID6,
		EFF2_LABEL_HYBRID8,
		EFF2_LABEL_HYBRID10,
		EFF2_LABEL_COUNT,
	};
	TH1 * GetCorrectionMap(UInt_t, UInt_t, UInt_t);
	TH1* GetEffCorrectionMap2(UInt_t, EFF2_LABEL, double &V0mean);
	TH1 * GetEffCorrectionMap2(const TString &, EFF2_LABEL);
	TH1 * GetCentCorrection();
	TGraphErrors * GetEffCorrectionMap(UInt_t run, Double_t cent, UInt_t fEffFilterBit);
	double GetEffCorrection(TGraphErrors *gCor, double pt ) const ;
	TAxis * GetCentBinEff();

	struct RunPeriod{
		UInt_t runStart;
		UInt_t runEnd;
		const char *pPeriod;
		double V0mean;
	};
private:
	//TList *fOutputList;          //! output data container 
	std::map<UInt_t, TH1 *> PhiWeightMap[8][20]; //! map for each run, index1: map id, index2: cent
	std::map<UInt_t, TGraphErrors *> EffWeightMap[20]; //!  cent

	//std::map<UInt_t, TH1 *> //pp?
	//typedef std::tuple<uint, uint, const char *, double> RunPeriod;
	std::vector<RunPeriod> runPeriods;
	TH1 *pPhiWeights; //!
	TGraphErrors *grEffCor; //! for one cent
	TAxis *fCentBinEff; //! for different cent bin for MC eff
	//int fDebugLevel; //
	UInt_t inputIndex;
	UInt_t phiInputIndex[8];
	UInt_t centInputIndex;
	UInt_t effInputIndex;
	UInt_t effInputIndex2;
	static const char *peff2Labels[EFF2_LABEL_COUNT];

	ClassDef(AliJCorrectionMapTask, 1);

};
#endif // AliJCorrectionMapTask_H
