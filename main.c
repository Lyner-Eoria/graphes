#include "Kit.h"
#include "Abe.h"
#include "Alex.h"
#include "Asynt.h"
#include "Code.h"
#include "Deque.h"
#include "Erreur.h"
#include "Graphe.h"
#include "Couplage.h" //APRES Graphe.h
#include "Foret.h"
#include "Tas.h"
#include "Tds.h"
#include "Ticket.h"
#include "Tp1.h"
#include "Tp2.h"
#include "Tp3.h"
#include "Tp4.h"

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	KitAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Kit mentionnés dans les include de main.c
		AlexAMORCER();
		AsyntAMORCER();
		ErreurAMORCER();
		GrapheAMORCER();//avant FlotAMORCER()
		CouplageAMORCER();
		DequeAMORCER();
		ForetAMORCER();
		TasAMORCER();
		TdsAMORCER();
		TicketAMORCER();
		Tp1AMORCER();
		Tp2AMORCER();
		Tp3AMORCER();
		Tp4AMORCER();
}//ModuleAmorceR

void DiagnostiqueR(char *sContexte,int bSucces){
	printf("Le code source %s valide au niveau %s%s",sEst(bSucces),sContexte,sChoix0(!bSucces,sC2(" ",sP(sPluriel(nErreurEnTout(),"erreur")))));
	printf("%c\n",(bSucces)?'.':':');
}//DiagnostiqueR

void CompileR(int nSource){
	const int bEclaireur=kV;
	int bSourceConnu=kV,bSucces;
	char *sSource;
	//Grammaire algébrique LL(1):
		//Programme->Instructions || FinFichier
		//		Instructions->Instruction Separateur Programme
		//Instruction->Emprunt || Reservation || Achat || Restitution || Radiation || Affectation  || Affichage || Autre
		//		Emprunt->"<" Livre Nom			  Livre répertorié et Nom en TDS
		//		Reservation->"?" Livre Nom		  Livre répertorié et Nom en TDS
		//		Achat->Prix Livre				  réel>0 et Livre non encore répertorié
		//		Restitution->">" Livre Nom		  Livre répertorié et Nom en TDS
		//		Radiation->Nom					  Nom en TDS
		//		Affectation->Expression Nom       Nom en TDS
		//		Affichage->"[" Identifiant"]"	  Identifiant en TDS
		//		Autre->Entier Suite				  Entier est une durée>0 pr une Interdiction et une date pr une inscription
		//Suite->Interdiction || Inscription
		//		Interdiction->Livre				  Livre répertorié
		//		Inscription->Nom				  Nom hors TDS
		//		Expression->"(" Chose ")"
		//		Chose->Somme || Produit || Terme || Expression
		//		Somme->Terme "+" Chose
		//		Produit->Terme "*" Chose
		//		Terme->Entier || Identifiant
		//		Nom->Identificateur
		//		Identifiant->Identificateur		déjà affecté,dc en TDS
	nSource=1;
	switch (nSource){
		case 0: sSource="1234     (3)@T1 Trac;(3..14) ;52 Trec $";
				break;
		case 1: sSource="(7) Sept;(3+Sept) Dix ;[Dix] ;[Sept] ;(Dix*(Sept+3)) Cent;[Cent] ;";
				break;
		case 2: //livre est acheté;LUI et ELLE s'inscrivent;Lui emprunte le livre et le restitue puis ELLE l'emprunte
				sSource="19.90 livre;8.05 autrelivre;240317 LUI;250317 ELLE; < livre LUI; >livre LUI; < livre ELLE;";//***********
				break;
		case 3: //1 bug sémantique: livre est acheté;LUI et ELLE s'inscrivent;Lui emprunte le livre donc ELLE ne peut pas l'emprunter
				sSource="19.90 livre; 240317 LUI; 250317 ELLE; < livre LUI; < livre ELLE;";
				break;
		case 4: //livre est acheté;LUI et ELLE s'inscrivent;Lui emprunte le livre donc ELLE ne peut pas l'emprunter
				sSource="19.90 livre; 240317 LUI; 50 livre; 2500 livre; < livre LUI; < livre ELLE;";
				break;
		case 7: sSource="240317 ELLE; 0.5 dune; < dune ELLE; 0 dune; < dune ELLE; > dune ELLE ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				break;
		case 8: sSource="240218 MOI; 0.5 livre; < livre MOI; 0 elle; < livre MOI; > livre MOI ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				break;
		default: bSourceConnu=kF;printf("Clause default: code source n°%d inconnu.\n",nSource);break;
	}
	bSucces=bSourceConnu;
	bSucces=bSucces && bAlexAnalyser(sSource); DiagnostiqueR("lexical",bSucces);
	bSucces=bSucces && bAsyntAnalyser(mAsyntSyntaxique,bEclaireur); DiagnostiqueR(sC2b("syntaxique",sP(sC2b((bEclaireur)?"avec":"sans","éclaireur"))),bSucces);
	bSucces=bSucces && bEclaireur && bAsyntAnalyser(mAsyntSemantique,bEclaireur); DiagnostiqueR("sémantique",bSucces);
	bSucces=bSucces && bEclaireur && bAsyntAnalyser(mAsyntGeneration,bEclaireur); DiagnostiqueR("génération du code",bSucces);
	if (bSourceConnu)
		AlexAfficher();
	else ErreurAfficherTout();
	if (bSucces)//lancer l'exécution du code C généré par le compilateur à partir de sSource
		CodeExecuter();
}//CompileR

void MacroTesteR() {
	int bSucces=1,uE=5;
	float rA=3.1, rB=5.869;
	char *sBonjour="BONJOUR";char *sBonsoir="BONSOIR";char *sSalut="SALUT";
	b(bSucces);
	d(uE);
	d(uE/(uE-3));
	d2(uE,uE-1);
	d3(uE,uE-1,uE-2);
	s(sBonjour);
	s2(sBonjour,sBonsoir);
	s3(sBonjour,sBonsoir,sSalut);
	f(rA);
	f2(rA,rB);
	uE=123456789;
	d(uE);
}//MacroTesteR

#define RESET		0
#define BLACK 		0
#define RED			1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7
char *colors[] = {"BLACK","RED","GREEN","YELLOW" "BLUE", "MAGENTA","CYAN","WHITE","EXIT"};
void textcolor(int attr, int fg, int bg)
{	char sCouleur[13+7];
	//char cCrochet0='[';char cCrochet1=']';
	d3(attr,fg,bg);
	sprintf(sCouleur, "%c[[%d;%d;%dm", 0x1B, 1, 31, 44);
	//printf("%c%c%c;%c%c;%c%c%c%s\n",0x1B, cCrochet0,cCrochet0, 1, 31, 44,cCrochet1,cCrochet1,"SALUT MON GARS");
	//sprintf(sCouleur, "%c[[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s%s\n",sCouleur,"NOUVELLE COULEUR");
}

void SPIgrapH(){
	graf *pgG;
	int bVoir=1;
	char *sVille="Ajaccio,Bayonne,Caen,Dunkerque,Evreux,Falaise,Genève,Hyères,Issoudun,Jarnac,Kourou,Le Mans,Marseille,Nice,Orléans,Paris,Quimper,Rennes,Strasbourg,Toulouse,Uzès,Valence,Wattrelos,Xeuilley,Yvetot,Zoza";
	const int knVilleEnTout=nItem(sVille);
	//ci-dessous,chaque arc contient successivt: initiale ville de Départ, initiale ville d'Arrivée, distance (3 décits), séparateur ":", hauteur max(1 décit), largeur max (1 décit), longueur max (1 ou 2 décits).
	char *sRoute0="AZ115:9999,BC760:9999,BD1063:9999,BG957:9999,BJ360:9999,BL830:9999,BP769:9999,BS1252:1234,BT766:9999,DW180:9999,EL150:9999,FR110:9999,HM120:9999";
	char *sRoute1="IL290:9999,LP216:9999,LR150:9999,LX530:9999,MN190:9999,MU120:9999,MV360:9999,OP129:9999,PM809:9999,PS456:9999,QR250:9999,RY320:9999";
	char *sRoute=sC2v(sRoute0,sRoute1);
	const int knRouteEnTout=nItem(sRoute);
	//ci-dessous,chaque colis est décrit par: nature du colis, séparateur ":", hauteur max(1 décit), largeur max (1 décit), longueur max (1 ou 2 décits).
	char *sColisCote="Anaconda:116,Bulldozer:6830,Catamaran:123,Dragster:123,Éléphant:132,Fusée:123,Girafe:123,Hydravion:366,Longrine:133,Mobile home:132,Péniche:123,Réacteur:123,Semi-remorque:132,Titanosaure:123";
	const int kuColisMax=nItem(sColisCote);
	typedef struct{ int hau;int laj;int lon;} cote;//dc 3 cotes
	cote nGabarit[1+knRouteEnTout];//3 cotes par route
	cote nCote[1+kuColisMax];//3 cotes par colis
	//d(nItem(sColisCote));
	//pgG,nGabarit[]:=description des routes: distances et gabarits
		GrapheCreer(-knVilleEnTout,&pgG);//génère un graphe à knSommetEnTout sommets et aucun arc.
		for (int uItem=1;uItem<=knRouteEnTout;uItem++){
			char *sArc=sItem(sRoute,uItem);
			if (bVoir) sd2(sArc,uItem,nChaineLg(sArc));
			Assert1("SPIgrapH route, taille de l'item incorrecte",bCroit(10,nChaineLg(sArc),11) );
			int sX=sArc[0]-'@';
			int sY=sArc[1]-'@';
			int nKm=iChaine(sChainon(sArc,2,5));
			if (bVoir) d3(sX,sY,nKm);
			if (bVoir) s2(sItem(sVille,sX),sItem(sVille,sY));
			GrapheArquer0(pgG,sX,sY,grCout,nKm);//crée l'arc (sX,sY) et le pondère avec nKm (champ .nCout)
			int aK=nGrapheArc(pgG,sX,sY);//numéro de l'arc dans pgG
			nGabarit[aK].hau=iChaine(sChainon(sArc,7,7));
			nGabarit[aK].laj=iChaine(sChainon(sArc,8,8));
			nGabarit[aK].lon=iChaine(sChainon(sArc,9,-1));
			if (bVoir) d4(aK,nGabarit[aK].hau,nGabarit[aK].laj,nGabarit[aK].lon);
			Assert2("SPIgrapH route, cote incorrecte",nGabarit[aK].hau>0,bCroit(1,nGabarit[aK].laj,nGabarit[aK].lon) );
		}
		GrapheVoir(pgG,"pgG");
	//nCote[]:=cotes de chaque colis
		for (int uColis=1;uColis<=kuColisMax;uColis++){
			char *sColis=sItem(sColisCote,uColis);
			int nSeparateur=mChainePos(':',sColis);
			if (bVoir) s(sColis);
			Assert1("SPIgrapH colis, séparateur absent ou mal placé",nSeparateur>0);
			nCote[uColis].hau=iChaine(sChainon(sColis,nSeparateur+0,nSeparateur+1));
			nCote[uColis].laj=iChaine(sChainon(sColis,nSeparateur+1,nSeparateur+2));
			nCote[uColis].lon=iChaine(sChainon(sColis,nSeparateur+2,-1));
			if (bVoir) sd3(sColis,nCote[uColis].hau,nCote[uColis].lon,nCote[uColis].laj);
		}
}//SPIgrapH

int main (int argc, const char * argv[]) {
	Regler();
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
		//for (i=2;i<=2;i++) CompileR(i);
		//BrouillonTESTER(4);
		//textcolor(RED, GREEN, BLUE);
		//textcolor(RESET, WHITE, BLACK);
		//CompileR(1);
		//CatriceTESTER(7);
		//EntierTESTER(1);
		//TritopeR();
		//ColorieR();
		 Tp1TESTER(0);
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}
