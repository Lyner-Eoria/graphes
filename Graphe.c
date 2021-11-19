#include "Kit.h"
#include "Deque.h"
#include "Foret.h"
#include "Graphe.h"
#include "Tas.h"
#include "Abe.h"
//structure de données du graphe courant G
#define kbCourtSinonLong 1
#define k1BipartiR kV
const int k1PerformanceCompareR=kV;
int bGrapheAmorceR;
int bGrapheCreeR;
int bGrapheBipartiR;
void CoutInverseR(graf *pgG);
void DijkstraAvecOuSansTasCompareR();
void GrapheCouvriR();
int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur);
void GrapheCheminerAuLargE (graf *pgG,int bSimuler,int sSource,int sTrappe);
void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int nMesure,int gcMode);
int bGrapheCheminE(graf *pgG,int sSource,int sTrappe);
int nGrapheChemineR (graf *pgG,int sSource,int sTrappe,int bSimuler,int *pnComplexiteh);
int nGrapheCheminerAuLargE (graf *pgG,int bSimuler,int sSource,int sTrappe);
int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh);//O(SlgS+A)
int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh);//O(S2)
void GrapheCompletCreerPondereR(int nSommet,graf **ppgG);
void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG);
void GraphePondererPareiL(graf *pgG);
void GrapheQuinconceR(graf *pgG,int bBipartir);
int bGrapheVidE(graf *pgG);
void GrapheCouvrirAvecKruskaL(graf *pgG,int bAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecKruskaL(graf *pgG,int bLogn,int bTas,int bAfficher);
int nGrapheCouvrirAvecP(graf *pgG);
void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecPriM(graf *pgG);
void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int nPoidsMax,graf **ppgG);
void GrapheSymetrizer(graf *pgG);
void GrapheViseR(graf *pgG,char *sMessage);

void DijkstraAvecOuSansTasCompareR(){
	//effectue kuMesureMax mesures sur les deux algorithmes de Dijkstra, ie versions sans tas et avec tas, et affiche les résultats des mesures.
	#define kuFacteur 10
	#define kuMesureMax 9
	graf *pgG;
	int bAfficher=k1Afficher;
	int nArc,bCheminer,uM,nSommet;
	const int ksSource=1;
	const int kuTab=4;
	int nComplexitehAvecTas[1+kuMesureMax];
	int nComplexitehSansTas[1+kuMesureMax];
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		GrapheCompletCreerPondereR(nSommet,&pgG);
			//GrapheVoir0(pgG,sC4b("Graphe à",sPluriel(nSommet,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
			bCheminer=bGrapheCheminerCourt(pgG,ksSource,ksSource+1,!k1Tas,bAfficher,&nComplexitehSansTas[uM]);
			bCheminer=bGrapheCheminerCourt(pgG,ksSource,ksSource+1,k1Tas,bAfficher,&nComplexitehAvecTas[uM]);
		GrapheCreer(0,&pgG);
	}
	Ligne();
	Titrer(" Tableau comparatif des algorithmes de Dijkstra \"sans tas\" vs \"avec tas\" pour les plus courts chemins ");
	Ligne();
	printf("%sGraphe complet  Temps total d'exécution T    Rapport des temps    T/pire temps théorique\n",sTab(kuTab));
	printf("%s   (S,A)          Sans tas   Avec tas        Sans tas/Avec tas     Sans tas   Avec tas  \n",sTab(kuTab));
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		nArc=(nSommet*(nSommet-1))/2;
		printf("%s  %s%s",sTab(kuTab),sCouple(nSommet,nArc),sE(10-nChaineLg(sCouple(nSommet,nArc))));
		printf("       %5d     %5d",nComplexitehSansTas[uM],nComplexitehAvecTas[uM]);
		printf("                 %5.2f",nComplexitehSansTas[uM]/(nComplexitehAvecTas[uM]*1.0));
		printf("            %5.2f",nComplexitehSansTas[uM]/(nSommet*nSommet*1.0));
		printf("      %5.2f",nComplexitehAvecTas[uM]/(nArc+nSommet*rLn(nSommet)));
		Ligne();
	}
	Ligne();
}//DijkstraAvecOuSansTasCompareR

int bGraphe(graf *pgG){//O(A)
	//vrai ssi les champs de gG décrivent effectivement un graphe quelconque ——pr les quatre champs nSommetEnTout,nArcEnTout,aHed et sSuk de gG.
	int bGraphe,aK,sX;
	Assert1("bGraphe",bGrapheAmorceR);
	bGraphe=(pgG->nSommetEnTout>=0) && (pgG->nArcEnTout>=0) && (pgG->aHed[1]==1);
	Assert1("bGraphe2",bGraphe);
	bGraphe=bGraphe && (pgG->aHed[pgG->nSommetEnTout+1]==pgG->nArcEnTout+1);
	Assert1("bGraphe3",bGraphe);
	if (bGraphe)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			bGraphe=bGraphe && pgG->aHed[sX]<=pgG->aHed[sX+1];
	Assert1("bGraphe4",bGraphe);
	if (bGraphe)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			bGraphe=bGraphe && bGrapheSommet(pgG,pgG->sSuk[aK]);
	Assert1("bGraphe5",bGraphe);
	return(bGraphe);//noter qu'un graphe qui vérifie bGraphe est un multigraphe;donc ce n'est pas nécessairement un graphe simple;
}//bGraphe

char *sGraphe(int tGrapheType){
	//rend le nom du graphe de type tGrapheType;cf GrapheNom en haut du module
	enum grType GrapheType;
	Assert1("sGraphe",bCroitStrict(grAlpha,tGrapheType,grOmega));
	char *sGraphe=sItem(GrapheNom,1+tGrapheType);
	return(sGraphe);
}//sGraphe

void GrapheAMORCER(){
	//amorce le présent module une fois pour toutes
	bGrapheAmorceR=kV;
	//tee("GrapheAMORCER:kuGrapheSommetLim,kuGrapheArcLim",kuGrapheSommetLim,kuGrapheArcLim);
	Assert2("GrapheAMORCER",bFrontiere8(kuGrapheSommetLim),bFrontiere8(kuGrapheArcLim));
}//GrapheAMORCER

void GrapheAntisymetriser(graf *pgG){//O(A)
	//antisymétrise pgG en complétant les (X,Y) par les (Y,X) manquants de coûts et de couleur opposés. Reconduit pgG->coulh[] et pgG->nCout[] sur l'arc (Y,X) manquant.
	int aK,sX,sY;
	Assert2("GrapheAntisymetriser",bGrapheAmorceR,bGraphe(pgG));
	GrapheSymetriser(pgG,grCouleur+grCout);
	GrapheVoir0(pgG,"pgG AVANT",grCouleur);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sY<sX){
					pgG->nCout[aK]=-abs(pgG->nCout[aK]);
					pgG->coulh[aK]=-abs(pgG->coulh[aK]);
				}
			}
	GrapheVoir0(pgG,"pgG APRÈS",grCouleur);
	Assert1("GrapheAntisymetriser",bGrapheSimple(pgG));
}//GrapheAntisymetriser

int nGrapheApparier(int nAttribut,graf **ppgG){
	//apparie les pondérations >1 identiques; eg, en remplaçant l'arc 2 (a,b,π5) et l'arc 7 (c,d,π5) par (a,b,π-7) (c,d,π-2),ie -7 et -2 sont des index négatifs sur l'arc apparié
	int nAppariement,aK,sX,sY,iPoids;
	int nArc[1+(*ppgG)->nArcEnTout];
	int nAlterEgo[1+(*ppgG)->nArcEnTout];
	VecteurRaz(nArc,(*ppgG)->nArcEnTout);
	VecteurRaz(nAlterEgo,(*ppgG)->nArcEnTout);
	for (nAppariement=0,aK=1;aK<=(*ppgG)->nArcEnTout;aK++){
		iPoids=iGraphePoids(*ppgG,aK,nAttribut);
		if (iPoids>1)
			if (!nArc[iPoids])
				nArc[iPoids]=aK;
			else if (nArc[iPoids]>0){
				nAlterEgo[aK]=nArc[iPoids];
				nAlterEgo[nArc[iPoids]]=aK;
				nAppariement++;
		}//résultat: nAlterEgo[1..5]: 3, 0, 1, 0, 0 si la donnée est: (1,3π9)  (1,5π1)  (2,4π9)  (2,6π1)  (3,4π1).
	}
	//VecteurVoir0("nAlterEgo",nAlterEgo);
	for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
		for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++)
			if (nAlterEgo[aK]>0)
				GraphePonderer(*ppgG,sX,sY=(*ppgG)->sSuk[aK],nAttribut,-nAlterEgo[aK]);
	return(nAppariement);
}//nGrapheApparier

int bGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//vrai ssi (sOrigine,sDestination) est un arc de gG
	int bArc;
	int aK;
	Assert3("bGrapheArc",bGraphe(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (bArc=kF,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			bArc=kV;//l'arc est effectivement présent dans gG
	return(bArc);
}//bGrapheArc

int nGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//si (sOrigine,sDestination) est un arc de gG,rend le numéro de cet arc (ce numéro est utilisé pour indexer sSuk[1..]);sinon,rend 0.
	int nArc;
	int aK;
	Assert3("nGrapheArc",bGraphe(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nArc=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nArc=aK;//l'arc est effectivement présent dans gG
	return(nArc);
}//nGrapheArc

char *sGrapheArc(graf *pgG,int aArcNumero){//O(S)
	//rend sous la forme d'un couple (sX,sY) les sommets sX et sY qui délimitent l'arc aArcNumero de pgG.
	char *sArc;
	int bEureka,sX;
	//Appel0("sGrapheArc");
		//tee("aArcNumero,pgG->nArcEnTout",aArcNumero,pgG->nArcEnTout);
		Assert2("sGrapheArc0",bGrapheSimple(pgG),bCroit(1,aArcNumero,pgG->nArcEnTout));
		for (bEureka=kF,sX=1;sX<=pgG->nSommetEnTout && !bEureka;sX++)
			if ( bCroit(pgG->aHed[sX],aArcNumero,pgG->aHed[sX+1]-1) ){
				sArc=sCouple(sX,pgG->sSuk[aArcNumero]);//l'arc est effectivement présent dans gG
				bEureka=kV;
			}
		Assert1("sGrapheArc1",bEureka);
		//sArc=sC2("Alpha","Beta");
	//Appel1("sGrapheArc");
	return(sArc);
}//sGrapheArc

void GrapheAreter(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter",sOrigine!=sDestination);
	GrapheArquer(pgG,sOrigine,sDestination);
	GrapheArquer(pgG,sDestination,sOrigine);
}//GrapheAreter

void GrapheAreter0(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc){//O(A)
	//ajoute l'arête (sOrigine,sDestination) à pgG ——affecte les champs désignés par nAttribut ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	GrapheArquer0(pgG,sOrigine,sDestination,nAttribut,iValeurSurArc);
	GrapheArquer0(pgG,sDestination,sOrigine,nAttribut,iValeurSurArc);
}//GrapheAreter0

void GrapheAreter1(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter1",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,grCouleur,nCouleur);
	GrapheArquer0(pgG,sDestination,sOrigine,grCouleur,nCouleur);
}//GrapheAreter1

void GrapheAreter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter1",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,grCouleur,nCouleurDirecte);
	GrapheArquer0(pgG,sDestination,sOrigine,grCouleur,nCouleurInverse);
}//GrapheAreter2

void GrapheArquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute à pgG l'arc (sOrigine,sDestination);modifie les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//d2(sOrigine,sDestination);
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (!bArquer){
		printf("Impossible d'ajouter l'arc(%d,%d) ——",sOrigine,sDestination);
		if (!bGrapheSommet(pgG,sOrigine)) printf("sommet origine inconnu.\n");
		if (!bGrapheSommet(pgG,sDestination)) printf("sommet destination inconnu.\n");
		if (bGrapheArc(pgG,sOrigine,sDestination)) printf("arc déjà présent.\n");
	}
	Assert1("GrapheArquer",bArquer);
}//GrapheArquer

void GrapheArquer0(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nAttribut ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	//if (sOrigine==12 && sDestination ==9) d4(145,sOrigine,sDestination,iValeurSurArc);
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	Assert1("GrapheArquer01",bArquer);
	if (bArquer)
		GraphePonderer(pgG,sOrigine,sDestination,nAttribut,iValeurSurArc);
}//GrapheArquer0

void GrapheArquer2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//d3(sOrigine,sDestination,nCouleur);
	int bArquer1=bGrapheArqueR(pgG,sOrigine,sDestination,nCouleurDirecte);
	int bArquer2=bGrapheArqueR(pgG,sDestination,sOrigine,nCouleurInverse);
	Assert1("GrapheArquer2",bArquer1 && bArquer2);
}//GrapheArquer2

void GrapheArquer3(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCout){//O(A)
	//ajoute effectivt l'arc (sOrigine,sDestination) à pgG ——affecte les champs nArcEnTout,aHed,sSuk,nCapaMax,nCapaMin,nCout. Déroute si échec.
	int aK;
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (bArquer){
		aK=nGrapheArc(pgG,sOrigine,sDestination);
		Assert1("GrapheArquer30",aK>0);
		pgG->nCapaMin[aK]=nCapaMin;
		pgG->nCapaMax[aK]=nCapaMax;
		pgG->nCout[aK]=nCout;
	}
	Assert1("GrapheArquer31",bArquer);
}//GrapheArquer3

int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed, sSuk et coulh.
	int bArquer,aK,sX;
	Assert3("bGrapheArqueR0 module non amorcé ou graphe non valide",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (!bGrapheSommet(pgG,sOrigine)) d(sOrigine);
	Assert1("bGrapheArqueR1 origine non définie",bGrapheSommet(pgG,sOrigine) );
	if (!bGrapheSommet(pgG,sDestination)) d(sDestination);
	Assert1("bGrapheArqueR2 destination non définie",bGrapheSommet(pgG,sDestination));
	if (bGrapheArc(pgG,sOrigine,sDestination))
		d2(sOrigine,sDestination);//pb: l'arc à ajouter figure déjà dans le graphe
	Assert1("bGrapheArqueR3 cet arc existe déjà",!bGrapheArc(pgG,sOrigine,sDestination));//l'arc à créer existe déjà
	bArquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination) && (!bGrapheArc(pgG,sOrigine,sDestination));
	if (bArquer){
		Assert1("bGrapheArqueR4 trop d'arcs",pgG->nArcEnTout+1<kuGrapheArcLim);
		//faire une place au nouvel arc en décalant vers les index hauts les demi-tableaux qui décrivent les valeurs des arc
			for (aK=pgG->nArcEnTout;aK>=pgG->aHed[sOrigine+1];aK--){
				pgG->sSuk[aK+1]=pgG->sSuk[aK];
				pgG->coulh[aK+1]=pgG->coulh[aK];
				pgG->nCapaMin[aK+1]=pgG->nCapaMin[aK];
				pgG->nCapaMax[aK+1]=pgG->nCapaMax[aK];
				pgG->nCout[aK+1]=pgG->nCout[aK];
			}
		//insérer le nouvel arc
			aK=pgG->aHed[sOrigine+1];
			pgG->sSuk[aK]=sDestination;
			pgG->coulh[aK]=nCouleur;
			for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX+1]++;
			pgG->nArcEnTout++;
	}
	Assert2("bGrapheArqueR9",bGraphe(pgG),bGrapheSimple(pgG));
	return(bArquer);
}//bGrapheArqueR

int bGrapheBiparti(graf *pgG){//O(A)
	//et rend la couleur du sommet sX dans pgG->sPer[sX]
	int bBiparti;
	int uC;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	graf *pgH;
	int aK,sX,sY,sZ;
	int nCouleur[kuGrapheSommetLim];
	int kbVoir=kF;
	if (kbVoir) Appel0("bGrapheBiparti");
		Assert3("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
		pgH=(graf *) malloc(sizeof(graf));
			//pgH soit la copie symétrisée de pgG (l'algo ci-dessous requiert un graphe symétrique).
				GrapheDupliquer(pgG,&pgH);
				GrapheSymetriser(pgH,grCouleur+grCout);
			//bBiparti:=pgH est bicolorable
				DequeAllouer(pgH->nSommetEnTout);//raze;O(pgH->nSommetEnTout)
					//décolorer tous les sommets de pgH
						for (sX=1;sX<=pgH->nSommetEnTout;sX++)
							nCouleur[sX]=cIncolore;
					for (bBiparti=kV,sZ=1;sZ<=pgH->nSommetEnTout;sZ++){
						if (nCouleur[sZ]==cIncolore){
							nCouleur[sZ]=cNoir;
							DequeEnfiler(sZ);
							if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgH->nSommetEnTout);
							while (nCardinal=nDequeCardinal(),nCardinal>0)
								for (uC=1;uC<=nCardinal;uC++){
									sX=sDequeDefiler();
									for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){
										sY=pgH->sSuk[aK];
										if (nCouleur[sY]==cIncolore){
											nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;
											DequeEnfiler(sY);
											if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgH->nSommetEnTout);
										} else if (nCouleur[sY]==nCouleur[sX])//cycle impair
											bBiparti=kF;
									}
								}//for
						}//if
					}//for
				DequeAllouer(0);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->sPer[sX]=nCouleur[sX];
			//VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
		free(pgH);
	if (kbVoir) Appel1("bGrapheBiparti");
	return(bBiparti);
}//bGrapheBiparti

int bGrapheBipartiOuAfficherCycleImpair(graf *pgG){//O(A)
	int bBiparti;
	int sConflit0,sConflit1;
	int uC,aK;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int sX,sY,sZ;
	int nCoulh[kuGrapheSommetLim];
	int sPere[kuGrapheSommetLim];
	Assert4("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
		//razer nPere[]
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				sPere[sX]=0;
		//décolorer tous les sommets du graphe
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				nCoulh[sX]=cIncolore;
		//(sConflit0,sConflit1),sPere[]:=(sommet en conflit avec sConflit1,sommet 1 en conflit avec sConflit0), sPere[sY]=sX si sY a été coloré grâce à sX.
			for (sConflit0=0,sConflit1=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
				if (nCoulh[sZ]==cIncolore){
					nCoulh[sZ]=cNoir;
					sPere[sZ]=sZ;
					DequeEnfiler(sZ);
					while (nCardinal=nDequeCardinal(),nCardinal>0)
						for (uC=1;uC<=nCardinal;uC++){
							sX=sDequeDefiler();
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
								sY=pgG->sSuk[aK];
								if (nCoulh[sY]==cIncolore){
									nCoulh[sY]=(nCoulh[sX]==cNoir)? cRouge: cNoir;
									sPere[sY]=sX;
									DequeEnfiler(sY);
								} else if (nCoulh[sY]==nCoulh[sX]){//cycle impair
									sConflit1=sX;sConflit0=sY;}
							}
						}//for
				}//while
			}//for
		//bBiparti:=pgG est bicolorable,ie aucun sommet n'est en conflit de couleur avec un sommet adjacent.
			bBiparti=(sConflit0==0);
		if (!bBiparti){
			//tee("sConflit0,sConflit1",sConflit0,sConflit1);
			printf("Un cycle impair a été détecté:");
			//enfiler les sommets qui ont permis de colorer sConflit0
				sX=sConflit0;
				while(sX!=sPere[sX]){
					DequeEnfiler(sX);//n'enfile rien si déjà enfilé
					sX=sPere[sX];
				}
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDefiler());
	DequeAllouer(0);//fin du mode file;la Deque fonctionnant soit en mode pile soit en mode file,on ne peut mélanger les deux modes.
	DequeAllouer(pgG->nSommetEnTout);//début du mode pile
			//empiler les sommets qui ont permis de colorer sConflit1
				DequeEmpiler(sX=sConflit1);
				while(sX!=sPere[sX])
					DequeEmpiler(sX=sPere[sX]);
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDepiler());
			printf(" %d.\n",sConflit0);//réaffiche sConflit0 afin de signifier qu'il s'agit bien d'un cycle, et non pas d'un chaîne.
		}
	DequeAllouer(0);
	return(bBiparti);
}//bGrapheBipartiOuAfficherCycleImpair

void GrapheBipartir(graf *pgG,int bBipartir){//O(A)
	//si bBipartir,négative dans pgG->aHed[] les sommets de l'ensemble X réputé biparti; sinon,dénégative pgG->aHed[].
	int bBiparti;
	int uC;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int aK,sX,sY,sZ;
	int nCouleur[kuGrapheSommetLim];
	int kbVoir=kF;
	if (kbVoir) Appel0("GrapheBipartir");
		FlipFlop("GrapheBipartir",bBipartir,&bGrapheBipartiR);
		if (bBipartir){
			Assert4("GrapheBipartir0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
			//bBiparti,nCouleur[]:=pgG est bicolorable,nCouleur[sX]:cRouge/cNoir si sX appartient à X/à Y.
				DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
					//décolorer tous les sommets de pgH
						for (sX=1;sX<=pgG->nSommetEnTout;sX++)
							nCouleur[sX]=cIncolore;
					for (bBiparti=kV,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
						if (nCouleur[sZ]==cIncolore){
							nCouleur[sZ]=cNoir;
							DequeEnfiler(sZ);
							if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgG->nSommetEnTout);
							while (nCardinal=nDequeCardinal(),nCardinal>0)
								for (uC=1;uC<=nCardinal;uC++){
									sX=sDequeDefiler();
									for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
										sY=pgG->sSuk[aK];
										if (nCouleur[sY]==cIncolore){
											nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;//cRouge,cNoir est la couleur des sommets de X/de Y.
											DequeEnfiler(sY);
											if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgG->nSommetEnTout);
										} else if (nCouleur[sY]==nCouleur[sX])//cycle impair
											bBiparti=kF;
									}
								}//for
						}//if
					}//for
				DequeAllouer(0);
			Assert1("GrapheBipartir2",bBiparti);//pgG est réputé biparti
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//négative dans pgG->aHed[] les sommets de l'ensemble X colorés en cRouge
				pgG->aHed[sX]=iSignePres(nCouleur[sX]==cRouge,pgG->aHed[sX]);
			if (0){
				printf("Ensemble X obtenu:{");
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						if (pgG->aHed[sX]<0)
							printf(" %d",sX);
				printf(" }.\n");
			}
	} else {for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=abs(pgG->aHed[sX]);
			Assert3("GrapheBipartir1",bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	}
	if (kbVoir) Appel1("bGrapheBiparti");
}//GrapheBipartir

void GrapheBipartitionne(graf *pgG){//O(A)
	//X devient X' et X"=X+nSommet,contrairt à GrapheBipartitionner(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;
	int aK;
	int nSommet;
	int kbVerifier=kF;
	int sX;
	Assert3("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbVerifier) GrapheVoir(pgG,"AVANT");
	nSommet=pgG->nSommetEnTout;
	nArc=pgG->nArcEnTout;
	//enfiler dans pgG->aHed[] nSommet nouveaux sommets X' devant les sommets X renommés nSommet+sX
		if (kbVerifier) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
		for (sX=nSommet;sX>=0;sX--)
			pgG->aHed[nSommet+sX+1]=nSommet+pgG->aHed[sX+1];//décale et donc translate les noms des sommets
		if (kbVerifier) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
		for (sX=nSommet;sX>0;sX--)
			pgG->aHed[sX]=sX;
		if (kbVerifier) VecteurVoir("aHed3",&pgG->aHed[0],1,2*nSommet+1);
	//enfiler dans pgG->sSuk[] un arc (X',X) pour chaque sommet X' créé
		if (kbVerifier) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc);
		for (aK=nArc;aK>0;aK--)
			pgG->sSuk[aK+nSommet]=pgG->sSuk[aK];//décale et pointe vers les sommets 1..nSommet,lesquels sont maintenant les nouveaux sommets
		for (aK=1;aK<=nSommet;aK++)
			pgG->sSuk[aK]=nSommet+aK;//les nouveaux sommets 1..nSommet pointent vers les anciens,ie ceux renommés nSommet+sX
		if (kbVerifier) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
	pgG->nSommetEnTout+=nSommet;
	pgG->nArcEnTout+=nSommet;
	if (kbVerifier) GrapheVoir(pgG,"APRES");
	/*if (0 && kbVerifier)
		GrapheSymetriser(pgG,grCouleur+grCout);*/
	Assert4("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheBiparti(pgG));
}//GrapheBipartitionne

void GrapheBipartitionner(graf *pgG){//O(A)
	//X devient X' et X"=X+1,contrairt à GrapheBipartitionne(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;//dit autrement,X est remplacé par l'arc (2*X-1,2*X).
	int aK;
	int kbScruter=kF;
	int nSommet;
	int sX,sY;
	Assert3("GrapheBipartitionner1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbScruter) Appel0("GrapheBipartitionner");
		if (kbScruter) GrapheVoir(pgG,"AVANT");
		nSommet=pgG->nSommetEnTout;
		nArc=pgG->nArcEnTout;
		//ménager entre les listes de sommets successeurs dédiés à chaque sommet source 1 arc par nouveau sommet,en terminant par un nouvel arc en pgG->sSuk[1].
			if (kbScruter) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc+nSommet);
			for (sX=nSommet;sX>0;sX--){
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX]=2*sY-1;
				}
				if (kbScruter) tee("aK,sX",aK,sX);
				pgG->sSuk[aK+sX]=2*sX;//nouvel arc,notamment en pgG->sSuk[1] puisque aK=0 quand sX=1.
			}
			if (kbScruter) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
		//interclasser les sommets originaux de sorte que X'=X+1 pour tout X
			if (kbScruter) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
			//d(2*nSommet+2);
			Assert1("GrapheBipartitionner3",2*nSommet+2<kuGrapheSommetLim);//pr li+3;sinon,ajouter un "if"
			for (sX=nSommet;sX>=0;sX--){
				pgG->aHed[2*sX+1]=pgG->aHed[sX+1]+sX;
				pgG->aHed[2*sX+2]=pgG->aHed[2*sX+1]+1;
			}
			if (kbScruter) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
			if (kbScruter) VecteurVoir("sSuk6",&pgG->sSuk[0],1,nArc+nSommet);
		pgG->nSommetEnTout+=nSommet;
		pgG->nArcEnTout+=nSommet;
		if (kbScruter) GrapheVoir(pgG,"APRES");
		if (0 && kbScruter)
			GrapheSymetriser(pgG,grCouleur+grCout);
		Assert4("GrapheBipartitionner9",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),!kbScruter || bGrapheBiparti(pgG));
	if (kbScruter) Appel1("GrapheBipartitionner");
}//GrapheBipartitionner

//#define GrapheType {grAlpha,gr2Aile,gr2Diam,grC2,grC3,grC4,grC5,grC6,grC4b,grD2,grD3,grD4,grK2,grK3,grK4,grK5,grK6,grL4,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grQ0,grQ1,grS2,grS3,grS4,grS5,grS6,grT,grT2,grW,grXor,grX,grXX,grXY,grOmega}
int nGrapheCardinal(int tQuadripole){
	//rend le nbre de sommets du graphe tQuadripole censé être un quadripôle
	enum grType GrapheType;
	int nCardinal=8;//d
	if ( bDans4(tQuadripole,gr2Croix,gr2P,grT,grX) ) nCardinal=4;
	if ( bDans2(tQuadripole,grC,grXor) ) nCardinal=6;
	if ( bDans2(tQuadripole,grPt,grPt) ) nCardinal=10;
	if ( bDans2(tQuadripole,grU,grU) ) nCardinal=5;
	return(nCardinal);
}//nGrapheCardinal

void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int nMesure,int gcMode){
	//affiche s'il existe le chemin qui relie sSource à sTrappe,sa grandeur (ie une longueur ou une largeur,selon gcMode) et sa valeur nMesure.
	int aK,ipKm=0,uS,sX,bLePlusLarge,bArbre;
	int nKm[1+pgG->nSommetEnTout];//coût de chaque arc du chemin à afficher
	Assert3("GrapheCheminE",bBool(bCheminer),pgG->sPer[sSource]==sSource,nMesure>=0);
	bArbre=gcMode==grArbreCouvrant;
	if (bCheminer){
		//d2(sSource,sTrappe);
		//VecteurVoir("pgG->nCout",pgG->nCout,1,pgG->nSommetEnTout);
		Tabuler(1);
		if (bArbre)
			printf("%sArêtes de l'arbre couvrant: ",sTabulation());
		else printf("%sChemin le plus %s du sommet %s au sommet %s: (",sTabulation(),sItem4(gcMode,"court","large","long","court en moyenne"),sEnt0(sSource,0),sEnt0(sTrappe,0));
		//afficher sommet par sommet le chemin qui relie sSource à sTrappe ——en partant de sSource:
			if (!bArbre){
				DequeAllouer(pgG->nSommetEnTout);
					//empiler les sommets car ils jalonnent le chemin à afficher dans le sens inverse du sens requis pour l'affichage, et les coûts des arcs du chemin
						sX=sTrappe;
						While(pgG->nSommetEnTout);
						while ( bWhile("GrapheCheminE",pgG->sPer[sX]!=sX) ){
							DequeEmpiler(sX);
							aK=nGrapheArc(pgG,pgG->sPer[sX],sX);
							//d4(pgG->sPer[sX],sX,aK,pgG->nCout[aK]);
							nKm[++ipKm]=pgG->nCout[aK];
							sX=pgG->sPer[sX];
						}
						DequeEmpiler(sX);
					//afficher les sommets en les dépilant: ils se présentent dans l'ordre requis pour l'affichage
						for (uS=nDequeCardinal();uS>0;uS--){
							sX=sDequeDepiler();
							printf("%s",sEnt0(sX,0));
							if (uS>1)
								printf(",");
						};
				DequeAllouer(0);
				printf(").\n");
			}else {
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]!=sX){
						aK=nGrapheArc(pgG,pgG->sPer[sX],sX);
						nKm[++ipKm]=pgG->nCout[aK];
						printf("(%s,%s)",sEnt0(pgG->sPer[sX],0),sEnt0(sX,0));
						if (sX<pgG->nSommetEnTout)
							printf(",");
					}
				printf(".\n");
			}
		bLePlusLarge=gcMode==grCheminLePlusLarge;
		if (bArbre)
			printf("%sPoids total de l'arbre couvrant: ",sTabulation());
		else printf("%s%s de ce chemin: ",sTabulation(),sPhrase0((bLePlusLarge)? "largeur": "longueur"));
		if (bLePlusLarge) printf("min(");
			for (int nArc=ipKm;nArc>0;nArc--)//décroissant afficher le chemin en partant de sSource et non pas de sTrappe
				printf("%d%s",nKm[nArc],sChoix0(nArc>1,(bLePlusLarge)?",":" + ") );
		if (bLePlusLarge) printf(")");
		//printf(" = %d %s.\n",nMesure,(bLePlusLarge)? "mètres": ((bArbre)? "unités": "km"));
		printf(" = %s.\n",sPluriel(nMesure,"unité"));
		//VecteurVoir("nKm",nKm,1,ipKm);
		Tabuler(-1);
	}
	else printf("    Il n'existe pas de chemin entre les sommets %d et %d.\n",sSource,sTrappe);
}//GrapheCheminE

int bGrapheCheminE(graf *pgG,int sSource,int sTrappe){
	//rend vrai ssi gG.sPer[] décrit un chemin qui relie sSource à sTrappe.
	int bChemine;
	int nSommet;
	int sX,sY;
	for (bChemine=kF,sX=sTrappe,nSommet=0;nSommet<=pgG->nSommetEnTout;nSommet++){
		bChemine=bChemine || (sX==sSource);
		sY=pgG->sPer[sX];//facilite le débogage
		sX=sY;
	}
	return(bChemine);
}//bGrapheCheminE

int nGrapheChemineR (graf *pgG,int sSource,int sTrappe,int bSimuler,int *pnComplexiteh){//O(S2)
	//remplit pgG->nVal[] avec les distances les plus courtes depuis sSource et rend la distance à sTrappe, (algo:Dijkstra sans tas);si bSimuler,affiche la simulation de l'algo.
	const int kbVoirPere=kF;
	const int kuInfini=1e4-1;
	int nDistanceParX,nD;//nD est la distance courante de sSource au sommet le plus proche de sSource
	int bFait[1+pgG->nSommetEnTout];
	int iDistanceNouvelle[1+pgG->nSommetEnTout];//dédié simulation
	int sProche=0,uSommet,aK,sX,sY,sZ;
	if (kbVoirPere) Appel0("nGrapheChemineR");
	*pnComplexiteh=0;
	//initialiser bFait[], pgG->nVal[] et pgG->sPer[].
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(pgG->nVal,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	pgG->nVal[sSource]=0;//distance entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	if (bSimuler)
		printf("%sSimulation de l'algo de cheminement de Dijkstra pour le calcul du chemin optimal:\n",sTabulation());
	if (bSimuler)//lister les noms des sommets et initialiser iDistanceNouvelle[] à kuInfini
		for (printf("\t "),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();iDistanceNouvelle[sZ]=pgG->nVal[sZ],sZ++)
			printf("%7s",sEnt0(sZ,0) );
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		if (bSimuler)//afficher le noms du sommet sProche élu et les seules distances qui ont changé
			for (printf("%s\t%s",sTabulation(),(sProche==0)? " ": sEnt0(sProche,0)),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();iDistanceNouvelle[sZ]=-1,sZ++)
				printf("%7s",(iDistanceNouvelle[sZ]==kuInfini)? "infini": (iDistanceNouvelle[sZ]>=0)? sEntier(pgG->nVal[sZ],7) : "    ." );
		//sProche:=numéro du sommet le plus proche de sSource, ou 0 si aucun nouveau sommet ne peut être atteint depuis sSource
			for (sProche=0,nD=kuInfini,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if ((*pnComplexiteh)++,!bFait[sX] && nD>pgG->nVal[sX])
					nD=pgG->nVal[sProche=sX];
		sX=sProche;
		//d(sProche);
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX réduit la distance entre sSource et sY
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; (*pnComplexiteh)++,aK++) {
				sY=pgG->sSuk[aK];
				nDistanceParX=pgG->nVal[sX]+pgG->nCout[aK];
				if ( pgG->nVal[sY]>nDistanceParX ) {//passer par sX est plus court
					iDistanceNouvelle[sY]=pgG->nVal[sY]=nDistanceParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin optimal qui relie sY à sSource.
				}
			}
			bFait[sX]=kV;
		}
	}//à chaque tour, calculer sProche coûte O(S). Chaque arc étant consulté 1 fois au plus ds "for aK",la complexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (kbVoirPere) VecteurVoir("sPer",pgG->sPer,1,pgG->nSommetEnTout);
	if (kbVoirPere) Appel1("nGrapheChemineR");
	return(pgG->nVal[sTrappe]);
}//nGrapheChemineR

int bGrapheCheminerAuLarge(graf *pgG,int sSource,int sTrappe,int tAfficher){//O(S2)
	//calcule et affiche si bAfficher le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas)
	int bChemine=0,nLargeur;
	Assert1("bGrapheCheminerAuLarge",bTrit(tAfficher));
	//d3(sSource,sTrappe,tAfficher);
	nLargeur=nGrapheCheminerAuLargE(pgG,tAfficher<0,sSource,sTrappe);
	bChemine=bGrapheCheminE(pgG,sSource,sTrappe);
	if (tAfficher!=0)
		GrapheCheminE(pgG,sSource,sTrappe,bChemine,nLargeur,grCheminLePlusLarge);
	return(bChemine);
}//bGrapheCheminerAuLarge

int nGrapheCheminerAuLargE(graf *pgG,int bSimuler,int sSource,int sTrappe){//O(S2)
	//calcule le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas);le coût d'1 arc est la largeur de l'arc,eg la largeur minimale d'une route.
	#define kbCheminerAuLarge kF
	const int kuInfini=1e5;
	int bFait[1+pgG->nSommetEnTout],iLargeurNouvelle[1+pgG->nSommetEnTout];
	int mLargeurMax;//capacité maximale des chemins qui relient sSource au sommet le plus proche de sSource
	int mLargeur[1+pgG->nSommetEnTout];
	int aK,nLargeurParX,sProche=0,uSommet,sX,sY,sZ;
	if (kbCheminerAuLarge) Appel0("nGrapheCheminerAuLargE");
	//initialiser bFait[], mLargeur[],iLargeurNouvelle[], pgG->nVal[] et pgG->sPer[].
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(mLargeur,1,pgG->nSommetEnTout,-1);
		VecteurValuer(pgG->nVal,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(iLargeurNouvelle,1,pgG->nSommetEnTout);//dédié simulation
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	iLargeurNouvelle[sSource]=mLargeur[sSource]=kuInfini;//largeur entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	if (bSimuler)
		printf("Simulation de l'algo de cheminement de Dijkstra pour le calcul du chemin le plus large:\n");
	if (bSimuler)//lister les noms des sommets et initialiser iLargeurNouvelle[]
		for (printf("\t "),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();sZ++)
			printf("%7s",sEnt0(sZ,0) );
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		if (bSimuler)//afficher le noms du sommet sProche élu et les seules distances qui ont changé
			for (printf("\t%s",(sProche==0)? " ": sEnt0(sProche,0)),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();iLargeurNouvelle[sZ]=-1,sZ++)
				printf("%7s",(iLargeurNouvelle[sZ]==kuInfini)? "infini": (iLargeurNouvelle[sZ]>=0)? sEntier(iLargeurNouvelle[sZ],7) : "    ." );
		//sProche:=numéro du sommet situé sur la route la plus large qui mène à sSource, ou 0 si aucun nouveau sommet n'est trouvé)
			for (sProche=0,mLargeurMax=-1,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if (!bFait[sX] && mLargeurMax<mLargeur[sX])
					mLargeurMax=mLargeur[sProche=sX];
		//d2(sProche,mLargeurMax);
		sX=sProche;
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX permet de cheminer de sSource à sY par un chemin plus large
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];
				Assert1("GrapheCheminerAuLargE",bCroit(0,pgG->nCout[aK],kuInfini-1));//largeur de l'arc
				nLargeurParX=yMin(mLargeur[sX],pgG->nCout[aK]);
				if ( mLargeur[sY]<nLargeurParX ) {//la route qui relie sSource à sY ne passe pas par sX; elle est moins large que celle qui relie sSource à sY en passant par sX.
					iLargeurNouvelle[sY]=mLargeur[sY]=nLargeurParX;
					//VecteurVoir("iLargeurNouvelle",iLargeurNouvelle,1,pgG->nSommetEnTout);
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus large qui relie sY à sSource.
					//d4(sY,sX,nLargeurParX,pgG->nCout[aK]);
				}
			}
			bFait[sX]=kV;
		}
	}//à chaque tour, calculer sProche coûte O(S). Chaque arc étant consulté 1 fois au plus dans "for aK",la complexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (kbCheminerAuLarge) VecteurVoir("mLargeur",&mLargeur[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) Appel1("nGrapheCheminerAuLargE");
	return(mLargeur[sTrappe]);
}//nGrapheCheminerAuLargE

int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bTas,int tCheminAfficher,int *pnComplexiteh){//O(SlgS+A)
	//Algo plus court chemin, Dijkstra sans tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	Assert1("bGrapheCheminerCourt",bTrit(tCheminAfficher));
	if (!bTas)
		nCheminLg=nGrapheChemineR(pgG,sSource,sTrappe,tCheminAfficher<0,pnComplexiteh);
	else nCheminLg=nGrapheCheminerTaS(pgG,sSource,sTrappe,pnComplexiteh);
	bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
	if (tCheminAfficher!=0)
		GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,nCheminLg,grCheminLePlusCourt);
	return(bCheminerCourt*nCheminLg);
}//bGrapheCheminerCourt

int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh){//O(S2)
	//Algo plus court chemin, Dijkstra AVEC tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	//Appel0("bGrapheCheminerCourtTaS");
		Assert1("bGrapheCheminerCourtTaS",bBool(bCheminAfficher));
		nCheminLg=nGrapheCheminerTaS(pgG,sSource,sTrappe,pnComplexiteh);
		bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
		if (bCheminAfficher)
			GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,nCheminLg,grCheminLePlusCourt);
	//Appel1("bGrapheCheminerCourtTaS");
	return(bCheminerCourt);
}//bGrapheCheminerCourtTaS

int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int tCheminAfficher,int *pnComplexiteh){//O(S2)
	//vrai ssi un plus long chemin de sSource à sTrappe est calculable ds pgG (distances élémentR dans pgG->nCout[]).
	int bCheminerLong=kV,nCheminLg,aK;
	GrapheInverser(pgG);
	bCheminerLong=!bGrapheCircuite(pgG);
	if (bCheminerLong){
		//négativer les coûts des arcs
			for (aK=1; aK<=pgG->nArcEnTout; aK++)
				pgG->nCout[aK] = - pgG->nCout[aK];
		nCheminLg=-nGrapheChemineR(pgG,sSource,sTrappe,tCheminAfficher<0,pnComplexiteh);
		//restaurer les coûts des arcs
			for (aK=1; aK<=pgG->nArcEnTout; aK++)
				pgG->nCout[aK] = - pgG->nCout[aK];
		bCheminerLong=bGrapheCheminE(pgG,sSource,sTrappe);
		if (tCheminAfficher)
			GrapheCheminE(pgG,sSource,sTrappe,bCheminerLong,nCheminLg,grCheminLePlusLong);
	}
	else if (tCheminAfficher)
		printf("Le chemin le plus long n'est pas calculable car le graphe contient un circuit.\n");
	return(bCheminerLong);
}//bGrapheCheminerLong

int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(AlgS)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo de plus court chemin exécuté: Dijkstra AVEC tas.
	const int kuInfini=9999;
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;//entier Naturel positif ou nul,donc préfixe "n".
	int bFait[1+pgG->nSommetEnTout];//b comme booléen
	int aK;//index d'Arc,donc préfixe "a".
	int sProche;//index de Sommet,donc préfixe "s".
	int uSommet;//entier naturel supérieur ou égal à Un,donc préfixe "u".
	int sX,sY;
	//bFait[], nDist[] et pgG->sPer[] soient initialisés.
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	*pnComplexiteh=3*pgG->nSommetEnTout;//coût initialisations
	TasAllouer(pgG->nSommetEnTout);
		//initialiser le tas (le coût total du module Tas, en terme de complexité algorithmique, sera ajouté en fin de routine grâce à nTasCout()
			for (sX=1; sX<=pgG->nSommetEnTout; sX++)
				TasInsererValuer(sX,kuInfini);
			TasActualiser(sSource,0);
			//TasVoir("Tas après initialisation");
		nDist[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE() chargé de cheminer sur le plus court chemin grâce à sPer[]
		for (uSommet=1; uSommet<=pgG->nSommetEnTout; (*pnComplexiteh)++, uSommet++) {//O(AlgS)
			//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
				//TasVoir("Tas avant extraction");
				sProche=eTasExtraire();//O(lgS)
			sX=sProche;
			if (sX!=0) {
				for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; (*pnComplexiteh)++, aK++) {
					sY=pgG->sSuk[aK];//chaque arc (sX,sY) est examiné 1 fois (si accessible par un chemin depuis sSource)
					nDistanceParX=nDist[sX]+pgG->nCout[aK];
					if ( nDist[sY]>nDistanceParX ) {
						nDist[sY]=nDistanceParX;
						//d2(sY,nDistanceParX);
						TasActualiser(sY,nDistanceParX);//O(lgS) par arc (sX,sY)
						//TasVoir("Tas après TasActualiser");
						pgG->sPer[sY]=sX;
					}
				}
				bFait[sX]=kV;//ie l'opportunité de passer par sX pour atteindre au plus court un sommet de pgG depuis sSource a été exploitée.
			}
		}//chaque sProche est obtenu en O(lgS) et chaque arc est consulté 1 fois, soit une complexité au pire égale à sup( O(S*lS),O(AlgS) ), dc O(AlgS).
		//VecteurVoir("sPer",pgG->sPer,1,pgG->nSommetEnTout);
		(*pnComplexiteh)+=nTasCout();//coût total du tas entre 2 allocations, donc à ajouter juste avant TasAllouer(0) qui remet ce coût à 0.
	TasAllouer(0);
	return(nDist[sTrappe]);
}//nGrapheCheminerTaS

int bGrapheCircuite(graf *pgG){//O(A)
	//vrai ssi pgG contient un circuit (algo de Marimont)
	int nCard;//n comme Naturel,dc 0 ou plus
	int bCircuite=kF;
	int uE;//E comme Elément;u comme Un ou plus
	int aK;//a comme Arc
	int nMarq[1+pgG->nSommetEnTout];
	int nMarque;
	int nPred[1+pgG->nSommetEnTout];
	int nSucc[1+pgG->nSommetEnTout];
	int sX,sY;//s comme Sommet
	//Appel0("bGrapheCircuite");
		Assert2("bGrapheCircuite1",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim));
		GrapheInverser(pgG);//VITAL
		if (pgG->nSommetEnTout>1){//algo de MARIMONT
			//nSucc[sX],nPred[sX] et nMarq[sX] soit le nombre total de successeurs,de prédécesseurs ainsi que la marque du sommet courant sX
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
					nSucc[sX]=pgG->aHed[sX+1]-pgG->aHed[sX];
					nPred[sX]=pgG->aDeh[sX+1]-pgG->aDeh[sX];
					nMarq[sX]=0;//ie sX n'est pas marqué
					Assert2("bGrapheCircuite2",nSucc[sX]>=0,nPred[sX]>=0);
				}
			DequeAllouer(pgG->nSommetEnTout);//raze;O(nSommetEnTout)
				//enfiler les sommets sources (ie sans prédécesseurs) et trappes (ie sans successeurs) en les marquant avec nMarque égal à 1
					for (nMarque=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
						if ( !nPred[sX] || !nSucc[sX] ){
							nMarq[sX]=nMarque;
							DequeEnfiler(sX);//O(1)
						}
				While(pgG->nSommetEnTout);
				while (bWhile("bGrapheCircuite3",(nMarque++,nCard=nDequeCardinal())) ){//nDequeCardinal() est en O(1) et le while en O(A) ——justification en fin de while
					for (uE=1;uE<=nCard;uE++){//NB les appels à la deque ds ce for vont modifier nDequeCardinal() mais pas nCard évalué li-1
						sX=sDequeDefiler();//O(1)/
						if (!nPred[sX])//si vrai,sX est une source;éliminer un arc (sX,sY),c'est retirer un prédécesseur de sY via "nPred[sY]--"
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//O(degré sortant de sX)
								if (!nMarq[sY=pgG->sSuk[aK]]){
									nPred[sY]--;
									Assert1("bGrapheCircuite4",nPred[sY]>=0);
									if (!nPred[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										DequeEnfiler(sY);//O(1)
									}
								}
							}
						else for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)//O(degré entrant de sX)
								if (!nMarq[sY=pgG->sKus[aK]]){
									nSucc[sY]--;
									Assert1("bGrapheCircuite5",nSucc[sY]>=0);
									if (!nSucc[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										DequeEnfiler(sY);//O(1)
									}
								}
					}//grâce à nMarq[],tt sommet est enfilé (et dc défilé) 1 fois Au plus, dc ses arcs examinés 1 fois Au plus,dc while est en O(A).
				}
			DequeAllouer(0);//O(1) Si vous ôtez cette ligne au vu du code de Deque,vous acceptez qu'une modification dudit code plante votre logiciel.
			//VecteurVoir("nMarq",nMarq,1,pgG->nSommetEnTout);
			for (bCircuite=0,sX=1; sX<=pgG->nSommetEnTout; sX++)//O(S);zéroter bCircuite ici initialise à l'évidence le bCircuite situé li+1 avant "||".
				bCircuite=bCircuite||!nMarq[sX];//quitter le for dès bCircuite vrai complique le code et n'améliore pas la borne O(A):mauvaise idée.
		}
	else bCircuite=kF;//redite,mais ainsi,li+1,bCircuite est à l'évidence valué; chercher sa valeur initiale ds les déclarations est inutile,dc gain de temps.
	//Appel1("bGrapheCircuite");
	return(bCircuite);
}//bGrapheCircuite

void GrapheCircuiterAuMieux(graf *pgG){
	//calcule et affiche un circuit de longueur moyenne minimale (moyennée sur le nombre d'arcs) dans pgG,réputé fortement connexe.
	const int kbAff = kF;
	const int kuPoidsInfini=kE4;
	int aK,nK,nK0,uK,aL,nMin,nPoidsTotal,sX,sY,sY0,sZ;
	float rMin,rMax,rMoyenne;
	int nSommet=pgG->nSommetEnTout;
	int nPoids[1+nSommet][1+nSommet];
	int sPere[1+nSommet][1+nSommet];
	Assert1("GrapheCircuiterEnMoyennE",bGrapheFortementConnexe(pgG));
	//les poids sont les couleurs du graphe
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->nPoids[aK]=pgG->coulh[aK];
	//nPoids[0][] soit initialisé
		GrapheInverser(pgG);//pr accéder en O(1) aux prédécesseurs
		for (sX=1;sX<=nSommet;sX++)
			nPoids[0][sX]=kuPoidsInfini;
		nPoids[0][1]=0;
		for (sY=1;sY<=nSommet;sY++)
			for (aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];
				if (sX==1)
					nPoids[0][sY]=pgG->nPoids[aK];
			}//for aL
	//nPoids[1..nSommet][] et sPere[1..nSommet][] soient affectés:
		for (uK=1;uK<=nSommet;uK++)
			for (sY=1;sY<=nSommet;sY++){
				for (nMin=kuPoidsInfini,aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
					sX=pgG->sKus[aL];
					aK=pgG->aInv[aL];
					nPoidsTotal=nPoids[uK-1][sX]+pgG->nPoids[aK];
					if (nPoidsTotal<nMin){
						nMin=nPoidsTotal;
						sZ=sX;//pour sPere li+4
					}
				}//for aL
				nPoids[uK][sY]=nMin;
				sPere[uK][sY]=sZ;
			}
		if (kbAff) for (nK=0;nK<=nSommet;nK++)
			VecteurVoir(sC3("nSommet[",sEnt(nK),"]"),nPoids[nK],1,nSommet);
		if (kbAff) for (uK=1;uK<=nSommet;uK++)
			VecteurVoir(sC3("sPere[",sEnt(uK),"]"),sPere[uK],1,nSommet);
	//sY0,nK0:=index caractéristiques du circuit optimal
		for (rMin=kuPoidsInfini,sX=1;sX<=nSommet;sX++){
			for (sY=0,rMax=0.0,nK=0;nK<nSommet;nK++){
				rMoyenne=((nPoids[nSommet][sX]-nPoids[nK][sX])*1.0)/(nSommet-nK);
				if (rMoyenne>rMax){
					sY=sX;
					uK=nK;
					rMax=rMoyenne;
				}
			}
			if (rMax<rMin){
				sY0=sY;
				nK0=uK;
				rMin=rMax;
			}
		}
	//tr("rMin",rMin);
	//teee("moyenne de 1 pour sY0,nPoidsTotal0,nArc0",sY0,nPoidsTotal0,nArc0);
	//afficher le circuit optimal de longueur moyenne minimale:
		printf("Circuit optimal: ( ");
			for (uK=nSommet-1,sX=sPere[uK][sY0];uK>=nK0;printf("%d ",sX),uK--)
				sX=sPere[uK][sX];
		printf("), de longueur moyenne minimale égale à %.2f.\n",rMin);
}//GrapheCircuiterAuMieux

void GrapheCliquer(graf *pgG,int uCliqueTaille){
	//empile dans pgG une clique à uCliqueTaille sommets.
	int sX,sY;
	const int kbVerif = kF;
	Assert1("GrapheCliquer",uCliqueTaille>0);
	int nSommet=pgG->nSommetEnTout;
	//d(nSommet);
	for (sX=1;sX<=uCliqueTaille;sX++)
		pgG->aHed[nSommet+sX+1]=pgG->aHed[nSommet+sX];
	pgG->nSommetEnTout+=uCliqueTaille;
	if(kbVerif) d(pgG->nSommetEnTout);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	for (sX=nSommet+1;sX<=pgG->nSommetEnTout;sX++)
		for (sY=nSommet+1;sY<=pgG->nSommetEnTout;sY++)
			if (sX!=sY)
				GrapheArquer(pgG,sX,sY);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	if(kbVerif) VecteurVoir("pgG->sSuk",pgG->sSuk,1,pgG->nArcEnTout);
}//GrapheCliquer

void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur){
	//colore l'arc (sOrigine,sDestination) avec la nCouleur
	int aK;
	Assert4("GrapheColorer0",bGrapheSommet(pgG,sOrigine), bGrapheSommet(pgG,sDestination), sOrigine!=sDestination, bCroit(0,nCouleur,knGrapheCouleurMax));
	for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++){
		if (pgG->sSuk[aK] == sDestination)
			pgG->coulh[aK]=nCouleur;
	}
}//GrapheColorer

void GrapheCompletCreerPondereR(int nSommet,graf **ppgG){
	int aK,sX,sY;
	//appel: DijkstraAvecOuSansTasCompareR()
	//Appel0("GrapheCompletCreerPondereR");
		GrapheCreer(-nSommet,ppgG);
		for (sX=1;sX<=nSommet;sX++)
			for (sY=1;sY<=nSommet;sY++)
				if (sX!=sY)
					GrapheArquer(*ppgG,sX,sY);
		//GrapheVoir(*ppgG,"Graphe complet créé");
		Assert1("GrapheCompletCreerPondereR1",bGrapheSimple(*ppgG));
		for (sX=1;sX<=nSommet;sX++)
			for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
				sY=(*ppgG)->sSuk[aK];
				(*ppgG)->nCout[aK]=kE4-sX-nSommet*sY;
			}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
		//si nSommet=6, faire que les plus courts chemins passent par les arcs (1,6),(6,5),(5,4),(4,3),(3,2) et (2,1)
			for (sX=1;sX<=nSommet;sX++)
				for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
					sY=(*ppgG)->sSuk[aK];
					if (sY==sX-1 || sX==1 && sY==nSommet)
						(*ppgG)->nCout[aK]=sX;
				}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
	//Appel1("GrapheCompletCreerPondereR");
}//GrapheCompletCreerPondereR

int nGrapheComposanteConnexe(graf *pgG){//O(A)
	//rend le nombre de composantes connexes du graphe non orienté associé à pgG
	int nCC[1+pgG->nSommetEnTout];//numéro de composante connexe
	int nCCcourante,nComposanteConnexe=0;
	graf *pgH;
	int aK,sX,sY,sZ,uS;
	Assert2("nGrapheComposanteConnexe",bGrapheAmorceR,bGrapheSimple(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		//pgH soit le graphe symétrique associé à pgH
			GrapheDupliquer(pgG,&pgH);//O(A)
			GrapheSymetriser(pgH,grCouleur+grCout);//O(A)
		VecteurRazer(nCC,1,pgG->nSommetEnTout);//O(S)
		DequeAllouer(pgG->nSommetEnTout);//O(1)
			for (nCCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//O(A)
				if (nCC[sZ]==0){//attribuer la composante connexe nCCcourante+1 à sZ et aux sommets atteints depuis sZ dans pgH symétrique
					DequeEnfiler(sZ);//sZ n'est enfilé qu'une fois
					nCCcourante++;
					While(1+pgH->nSommetEnTout);
					while (bWhile("nGrapheComposanteConnexe",!bDequeVide())){
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							nCC[sX]=nCCcourante;
							for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//les successeurs de sY ne sont passés en revue qu'une fois
								sY=pgH->sSuk[aK];
								if (nCC[sY]==0)//sY n'est enfilé qu'une fois
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//if
		DequeAllouer(0);//O(1)
	free(pgH);
	nComposanteConnexe=nCCcourante;
	//d(nComposanteConnexe);
	return(nComposanteConnexe);
}//nGrapheComposanteConnexe

int nGrapheComposanteFortementConnexe(graf *pgFortementConnexe){//O(SA)
	//rend le nombre de composantes fortement connexes (CFC) de pgG et stocke dans pgG->sPer[] le numéro de CFC attribué à chacun des sommets.
	int bAtteint[2][1+pgFortementConnexe->nSommetEnTout];
	int nCFC[1+pgFortementConnexe->nSommetEnTout];//numéro de composante fortement connexe attribué au sommet courant
	int nCFCcourante;
	int nComposanteFortementConnexe=0;
	graf *pgG=pgFortementConnexe;
	int aK,sX,sY,sZ,uS;
	int cPasse,bVoir = kF;
	Assert2("nGrapheComposanteFortementConnexe",bGrapheAmorceR,bGrapheSimple(pgG));
	GrapheInverser(pgG);//mm si déjà fait
	//GrapheViseR(pgG,"Graphe inversé");
	VecteurRazer(nCFC,1,pgG->nSommetEnTout);//O(S)
	DequeAllouer(1+pgG->nSommetEnTout);//O(1)
		for (nCFCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//S*sup(S,A),dc O(SA)
			if (nCFC[sZ]==0){//marquer parmi tous les sommets atteints depuis sZ dans pgG ceux qui mènent à sZ dans le graphe inversé de pgG
				//if (bVoir) d(sZ);
				VecteurRazer(bAtteint[0],1,pgG->nSommetEnTout);//O(S)
				VecteurRazer(bAtteint[1],1,pgG->nSommetEnTout);//O(S)
				for (cPasse=0;cPasse<=1;cPasse++){//cPasse=0: accès au graphe direct;cPasse=1: accès au graphe inversé (champs aDeh et sKus)
					DequeRazer(1+pgG->nSommetEnTout);
					DequeEnfiler(sZ);
					While(pgG->nSommetEnTout);
					while (bWhile("nGrapheComposanteFortementConnexe",!bDequeVide())){//O(A)
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							bAtteint[cPasse][sX]=nCFCcourante+1;
							//if (bVoir) tee("cPasse,sX défilé",cPasse,sX);
							for (aK=(cPasse==0)? pgG->aHed[sX]: pgG->aDeh[sX];(cPasse==0)? aK<pgG->aHed[sX+1]: aK<pgG->aDeh[sX+1];aK++){
								sY=(cPasse==0)? pgG->sSuk[aK]: pgG->sKus[aK];
								if (!bAtteint[cPasse][sY])
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//for cPasse
			//if (bVoir) TableauVoir("bAtteint",bAtteint,0,1,1,pgG->nSommetEnTout);
			for (nCFCcourante++,sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (bAtteint[0][sX] && bAtteint[1][sX])
					nCFC[sX]=nCFCcourante;
		}
	DequeAllouer(0);//O(1)
	if (bVoir) VecteurVoir("Numéro de composante attribuée à chaque sommet",nCFC,1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->sPer[sX]=nCFC[sX];
	nComposanteFortementConnexe=nCFCcourante;
	if (bVoir) d(nComposanteFortementConnexe);
	return(nComposanteFortementConnexe);
}//nGrapheComposanteFortementConnexe

void GrapheConnecter(graf *pgG,int bArete,int sOrigine,int sDestination){//O(A)
	//ajoute l'arête ou l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nAttribut ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	GrapheArquer(pgG,sOrigine,sDestination);
	if (bArete)
		GrapheArquer(pgG,sDestination,sOrigine);
}//GrapheConnecter

void GrapheConnecter0(graf *pgG,int bArete,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc){//O(A)
	//ajoute l'arête ou l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nAttribut ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	GrapheArquer0(pgG,sOrigine,sDestination,nAttribut,iValeurSurArc);
	if (bArete)
		GrapheArquer0(pgG,sDestination,sOrigine,nAttribut,iValeurSurArc);
}//GrapheConnecter0

void GrapheConnecter1(graf *pgG,int bArete,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheConnecter1",sOrigine!=sDestination);
	GrapheConnecter0(pgG,bArete,sOrigine,sDestination,grCouleur,nCouleur);
}//GrapheConnecter1

void GrapheConnecter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheConnecter2",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,grCouleur,nCouleurDirecte);
	GrapheArquer0(pgG,sDestination,sOrigine,grCouleur,nCouleurInverse);
}//GrapheConnecter2

int bGrapheConnexe(graf *pgG){//O(A)
	int nComposanteConnexe=nGrapheComposanteConnexe(pgG);
	return(nComposanteConnexe==1);
}//bGrapheConnexe

int nGrapheCouleur(graf *pgG,int sOrigine,int sDestination){//O(S)
	//rend la couleur réputée non nulle de l'arc(sOrigine,sDestination), ou 0 si arc inexistant
	int aK;
	int nCouleur;
	Assert4("nGrapheCouleur",bGrapheAmorceR,bGrapheSimple(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nCouleur=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nCouleur=pgG->coulh[aK];
	return(nCouleur);
}//nGrapheCouleur

char *sGrapheCouple(graf *pgG,int sX,int sY,int nAttribut){
	//affiche les arcs de pgG sous forme de triplets (origine,destination,attributs) ——par exemple,GrapheVoir0(pgG,grCout+grPhi) affichera les champs nCout et nPhi.
	Assert2("sGrapheCouple2",bGrapheAmorceR,pgG!=NULL);
	Assert3("sGrapheCouple3",bCroit(1,sX,pgG->nSommetEnTout),bCroit(1,sY,pgG->nSommetEnTout),nAttribut>0);
	char *sCouple;
	int aK=nGrapheArc(pgG,sX,sY);
	if (nAttribut & grCapaMax)	sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"≤",sPar3(pgG->nCapaMax[aK])));
	if (nAttribut & grCapaMin)	sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"≥",sPar3(pgG->nCapaMin[aK])));
	if (nAttribut & grCouleur)	sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"ç",sPar3(pgG->coulh[aK])));
	if (nAttribut & grCout)		sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"©",sPar3(pgG->nCout[aK])));
	if (nAttribut & grPoids)	sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"π",sPar3(pgG->nPoids[aK])));
	if (nAttribut & grPhi)		sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),"ƒ",sPar3(pgG->nPhi[aK])));
	return(sCouple);
}//sGrapheCouple

void GrapheCouvriR(){
	#define kuSmax 6
	const int kuFacteurMultiplicatif=kE4;
	const int kuPoidsMaxBidon=kE5;
	const int k1Prim=kV;
	int nCoteX[1+kuSmax]={-1,1,2,2,3,3,1};
	int nCoteY[1+kuSmax]={-1,1,2,3,3,4,4};
	int nAretePoids,aK,sX,sY;
	graf *pgG;
	Appel0("GrapheCouvriR");
		GrapheSymetriqueCreerPondereR(k1Dense,kuSmax,kuPoidsMaxBidon,&pgG);//les poids affectés sont provisoires
		//poids(X,Y):=distance(X,Y) pr tout couple (X,Y) de sommets de pgG
			for (sX=1;sX<=kuSmax;sX++)
				for (sY=sX+1;sY<=kuSmax;sY++){
					nAretePoids=nRac( kuFacteurMultiplicatif*(nCarreh(nCoteX[sX]-nCoteX[sY])+nCarreh(nCoteY[sX]-nCoteY[sY])) );
					aK=nGrapheArc(pgG,sX,sY);
					pgG->nCout[aK]=nAretePoids;
					aK=nGrapheArc(pgG,sY,sX);
					pgG->nCout[aK]=nAretePoids;
				}
		GrapheVoir0(pgG,"graphe complet pondéré à \"électrifier\"",grCout);
		Assert1("GrapheCouvriR graphe symétrique attendu",bGrapheSymetrique(pgG));//indispensable pour appeler GrapheCouvrirAvecPrimOuP
		GrapheCouvrirAvecPrimOuP(pgG,!k1Prim,k1Afficher,!k1PerformanceCompareR);
		GrapheCouvrirAvecKruskaL(pgG,k1Afficher,!k1PerformanceCompareR);
	Appel1("GrapheCouvriR");
}//GrapheCouvriR

void GrapheCouvrir(graf *pgG,int tPerformanceComparer,int bAfficher){
	//rend dans pgG->sPer la description d'un acpm qui couvre pgG réputé symétrique puisque non orienté.
	Assert1("GrapheCouvrir",bGrapheSymetrique(pgG));
	GrapheCouvrirAvecKruskaL(pgG,bAfficher,tPerformanceComparer);
}//GrapheCouvrir

void GrapheCouvrirAvecKruskaL(graf *pgG,int bAfficher,int tPerformanceComparer){
	//affiche l'acpm sur pgG,réputé non orienté,acpm calculé selon tPerformanceComparer.
	const int kuModeMax=3;
	int nComplexiteh[1+kuModeMax],nLg[1+kuModeMax];
	int nLgMax,nMode;
	//const int k1Abe=kV;
	const int k1Logn=kV;
	Assert2("GrapheCouvrirAvecKruskaL",bTrit(tPerformanceComparer),bGrapheSymetrique(pgG));
	//d(tPerformanceComparer);
	//Appel0("GrapheCouvrirAvecKruskaL");
		//4 arbres couvrants sont calculés: d'abord 2 arbres de poids minimal sans tas, puis 2 arbres de poids minimal avec tas
			VecteurRazer(nComplexiteh,0,kuModeMax);
			if (tPerformanceComparer>0){//comparer les caractéristiques de l'algorithme optimisé avec des variantes non optimisées ou de poids quelconque.
				nComplexiteh[0]=nGrapheCouvrirAvecKruskaL(pgG,!k1Logn,!k1Tas,bAfficher);//arbre couvrant n°1,aucune optimisation
				nComplexiteh[1]=nGrapheCouvrirAvecKruskaL(pgG,k1Logn,!k1Tas,bAfficher);//arbre couvrant n°2,hauteur des anti-arbres optimisée
				nComplexiteh[2]=nGrapheCouvrirAvecKruskaL(pgG,!k1Logn,k1Tas,bAfficher);//arbre couvrant n°3;utilise un minimier
			}
			if (tPerformanceComparer<0){
				nComplexiteh[3]=nGrapheCouvrirAvecPriM(pgG);//arbre couvrant n°4;algo le plus efficace sur un graphe dense
				if (1)
					GrapheCheminE(pgG,1,pgG->nSommetEnTout,kV,pgG->sPer[0],grArbreCouvrant);
			}else nComplexiteh[3]=nGrapheCouvrirAvecKruskaL(pgG,k1Logn,k1Tas,bAfficher);//arbre couvrant n°4;algo le plus efficace sur un graphe dense
			//VecteurVoir("nComplexiteh",nComplexiteh,0,kuModeMax);
			if (tPerformanceComparer>0){
				Titrer("Comparaison des algorithmes de calcul d'acpm par la méthode de Kruskal");
				printf("%sOption    Forêt optimisée    Tas (minimier)    Durée du calcul\n",sTab(1));
				for (nLgMax=0,nMode=0;nMode<=kuModeMax;nMode++)
					nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
				//VecteurVoir("nLg",nLg,0,kuModeMax);d(nLgMax);
				for (nMode=0;nMode<=kuModeMax;nMode++)
printf("%s  %d           %s                 %s          %s%s\n",sTab(1),nMode,sOui(nMode%2),sOui(nMode/2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
			}
	//Appel1("GrapheCouvrirAvecKruskaL");
}//GrapheCouvrirAvecKruskaL

int nGrapheCouvrirAvecKruskaL(graf *pgG,int bLogn,int bTas,int bAfficher){
	//calcule et affiche un arbre couvrant (résultat ds pgG->nVal[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Kruskal. Rend une mesure de sa complexité.
	int aArete,nAreteEnTout,nAreteTotalDansArbre;
	int nComplexiteh=0,aK;
	int nHauteur,nHauteurMax;
	int nPoids,nPoids0,nPoidsTotal,nVersus;
	int sX,sY,ccX,ccY;
	//Appel0("nGrapheCouvrirAvecKruskaL");
		Assert1("nGrapheCouvrirAvecKruskaL",bGrapheSymetrique(pgG));
		//GrapheVoir0(pgG,"pgG pr Kruskal",grCout);
		ForetINITIALISER(pgG->nSommetEnTout,bLogn);
			//razer arbre couvrant vu comme un sous-graphe de pgG identifié par un booléen à 1 ssi l'arc est ds l'arbre couvrant
				VecteurRazer(pgG->nVal,1,pgG->nArcEnTout);
			//pgG->nPhi:=sommet origine de chaque arc
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						pgG->nPhi[aK]=sX;
			if (bTas){
				TasINITIALISER();
				TasAllouer(pgG->nArcEnTout);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						TasInsererValuer(aK,pgG->nCout[aK]);
				//TasVoir("initialisation");
			} else {//tri non optimisé,eg tri par insertion.
				VecteurTrier(pgG->nCout,1,pgG->nArcEnTout);
				nComplexiteh=pgG->nArcEnTout*pgG->nArcEnTout;
				//sd("nComplexiteh par insertion",nComplexiteh);
			}
			printf("Exécution de l'algorithme de Kruskal %s minimier et %s optimisation de la forêt:\n",sChoix(bTas,"avec","sans"),sChoix(bLogn,"avec","sans"));
			nAreteEnTout=pgG->nArcEnTout;
			for (nPoids0=0,aK=1;aK<=nAreteEnTout;aK++){
				//aArete=aAreteSuivante():
					//b(bTas);
					if (bTas){
						aArete=eTasExtraire();
						//TasVoir("");
					} else aArete=aK;
				nPoids=pgG->nCout[aArete];
				//sd("poids courant",nPoids);
				Assert1("nGrapheCouvrirAvecKruskaL",!bTas || nPoids0<=nPoids);//vérifie que eTasExtraire() rend des arêtes successives de poids croissants
				nPoids0=nPoids;
				sX=pgG->nPhi[aArete];
				sY=pgG->sSuk[aArete];
				//d3(aArete,sX,sY);
				ccX=nForetComposante(sX);
				ccY=nForetComposante(sY);
				if (ccX!=ccY){
					//printf("    Arête (%d,%d) prise.\n",sX,sY);
					ForetFusionner(ccX,ccY);
					//ForetVoir("fusion");
					pgG->nVal[aArete]=1;//ajoute aArete à l'arbre couvrant
				}
			}
			if (bTas)
				nComplexiteh+=nTasCout();
			//d(nTasCout());
			if (bTas)
				TasAllouer(0);
			if (1 && bAfficher){//Afficher l'arbre couvrant et son poids total
				//nAreteTotalDansArbre:=nombre total d'arêtes de l'arbre couvrant
					for (nAreteTotalDansArbre=0,aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							nAreteTotalDansArbre+=1;
				printf("    Arbre couvrant résultant à %s spécifiées par des triplets (sommet,sommet:poids):\n\t\t",sPluriel(nAreteTotalDansArbre,"arête"));
					for (aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							printf(" (%s,%s:%d) ",sEnt0(pgG->nPhi[aK],0),sEnt0(pgG->sSuk[aK],0),pgG->nCout[aK]);
				bPrint(".");
				//nPoidsTotal:=poids total des arêtes de l'arbre couvrant
					for (nPoidsTotal=0,aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							nPoidsTotal+=pgG->nCout[aK];
				printf("\t\t\tPoids total de l'arbre couvrant obtenu%s: %d.\n",sChoix(bTas," (réputé minimal)",""),nPoidsTotal);
				nComplexiteh+=nForetComplexiteh(&nHauteur);
				nHauteurMax=mPoidsFort(pgG->nSommetEnTout);
				printf("    Hauteur maximale théorique de la forêt équilibrée: %s. Hauteur maximale obtenue: %s.\n",sPar3(nHauteurMax),sPar3(nHauteur));
				nVersus=2*nAreteEnTout*nHauteurMax;//2 appels à nForetComposante par arête
				printf("\t\t\tCumul itérations de nForetComposante() vs maximum théorique 2Alog2(S): %s vs %s.\n",sPar3(nComplexiteh),sPar3(nVersus));
			}
		ForetINITIALISER(0,bLogn);
		//d(nComplexiteh);
	//Appel1("nGrapheCouvrirAvecKruskaL");
	return(nComplexiteh);
}//nGrapheCouvrirAvecKruskaL

void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG){
	int nArete,nPoids,nPoidsTotal;
	int aK,sX,sY;
	nArete=pgG->nSommetEnTout-1;//vu bGrapheConnexe(pgG).
	printf("——— Résultat avec %s: un arbre couvrant de poids minimal à %s:\n     ",sAlgorithme,sPluriel(nArete,"arête"));
	//afficher les arêtes avec leurs poids respectifs ainsi que nPoidsTotal:
		for (nArete=0,nPoidsTotal=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (pgG->sPer[sY]==sX){//tout arc (X,Y) qui vérifie pgG->sPer[sY]==sX appartient à l'arbre couvrant
					nArete++;
					nPoids=pgG->nCout[aK];
					printf("(%d,%d:%d)%s",sX,sY,nPoids,(nArete+1<pgG->nSommetEnTout)?",":"");
					nPoidsTotal+=nPoids;
				}
			}
		printf(" ——poids total:%d.\n",nPoidsTotal);
}//GrapheCouvrirAfficheR

int nGrapheCouvrirAvecP(graf *pgG){//O(S2)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant l'algo P vu en TD. Rend une mesure de sa complexité.
	const int kuInfini=kE4-1;
	const int kbVoir=kF;
	int nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecP");
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecP2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) d(nCoutMax);
			Assert1("nGrapheCouvrirAvecP3",nCoutMax<kuInfini);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		AbeAllouer(pgG->nSommetEnTout,kuInfini);//O(1)
			//Abe:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					AbeModifier(sX,nDist[sX]);//O(lgS)
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(S2)
				AbePropager();//O(S)
				if (kbVoir) AbeVoir("avant extraction");
				sX=eAbeExtraire();//O(1)
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//donc positive strictt.
				if (kF || kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						AbeModifier(sY,nDist[sY]);//O(1)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				//if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh=nAbeCout();//ajoute le coût total des opérations effectuées sur l'abe entre les deux AbeAllouer().
		AbeAllouer(0,kuInfini);//O(1)
	if (kbVoir) Appel1("nGrapheCouvrirAvecP");
	return(nComplexiteh);
}//nGrapheCouvrirAvecP

int nGrapheCouvrirAvecPriM(graf *pgG){//O(SlgS+AlgS)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Prim avec tas. Rend une mesure de sa complexité.
	const int kuInfini=kE3-1;
	const int kbVoir=kF;
	int nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecPriM");
		Assert1("nGrapheCouvrirAvecPriM",bGrapheSymetrique(pgG));
		printf("Arbre couvrant de poids minimal (algo de PRIM avec minimier):\n");
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecPriM2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) d(nCoutMax);
			Assert1("nGrapheCouvrirAvecPriM3",nCoutMax<kuInfini);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=coût kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		TasINITIALISER();
		TasAllouer(pgG->nSommetEnTout);//O(1)
			//Tas:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					TasInsererValuer(sX,nDist[sX]);//O(lgS)
		//TasVoir("initialisation");
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(SlgS+AlgS)
				//VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
				if (kbVoir) TasVoir("avant extraction");
				sX=eTasExtraire();//O(lgS)
				//sd("sommet extrait",sX);
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//change donc de signe et devient strictement positif.
				if (kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						//printf("actualisO du sommet %d avec le coût %d.\n",sY,nDist[sY]);
						TasActualiser(sY,nDist[sY]);//O(lgS)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh+=nTasCout();//ajoute le coût total des opérations effectuées sur le tas entre les deux TasAllouer().
		TasAllouer(0);
		pgG->sPer[0]=yVecteurSomme(nDist,1,pgG->nSommetEnTout);
		if (kbVoir) d(nComplexiteh);
	if (kbVoir) Appel1("nGrapheCouvrirAvecPriM");
	return(nComplexiteh);
}//nGrapheCouvrirAvecPriM

void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer){
	//le code de cette routine est à compléter ——en ajoutant notamment du code pris dans GrapheCouvrirAvecKruskaL.
	const int kuModeMaxi=2;
	int nComplexiteh[kuModeMaxi],nComplexitehMax[kuModeMaxi],nMode,nLgMax,nLg[kuModeMaxi];
	Assert3("GrapheCouvrirAvecPrimOuP",bGrapheSymetrique(pgG),bGrapheConnexe(pgG),pgG->nSommetEnTout>1);
	//nComplexiteh[0]=nComplexiteh[1]=0;
	if (bPrim || bPerformanceComparer){
		nComplexiteh[0]=nGrapheCouvrirAvecPriM(pgG);//O(SlgS+AlgS)
		if (bAfficher)
			GrapheCouvrirAfficheR("Prim",pgG);
	}
	if (!bPrim || bPerformanceComparer){
		nComplexiteh[1]=nGrapheCouvrirAvecP(pgG);//O(S2)
		if (bAfficher)
			GrapheCouvrirAfficheR("P",pgG);
	}
	if (bPerformanceComparer){
		//tee("nComplexiteh[0],nComplexiteh[1]",nComplexiteh[0],nComplexiteh[1]);
		Titrer("Comparaison des performances Prim vs P pour le calcul d'acpm");
		printf("%sOption    Prim (minimier)    P(abe)    Durée du calcul\n",sTab(1));
		for (nLgMax=0,nMode=0;nMode<kuModeMaxi;nMode++)
			nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
		//VecteurVoir("nLg",nLg,0,1);d(nLgMax);
		for (nMode=0;nMode<kuModeMaxi;nMode++)
			printf("%s  %d           %s             %s      %s%s\n",sTab(1),nMode,sOui(nMode%2==0),sOui(nMode%2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
		nComplexitehMax[0]=pgG->nArcEnTout*nLog2(pgG->nSommetEnTout);
		nComplexitehMax[1]=pgG->nSommetEnTout*pgG->nSommetEnTout;
		printf("Gains sur le pire cas: SlgS/Prim=%s et S2/P=%s. Facteur de vitesse gagné sur Prim par le challenger P: %s.\n",
			sDiv(nComplexitehMax[0],nComplexiteh[0]),sDiv(nComplexitehMax[1],nComplexiteh[1]),sDiv(nComplexiteh[0],nComplexiteh[1]));
	}
}//GrapheCouvrirAvecPrimOuP

void GrapheCreer(int iSommet,graf **ppgG){
	//si iSommet!=0, alloue un espace pour pgG puis,seult si iSommet>0,ajoute des arcs via GrapheDecrire(); si iSommet est nul,libère l'espace.
	int sX;
	//FlipFlop("GrapheCreer",iSommet!=0,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer(0,…) avant une nouvelle allocation.
	if (iSommet!=0){
		Assert1("GrapheCreer 1",abs(iSommet)<kuGrapheSommetLim);
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=abs(iSommet);
		(*ppgG)->nArcEnTout=0;
		if (iSommet>0){
			GrapheDecrire(*ppgG);//génère un graphe simple avec (*ppgG)->nSommetEnTout sommets et quelques arcs choisis.
		}else for (sX=1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=1;//génère donc un graphe simple avec (*ppgG)->nSommetEnTout sommets et aucun arc.
		Assert1("GrapheCreer 2",bGrapheSimple(*ppgG));
	}
	else free(*ppgG);
}//GrapheCreer

void GrapheCreer0(graf **ppgG,int bCreer){
	//crée un graphe vide, ie sans sommets ni arcs.
	//FlipFlop("GrapheCreer0",bCreer,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer0(0,…) avant une nouvelle allocation.
	if (bCreer){
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=0;
		(*ppgG)->nArcEnTout=0;
		(*ppgG)->aHed[1]=1;
	}else {free(*ppgG);*ppgG=NULL;}
}//GrapheCreer0

void GrapheCreer1(graf **ppgG,int nGrapheForme,int nGrapheTaille,int bCreer){
	//si bCreer,crée le graphe de numéro nGraphe; sinon,restitue le graphe alloué
	//NB Les graphes générés ne sont pas, en général, symétriques; Pour les symétriser,appeler GrapheSymetriser(pgG) après la création.
	graf *pgG;
	enum grType GrapheType;
	enum eCouleur CouleurType;//pr accéder aux couleurs de Kit.h
// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grXX,grOmega}
	int sX,sY;
	char ks2Aile[]="AC2BD3CE1DF1EG2FH2GF3HE3GA1HB1";//2 papillons à 4 sommets
	char ks2Croix[]="AD1BC1";//entrées A, B, sorties C,D.
	char ks2Diam[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char ks2P[]="AB2CD2";//entrées A, B, sorties C,D.

 	//char ksE2[]="AC1BA1BD1CB1DC1";
	//char ksE3[]="AD1BF1CE1DC1DF1EB1ED1FA1FE1";//échafaudage en dipôle. Triangles externes et internes circulaires
	char ksE2[]="AC1BA1BD1CB1CD1";
	char ksE3[]="AD1BF1CE1DC1DF1EB1ED1EF1FA1";//échafaudage en dipôle. Triangles externes et internes circulaires

	char ksFigure8aPage272[]="AB0AC0BC1BE0CD0DE1DG0EF0FG1FH0";//Gondran et Minoux Eyrolles 37 pour tester les couplages qcq
	//char ksPrisme[]="AB1AE1BA2BD3BE1CD1CF1DC2DF2EA2EB2EF3FC2FD1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	//char ksPrisme[]="AB1AE1BA2BE1CD1CF1DC2DF2EA2EB2EF3FC2FD1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksPrisme[]="AB1AE1BA1BE1CD1CF1DC1DF1EA1EB1EF1FC1FD1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksPt[]="AB1AJ2BC1BF2CD1CG2DE1DH2EA1EI2FH3FI3GI3GJ3HJ3";
	char ksT[]="AB1AC1BA1BD1CD1DC1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksT2[]="AB1AC1BA1BD1CB1CD1DA1DC1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	//char ksT2[]="AB4AC4BA4BD4CB4CD4DA4DC4";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksU[]="AB2AC1AE2BD1BE1CE1CD2DE2";//carré sans cycle. NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksX[]="AC1BD1CB2DA3";//NB 1 papillon; entrées A, B, sorties C,D.
	char ksQ0[]="AE2BE2EC2ED2";//NB 1 croix orientée; entrées A, B, sorties C,D.
	char ksQ1[]="AE2BE2EF3FC2FD2";//NB 1 croix étirée au centre; entrées A, B, sorties C,D.

	//char ksXX[]="AE2BF2CH3DG5EB8EG9FA7FH9GC6HD4";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksXor[]="AC1BD1CF2DF2EA3EB3FE4";//NB domino,exclusion mutuelle; entrées A et B, sorties C et D.
	char ksXX[]="AC2BD2CB2CE3DA2DF3EG2FH2GF2HE2";//NB les coins du quadripôle NE SONT PAS les sommets A,B,C et D.
	char ksXY[]="AE1BF1EB2FA5EG1FH1GC1HD1CH6DG3";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksW[]="AC2AD2AE2BC2BD2BE2CA2DB2EC2ED2";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksZ[]="AC3AE1BD3BI1CM3DK3EJ2FB3FE2GF2GH2HA3HI2IN2JC1JK2KF3KL2LG2MH3ML2ND1NM2";//NB les coins du quadripôle sont les sommets A,B,C et D.

	GrapheCreer0(ppgG,bCreer);//oui,mm pr grXX,tant pis
	if (bCreer){
		pgG=*ppgG;
		switch (nGrapheForme) {
			case gr2Aile:
				GrapheGenerer(ks2Aile,grCouleur,ppgG);
			break;
			case gr2Croix:
				GrapheGenerer(ks2Croix,grCouleur,ppgG);
			break;
			case gr2Diam:
				GrapheGenerer(ks2Diam,grCouleur,ppgG);
			break;
			case gr2P:
				GrapheGenerer(ks2P,grCouleur,ppgG);
			break;
			case grC:	//C comme Cycle: Cn est un cycle à n sommets
				GrapheSommer(pgG,nGrapheTaille);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,uModulo1(sX+1,pgG->nSommetEnTout),grCouleur,coVert);
			break;
			case grC4b:	//C4 + 1 arc (2,4)
				GrapheSommer(pgG,4);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,uModulo1(sX+1,pgG->nSommetEnTout),grCouleur,coVert);
				GrapheArquer0(pgG,2,4,grCouleur,coVert);
			break;
			case grD:	//peigne à Dn dents
				GrapheSommer(pgG,2*(nGrapheTaille));
				for (sX=1;sX<=pgG->nSommetEnTout/2-1;sX++)
					GrapheArquer0(pgG,2*sX-1,2*sX+1,grCouleur,coVert);//base du peigne=sommets impairs
				for (sX=1;sX<=pgG->nSommetEnTout/2;sX++)
					GrapheArquer0(pgG,2*sX-1,2*sX+0,grCouleur,coVert);//dents du peigne, de sommets impair à sommet suivant
			break;
			case grE2:
				GrapheGenerer(ksE2,grCouleur,ppgG);
			break;
			case grE3:
				GrapheGenerer(ksE3,grCouleur,ppgG);
			break;
			case grK:	//K comme Kuratowski: Kn est une clique (un sous-graphe complet) à n sommets
				//d(nGraphe-grK2+2);
				GrapheSommer(pgG,nGrapheTaille);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=1;sY<=pgG->nSommetEnTout;sY++)
						if (sX!=sY)
							GrapheArquer0(pgG,sX,sY,grCouleur,coVert);
			break;
			case grL4:	//C3 + 1 arc (3,4)
				GrapheSommer(pgG,4);
				GrapheArquer0(pgG,1,2,grCouleur,coVert);
				GrapheArquer0(pgG,2,3,grCouleur,coVert);
				GrapheArquer0(pgG,3,1,grCouleur,coVert);
				GrapheArquer0(pgG,3,4,grCouleur,coVert);
			break;
			case grP://P comme Path: Pn est un chemin à n sommets
				GrapheSommer(pgG,nGrapheTaille);
				for (sX=1;sX<pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,sX+1,grCouleur,1);
				//GrapheVoir(pgG,"pgG après création");
			break;
			case grPt://graphe de Petersen (pentagone ABCDE relié une étoile FGHIJ)
				GrapheGenerer(ksPt,grCouleur,ppgG);
			break;
			case grPtr://P comme Prisme triangulaire
				GrapheGenerer(ksPrisme,grCouleur,ppgG);
			break;
			case grQ0:
				GrapheGenerer(ksQ0,grCouleur,ppgG);
			break;
			case grQ1:
				GrapheGenerer(ksQ1,grCouleur,ppgG);
			break;
			case grS://S comme Star: Sn est une étoile à n extrémités (1 sommet central)
				GrapheSommer(pgG,nGrapheTaille);
				for (sX=2;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,1,sX,grCouleur,coVert);
			break;
			case grT://tambour: 1 disque haut sous forme de cycle à 2 sommets relié à un disque bas identique
				GrapheGenerer(ksT,grCouleur,ppgG);
			break;
			case grT2://grT plus deux arcs qui se croisent et vont du disque bas vers le disque haut
				GrapheGenerer(ksT2,grCouleur,ppgG);
			break;
			case grU: //carré sans cycle.
				GrapheGenerer(ksU,grCouleur,ppgG);
			break;
			case grW: //diabolo intriqué dans un huit
				GrapheGenerer(ksW,grCouleur,ppgG);
			break;
			case grXor: //1 exclusion mutuelle: (5,1),(1,3),(3,6),(5,2),(2,4),(4,6),(5,6).
				GrapheGenerer(ksXor,grCouleur,ppgG);
			break;
			case grX: //1 papillon: (1,3),(2,4),(3,2) et (4,1).
				GrapheGenerer(ksX,grCouleur,ppgG);
			break;
			case grXX: //20 écrit en chiffres romains ——deux X côte à côte confinés entre deux barres horizontales et verticales.
				GrapheGenerer(ksXX,grCouleur,ppgG);
			break;
			case grXY: //grXX à une renumérotation des sommets près
				GrapheGenerer(ksXY,grCouleur,ppgG);
			break;
			case grZ:
				GrapheGenerer(ksZ,grCouleur,ppgG);
			break;
			case grOmega://Gondran et Minoux Eyrolles 37 pour tester les couplages qcq (contient notamment des triangles imbriqués)
				GrapheGenerer(ksFigure8aPage272,grCouleur,ppgG);
			break;
			default:Assert1("GrapheCreer1: numéro de graphe inconnu (cf GrapheType)",0);
		}//switch (nGraphe)
	};
}//GrapheCreer1

void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]){
	//crée un graphe simple à nSommet sommets et nArc arcs listés dans nArcOrigine[] et nArcDestination[];déroute en cas de problème.
	int sDestination;
	int aK;
	int sOrigine;
	Assert4("GrapheCreer20",nSommet>=0, nArc>=0, nArcOrigine!=NULL, nArcDestination!=NULL);
	GrapheCreer(-nSommet,ppgG);//crée un graphe à nSommet sommets et aucun arc
	//Ajouter tous les arcs aK spécifiés par nArcOrigine[aK] et nArcDestination[aK] et dérouter si un ajout est impossible:
		for (aK=1;aK<=nArc;aK++){
			sOrigine=nArcOrigine[aK];
			sDestination=nArcDestination[aK];
			//tee("création de l'arc",sOrigine,sDestination);
			GrapheArquer(*ppgG,sOrigine,sDestination);//actualise notamment pgG->nArcEnTout;déroute si l'arc ne peut être créé.
		}
	Assert1("GrapheCreer22",bGrapheSimple(*ppgG));
}//GrapheCreer2

int nGrapheCycle2(graf *pgG){
	//rend le nombre de cycles de longueur 2  ds pgG
	int nCycle2=0,sX,sY,aK;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if ( sX<sY && nGrapheArc(pgG,sY,sX) )
				nCycle2++;
		}
	//d(nCycle2);
	return(nCycle2);
}//nGrapheCycle2

void GrapheDecrire(graf *pgG){
	//rend un graphe simple "intéressant" à pgG->nSommetEnTout sommets, ie un graphe connexe obtenu en empilant quelques arcs choisis.
	int uArc,uArcMax,aK,sX,sY;
	int bSucc[1+pgG->nSommetEnTout];
	//Appel0("GrapheDecrire");
		Assert2("GrapheDecrire",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim-1));
		//préparer d'abord un graphe à 1 sommet et aucun arc et faciliter le débogage en razant autant que possible aHed[] et sSuk[]
			pgG->aHed[0]=0;//zèle
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=0;
			pgG->aHed[1]=1;
			for (aK=1;sX<=pgG->nSommetEnTout;aK++)
				pgG->sSuk[aK]=0;
		//lier chaque sommet sX à plusieurs autres sommets, jusqu'à,si possible,sX autres sommets:
			for (pgG->nArcEnTout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)
					bSucc[sY]=kF;//ie sY n'est pas un successeur de sX
				pgG->aHed[sX+1]=pgG->aHed[sX];
				sY=sX;
				uArcMax=3*sX;
				for (uArc=1;uArc<=uArcMax;uArc++){
					sY=uModulo1(sY+uArcMax,pgG->nSommetEnTout);//tente un sommet successeur sY
					if ( (sY!=sX) && !bSucc[sY] ){//le sommet successeur sY a du sens pour sX et c'est effectivement un nouveau successeur
						pgG->nArcEnTout++;
						pgG->sSuk[aK=pgG->nArcEnTout]=sY;
						pgG->nCapaMax[aK]=1;
						pgG->nCout[aK]=1;
						pgG->aHed[sX+1]++;
						bSucc[sY]=kV;
					}
				}
			}
		//GrapheInverser(pgG);//affecte en O(A) les tableaux aDeh[] et sKus[] qui décrivent le graphe inverse du graphe défini par aHed[] et aSuK[]
		Assert1("GrapheDecrire",bGrapheSimple(pgG));
	//Appel1("GrapheDecrire");
}//GrapheDecrire

void GrapheDedoubler(int sDedoublota,graf **ppgG){//O(A)
	//dédouble le sommet sDedoublota
	Assert1("GrapheDedoubler",bCroit(1,sDedoublota,(*ppgG)->nSommetEnTout));
	int bVoir=0;
	int nArcat,nCopiota,aK,sX,nOffset,nDecalage;
	if (bVoir) GrapheVoir0(*ppgG,"*ppgG AVANT dédoublement",grCout);
		GrapheSommer(*ppgG,1);
		int sSommetEnSus=(*ppgG)->nSommetEnTout;
		if (bVoir) d(sDedoublota);
		//tout arc qui part de sDedoublota part dorénavant de sSommetEnSus
			nCopiota=(*ppgG)->aHed[sDedoublota+1]-(*ppgG)->aHed[sDedoublota];
			for (nArcat=(*ppgG)->nArcEnTout,aK=(*ppgG)->aHed[sDedoublota];aK<(*ppgG)->aHed[sDedoublota+1];aK++){
				nOffset=nArcat+aK-(*ppgG)->aHed[sDedoublota]+1;
				(*ppgG)->sSuk[nOffset]=(*ppgG)->sSuk[aK];
				(*ppgG)->nCout[nOffset]=(*ppgG)->nCout[aK];
				(*ppgG)->nArcEnTout=nOffset;
			}
			(*ppgG)->aHed[(*ppgG)->nSommetEnTout+1]=(*ppgG)->nArcEnTout+1;
		if (bVoir) GrapheViseR(*ppgG,"tout arc qui part de sDedoublota recopié au bout");
		//tout arc qui part de sSommet est supprimé, sauf 1
			nDecalage=nCopiota-1;
			if (bVoir) d2(nCopiota,nDecalage);
			for (aK=(*ppgG)->aHed[sDedoublota]+1;aK<=(*ppgG)->nArcEnTout;aK++){
				(*ppgG)->sSuk[aK-nDecalage]=(*ppgG)->sSuk[aK];
				(*ppgG)->nCout[aK-nDecalage]=(*ppgG)->nCout[aK];
			}
			for (sX=(*ppgG)->aHed[sDedoublota]+1;sX<=(*ppgG)->aHed[(*ppgG)->nSommetEnTout+1];sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]-nDecalage;
			(*ppgG)->nArcEnTout=(*ppgG)->nArcEnTout-nDecalage;
			(*ppgG)->aHed[(*ppgG)->nSommetEnTout+1]=(*ppgG)->nArcEnTout+1;
		if (bVoir) GrapheViseR(*ppgG,"tout arc qui sort de sDedoublota est supprimé (sauf 1)");
		//un arc unique part de sSommet à destination de sSommetEnSus
			aK=(*ppgG)->aHed[sDedoublota];
			(*ppgG)->sSuk[aK]=sSommetEnSus;
	if (bVoir) GrapheVoir0(*ppgG,"ppgG APRES dédoublement",grCout);
}//GrapheDedoubler

int nGrapheDegreh(graf *pgG,int sSommet,int tMode){//O(A)
	//tMode= -1: degré entrant, 0: entrant+sortant, +1: sortant.
	int aK,nDegreh,nEntrant,nSortant;
	Assert3("nGrapheDegreh",bGrapheSimple(pgG),bGrapheSommet(pgG,sSommet),bTrit(tMode) );
	if (tMode>=0)
		for (nEntrant=0,aK=1;aK<=pgG->nArcEnTout;aK++)
			if (sSommet==pgG->sSuk[aK])
				nEntrant++;
	nSortant=pgG->aHed[sSommet+1]-pgG->aHed[sSommet];
	if (tMode<0) nDegreh=nEntrant;
	if (tMode==0) nDegreh=nEntrant+nSortant;
	if (tMode>0) nDegreh=nSortant;
	return(nDegreh);
}//nGrapheDegreh

void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination){//O(A)
	//rend les sommets qui délimitent l'arc de rang1 uArcIndex dans pgG;déroute si uArcIndex n'est pas l'index d'un arc de pgG.
	int aK,sX;
	Assert3("GrapheDelimiteR1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//d2(uArcIndex,pgG->nArcEnTout);
	Assert1("GrapheDelimiteR2",bCroit(1,uArcIndex,pgG->nArcEnTout));
		for (*psOrigine=0,*psDestination=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (aK==uArcIndex){
					*psOrigine=sX;
					*psDestination=pgG->sSuk[aK];
				}
		}
	Assert2("GrapheDelimiteR3",*psOrigine>0,*psDestination>0);
}//GrapheDelimiter

void GrapheDerouler(graf *pgG){
	//transforme pgG=(S,A) de façon à obtenir un dag à S*S sommets:à chaque arc (sX,sY) de pgG,on associe S-1 arcs (sXi,sYj) avec 1≤i<S et j=i+1.
	const int bVoir=kF;
	int uEtage,aK,aKlim,sX;
	if (bVoir) Appel0("GrapheDerouler");
		Assert3("GrapheDerouler1",bGrapheAmorceR,pgG->nSommetEnTout>0,bGrapheSimple(pgG));
		Assert2("GrapheDerouler2",pgG->nSommetEnTout*pgG->nSommetEnTout<kuGrapheSommetLim,pgG->nArcEnTout*(pgG->nSommetEnTout-1)<kuGrapheArcLim);
		//affecter pgG->sSuk[]: chague arc relie un sommet source de l'étage uEtage à un sommet cible de l'étage uEtage+1 (uEtage=1 ssi 1er étage):
			for (uEtage=pgG->nSommetEnTout-1;uEtage>=1;uEtage--)
				for (aK=pgG->nArcEnTout;aK>=1;aK--)
					pgG->sSuk[aK+(uEtage-1)*pgG->nArcEnTout]=pgG->sSuk[aK]+uEtage*pgG->nSommetEnTout;
		//affecter pgG->aHed[] hors dernier étage: chague sommet source n'a pour successeurs que des sommets situés à l'étage suivant:
			for (uEtage=2;uEtage<=pgG->nSommetEnTout-1;uEtage++)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX+(uEtage-1)*pgG->nSommetEnTout]=pgG->aHed[sX+(uEtage-2)*pgG->nSommetEnTout]+pgG->nArcEnTout;
		//affecter pgG->aHed[] pour le dernier étage: les sommets du dernier étage n'ont aucun successeur
			aKlim=pgG->nArcEnTout*(pgG->nSommetEnTout-1)+1;
			if (bVoir) d(pgG->nSommetEnTout*pgG->nSommetEnTout);
			if (bVoir) d(aKlim);
			if (bVoir) VecteurVoir("pgG->aHed AVANT",pgG->aHed,1,pgG->nSommetEnTout*pgG->nSommetEnTout+1);
			if (bVoir) VecteurVoir("pgG->sSuk AVANT",pgG->sSuk,1,aKlim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX--)
				pgG->aHed[(pgG->nSommetEnTout-1)*pgG->nSommetEnTout+sX]=aKlim;
			pgG->aHed[pgG->nSommetEnTout*pgG->nSommetEnTout+1]=aKlim;
		//affecter pgG->nArcEnTout et pgG->nSommetEnTout
			pgG->nArcEnTout=aKlim-1;
			pgG->nSommetEnTout=pgG->nSommetEnTout*pgG->nSommetEnTout;
		if (bVoir) VecteurVoir("pgG->aHed APRES",pgG->aHed,1,pgG->nSommetEnTout+1);
		if (bVoir) VecteurVoir("pgG->sSuk APRES",pgG->sSuk,1,aKlim);
		Assert2("GrapheDerouler3",bGrapheSimple(pgG),!bGrapheCircuite(pgG));
	if (bVoir) Appel1("GrapheDerouler");
}//GrapheDerouler

float fGrapheDensiteh(graf *pgSimple){
	//rend la densité du graphe simple pgSimple orienté ou non,ou -1 si non défni. S'il est non orienté,chaque arête est représentée par deux arcs opposés.
	//Dit autrement, le calcul de la densité du graphe ne dépend pas du mode orienté ou non orienté puisque pgSimple est de toute façon un graphe orienté.
	int nArcAuPlus;//nombre d'arcs d'un graphe simple complet
	Assert1("fGrapheDensiteh",bGrapheSimple(pgSimple));
	float fDensiteh=-1.0;//ie densité non définie
	nArcAuPlus=pgSimple->nSommetEnTout*(pgSimple->nSommetEnTout-1);//chaque sommet a pgSimple->nSommetEnTout-1 voisins et il y a Au plus deux arcs opposés entre 2 sommets quelconques.
	if (pgSimple->nSommetEnTout>1){
		fDensiteh=pgSimple->nArcEnTout*1.0/nArcAuPlus;
	}else if (pgSimple->nSommetEnTout==1)//tout arc ou arete formerait une boucle sur le sommet unique de pgSimple: absurde. dc pgSimple->nArcEnTout=0.
		fDensiteh=-1.0;//le nombre d'arcs, égal à 0, est à la fois maximal et minimal. Donc la densité n'est pas définie.
	else fDensiteh=-1.0;//aucun sommet et aucun arc;le nombre d'arcs, égal à 0, est encore à la fois maximal et minimal. Donc densité non définie.
	//tr("fDensiteh",fDensiteh);
	return(fDensiteh);
}//fGrapheDensiteh

int bGrapheDesareter(graf *pgG,int sExtremiteh0,int sExtremiteh1){//O(A)
	//retire de pgG l'arête (sExtremiteh0,sExtremiteh1) s'il existe;rend vrai ssi l'arête a pu être retirée ——donc elle existait à l'appel de la routine.
	Assert2("bGrapheDesareter0",bGrapheAmorceR,bGraphe(pgG));
	int bDesareter=bGrapheSommet(pgG,sExtremiteh0) && bGrapheSommet(pgG,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh0,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh1,sExtremiteh0);
	Assert2("bGrapheDesareter1",bGraphe(pgG),bBool(bDesareter));
	return(bDesareter);
}//bGrapheDesareter

void GrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//d2(sOrigine,sDestination);
	int bDesarquer=bGrapheDesarquer(pgG,sOrigine,sDestination);
	Assert1("GrapheDesarquer UN",bDesarquer);
}//GrapheDesarquer

int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//retire de pgG l'arc (sOrigine,sDestination) s'il existe;rend vrai ssi l'arc a pu être retiré ——donc il existait à l'appel de la routine.
	int aK,aL,sX;
	Assert2("bGrapheDesarquer0",bGrapheAmorceR,bGraphe(pgG));
	int bDesarquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination);
	if (bDesarquer){
		//aL soit l'index de l'arc (sOrigine,sDestination) dans sSuk[], ou 0 si non défini.
			for (aL=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
				if (pgG->sSuk[aK]==sDestination)
					aL=aK;//unique vu Assert3(bGrapheDesarquer0,…,bGrapheSimple(pgG));
		bDesarquer=(aL>0);
	}
	if (bDesarquer){//l'arc (sOrigine,sDestination) existe bien dans pgG et son index dans sSuk[] est aL.
		//retirer l'arc de rang1 aL crée un trou en sSuk[aL]; le combler en tassant à gauche les éléments de sSuk situés au-delà de sSuk[aL]:
			for (aK=aL;aK<pgG->nArcEnTout;aK++){
				pgG->sSuk[aK]=pgG->sSuk[aK+1];
				pgG->nCapaMin[aK]=pgG->nCapaMin[aK+1];
				pgG->nCapaMax[aK]=pgG->nCapaMax[aK+1];
				pgG->coulh[aK]=pgG->coulh[aK+1];
				pgG->nCout[aK]=pgG->nCout[aK+1];
				pgG->nPoids[aK]=pgG->nPoids[aK+1];
			}
			pgG->sSuk[pgG->nArcEnTout]=0;
		//décrémenter tous les éléments de aHed[] situés après pgG->aHed[sOrigine] pour pouvoir accéder aux éléments de sSuk[] qui ont été décalés:
			for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX+1]--;
		pgG->nArcEnTout--;
	}
	Assert2("bGrapheDesarquer1",bGraphe(pgG),bBool(bDesarquer));
	return(bDesarquer);
}//bGrapheDesarquer

void GrapheDesarquerTout(graf *pgG,int sAccroche){
	//retire de pgG tous les arcs éventuels incidents à sAccroche (ne fait rien si aucun arc de pgG n'a sAccroche pour origine ou destination).
	int bIncidence,nIncidence0,nIncidence1;
	int aK,sX,sY;
	Assert3("GrapheDesarquerTout1",bGrapheAmorceR,bGraphe(pgG),bGrapheSommet(pgG,sAccroche));
	//retirer ts les arcs éventuels qui ont pour origine sAccroche
		nIncidence0=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,aK=pgG->aHed[sAccroche];aK<pgG->aHed[sAccroche+1]; aK++){
				sY=pgG->sSuk[aK];
				bIncidence=bGrapheDesarquer(pgG,sAccroche,sY) || bIncidence;
			}
			nIncidence0++;
		} while (bWhile("GrapheDesarquerTout11",bIncidence));
	Assert3("GrapheDesarquerTout2",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//retirer ts les arcs éventuels qui ont pour destination sAccroche
		nIncidence1=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,sX=1; sX<=pgG->nSommetEnTout; sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1]; aK++){
					sY=pgG->sSuk[aK];
					if (sY==sAccroche){
						bIncidence=bGrapheDesarquer(pgG,sX,sAccroche) || bIncidence;
					}
				}//for aK
			nIncidence1++;
		} while (bWhile("GrapheDesarquerTout22",bIncidence));
	Assert2("GrapheDesarquerTout3",bGrapheAmorceR,bGraphe(pgG));
}//GrapheDesarquerTout

void GrapheDupliquer(graf *pgOriginal,graf **ppgCopie){
	int aK;
	int sX;
	Assert4("GrapheDupliquer0",bGrapheAmorceR,bGraphe(pgOriginal),bGrapheSimple(pgOriginal),ppgCopie!=NULL);
	(*ppgCopie)->nSommetEnTout=pgOriginal->nSommetEnTout;
	(*ppgCopie)->nArcEnTout=pgOriginal->nArcEnTout;
	for (sX=1;sX<=pgOriginal->nSommetEnTout+1;sX++){
		(*ppgCopie)->aHed[sX]=pgOriginal->aHed[sX];//dont aHed[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->aDeh[sX]=pgOriginal->aDeh[sX];//dont aDeh[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->sPer[sX]=pgOriginal->sPer[sX];
	}
	for (aK=1;aK<=pgOriginal->nArcEnTout;aK++){
		(*ppgCopie)->sSuk[aK]=pgOriginal->sSuk[aK];
		(*ppgCopie)->sKus[aK]=pgOriginal->sKus[aK];
		(*ppgCopie)->aInv[aK]=pgOriginal->aInv[aK];
		(*ppgCopie)->nCapaMax[aK]=pgOriginal->nCapaMax[aK];
		(*ppgCopie)->nCapaMin[aK]=pgOriginal->nCapaMin[aK];
		(*ppgCopie)->nCout[aK]=pgOriginal->nCout[aK];
		(*ppgCopie)->nPoids[aK]=pgOriginal->nPoids[aK];
		(*ppgCopie)->aArcTo[aK]=pgOriginal->aArcTo[aK];
		(*ppgCopie)->nVal[aK]=pgOriginal->nVal[aK];
		(*ppgCopie)->coulh[aK]=pgOriginal->coulh[aK];
	}
	Assert3("GrapheDupliquer1",bGrapheAmorceR,bGraphe(*ppgCopie),bGrapheSimple(*ppgCopie));
}//GrapheDupliquer

void GrapheEmpiler(graf *pgEmpilota,int nAttribut,graf *pgG){
	//empile sur pgG une occurrence de pgEmpilota, les sommets de pgEmpilota étant renumérotés.
	int aK,aL,sX,sY;
	int nOffset=pgG->nSommetEnTout;
	GrapheSommer(pgG,pgEmpilota->nSommetEnTout);
	for (sX=1;sX<=pgEmpilota->nSommetEnTout;sX++)
		for (aK=pgEmpilota->aHed[sX];aK<pgEmpilota->aHed[sX+1];aK++){
			sY=pgEmpilota->sSuk[aK];
			GrapheArquer(pgG,nOffset+sX,nOffset+sY);
			aL=nGrapheArc(pgG,nOffset+sX,nOffset+sY);
			if (nAttribut & grCapaMax) pgG->nCapaMax[aL]=pgEmpilota->nCapaMax[aK];
			if (nAttribut & grCapaMin) pgG->nCapaMin[aL]=pgEmpilota->nCapaMin[aK];
			if (nAttribut & grCouleur) pgG->coulh[aL]=pgEmpilota->coulh[aK];
			if (nAttribut & grCout) pgG->nCout[aL]=pgEmpilota->nCout[aK];
			if (nAttribut & grPoids) pgG->nPoids[aL]=pgEmpilota->nPoids[aK];
			if (nAttribut & grPhi) pgG->nPhi[aL]=pgEmpilota->nPhi[aK];
		}
}//GrapheEmpiler

void GrapheEtoiler(graf *pgG,int uEtoile,int nBrancheParEtoile){
	//empile sur pgG uEtoile composantes connexes. Chacune est une étoile. Traite aussi le cas limite: une étoile avec 0 branche.
	int uB,uE;
	Assert2("GrapheEtoiler",uEtoile>0,nBrancheParEtoile>=0);
	int uSommetParEtoile=1+nBrancheParEtoile;
	int nSommet=pgG->nSommetEnTout;
	//d(pgG->nSommetEnTout+uEtoile*uSommetParEtoile);
	Assert1("GrapheEtoiler aHed",pgG->nSommetEnTout+uEtoile*uSommetParEtoile<kuGrapheSommetLim);
	for (uE=1;uE<=uEtoile*uSommetParEtoile;uE++)
		pgG->aHed[nSommet+uE+1]=pgG->aHed[nSommet+uE];
	pgG->nSommetEnTout+=uEtoile*uSommetParEtoile;
	Assert1("GrapheEtoiler sSuk",pgG->nArcEnTout+uEtoile*uSommetParEtoile<kuGrapheArcLim);
	for (uE=1;uE<=uEtoile;uE++)
		for (uB=1;uB<=nBrancheParEtoile;uB++)
			GrapheArquer(pgG,nSommet+uSommetParEtoile*(uE-1)+1,nSommet+uSommetParEtoile*(uE-1)+1+uB);
}//GrapheEtoiler

int bGrapheEulerien(graf *pgG,int szSource,int szTrappe){
	//pgG admet un parcours eulérien (fermé/ouvert selon que szSource et szTrappe sont nuls/non nuls ——solidairement;sinon,appel non défini.
	int nDegreh[1+pgG->nSommetEnTout];
	int bEulerien;
	int aK,aL;
	int sX;
	Assert4("bGrapheEulerien1",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->aDeh[1]>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
	if (szSource!=0)
		Assert2("bGrapheEulerien2",bGrapheSommet(pgG,szSource),bGrapheSommet(pgG,szTrappe));
	//nDegreh[sX]:=degré du sommet sX pour tout sX
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			nDegreh[sX]=0;
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			//nDegreh[sX]+=degré sortant de sX,ie le nb de successeurs de sX
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					nDegreh[pgG->sSuk[aK]]++;
			//nDegreh[sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
				for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
					nDegreh[pgG->sKus[aL]]++;
		}
	for (bEulerien=kV,sX=1;sX<=pgG->nSommetEnTout;sX++)
		if ( (szSource==0) || (sX!=szSource && sX!=szTrappe) )
			bEulerien=bEulerien && bPair(nDegreh[sX]);
	return(bEulerien);
}//bGrapheEulerien

int bGrapheEulerier(graf *pgOrienteh,int szSource,int szTrappe){
	//rend dans pgOrienteh->nVal un parcours eulérien qui va de szSource à szTrappe ——donc fermé ssi szSource=szTrappe. rend faux ssi impossible;
	int bEulerier,nSommat,nGreffe=0,nMalloc=0,nPasse;
	int aNext[kuGrapheSommetLim];
	int aK,sX,sY;
	const int kbVoir=kF;
	typedef struct{
		int	 sVertex;
		void *pLien;
	}cellule,*pcellule;
	cellule *pcListe,*pcGreffe,*pcInsert,*pcSuivant,*pcPrecedent;
	graf *pgG=pgOrienteh;
	if (kbVoir) Appel0("bGrapheEulerier");
		Assert4("bGrapheEulerier1",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->aDeh[1]>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
		if (szSource!=0)
			Assert2("bGrapheEulerier2",bGrapheSommet(pgG,szSource),bGrapheSommet(pgOrienteh,szTrappe));
		bEulerier=bGrapheEulerien(pgG,szSource,szTrappe);
		if (bEulerier){
			//pcListe contienne une liste de cellules; chaque cellule mémorise le sommet courant rencontré lors de l'exploration du graphe.
				pcListe=malloc(sizeof(cellule));nMalloc++;pcListe->sVertex=szSource;pcListe->pLien=NULL;
			//pcInsert pointe dans pcListe la cellule courante après laquelle le prochain parcours sera inséré.
				pcInsert=pcListe;
			nSommat=1;//nombre courant d'occurrences de sommets qui jalonnent le parcours
			//aNext[sX] indexe un arc sortant non encore exploré d'origine sX; cet arc existe aussi longtemps que aNext[sX]<pgG->aHed[sX+1].
				VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
				nPasse=0;//nombre d'itérations dans la boucle principale ci-dessous
				While(pgG->nArcEnTout+pgG->nSommetEnTout);
				do{//si un sX dans pcInsert a des arcs non encore explorés,explorer ce sommet et greffer le parcours obtenu sur le parcours principal:
					sX=pcInsert->sVertex;
					//nPasse++;tee("nPasse,sX",nPasse,sX);
					if (aNext[sX]<pgG->aHed[sX+1]){//il reste des arcs sortants non encore explorés
						//partir du sommet sX et traverser un maximum d'arcs non encore explorés
							aK=aNext[sX];
							sY=sX;
							pcGreffe=NULL;
							nGreffe++;if (kbVoir) printf("greffe n°%d:",nGreffe);
							While(1+pgG->nArcEnTout);
							do {
								aNext[sY]=aNext[sY]+1;
								sY=pgG->sSuk[aK];
								if (kbVoir) printf(" %d",sY);
								pcSuivant=malloc(sizeof(cellule));nMalloc++;
								pcSuivant->sVertex=sY;
								if (pcGreffe==NULL)
									pcGreffe=pcSuivant;
								else pcPrecedent->pLien=pcSuivant;
								pcPrecedent=pcSuivant;
								nSommat++;
								aK=aNext[sY];
							}while( bWhile("bGrapheEulerier1",aK!=pgG->aHed[sY+1]) );
						if (kbVoir) printf(".\n");
						//greffer le parcours secondaire
							pcSuivant->pLien=pcInsert->pLien;//la cellule qui suit la dernière cellule du parcours secondaire pcSuivant est la cellule pcInsert->pLien.
							pcInsert->pLien=(pcellule) pcGreffe;//la première cellule de la liste secondaire
					}else pcInsert=pcInsert->pLien;
				}while ( bWhile("bGrapheEulerier2",pcInsert!=NULL) );
				Assert1("bGrapheEulerier3",nSommat==1+pgG->nArcEnTout);//les arcs de pgG ont bien été exploités TOUS et exactement une fois
			//pgG->nVal[]:=copie des 1+pgG->nArcEnTout sommets stockés dans la liste chaînée accessible depuis la cellule pcListe:
				pcInsert=pcListe;
				VecteurRazer(pgG->nVal,1,nSommat);
				for (aK=1;aK<=nSommat;aK++){
					pgG->nVal[aK]=pcInsert->sVertex;
					pcSuivant=pcInsert->pLien;
					free(pcInsert);nMalloc--;
					pcInsert=pcSuivant;
				}
				Assert1("bGrapheEulerier4",pcInsert==NULL);
			VecteurVoir("pgG->nVal",pgG->nVal,1,nSommat);
			//toute cellule allouée a été restituée
				if (nMalloc!=0)
					d(nMalloc);
				Assert1("bGrapheEulerier5",nMalloc==0);
		}
	if (kbVoir) Appel1("bGrapheEulerier");
	return(bEulerier);
}//bGrapheEulerier

void GrapheExplorer(graf *pgG,int bLargeurSinonProfondeur){//O(A)
	//explore pgG en largeur d'abord
	const int kbVoir=kF;
	int sX,sY;
	int bMarque[1+pgG->nSommetEnTout];
	int aNext[1+pgG->nSommetEnTout];
	if (kbVoir) Appel0(sC3b("GrapheExplorer en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
		Assert4("GrapheExplorer",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bBool(bLargeurSinonProfondeur));
		VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
		VecteurRazer(bMarque,1,pgG->nSommetEnTout);
		bMarque[sX=1]=kV;if (kbVoir) d(sX);
		DequeAllouer(pgG->nSommetEnTout);
			if (bLargeurSinonProfondeur) DequeEnfiler(sX);else DequeEmpiler(sX);
			do{
				sX=sDequeSommet();
				if (aNext[sX]<pgG->aHed[sX+1]){
					sY=pgG->sSuk[aNext[sX]];
					if (!bMarque[sY]){
						bMarque[sY]=kV;if (kbVoir) d(sY);
						if (bLargeurSinonProfondeur) DequeEnfiler(sY);else DequeEmpiler(sY);
					}
					aNext[sX]++;//n'altère dc pas pgG->aHed
				}else sX=(bLargeurSinonProfondeur)? sDequeDefiler(): sDequeDepiler();
			}while (!bDequeVide());
		DequeAllouer(0);
	if (kbVoir) Appel1(sC3b("GrapheExplorer en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
}//GrapheExplorer

int bGrapheFortementConnexe(graf *pgG){//O(SA)
	int nComposanteFortementConnexe=nGrapheComposanteFortementConnexe(pgG);
	return(nComposanteFortementConnexe==1);
}//bGrapheFortementConnexe

void GrapheGenerer(char kcArc[],int nAttribut,graf **ppgG){
	//Alloue et rend ppgG défini par les triplets d'arcs colorés (origine,destination,couleur),eg kcArc="AC1AD1AE1AF1BC2BD2BE2BF2".
	int uArc,uArcEnTout,nC,uChaineLg,nCouleur,bCouleurNulle,sDernier,sDestination,sOrigine,sPremier,uS,nSommet;
	int nArc0[kuGrapheArcLim];//NB sommet origine de l'arc
	int nArc1[kuGrapheArcLim];//NB sommet destination de l'arc
	int nDistinct[1+kuByteMax];
	char cSommet;
	uChaineLg=nChaineLg(kcArc);
	Assert2("GrapheGenerer1: lgr de chaîne pas multiple de 3", uChaineLg %3==0,uChaineLg<kuByteMax);//chaque triplet occupe 3 caractères, donc uChaineLg est un multiple de 3.
	//nSommet:=nb de sommets distincts cités ds kcArc censé être une suite de triplets (origine,destination,couleur) qui occupent 3 caractères.
		//nDistinct[sX]:=nombre de références au sommet sX,lequel est censé être une majuscule ou une minuscule
			for (uS=1;uS<=kuByteMax;uS++)
				nDistinct[uS]=0;
			for (nC=0;nC<uChaineLg;nC++)
				if (nC%3!=2){//nC est censé indexer un sommet, pas une couleur
					cSommet=kcArc[nC];
					Assert1("GrapheGenerer2: nom de sommet incorrect",bCroit('a',cSommet,'z') || bCroit('A',cSommet,'Z') );
					nSommet=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
					Assert1("GrapheGenerer3: nom de sommet trop grand",bCroit(1,nSommet,26+26) );
					nDistinct[nSommet]++;
				}
		//nDernier:=numéro du sommet de rang maximal; les sommets de kcArc[] sont réputés commencer à la lettre 'A' et être consécutifs
			for (sPremier=kuIntegerMax,sDernier=0,uS=1;uS<=kuByteMax;uS++)
				if (nDistinct[uS]>0){
					sPremier=iMin(sPremier,uS);
					sDernier=iMax(sDernier,uS);
				}
			Assert1("GrapheGenerer4", sPremier==1);
			for (uS=sPremier;uS<=sDernier;uS++)
				Assert1("GrapheGenerer5", nDistinct[uS]>0);//ts les noms de sommets cités couvrent un facteur gauche de [A-Za-z]
		nSommet=sDernier;
		//d(nSommet);
	uArcEnTout=(uChaineLg)/3;
	Assert1("GrapheGenerer6", uArcEnTout>0);
	//nArc0[]:=sommets origine listés ds cArc[]
		for (nArc0[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			nArc0[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//nArc1[]:=sommets destination listés ds cArc[]
		for (nArc1[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-2];
			nArc1[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//ppgG soit le graphe à nSommet sommets et uArcEnTout arcs d'origine nArc0[] et de destination nArc1[]
		//d2(nSommet,uArcEnTout);
		GrapheCreer2(ppgG,nSommet,uArcEnTout,nArc0,nArc1);
		//d((*ppgG)->nSommetEnTout);
	//colorier chaque arc de ppgG avec la couleur spécifiée dans kcArc[] et calculer,pour info, bCouleurNulle:=toutes les couleurs sont nulles:
		for (bCouleurNulle=kF,nArc1[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			sOrigine=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			cSommet=kcArc[3*uArc-2];
			sDestination=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			nCouleur=kcArc[3*uArc-1]-'0';
			Assert1("GrapheGenerer7", bCroit(0,nCouleur,knGrapheCouleurMax));
			bCouleurNulle=bCouleurNulle || (nCouleur==0);
			//t(sC7("arc (",sEnt(sOrigine),",",sEnt(sDestination),",",sEnt(nCouleur),")"));
			GraphePonderer(*ppgG,sOrigine,sDestination,nAttribut,nCouleur);
		}
		//d((*ppgG)->nSommetEnTout);
		//Assert1("bGrapheGenerer6",!bCouleurNulle);
}//GrapheGenerer

void GrapheINITIALISER(){//O(?)
	//relance le présent module
	Assert1("GrapheINITIALISER",bGrapheAmorceR);
}//GrapheINITIALISER

void GrapheInverser(graf *pgG){//O(A)
	//affecte aDeh[],sKus[] qui décrivent le graphe inverse de pgG,et aInv[] qui donne l'index aK=pgG->aInv[aL] de l'arc inverse de l'arc d'index aL.
	const int kbDisert = kF;
	int aK,aL;
	int nPred[1+pgG->nSommetEnTout];
	int sX,sY,sZ;
	Assert1("GrapheInverser",bGrapheAmorceR);
	//sd("GrapheInverser",pgG->nSommetEnTout);
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++){//O(A)
			sY=pgG->sSuk[aK];
			nPred[sY]++;
		}
		//VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
	//aDeh[sX]:=1+nombre total d'arcs qui auront pour extrémité les sommets 1 à sX (inclus)
		pgG->aDeh[0]=1;//technique
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			pgG->aDeh[sX]=pgG->aDeh[sX-1]+nPred[sX];
		pgG->aDeh[pgG->nSommetEnTout+1]=pgG->nArcEnTout+1;
		//VecteurVoir("aDeH0",pgG->aDeh,1,pgG->nSommetEnTout+1);
	//sKus[] et aInv[] soient affectés
		Assert1("GrapheInverser0",pgG->nArcEnTout>0);
		VecteurRazer(pgG->aInv,1,pgG->nArcEnTout);//O(A)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				Assert1("GrapheInverser1",sY>0);
				pgG->aDeh[sY]--;
				aL=pgG->aDeh[sY];
				Assert1("GrapheInverser2",aL>0);
				pgG->sKus[aL]=sX;
				pgG->aInv[aL]=aK;//dc aK est l'index de l'arc (sX,sY) dans sSuk[] et aL est l'index de (sY,sX) dans sKus[].
			}
	if (kbDisert) GrapheViseR(pgG,"Graphe Inversé");
	if (kbDisert) Titrer("vérifications");
	//vérifier que pgG->aInv permet de passer du graphe inverse au graphe direct
		for (sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//O(A)
			for (aL=pgG->aDeh[sZ];aL<pgG->aDeh[sZ+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];//aL donne aK ——mais en général aK ne donne pas aL
				sY=pgG->sSuk[aK];
				Assert2("GrapheInverser4",sY==sZ,pgG->sSuk[pgG->aInv[aL]]==sZ);
			}
	if (kbDisert)//constater que pgG->aInv NE PERMET PAS DE PASSER DU GRAPHE DIRECT AU GRAPHE INVERSE (sauf exception très rare)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				aL=pgG->aInv[aK];
				sZ=pgG->sKus[aL];
				d3(sX,sY,sZ);
				d2(aK,aL);
				Assert1("GrapheInverser9",sX==sZ);//plante le plus souvent quelque part
			}
}//GrapheInverser

void GrapheOrdonnanceR(graf *pgG,int sSource){//O(A)
	//rend la date au plus tot pour chaque sommet sX ds pgG->nVal[sX]
	const int kbVoir=kF;
	int uNiveau[1+pgG->nSommetEnTout],uSuivant[1+pgG->nSommetEnTout];
	int nDateParX,aK,sX,sY;
	if (kbVoir) Appel0("GrapheOrdonnanceR");
	//uNiveau[],uSuivant[]:=niveaux topologiques, suite des sommets triés par niveau;en 1er,car écrase pgG->nVal[]
		GrapheTrierTopologiquement(pgG,!k1Afficher);//O(A);résultat dans pgG->nVal[]
		VecteurCopier(pgG->nVal,1,pgG->nSommetEnTout,uNiveau);
		VecteurTrier2(uNiveau,1,pgG->nSommetEnTout,uSuivant);//O(S)
	//initialiser pgG->nVal[] et pgG->sPer[].
		VecteurRazer(pgG->nVal,1,pgG->nSommetEnTout);//dates au plus tôt
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
		pgG->nVal[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	//initialiser les successeurs de sSource
		for (aK=pgG->aHed[sSource]; aK<pgG->aHed[sSource+1]; aK++)//O(S)
			pgG->nVal[pgG->sSuk[aK]]=pgG->nCout[aK];
	//VecteurVoir("uNiveau",uNiveau,1,pgG->nSommetEnTout);
	for (int uSommet=1;uSommet<=pgG->nSommetEnTout; uSommet++) {//O(A)
		sX=uSuivant[uSommet];
		//pr tt voisin sY de sX, modifier pgG->nVal[sY] si passer par sX retarde la date au plus tôt de sY
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];//pr info
				nDateParX=pgG->nVal[sX]+pgG->nCout[aK];
				if ( pgG->nVal[sY]<nDateParX ) {//pgG->nVal[sY] est moins tôt
					pgG->nVal[sY]=nDateParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus critique qui relie sY à sSource.
				}
			}
	}
	if (kbVoir) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbVoir) Appel1("GrapheOrdonnanceR");
}//GrapheOrdonnanceR

void CheminCritiqueEnumereR(graf *pgG,int sSource,int sTrappe,int ipPile,int sPile[],int nEffectif,int *pnCumul){
	//si nEffectif est nul,rend ds pnCumul le nb de chemins;sinon, affiche les nEffectif chemins;utilise sPile pr empiler les sommets depuis sSource, et ipPile réputé initialisé à 1.
	if (ipPile==1)
		*pnCumul=0;
	if (!pgG->nVal[sSource])
		sPile[ipPile]=sSource;
		if (sSource!=sTrappe){
			for (int aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
				if (!pgG->nVal[pgG->sSuk[aK]])
					CheminCritiqueEnumereR(pgG,pgG->sSuk[aK],sTrappe,ipPile+1,sPile,nEffectif,pnCumul);
		}else {
			(*pnCumul)++;
			if (nEffectif){
				VecteurVoir(sC4(sTabulation(),"Chemin n°",sEntier(*pnCumul,nLog10(nEffectif))," "),sPile,1,ipPile);
			}
		}
}//CheminCritiqueEnumereR

int bGrapheOrdonnancer(graf *pgG,int bStrict,int bAfficher){//O(A)
	//ordonnanct, strict potentiel-tâches avec des arcs sortants de mm cout si bStrict;rend les marges ds pgG->nVal[]
	const int bVoir=kF;
	int nCoutBasique,aK,bOrdonnancer=1,cPole,bPotentielTache,nSource=0,sSource,sX,sY,nTrappe=0,sTrappe;
	int tDateAuPlusTot[1+pgG->nSommetEnTout],tDateAuPlusTard[1+pgG->nSommetEnTout],nPred[1+pgG->nSommetEnTout];
	int nCheminCritique,ipPile,iPile[1+pgG->nSommetEnTout];//pile des sommets qui jalonnent les chemins critiques
	graf *pgH;
	if (bVoir) Appel0("GrapheOrdonnancer");
		Assert2("bGrapheOrdonnancer dag unique attendu",!bGrapheCircuite(pgG),bGrapheConnexe(pgG));
		//bPotentielTache:=pr chque sommet sX de pgG, ts les arcs d'origine sX ont mm poids
			for (bPotentielTache=kV,sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (nCoutBasique=pgG->nCout[pgG->aHed[sX]],aK=pgG->aHed[sX]+1;aK<pgG->aHed[sX+1];aK++){
					bPotentielTache=bPotentielTache && pgG->nCout[aK]==nCoutBasique;
					if (!bPotentielTache && bStrict) printf("pas potentiel-tâche au sommet %d.\n",sX);
				}
		if (0)
			Assert1("bGrapheOrdonnancer type potentiel-tâche attendu",bPotentielTache);
		GrapheCreer(-pgG->nSommetEnTout,&pgH);
			//pgH:=graphe symétrique de pgG
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						GrapheArquer0(pgH,sY=pgG->sSuk[aK],sX,grCout,pgG->nCout[aK]);
				Assert2("bGrapheOrdonnancer graphe symétrique erroné",pgG->nSommetEnTout==pgH->nSommetEnTout,pgG->nArcEnTout==pgH->nArcEnTout);
			//sSource,sTrappe soient les sommets du dipôle réputé unique qui circonscrit les tâches à ordonnancer
				for (nSource=nTrappe=cPole=0;cPole<=1;cPole++){
					graf *pgP=(cPole)? pgH:pgG;
					for (sX=1;sX<=pgP->nSommetEnTout;sX++)
						nPred[sX]=pgP->aHed[sX+1]-pgP->aHed[sX];
					for (int sX=1;sX<=pgP->nSommetEnTout;sX++)
						if (!nPred[sX]){
							if (cPole) nTrappe++; else nSource++;
							if (cPole) sSource=sX; else sTrappe=sX;
						}
				}
				if (!(nSource==1 && nTrappe==1)) d2(nSource,nTrappe);
				Assert2("bGrapheOrdonnancer dipôle attendu",nSource==1,nTrappe==1);
			//tDateAuPlusTot:=dates au plus tôt
				GrapheOrdonnanceR(pgG,sSource);//O(A)
				VecteurCopier(pgG->nVal,1,pgG->nSommetEnTout,tDateAuPlusTot);
			//tDateAuPlusTard:=dates au plus tard
				GrapheOrdonnanceR(pgH,sTrappe);//O(A)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					tDateAuPlusTard[sX]=tDateAuPlusTot[sTrappe]-pgH->nVal[sX];
		GrapheCreer(0,&pgH);
		//pgG->nVal[]:=marges
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->nVal[sX]=tDateAuPlusTard[sX]-tDateAuPlusTot[sX];
			Assert1("bGrapheOrdonnancer marge positive attendue",yVecteurInf(pgG->nVal,1,pgG->nSommetEnTout)>=0);
		printf("Ordonnancement:\n");
Tabuler(1);
		//afficher les dates au plus tôt et au plus tard, les marges et la mention éventuelle "tâche critique"
			for (printf("%stâche    date au plus tôt   date au plus tard    marge     tâche critique\n",sTabulation()),sX=1;sX<=pgG->nSommetEnTout;sX++)
				printf("%s  %s%15d  %15d  %15d %15s\n",sTabulation(),sEnt0(sX,0),tDateAuPlusTot[sX],tDateAuPlusTard[sX],pgG->nVal[sX],sChoix0(!pgG->nVal[sX],sEnt0(sX,0)));
		//afficher le nombre et la liste des chemins critiques
			CheminCritiqueEnumereR(pgG,sSource,sTrappe,ipPile=1,iPile,0,&nCheminCritique);
			printf("%sIl y a %s%s\n",sTabulation(),sPluriel(nCheminCritique,"chemin$ critique$"),(nCheminCritique<10)? ":":".");
			if (nCheminCritique<10)
				CheminCritiqueEnumereR(pgG,sSource,sTrappe,ipPile=1,iPile,nCheminCritique,&nBof);
Tabuler(-1);
	if (bVoir) Appel1("bGrapheOrdonnancer");
	bOrdonnancer=0;
	return(bOrdonnancer);
}//bGrapheOrdonnancer

int iGraphePoids(graf *pgG,int nArc,int nAttribut){
	int iPoids;
	Assert1("iGraphePoids",bCroit(1,nArc,pgG->nArcEnTout));
	if (nAttribut & grCapaMax) iPoids=pgG->nCapaMax[nArc];
	if (nAttribut & grCapaMin) iPoids=pgG->nCapaMin[nArc];
	if (nAttribut & grCouleur) iPoids=pgG->coulh[nArc];
	if (nAttribut & grCout) iPoids=pgG->nCout[nArc];
	if (nAttribut & grPoids) iPoids=pgG->nPoids[nArc];
	if (nAttribut & grPhi) iPoids=pgG->nPhi[nArc];
	return(iPoids);
}//iGraphePoids

void GraphePolariser(graf *pgG,int *psSource,int *psTrappe){//O(A)
	//ajoute à pgG une source/une trappe unique reliée à ts les sommets sans prédécesseurs/sans successeurs,transformant ainsi pgG en dipôle.
	int bArquer;
	int aK;
	int nPred[kuGrapheSommetLim];
	int nSommet;
	int sX;
	Assert2("GraphePolariser0",bGrapheSimple(pgG),pgG->nSommetEnTout+3<kuGrapheSommetLim);
	nSommet=pgG->nSommetEnTout;
	*psSource=nSommet+1;
	*psTrappe=nSommet+2;
	pgG->nSommetEnTout+=2;//avant l'appel de bGrapheArqueR afin de valider les assertions au début du code de bGrapheArqueR()
	pgG->aHed[nSommet+2]=pgG->aHed[nSommet+1];
	pgG->aHed[nSommet+3]=pgG->aHed[nSommet+2];
	Assert1("GraphePolariser1",bGrapheSimple(pgG));
	bArquer=kV;
	//sSource soit reliée à tous les sommets sans prédécesseurs
		for (sX=1;sX<=nSommet;sX++)
			nPred[sX]=0;
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				nPred[pgG->sSuk[aK]]++;
		for (sX=1;sX<=nSommet;sX++)
			if (nPred[sX]==0)
				bArquer=bArquer && bGrapheArqueR(pgG,*psSource,sX,0);//confronte sSource à pgG->nSommetEnTout
	//sTrappe soit reliée à tous les sommets sans successeurs
		for (sX=1;sX<=nSommet;sX++)
			if (pgG->aHed[sX]==pgG->aHed[sX+1])
				bArquer=bArquer && bGrapheArqueR(pgG,sX,*psTrappe,0);//confronte sSource à pgG->nSommetEnTout
	Assert2("GraphePolariser2",bArquer,bGrapheSimple(pgG));
}//GraphePolariser

void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nAttribut ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("GraphePonderer0",aK>0);
	if (nAttribut & grCapaMax) pgG->nCapaMax[aK]=iValeurSurArc;
	if (nAttribut & grCapaMin) pgG->nCapaMin[aK]=iValeurSurArc;
	if (nAttribut & grCouleur) pgG->coulh[aK]=iValeurSurArc;
	if (nAttribut & grCout) pgG->nCout[aK]=iValeurSurArc;
	if (nAttribut & grPoids) pgG->nPoids[aK]=iValeurSurArc;
	if (nAttribut & grPhi) pgG->nPhi[aK]=iValeurSurArc;
}//GraphePonderer

/*void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nArcCout){//O(A)
	//pgG->nCout["sOrigine,sDestination"]=nArcCout.
	Assert1("GraphePonderer",nArcCout>=0);
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	pgG->nCout[aK]=nArcCout;
}//GraphePonderer
*/
void GraphePonderer0(graf *pgG,int nArcCout){//O(A)
	//initialise pgG->nCout[aK] avec nArcCout.
	Assert1("GraphePonderer0",nArcCout>=0);
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		pgG->nCout[aK]=nArcCout;
}//GraphePonderer0

void GraphePonderer1(graf *pgG,int nArcPoids){//O(A)
	//initialise le champ nPoids de (sX,sY) avec nArcPoids*sX+sY.
	Assert1("GraphePonderer1",nArcPoids>0);
	int aK,sX,sY;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			pgG->nPoids[aK]=nArcPoids*sX+sY;
		}
}//GraphePonderer1

void GraphePonderer2(graf *pgG,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMax et nCout de pgG avec des valeurs aléatoires dans [1..uCapaMax] et [1..uCoutMax], unitaires si uCapaMax ou uCoutMax=1.
	Assert2("GraphePonderer2",uCapaMax>0,uCoutMax>0);
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer2

void GraphePonderer3(graf *pgG,int uCapaMin,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec des valeurs aléatoires dans [1..uCapaMax],etc, unitaires si uCapaMax,etc,=1.
	Assert3("GraphePonderer3",uCapaMin>0,uCapaMax>0,uCoutMax>0);
	int aK;
	//d3(uCapaMin,uCapaMax,uCoutMax);
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMin[aK]=uHasard(uCapaMin);
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer3

void GraphePonderer5(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec les valeurs positives ou nulles spécifiées uCapaMin,uCapaMax et uCoutMax.
	Assert3("GraphePonderer50",nCapaMin>=0,nCapaMax>=0,nCoutMax>=0);
	//tee("sOrigine,sDestination",sOrigine,sDestination);
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("GraphePonderer51",aK>0);
	pgG->nCapaMin[aK]=nCapaMin;
	pgG->nCapaMax[aK]=nCapaMax;
	pgG->nCout[aK]=nCoutMax;
}//GraphePonderer5

void GraphePondererAleatoirement(graf *pgG,int uBorneMax){//O(A)
	//initialiser pgG avec des valeurs aléatoires dans [1..uBorneMax] les 3 champs nCapaMax[],nCout[] et nPoids[]
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMax[aK]=uHasard(uBorneMax);
		pgG->nCout[aK]=uHasard(uBorneMax);
		pgG->nPoids[aK]=uHasard(uBorneMax);
	}
}//GraphePondererAleatoirement

void GraphePondererDistinctement(graf *pgG,int iOffset){//O(A)
	//initialise le cout des arcs (sX,sY) avec des valeurs distinctes en commençant par iOffset>=0 pr le 1er arc rencontré ou -1 si iOffset<0
	int aK,iCout,nCout;
	int nOffset=abs(iOffset);
	for (nCout=(iOffset>=0)? nOffset: 1,aK=1;aK<=pgG->nArcEnTout;aK++){
		iCout=(iOffset>=0)? nCout: -aK;
		//d2(aK,iCout);
		if (pgG->nCout[aK]==0)
			pgG->nCout[aK]=iCout;
		if (pgG->nCout[aK]>0 && iOffset>0)
			pgG->nCout[aK]=iCout;
		nCout+=1;
	}
}//GraphePondererDistinctement

void GraphePondererPareiL(graf *pgG){//O(A)
	//pgG->nCout[(X,Y)]=pgG->nCout[(Y,X)]=Sup(pgG->nCout[(X,Y)],pgG->nCout[(Y,X)]).
	int aK,sX,sY;
	int nMatrice[1+pgG->nSommetEnTout][1+pgG->nSommetEnTout];//N.B. NE PAS L'INITIALISER CAR CELA COUTERAIT O(S2), PLUS CHER QUE O(A) si pgG non dense.
	Assert1("GraphePondererPareiL",bGrapheSymetrique(pgG));
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurRazer(nMatrice[sX],1,pgG->nSommetEnTout);
	if (0) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurVoir("nMatrice[sX]",nMatrice[sX],1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			nMatrice[sY][sX]=nMatrice[sX][sY]=iSup(pgG->nCout[aK],nMatrice[sX][sY]);
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			pgG->nCout[aK]=nMatrice[sX][sY];
		}
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
}//GraphePondererPareiL

void GrapheRenumeroter(graf **ppgG,int sSommetAvant,int sSommetApres){//O(A)
	//retire tous les liens attachés à sSommetAvant et les attache à sSommetApres censé être de degré nul.
	const int bInfo=kF;
	int aK,nDegreh1,sX,ipPile;
	int sCopille[1+(*ppgG)->nSommetEnTout];
	Assert4("GrapheRenumeroter",bGrapheSommet(*ppgG,sSommetAvant),bGrapheSommet(*ppgG,sSommetApres),bGrapheSimple(*ppgG),nGrapheDegreh(*ppgG,sSommetApres,0)==0);
	if (bInfo) GrapheViseR(*ppgG,"AVANT");
	//tt arc qui arrive en sSommetAvant arrive dorénavant en sSommetApres
		for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
			if ( (*ppgG)->sSuk[aK]==sSommetAvant )
				(*ppgG)->sSuk[aK]=sSommetApres;
		Assert1("GrapheRenumeroter 1",bGrapheSimple(*ppgG) );
	nDegreh1=(*ppgG)->aHed[sSommetAvant+1]-(*ppgG)->aHed[sSommetAvant];
	if (bInfo) d2(1,nDegreh1);
	//tt arc qui part de sSommetAvant part dorénavant de sSommetApres
		//empiler les futurs successeurs de sSommetApres
			for (ipPile=0,aK=(*ppgG)->aHed[sSommetAvant];aK<(*ppgG)->aHed[sSommetAvant+1];aK++)
				sCopille[ipPile++]=(*ppgG)->sSuk[aK];
		//supprimer les nDegreh1 successeurs de sSommetAvant
			for (aK=(*ppgG)->aHed[sSommetAvant+1];aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->sSuk[aK-nDegreh1]=(*ppgG)->sSuk[aK];
			for (sX=sSommetAvant+1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]-nDegreh1;
		//créer un espace de taille nDegreh1 pour les successeurs de sSommetApres
			for (aK=(*ppgG)->nArcEnTout;aK>=(*ppgG)->aHed[sSommetApres+1];aK--)
				(*ppgG)->sSuk[aK+nDegreh1]=(*ppgG)->sSuk[aK];
			for (sX=sSommetApres+1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]+nDegreh1;
		//loger la pile ds l'espace en question
			for (aK=(*ppgG)->aHed[sSommetApres];aK<(*ppgG)->aHed[sSommetApres]+nDegreh1;aK++)
				(*ppgG)->sSuk[aK]=sCopille[--ipPile];
		Assert1("GrapheRenumeroter 2",bGrapheSimple(*ppgG));
		if (bInfo) d( (*ppgG)->nArcEnTout);
	if (bInfo) GrapheViseR(*ppgG,"APRES");
		if (bInfo) d2(2,nGrapheDegreh(*ppgG,sSommetAvant,0));
		Assert1("GrapheRenumeroter 3",bGrapheSimple(*ppgG) );
		Assert1("GrapheRenumeroter 4",nGrapheDegreh(*ppgG,sSommetAvant,0)==0);
}//GrapheRenumeroter

void GrapheRenumeroterTout(int sListe[],graf *pgG){
	//prend en donnée la liste des futurs numéros de sommets de ppgG et remplace chaque arc (sX,couleur,sY) de ppgG par (sListe[sX],couleur,sListe[sY])
	int bVoir=0;
	graf *pgCopie;
	Assert1("GrapheRenumerote",sListe[0]==pgG->nSommetEnTout);
	GrapheCreer0(&pgCopie,k1Creer);
		GrapheDupliquer(pgG,&pgCopie);
		for (int sX=pgG->nSommetEnTout;sX>0;sX--)
			GrapheDesarquerTout(pgG,sX);
		if (bVoir) GrapheVoir(pgG,"QuatriceRenumeroteR:pgG désarqué");
			for (int sX=1;sX<=pgCopie->nSommetEnTout;sX++)
				for (int aK=pgCopie->aHed[sX];aK<pgCopie->aHed[sX+1];aK++){
					int sY=pgCopie->sSuk[aK];
					int sZ=sListe[sX];
					int sT=sListe[sY];
					GrapheArquer0(pgG,sZ,sT,grCouleur,pgCopie->coulh[aK]);
				}
		if (bVoir) GrapheVoir(pgG,"QuatriceRenumeroteR:pgG renuméroté");
	GrapheCreer0(&pgCopie,!k1Creer);
}//GrapheRenumeroterTout

int bGrapheQuadripole(int nTypeDeMotif){
	enum grType GrapheType;
	int bQuadripole=bDans7(nTypeDeMotif,gr2Croix,grQ0,grQ1,grX,grXX,grU,grW);
	return(bQuadripole);
}//bGrapheQuadripole

int nGrapheQuadripoler(graf *pgSansMotif,int nMotifForme,int nMotifTaille,int bCroiser,int nAttribut,graf **ppgAvecMotif){
	//pgAvecMotif:= à chq sX de pgSansMotif on associe (sX+0,sX+1,sX+n-1,sX+n),avec entrée et sortie selon nMotifForme;rend nb sommets par motif.
	const int bInfo=kF;
	int nDigit,aK,sX,sY,sXprim,sYprim,uArcValeur,uMotif,uMultipleDe10,nSommetParMotif,nOffset;
	graf *pgMotif;
	enum grType GrapheType;
	if (bInfo) Appel0("nGrapheQuadripoler");
		Assert1("nGrapheQuadripoler",bGrapheQuadripole(nMotifForme));
		if (bInfo) GrapheVoir0(pgSansMotif,"pgSansMotif ORIGINAL",nAttribut);
		GrapheCreer1(&pgMotif,nMotifForme,nMotifTaille,k1Creer);
			if (bInfo) GrapheVoir0(pgMotif,sC2b("pgMotif",sGraphe(nMotifForme)),nAttribut);
			nSommetParMotif=pgMotif->nSommetEnTout;
			//d(nSommetParMotif);
			GrapheCreer0(ppgAvecMotif,k1Creer);
			GrapheSommer(*ppgAvecMotif,nSommetParMotif*pgSansMotif->nSommetEnTout);
			//ajouter les arcs internes aux motifs
				nDigit=nLog10(1+(*ppgAvecMotif)->nSommetEnTout);
				uMultipleDe10=zPuissance(10,nDigit);
				for (uMotif=1;uMotif<=pgSansMotif->nSommetEnTout;uMotif++)
					for (sX=1;sX<=nSommetParMotif;sX++)
						for (aK=pgMotif->aHed[sX];aK<pgMotif->aHed[sX+1];aK++){
							sY=pgMotif->sSuk[aK];
							sXprim=nSommetParMotif*(uMotif-1)+sX;
							sYprim=nSommetParMotif*(uMotif-1)+sY;
							uArcValeur=uMultipleDe10*uMotif+sX;
							uArcValeur=pgMotif->coulh[aK];
							//uArcValeur=(200+sXprim+1)/2;//dc diag de mm poids pr grX
							//if (bInfo) d7(1234,uMotif,sX,sY,sXprim,sYprim,uArcValeur);
							GrapheArquer0(*ppgAvecMotif,sXprim,sYprim,nAttribut,uArcValeur);
						}
			//ajouter les arcs noirs externes aux motifs: la valeur de l'arc associé à pgSansMotif[aK=(sX,sY)] est celle de pgSansMotif->coulh[aK]
				nOffset=(nMotifForme==grU)? 2 : 0;
				if (bInfo) d2(bCroiser,nOffset);
				for (sX=1;sX<=pgSansMotif->nSommetEnTout;sX++)
					for (aK=pgSansMotif->aHed[sX];aK<pgSansMotif->aHed[sX+1];aK++){
						sY=pgSansMotif->sSuk[aK];
						sXprim=nSommetParMotif*(sX-1)+nSommetParMotif-2+bCroiser;//si bCroiser, sortie D ds la diagonale de A.
						sYprim=nSommetParMotif*(sY-1)+1;//entrée A.
						if (bInfo) d6(5678,sX,sY,sXprim,sYprim,pgSansMotif->coulh[aK]);
						GrapheArquer0(*ppgAvecMotif,sXprim,sYprim,nAttribut,pgSansMotif->coulh[aK]);
					}
		GrapheCreer1(&pgMotif,nMotifForme,nMotifTaille,!k1Creer);
	if (bInfo) Appel1("nGrapheQuadripoler");
	return(nSommetParMotif);
}//nGrapheQuadripoler

void GrapheQuinconceR(graf *pgG,int bBipartir){
	//déroule pgG en quinconce de façon à obtenir un dag puis,si bBipartir,dédouble chaq sommet en lui attribuant 2 numéros de sommets csécutifs.
	const int kbQuinconcer=kF;
	int bDesarquer;
	int nOffset;
	int bQuinconce;
	int uCoteh,nEtage,aK,sX,sY;
	if (kbQuinconcer) Appel0("GrapheQuinconceR");
	Assert1("GrapheQuinconceR1",bGrapheSimple(pgG));
	uCoteh=pgG->nSommetEnTout;//côté du graphe étagé à venir
	GrapheDerouler(pgG);
	Assert1("GrapheQuinconceR2",bGrapheSimple(pgG));
	//supprimer les arcs hors quinconce
		for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
			bQuinconce=(bPair(nEtage)==bPair(sX));
			if (sX==1)
				Assert1("bQuinconce",bQuinconce);
			for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
				if (!bQuinconce){
					sY=pgG->sSuk[aK];
					bDesarquer=bGrapheDesarquer(pgG,sX,sY);
					Assert1("GrapheQuinconceR",bDesarquer);
				}
			}
			if ((sX-1) % uCoteh==0)
				nEtage--;
		}
		if (kbQuinconcer) VecteurVoir("aHed4",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk4",&pgG->sSuk[0],1,pgG->nArcEnTout+pgG->nSommetEnTout/2);
		if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé");
	Assert1("GrapheQuinconceR3",bGrapheSimple(pgG));
	if (bBipartir){//réaffecter les sommets hors quinconce;le sommet 1 dédoublé devient 1 et 2;mais à l'étage suivant,le sommet n devient n-1 et n.
		//insérer dans pgG->sSuk[] 1 arc par sommet hors quinconce ——de façon à ajouter 1 arc en pgG->sSuk[1] et en prendre acte dans pgG->aHed[].
			Assert1("GrapheQuinconceR4",pgG->nArcEnTout+pgG->nSommetEnTout<kuGrapheArcLim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX-=2)
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX-1];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX/2]=-sY;//décale les arcs et en profite pour les marquer négativement (exploité plus bas, et pour deboguer)
				}
			for (nOffset=0,nEtage=0,sX=1;sX<=pgG->nSommetEnTout+1;sX++){
				if (bQuinconce=(bPair(nEtage)==bPair(sX)))
					nOffset++;
				pgG->aHed[sX]+=nOffset;
				if ((sX-1) % uCoteh==0)
					nEtage++;
			}
			pgG->nArcEnTout+=nOffset;
			if (kbQuinconcer) VecteurVoir("aHed5",&pgG->aHed[0],1,pgG->nSommetEnTout);
			if (kbQuinconcer) VecteurVoir("sSuk5",&pgG->sSuk[0],1,pgG->nArcEnTout);
			if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé TRANSITOIRE");
		//actualiser la cible de chaque arc: l'arc origine d'un sommet dédoublé cible le sommet suivant;l'arc destination cible un sommet positif.
			for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
				bQuinconce=(bPair(nEtage)==bPair(sX));
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					if (sY<0)//cet arc original doit cibler maintenant le sommet origine de chaque sommet bipartitionné
						pgG->sSuk[aK]=bPair(nEtage)? -sY : -sY-1;//cible le bon sommet positif.
					else pgG->sSuk[aK]=sX+1;//logique car le sommet 1 est devenu 1 et 2;à l'étage suivant, n est devenu n-1 et n
				}
				if ((sX-1) % uCoteh==0)
					nEtage--;
			}
		if (kbQuinconcer) VecteurVoir("aHed6",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk6",&pgG->sSuk[0],1,pgG->nArcEnTout);
		if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé FINAL");
	}//Le plus souvent,le graphe obtenu n'est pas connexe.
	Assert2("GrapheQuinconceR2",bGrapheSimple(pgG),!bBipartir || bGrapheBiparti(pgG));//Si bBipartir,aucun sommet n'est isolé.
	if (kbQuinconcer) Appel1("GrapheQuinconceR");
}//GrapheQuinconceR

void GrapheQuintesser(graf *pgG,int nSommet){
	//génère un graphe déroulé bipari en quiconce puis l'étoile et connecte les étoiles amont et aval à chaque colonne;
	#define kbQuintesser kF
	int uB,uE,nPaire,sX,sYamont,sYaval;
	int bDesarquer;
	int aK,aL;
	int nSommet0;
	if (kbQuintesser) Appel0("GrapheQuintesser");
	if (kbQuintesser) d(nSommet);
	GrapheCliquer(pgG,nSommet);
	if (0){
		if (nSommet==3)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,3,2);
		if (nSommet==4)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,2,4);
	}
	GrapheVoir(pgG,"Graphe cliqué");
	GrapheBipartitionner(pgG);
	GrapheVoir(pgG,"Graphe cliqué biparti");
	GrapheQuinconceR(pgG,k1BipartiR);
	//refermer le chemin diagonal pour obtenir un circuit
		GrapheArquer(pgG,1,pgG->nSommetEnTout);
	GrapheVoir(pgG,"Graphe cliqué biparti quinconcé et bipartitionné");
	nSommet0=pgG->nSommetEnTout;
	int nEtoile=4*nSommet;
	if (kbQuintesser) d(nEtoile);
	int uBrancheParEtoile=nSommet;
	int nSommetParEtoile=1+uBrancheParEtoile;
	if (kbQuintesser) d(uBrancheParEtoile);
	GrapheEtoiler(pgG,nEtoile,uBrancheParEtoile);
	GrapheVoir(pgG,"Graphe cliqué biparti quinconcé bipartitionné et étoilé");
	if (kbQuintesser) d(nSommet0);
	//connecter les étoiles au reste du graphe
		for (uE=1;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;//centre étoile amont
			sYaval=sYamont+nSommetParEtoile;//centre étoile aval
			if (kbQuintesser) printf("Centres des étoiles amont et aval:%d,%d.\n",sYamont,sYaval);
			for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				if (kbQuintesser) printf("arc sX,Centre amont:       (%2d,%2d)\n",sX,sYamont);
				if (kbQuintesser) printf("arc sX,Centre aval:       (%2d,%2d)\n",sX+1,sYaval);
				GrapheArquer(pgG,sX,sYamont);
				GrapheArquer(pgG,sX+1,sYaval);
				sX+=4*nSommet;
			}
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->aDeh[sX]=0;
	for (nPaire=0,uE=1;uE<=nEtoile/2;uE++){
		sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;
		sYaval=sYamont+nSommetParEtoile;
		pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
		if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
		if (kbQuintesser) sd("étoile0",sYamont);
		for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
			//if (kbQuintesser) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
			//if (kbQuintesser) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
			aK=nGrapheArc(pgG,sX,sYamont);
			aL=nGrapheArc(pgG,sX+1,sYaval);
			pgG->aDeh[sX]=sX+1;pgG->aDeh[sX+1]=sX;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sX,sX+1));
			pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
			sX+=4*nSommet;
		}
	}
	teee("nEtoile,uBrancheParEtoile+1,nPaire",nEtoile,uBrancheParEtoile+1,nPaire);
	Assert1("GrapheQuintesser",sYaval=pgG->nSommetEnTout);
	if (kbQuintesser) Appel1("GrapheQuintesser");
}//GrapheQuintesser

void GrapheRetourner(graf *pgG,int bRetourner,graf **ppgH){
	//si bRetourner,alloue et rend le graphe inverse de pgG;sinon,restitue pgH
	int sX,sY;
	if (bRetourner){
		GrapheCreer(-pgG->nSommetEnTout,ppgH);
			//pgH:=graphe symétrique de pgG
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						GrapheArquer0(*ppgH,sY=pgG->sSuk[aK],sX,grCout,pgG->nCout[aK]);
				Assert2("GrapheRetourner",pgG->nSommetEnTout==(*ppgH)->nSommetEnTout,pgG->nArcEnTout==(*ppgH)->nArcEnTout);
	}else GrapheCreer(0,ppgH);
}//GrapheRetourner

int bGrapheSimple(graf *pgG){
	//ni boucle,ni plus d'un arc d'un sommet origine à un sommet destination
	int aK,sX,sY;
	int bSimple;
	int nSucc[1+pgG->nSommetEnTout];
	Assert2("bGrapheSimple",bGrapheAmorceR,bGraphe(pgG));
	for (bSimple=kV,sX=1;sX<=pgG->nSommetEnTout;sX++){
		for (sY=1;sY<=pgG->nSommetEnTout;sY++)
			nSucc[sY]=0;
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if ( !bGrapheSommet(pgG,sY) || (sX==sY) || (++nSucc[sY]>1) )
				bSimple=kF;
		}
	}
	return(bSimple);
}//bGrapheSimple

void GrapheSommer(graf *pgG,int inEmpilerSinonDepiler){
	//si inEmpilerSinonDepiler>0,empile inEmpilerSinonDepiler sommets;si <0,élimine ts les arcs liés aux sommets et les dépile (n° pgG->nSommetEnTout) puis dépile ce sommet
	int uS;
	Assert2("GrapheSommer1",bGrapheAmorceR,bGrapheSimple(pgG));
	//d(inEmpilerSinonDepiler);
	if (inEmpilerSinonDepiler!=0)
		if (inEmpilerSinonDepiler>0) {
			Assert1("GrapheSommer2",pgG->nSommetEnTout+inEmpilerSinonDepiler<kuGrapheSommetLim);
			for (uS=1;uS<=inEmpilerSinonDepiler;uS++){
				pgG->aHed[pgG->nSommetEnTout+2]=pgG->aHed[pgG->nSommetEnTout+1];//crée les nouveaux sommets,sans arcs incidents.
				(pgG->nSommetEnTout)+=1;
			}//d(pgG->nSommetEnTout);
		}
		else {
			Assert1("GrapheSommer3",pgG->nSommetEnTout>-inEmpilerSinonDepiler);
			for (uS=1;uS<=-inEmpilerSinonDepiler;uS++){
				GrapheDesarquerTout(pgG, pgG->nSommetEnTout);//dépile le dernier sommet
				pgG->aHed[pgG->nSommetEnTout+1]=0;
				(pgG->nSommetEnTout)--;
			}
		}
	Assert2("GrapheSommer4",bGraphe(pgG),bGrapheSimple(pgG));
}//GrapheSommer

int bGrapheSommet(graf *pgG,int sSommet){
	int bGrapheSommet=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bGrapheSommet);
}//bGrapheSommet

int bGrapheSymetrique(graf *pgG){//O(A)
	//à tout arc (X,Y) présent dans pgG correspond dans pgG un arc inverse (Y,X)
	graf *pgH;
	int bSymetrique;
	Assert2("bGrapheSymetrique",bGrapheAmorceR,bGraphe(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		//GrapheVoir(pgH,"pgH");
		GrapheSymetriser(pgH,grCouleur+grCout);//O(A)
		bSymetrique=(pgG->nArcEnTout==pgH->nArcEnTout);
	free(pgH);
	//Assert1("bGrapheSymetrique1",bSymetrique);
	return(bSymetrique);
}//bGrapheSymetrique

void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int uPoidsMax,graf **ppgG){
	//alloue et rend un graphe symétrique "intéressant" à nSommetEnTout sommets,pondéré aléatoirement de 1 à uPoidsMax ——champ (*ppgG)->nCout.
	int aK,aL;
	int sX,sY;
	//Appel0("GrapheSymetriqueCreerPondereR");
		Assert2("GrapheSymetriqueCreerPondereR",uPoidsMax>0,bCroitStrict(0,nSommetEnTout,kuGrapheSommetLim));
		if (bDense)
			GrapheCompletCreerPondereR(nSommetEnTout,ppgG);
		else GrapheCreer(nSommetEnTout,ppgG);
			//GrapheVoir(pgG,"AVANT symétrisation");
			GrapheSymetriser(*ppgG,grCouleur+grCout);
			//GrapheVoir(pgG,"APRES symétrisation");
			if (0){
				t("Extrémités des arêtes");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sSuk[aK]);
				printf("\n");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sKus[aK]);
				printf("\n");
			}
			GrapheInverser(*ppgG);//pour Kruskal
			//initialiser les poids pgG->nCout[aK] et compléter la correspondance aK->sX,sY via pgG->nPhi[aK]=sX en plus de pgG->sSuk[aK]=sY
				for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
					for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
						sY=(*ppgG)->sSuk[aK];
						aL=(*ppgG)->aInv[aK];
						Assert1("GrapheSymetriqueCreerPondereR2",(*ppgG)->sSuk[aL]==sX);
						(*ppgG)->nPhi[aK]=sX;
						Assert1("GrapheSymetriqueCreerPondereR3",(*ppgG)->sSuk[(*ppgG)->aInv[aK]]==(*ppgG)->nPhi[aK]);//donc nPhi est d'une certaine façon superflu
						(*ppgG)->nCout[aK]=uHasard(uPoidsMax);
						//teeee("arête et poids X Y",aK,pgG->nCout[aK],sX,sY);
					}
				GraphePondererPareiL(*ppgG);//O(A);le poids des arcs (X,Y) et (Y,X) est maintenant identique.
			//GrapheVoir0(*ppgG,"——— Donnée: un graphe non orienté");
				if (0) for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++){
					d(aK);
					Assert1("GrapheSymetriqueCreerPondereR8",(*ppgG)->nPhi[aK]>0);
				}
	//Appel1("GrapheSymetriqueCreerPondereR");
}//GrapheSymetriqueCreerPondereR

void GrapheSymetriser(graf *pgG,int nAttribut){//O(A)
	//symétrise pgG en complétant les (X,Y) par les (Y,X) manquants. Si nAttribut non nul,recopie l'attribut en question de (X,Y) vers (Y,X).
	int aK,aL,aM;//aM est l'index de pile qui progresse sur pgG->sSuk[],cf pgG->sSuk[++aM]
	graf *pgH;
	int nCumul[1+pgG->nSommetEnTout];
	int bPred[1+pgG->nSommetEnTout];
	int bSucc[1+pgG->nSommetEnTout];
	int sX,sZ;
	Assert2("GrapheSymetriser",bGrapheAmorceR,bGraphe(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		GrapheInverser(pgH);//O(A)
		//GrapheVoir1(pgG,k1Couleur,"pgG");GrapheVoir1(pgH,k1Couleur,"pgH");
		//pgG->sSuk[],pgG->coulh[],nCumul[]:= les arcs de pgG symétrisé, ses couleurs, le cumul des arcs empilés sommet par sommet.
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				bPred[sX]=bSucc[sX]=kF;
//GrapheVoir1(pgH,k1Couleur,"pgH");
			for (aM=0,sX=1;sX<=pgH->nSommetEnTout;sX++){//O(A): les 3 aK et les 3 aL ci-dessous visitent 6 fois la totalité des arcs de pgH
				//bSucc[] / bPred[]:=coche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kV;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kV;
					//VecteurVoir("nSucc",nSucc,1,pgG->nSommetEnTout);VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
				//empiler dans pgG les sommets de bSucc union bPred,ie tous ceux de pgH->sSuk[],plus ceux cochés dans bPred mais pas dans bSucc:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//au total,cet aK aura passé en revue 1 fois la totalité des arcs de pgH
						Assert1("GrapheSymetriser1",aM+1<kuGrapheArcLim);
						pgG->sSuk[++aM]=pgH->sSuk[aK];//empile ds pgG
						pgG->nCapaMax[aM]=pgH->nCapaMax[aK];
						pgG->nCapaMin[aM]=pgH->nCapaMin[aK];
						pgG->coulh[aM]=pgH->coulh[aK];
						pgG->nCout[aM]=pgH->nCout[aK];
						pgG->nPoids[aM]=pgH->nPoids[aK];
						//d2(1,aM);
					}
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++){//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						sZ=pgH->sKus[aL];
						if (bPred[sZ] && !bSucc[sZ]){//ajouter l'arc manquant aL:
							Assert1("GrapheSymetriser2",aM+1<kuGrapheArcLim);
							pgG->sSuk[++aM]=sZ;
						//d2(2,aM);
							pgG->nCapaMax[aM]=0;
							pgG->nCapaMin[aM]=0;
							pgG->coulh[aM]=0;//la couleur de l'arc aL est celle de l'arc inverse de aL.
							pgG->nCout[aM]=0;
							pgG->nPoids[aM]=0;

							if (nAttribut & grCapaMax) pgG->nCapaMax[aM]=pgH->nCapaMax[pgH->aInv[aL]];
							if (nAttribut & grCapaMin) pgG->nCapaMin[aM]=pgH->nCapaMin[pgH->aInv[aL]];
							if (nAttribut & grCouleur) pgG->coulh[aM]=pgH->coulh[pgH->aInv[aL]];//la couleur de l'arc aL est celle de l'arc inverse de aL.
							if (nAttribut & grCout) pgG->nCout[aM]=pgH->nCout[pgH->aInv[aL]];
							if (nAttribut & grPoids) pgG->nPoids[aM]=pgH->nPoids[pgH->aInv[aL]];
						}
					}
				nCumul[sX]=aM;
				//bSucc[] / bPred[]:=décoche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kF;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kF;
			}
	free(pgH);
	//pgG->aHed[]:=nouveaux index fonctions de nCumul[]
		//pgG->aHed[1] vaut déjà 1.
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX+1]=nCumul[sX]+1;
	//pgG->nSommetEnTout est déjà correct: symétriser le graphe ne modifie pas le nombre de ses sommets.
	pgG->nArcEnTout=nCumul[pgG->nSommetEnTout];
	Assert1("GrapheSymetriser",bGrapheSimple(pgG));
	//GrapheVoir1(pgG,k1Couleur,"pgG symétrisé");
}//GrapheSymetriser

void GrapheTESTER(int iTest){
	const int k1Prim=kV;
	const int ksSource=1;
	int bkAfficher=1;
	int nArcOrigine[]=    {0,   1,2,3,3,2};
	int nArcDestination[]={0,   2,3,1,2,1};
	int nGraphe,nPoidsMax;
	char kcTriominoComplet[]="AB1BC1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 1 composante fortement connexe
	char kcTriominoIncomplet[]="AB1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 5 composantes fortement connexes
	int bBiparti,bCheminer,bCircuit,nComplexiteh,bEulerien,aK;
	graf *pgG,*pgH;
	int bSimple;
	int nSommet,uSommet;
	enum grType GrapheType;
	// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grOmega}

	Appel0(sC2("GrapheTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=8,pgG) );
					bSimple=bGrapheSimple(pgG);
					printf( "Le graphe à %s %s simple.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bSimple) );
					GrapheCreer(0,&pgG);
					break;
			case 2: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=2,pgG) );
					GrapheSymetriser(pgG,grCouleur+grCout);
					GrapheVoir(pgG,"graphe eulérien non orienté");
					GrapheInverser(pgG);
					bEulerien=bGrapheEulerien(pgG,1,1);
					printf( "Le graphe à %s %s eulérien.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bEulerien) );
					bEulerien=bEulerien && bGrapheEulerier(pgG,1,1);
					GrapheCreer(0,&pgG);
					break;
			case 3: GrapheSymetriqueCreerPondereR(k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0(pgG,"——— Donnée: un graphe non orienté",grCout);
						GrapheCouvrirAvecPrimOuP(pgG,k1Prim,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 4: GrapheSymetriqueCreerPondereR(!k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0(pgG,"——— Donnée: un graphe non orienté",grCout);
						GrapheCouvrirAvecKruskaL(pgG,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 5: GrapheCouvriR();
					break;
			case 6: if (0) for (uSommet=1;uSommet<10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerCourt(pgG,ksSource,pgG->nSommetEnTout,!k1Tas,bkAfficher,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=10;uSommet<=10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheArquer(pgG, 1, 4);
							bGrapheDesarquer(pgG, 4, 2);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerLong(pgG,ksSource,pgG->nSommetEnTout,bkAfficher,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=3;uSommet<10;uSommet++){
						GrapheCreer(uSommet, &pgG);
							GrapheInverser(pgG);
							GrapheVoir2(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCircuit=bGrapheCircuite(pgG);
							t(sC3bp("Il",sUn("y a",bCircuit),"circuit"));
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(4,&pgG);
							GrapheDerouler(pgG);
							GrapheVoir(pgG,sC4b("Le graphe étagé a",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
						GrapheCreer(0,&pgG);
					}
					if (1){
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG,grCouleur+grCout);
							GraphePondererAleatoirement(pgG,5);
							GrapheVoir0(pgG,"Graphe de largeur",grCout);
							bCircuit=bGrapheCheminerAuLarge(pgG,1,6,kV);//***********
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(3,&pgG);
							GrapheSymetriser(pgG,grCouleur+grCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheSymetriser(pgG,grCouleur+grCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG,grCouleur+grCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
					}
					break;
					if (0){
						GrapheCreer(3,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
					}
					break;
			case 7:	{//GrapheQuinconceR & GrapheEtoiler
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
							GrapheQuinconceR(pgG,k1BipartiR);
							GrapheVoir(pgG,"Graphe biparti quinconcé et bipartitionné");
							GrapheEtoiler(pgG,2,3);
							GrapheVoir(pgG,"Graphe biparti quinconcé et bipartitionné et étoilé 2*3");
						GrapheCreer(0,&pgG);
					}
					break;
			case 8:	{//GrapheCliquer
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir(pgG,"Graphe original");
							GrapheCliquer(pgG,4);
							GrapheVoir(pgG,"Graphe original cliqué");
						GrapheCreer(0,&pgG);
					}
					break;
			case 11:{//GrapheQuintesser
						GrapheCreer0(&pgG,kV);
							GrapheQuintesser(pgG,nSommet=3);
							GrapheVoir(pgG,"Graphe quiné");
						GrapheCreer0(&pgG,kF);
					}
					break;
			case 13:	DijkstraAvecOuSansTasCompareR();
					break;
			case 15:	GrapheCreer(4,&pgG);
						GrapheColorer(pgG,1,2,1);
						GrapheColorer(pgG,2,4,2);
						GrapheColorer(pgG,3,2,3);
						GrapheColorer(pgG,3,1,4);
						GrapheColorer(pgG,3,4,5);
						GrapheVoir1(pgG,k1Couleur,"Graphe original");
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER90",!bBof);
						GrapheSymetriser(pgG,grCouleur+grCout);
						GrapheVoir1(pgG,k1Couleur,"Graphe symétrisé");
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER91",bBof);
					GrapheCreer(0,&pgG);
					break;
			case 20:	GrapheGenerer(kcTriominoIncomplet,grCouleur,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 30:	GrapheGenerer(kcTriominoComplet,grCouleur,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 40:
					Titrer("test des types de graphe générées");
					for (nGraphe=grAlpha+1;nGraphe<grOmega;nGraphe++){
						GrapheCreer1(&pgG,nGraphe,0,k1Creer);
							GrapheVoir(pgG,sGraphe(nGraphe));
						GrapheCreer0(&pgG,kF);
					}
					break;
			case 41:
					Titrer("test de nGrapheQuadripoler");
					GrapheCreer1(&pgG,grK,3,k1Creer);
						GrapheVoir(pgG,sGraphe(grK));
						nBof=nGrapheQuadripoler(pgG,grQ0,0,!k1Croiser,grCouleur,&pgH);
						GrapheVoir(pgH,sC2b(sGraphe(grK),"quadripolé") );
					GrapheCreer1(&pgG,grK,3,!k1Creer);
					break;
			case 42:
					Titrer("test de GrapheRenumeroter");
					GrapheCreer1(&pgG,grK,3,k1Creer);
						GrapheSommer(pgG,1);
						GrapheVoir(pgG,sGraphe(grK));
						d2(1,nGrapheDegreh(pgG,1,0));
						GrapheRenumeroter(&pgG,1,4);
						GrapheVoir(pgG,sC2b(sGraphe(grK),"renumeroté") );
						d2(2,nGrapheDegreh(pgG,1,0));
						GrapheRenumeroter(&pgG,4,1);
						d2(3,nGrapheDegreh(pgG,1,0));
						GrapheVoir(pgG,sC2b(sGraphe(grK),"renumeroté") );
					GrapheCreer1(&pgG,grK,3,!k1Creer);
					break;
			default:break;
		}
	Appel1(sC2("GrapheTESTER,test n°",sEnt(iTest)));
}//GrapheTESTER

void GrapheTitreR(graf *pgG,char *sMessage){
	const int kuIndentation=1;
	printf("%s%c(%s, %s, densité %.3f):\n%s",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"),fGrapheDensiteh(pgG),sTab(kuIndentation));
}

void GrapheTranslater(graf *pgG,int nOffset){
	//renumérote tous les sommets de pgG: le sommet n°sX sera renuméroté sX+nOffset.
	int aK,sX;
	Assert1("GrapheTranslater",nOffset>=0);
	if (nOffset>0){
		//d2(uOffset,pgG->nSommetEnTout);
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
		GrapheSommer(pgG,nOffset);
		//d2(uOffset,pgG->nSommetEnTout);
		for (sX=pgG->nSommetEnTout+1;sX>nOffset;sX--)
			pgG->aHed[sX]=pgG->aHed[sX-nOffset];
		for (sX=nOffset;sX>0;sX--)
			pgG->aHed[sX]=1;
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->sSuk[aK]+=nOffset;
	}
}//GrapheTranslater

void GrapheTrierTopologiquement(graf *pgG,int bAfficher){//O(A)
	//effectue un tri topologique et stocke les niveaux des sommets ds pgG->nVal
	const int kbVoir=0;
	int nNiveau[1+pgG->nSommetEnTout];
	int nPred[1+pgG->nSommetEnTout];
	int uCardinal,uS,aK,sX,sY,nNivo=0;
	Assert1("GrapheTrierTopologiquement",bGrapheSimple(pgG));
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)//O(A)
			nPred[sY=pgG->sSuk[aK]]++;
	DequeAllouer(pgG->nSommetEnTout);
		VecteurRazer(nNiveau,1,pgG->nSommetEnTout);//O(S)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			if (!nPred[sX]) DequeEnfiler(sX);
		if (kbVoir) VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
		while (!bDequeVide())//O(A)
			for (nNivo++,uCardinal=nDequeCardinal(),uS=1;uS<=uCardinal;uS++){
				sX=sDequeDefiler();
				nNiveau[sX]=nNivo;
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nPred[sY=pgG->sSuk[aK]]--;
					Assert1("GrapheTrier8",nPred[sY]>=0);
					if (!nPred[sY])
						DequeEnfiler(sY);
				}
			}
		if (kbVoir || bAfficher){
			if (bAfficher)
				printf("%sTri topologique:\n",sTabulation());
			Tabuler(1);
				VecteurVoir1("Niveau",nNiveau,1,pgG->nSommetEnTout);
			Tabuler(-1);
		}
		VecteurCopier(nNiveau,1,pgG->nSommetEnTout,pgG->nVal);
	DequeAllouer(0);
}//GrapheTrierTopologiquement

int bGrapheVidE(graf *pgG){
	int bVide;
	Assert2("bGrapheVidE0",bGrapheAmorceR,bGraphe(pgG));
	bVide=(pgG->nSommetEnTout==0);
	if (bVide)
		Assert1("bGrapheVidE1",pgG->nArcEnTout==0);//sinon,savoir pourquoi
	return(bVide);
}//bGrapheVidE

void GrapheViseR(graf *pgG,char *sMessage){
	//affiche les 5 champs aHed,aDeh,sSuk,sKus et aInv de pgG
	int aK,sX;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s et %s):\n",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	if (pgG->nArcEnTout>0){
		for (printf(" aHed:"),sX=1;sX<=pgG->nSommetEnTout;sX++)
			printf("  (%d,%d)",sX,pgG->aHed[sX]);
		printf("  [%d,%d].\n",sX,pgG->aHed[sX]);
		for (printf(" aDeh:"),sX=1;sX<=pgG->nSommetEnTout;sX++)
			printf("  (%d,%d)",sX,pgG->aDeh[sX]);
		printf("  [%d,%d].\n",sX,pgG->aDeh[sX]);
		printf(" sSuk:");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sSuk[aK]);
		}
		printf(".\n sKus:");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sKus[aK]);
		}
		printf(".\n aInv:");
		for (aK=1;aK<=pgG->nArcEnTout;aK++){
			printf("  (%d,%d)",aK,pgG->aInv[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheViseR

void GrapheVoir(graf *pgG,char *sMessage){
	//énumère les arcs de pgG sous la forme de couples (origine,destination),à raison de kuArcParLigne arcs par ligne
	const int kuArcParLigne=10;
	const int kuIndentation=1;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	//Appel0("GrapheVoir");
		GrapheTitreR(pgG,sMessage);
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					if (pgG->nSommetEnTout<kE2 && pgG->nArcEnTout<kE2)
						printf("  (%2s,%2s)",sEnt(sX),sEnt(pgG->sSuk[aK]));
					else printf("  (%3s,%3s)",sEnt(sX),sEnt(pgG->sSuk[aK]));
					if (aK % kuArcParLigne==0 && aK<pgG->nArcEnTout)
						printf("\n%s",(aK<pgG->nArcEnTout)? sTab(kuIndentation) : "");
				}
		} else printf(" Aucun arc");
		printf(".\n");
	//Appel1("GrapheVoir");
}//GrapheVoir

void GrapheVoir0(graf *pgG,char *sMessage,int nAttribut){
	//affiche les arcs de pgG sous forme de triplets (origine,destination,attributs) ——par exemple,GrapheVoir0(pgG,grCout+grPhi) affichera les champs nCout et nPhi.
	//Appel0("GrapheVoir0");
		Assert3("GrapheVoir",bGrapheAmorceR,pgG!=NULL,sMessage!=0);
		printf("%s à %s et %s spécifié par triplets (sommet,sommet",sMessage,sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel((pgG->nArcEnTout), "arc"));
			if (nAttribut & grCapaMax) printf(",≤capamax");
			if (nAttribut & grCapaMin) printf(",≥capamin");
			if (nAttribut & grCouleur) printf(",çouleur");
			if (nAttribut & grCout) printf(",©coût");
			if (nAttribut & grPoids) printf(",πpoids");
			if (nAttribut & grPhi) printf(",ƒphi");
		printf("):\n   ");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					int sY=pgG->sSuk[aK];
					printf("  (%s,%s",sEnt(sX),sEnt(sY));
					if (nAttribut & grCapaMax) printf("≤%d",pgG->nCapaMax[aK]);
					if (nAttribut & grCapaMin) printf("≥%d",pgG->nCapaMin[aK]);
					if (nAttribut & grCouleur) printf("ç%d",pgG->coulh[aK]);
					if (nAttribut & grCout) printf("©%d",pgG->nCout[aK]);
					if (nAttribut & grPoids) printf("π%d",pgG->nPoids[aK]);
					if (nAttribut & grPhi) printf("ƒ%d",pgG->nPhi[aK]);
					printf(")");
				}
				//printf("\n");
			}
		} else printf(" CE GRAPHE NE CONTIENT À CET INSTANT AUCUNE ARÊTE");
		printf(".\n");
	//Appel1("GrapheVoir0");
}//GrapheVoir0

void GrapheVoir1(graf *pgG,int bDontCouleur,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination,couleur)
	const int kbLitteral=1;
	char cOrigine,cDestination;
	char cCouleur[1+knGrapheCouleurMax+2]={'z','v','r','b','j','n','d','g','h','f','s'};//zéro,vert,rouge,bleu,jaune,f=facultatif
	//Appel0("GrapheVoir1");
		Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
		//printf("%s%c(%s et %s):\n   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		GrapheTitreR(pgG,sMessage);
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					if (kbLitteral){
						//printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
						cOrigine=(bCroit(1,sX,kuMinusculeOffset-1))? 'A'+sX-kuMajusculeOffset : 'a'+sX-kuMinusculeOffset;
						cDestination=(bCroit(1,pgG->sSuk[aK],kuMinusculeOffset-1))? 'A'+pgG->sSuk[aK]-kuMajusculeOffset : 'a'+pgG->sSuk[aK]-kuMinusculeOffset;
						if (bDontCouleur)
							printf(" (%c,%c,%c)",cOrigine,cDestination,cCouleur[pgG->coulh[aK]]);
						else printf(" (%c,%c)",cOrigine,cDestination);
					} else if (bDontCouleur)
						printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
					else printf(" (%c,%c)",cOrigine,cDestination);
				}
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir1");
}//GrapheVoir1

void GrapheVoir2(graf *pgG,char *sMessage){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination)
	//Appel0("GrapheVoir2");
		Assert2("GrapheVoir2",bGrapheAmorceR,sMessage!=0);
		//printf("%s%c(%s et %s):\n",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		GrapheTitreR(pgG,sMessage);
		printf(" direct:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					printf("  (%s,%s",sEnt(sX),sEnt(pgG->sSuk[aK]));
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(" inverse:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
					printf("  (%s,%s",sEnt(sX),sEnt(pgG->sSuk[aK]));
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir2");
}//GrapheVoir2

void GrapheVoir3(graf *pgG,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination,capamin) puis (origine,destination,capamax) puis (origine,destination,cout)
	#define kbArc 1
	//Appel0("GrapheVoir3");
		Assert2("GrapheVoir3",bGrapheAmorceR,sMessage!=0);
		//GrapheVoir2(pgG,sMessage);
		printf("%s%c(%s et %s):   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		printf("\n -capa min:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCapaMin[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(".\n -capa max:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%3d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCapaMax[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(".\n -cout arc:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%3d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCout[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir3");
}//GrapheVoir3
