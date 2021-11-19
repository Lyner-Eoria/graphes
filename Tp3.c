#include "Kit.h"
#include "Graphe.h"
#include "Tp3.h"
int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void PerformanceComapreR(int uSommetMax);
void Tp3CalculerTout(char * sGraphe);

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER

void Tp3TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: 
			Tp3CalculerTout("AB1AC2AD1BC2DE1CE3");
			break;
		case 2:
			PerformanceComapreR(256);
			break;
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

void PerformanceComapreR(int uSommetMax) {
	enum grType GrapheType;
	const int poidsMax = 9;
	int nLg = 15, nLg2 = 8;
	ChaineGarnir('.');
		printf("%s%s %s%s\n", sE(6), sChaine2("Comptage", 6 * nLg - 6), sE(6), sChaine2("Chronométrage", 2 * nLg2 + nLg - 6));
	ChaineGarnir(' ');
	printf("    S%s%s%s", sChaine0("S*S", nLg), sChaine0("Cumul sans tas", nLg), sChaine2("(S*S)/Cumul", nLg));
	printf("%s%s%s", sChaine0("S2LogS", nLg), sChaine0("Cumul avec tas", nLg), sChaine2("S2LogS/Cumul", nLg));
	printf("%s%s%s\n", sChaine0("Sans", nLg2), sChaine0("Avec", nLg2), sChaine2("Sans/Avec", nLg));
	HasardInit(time(0));
	graf *pgG;
	int complStas, complAtas, chrStas, chrAtas;
	//rep jsq S > uSommetMax
		for(int S = 1; S <= uSommetMax; S *= 2) {
			GrapheCreer1(&pgG,grK,S,k1Creer);
				GraphePondererAleatoirement(pgG, poidsMax);
				//GrapheVoir0(pgG, "", grCout);
				chrStas = zChrono(kV);
				bGrapheCheminerCourt(pgG, 1, S, !k1Tas, !k1Afficher, &complStas);
				chrStas = zChrono(kF);
				chrAtas = zChrono(kV);
				bGrapheCheminerCourt(pgG, 1, S, k1Tas, !k1Afficher, &complAtas);
				chrAtas = zChrono(kF);
			GrapheCreer1(&pgG,grK,S,!k1Creer);
			//afficher res
			printf("  %s%s%s%s", sEnt3(S, 3), sChaine0(sEnt(S*S), nLg), sEnt3(complStas, nLg), sChaine2(sRatio(S*S, complStas), nLg));
			printf("%s%s%s", sEnt3(S*nLog2(S), nLg), sChaine0(sEnt(complAtas), nLg), sChaine2(sRatio(S*nLog2(S), complAtas), nLg));
			printf("%s%s%s\n", sEnt3(chrStas, nLg2), sChaine0(sEnt(chrAtas), nLg2), sChaine2(sRatio(chrStas, chrAtas), nLg));
	}
}//PerformanceComapreR

void Tp3CalculerTout(char * sGraphe) {
	graf *pgG;
	int comp;
	GrapheGenerer(sGraphe, grCout, &pgG);
		GrapheVoir0(pgG, "", grCout);
		ModeCaractere(1);
		bGrapheCheminerCourt(pgG, 1, pgG->nSommetEnTout, !k1Tas, k1Afficher, &comp);
		ModeCaractere(0);
	GrapheCreer(0, &pgG);
}