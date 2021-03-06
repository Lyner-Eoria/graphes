#include "Kit.h"
#include "Alex.h"
#include "Erreur.h"
#define knPileMaX 50
int bErreurAmorceR;
int ipErreuR;//ip = index de pile
struct{int eBug;int uLxm;} nPilE[1+knPileMaX];
enum niErreuR {niAlphA,niLexicaL,niSyntaxiquE,niSemantiquE,niOmegA};

void ErreurAfficheR(int ipErreur);
int nErreurNiveaU(int ipErreur);

void ErreurAfficheR(int ipErreur){
	//affiche en clair l'erreur numéro ipErreur;ip = index de pile
	char *sErreur;
	Assert1("ErreurAfficheR",bCroit(1,ipErreur,knPileMaX));
	sErreur="erreur système";//signifie que votre compilateur se plante
	AlexDenoncer(nPilE[ipErreur].uLxm);
	switch (nPilE[ipErreur].eBug) {
		case  eAlexInconnu:	    sErreur="lexème inconnu";break;
		case  eAlexEntieR:	    sErreur="lexème inconnu;si c'est un entier basé, format ([0..b-1]+)'b, en appelant b la base,0<b<10";break;
		case  eAlexReel:	    sErreur="lexème inconnu;si c'est un réel, 1 seul point entre parties entière et fractionnaire,eg 0.0";break;
		
		case  eSyntChosE:		sErreur="somme ou produit ou terme attendu";break;
		case  eSyntInstruction:	sErreur="instruction attendue";break;
		case  eSyntLivre:		sErreur="livre attendu (type texte,ni blanc ni apostrophe ni trait d'union)";break;
		case  eSyntNom:			sErreur="nom attendu (type identificateur)";break;
		case  eSyntProgramme:	sErreur="instruction ou fin de fichier attendue";break;
		case  eSyntSeparateur:	sErreur="séparateur attendu (ajouter le symbole \";\")";break;
		case  eSyntSuite:		sErreur="inscription ou interdiction attendue";break;

		case  eSemAffichage:	sErreur="identifiant inconnu";break;
		case  eSemAffectation:	sErreur="nom attendu pour affectation";break;
		case  eSemDate:			sErreur="date attendue (au format JJMMAA)";break;
		case  eSemDelaiTropLong:sErreur="délai d'interdiction limité à 99 jours maximum";break;//*********************************
		case  eSemDoublon:		sErreur="ce livre est déjà présent en bibliothèque";break;
		case  eSemHoraire:		sErreur="horaire au format \"hh.mm\" avec 0≤h≤23 et 0≤mm≤59 attendu";break;
		case  eSemIdentifiant:	sErreur="identifiant sans valeur affectée";break;
		case  eSemLivreDispo:   sErreur="ce livre est actuellement disponible, le réserver est inutile";break;
		case  eSemInscrit:		sErreur="personne déjà inscrite";break;
		case  eSemLivreInconnu:	sErreur="le livre cité est inconnu";break;
		case  eSemLivrePris:	sErreur="ce livre existe mais il ne peut pas être emprunté car il est déjà pris";break;
		case  eSemNonInscrit:	sErreur="personne non inscrite";break;
		case  eSemPrix:			sErreur="prix NON NUL attendu";break;
		case eSyntTerme:		sErreur="terme attendu,ie entier ou expression";break;
		default:break;
	}
	printf(": %s (niveau %s).",sPhrase0(sErreur),sItem("lexical,syntaxique,sémantique",nErreurNiveaU(ipErreur)));
}//ErreurAfficheR

void ErreurAfficher(int uLigne){
	//affiche le libellé de toutes les erreurs détectées sur la ligne uLigne
	int ipErreur;
	for (ipErreur=1;ipErreur<=ipErreuR;ipErreur++)
		if (nAlexLigne(nPilE[ipErreur].uLxm)==uLigne)
			ErreurAfficheR(ipErreur);
}//ErreurAfficher

void ErreurAfficherTout(){
	//affiche à la console les erreurs éventuelles qui ont été empilées pendant la compilation
	int ipErreur;
	Assert2("ErreurAfficherTout",bErreurAmorceR,ipErreuR>=0);
	for (ipErreur=1;ipErreur<=ipErreuR;ipErreur++)
		ErreurAfficheR(ipErreur);
	Ligne();
}//ErreurAfficherTout

void ErreurAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	ipErreuR=0;
	bErreurAmorceR=kV;
}//ErreurAMORCER

void ErreurEmpiler(int nErreurNumero, int nLexeme){
	//empile le nErreurNumero et le nLexeme où l'erreur a été détectée (donc l'erreur concerne ce lexème ou l'un de ses prédécesseurs) 
	int bDebug=kF;
	Assert3("ErreurEmpiler",bErreurAmorceR,bCroitStrict(eLimite0,nErreurNumero,eLimite1),bAlexLexeme(nLexeme));
	if (bDebug){
		d2(nErreurNumero,nLexeme);
		AlexDenoncer(nLexeme);
	}
	ipErreuR++;
	nPilE[ipErreuR].eBug=nErreurNumero;
	nPilE[ipErreuR].uLxm=nLexeme;
	Assert1("ErreurEmpiler1",nErreurNiveaU(ipErreuR)>0);
}//ErreurEmpiler

int bErreurEmpiler(int nErreurNumero, int nLexeme){
	//empile le nErreurNumero et le nLexeme où l'erreur a été détectée (donc l'erreur est sur ce lexème ou avant celui-ci) 
	ErreurEmpiler(nErreurNumero,nLexeme);
	return(1);
}//bErreurEmpiler

int nErreurEnTout(){
	Assert2("nErreurEnTout",bErreurAmorceR,ipErreuR>=0);
	return(ipErreuR);
}//nErreurEnTout

void ErreurINITIALISER(){
	//relance le présent module
	Assert1("ErreurINITIALISER",bErreurAmorceR);
	ipErreuR=0;
}//ErreurINITIALISER

int nErreurNiveaU(int ipErreur){
	int nNiveau=0;
	if ( bCroitStrict(eAlex0,nPilE[ipErreur].eBug,eAlex1) )
		nNiveau=niLexicaL;
	if ( bCroitStrict(eSynt0,nPilE[ipErreur].eBug,eSynt1) )
		nNiveau=niSyntaxiquE;
	if ( bCroitStrict(eSem0,nPilE[ipErreur].eBug,eSem1) )
		nNiveau=niSemantiquE;
	return(nNiveau);
}//nErreurNiveaU

void ErreurTESTER(int iTest){
	//teste le présent module
	Appel0(sC2("ErreurTESTER,test n°",sEnt(iTest)));
		Assert1("ErreurTESTER",bErreurAmorceR);
		switch (iTest) {
			case  1:	break;
			default:break;
		}
	Appel1(sC2("ErreurTESTER,test n°",sEnt(iTest)));
}//ErreurTESTER

/*
int bAlexHoraire(int uLexeme){
	#define kuHeureHeurePointMinuteMinuteLg 5
	int bHoraire;
	float rHoraire;
	int nMinute;
	char sLexeme[knByteLiM];
	bHoraire=bAlexReel(uLexeme);
	if (bHoraire){
		CodeSourceTrancheR(lxmChainE[uLexeme].indexdebut,lxmChainE[uLexeme].indexfin,kF,sLexeme);
		//tt("sLexeme",sG(sLexeme));
		bHoraire=bHoraire && (nChaineLg(sLexeme)==kuHeureHeurePointMinuteMinuteLg);
		if (bHoraire){
			sscanf(sLexeme,"%f5.2",&rHoraire);
			//tr("rHoraire",rHoraire);
			nMinute=trunc(rHoraire*100);
			nMinute=nMinute%100;
			//sd("nMinute",nMinute);
			bHoraire=bHoraire && bCroit(0,nMinute,59);
			//compléter le code pour les heures
		}
	}
	return(bHoraire);
}//bAlexHoraire
*/
