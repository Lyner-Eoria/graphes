#include "Kit.h"
#include "Graphe.h"
#include "Tp2.h"
#include "Deque.h"
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué
void TP2ColorieR(char *sCodeSource);

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			GrapheCreer(0,&pgG);
			break;
		case 20: TP2ColorieR("AB1AC1BC2CD3");
			break;
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

void TP2ColorieR(char *sGrapheSource){
	graf *g;
	//si défini,.
	Appel0("TP2ColorieR");
		printf("\t\t\t Code source: %s.\n",sG(sGrapheSource));
		// générer g
			GrapheGenerer(sGrapheSource, grPoids, &g);
			GrapheSymetriser(g, grPoids);
			GrapheVoir0(g, "Graphe", grPoids);
		DequeAllouer(g->nSommetEnTout);
			// déconstruire g
				int dSommets[g->nSommetEnTout + 1], sX1, sX2, aK, sMax;
				for (sX1 = 1; sX1 <= g->nSommetEnTout; sX1++) {
					VecteurRaz(dSommets, g->nSommetEnTout);
					for (sX2 = 1; sX2 <= g->nSommetEnTout; sX2++) {
						dSommets[sX2] = 0;
						for (aK = g->aHed[sX2]; aK < g->aHed[sX2+1]; aK++)
							if(g->nPoids[aK] > 0)
								dSommets[sX2] += 1;
					}
					VecteurVoir0("Degrés", dSommets);
					sMax = 1;
					for(sX2 = 2; sX2 <= g->nSommetEnTout; sX2++)
						sMax = dSommets[sX2] > dSommets[sMax] ? sX2 : sMax;
					d(sMax);
					DequeEmpiler(sMax);
					ModeCaractere(1);
					DequeVoirPile("Pile");
					ModeCaractere(0);
					for(aK = g->aHed[sMax]; aK < g->aHed[sMax+1]; aK++)
						g->nPoids[aK] = -g->nPoids[aK];
				}
			//reconstruire g
				int nCouleur[g->nSommetEnTout + 1], bColoris[g->nSommetEnTout + 1], sC, i;
				VecteurRaz(nCouleur, g->nSommetEnTout);
				for (sX1 = 1; sX1 <= g->nSommetEnTout; sX1++) {
					sC = sDequeDepiler();
					d(sC);
					VecteurRaz(bColoris, g->nSommetEnTout);
					for (aK = g->aHed[sC]; aK < g->aHed[sC+1]; aK++)
						bColoris[nCouleur[g->sSuk[aK]]] = 1;
					for(i = 1; bColoris[i]; i++);
					nCouleur[sC] = i;
					VecteurVoir0("Couleurs", nCouleur);
				}
				for(sX1 = 1; sX1 < g->nSommetEnTout; sX1++) {
					printf("R%d: ", sX1);
					for(i = 1; i <= g->nSommetEnTout; i++)
						if(nCouleur[i] == sX1)
							printf("%d ", i);
					printf("\n");
				}
		DequeAllouer(0);
	Appel1("TP2ColorieR");
}//TP2ColorieR