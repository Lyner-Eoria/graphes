#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L3 = a*.b
// Grammaire algébrique:
            // (a) S->K
            // (b) K->a.K+b
// Grammaire homogène:
            // (1) S->Q+B
            // (2) K->A.P
            // (3) P->K+A
			// (4) Q->P.B
            // (6) A->a
            // (7) B->b
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin);
int bP(int iDebut,int *piFin);
int bQ(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bU(int iDebut,int *piFin);

void Tp1AMORCER(){
    bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1INITIALISER(){
    Assert1("Tp1INITIALISER",bTp1AmorceR);
}//Tp1INITIALISER

void Tp1TesteR(char *sMot,int nLgMax){
    int bEngendre,iFin,bSucces;
    sMOT=sMot;
    bSucces=bS(0,&iFin);
    bEngendre=bSucces && nChaineLg(sMOT)==iFin;
    if (bEngendre)
        printf("%s: %s %s engendré par la grammaire décrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
    if (nChaineLg(sMot)<nLgMax){
        Tp1TesteR(sC2(sMot,"a"),nLgMax);
        Tp1TesteR(sC2(sMot,"b"),nLgMax);
    }
}//Tp1TesteR

void Tp1TESTER(int iTest){
    int bEngendre,iFin,bSucces;
    Assert1("Tp1TESTER0",bTp1AmorceR);
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 0: Tp1TesteR("",10);break;
            case 1: sMOT="aab";break;
            case 2: sMOT="aaba";break;
            default:Assert1("Tp1TESTER1",0);break;
        }
    if (iTest>0){
        bSucces=bS(0,&iFin);
        bEngendre=bSucces && nChaineLg(sMOT)==iFin;
        printf("%s: %s %s engendré par la grammaire décrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
    }
}//Tp1TESTER

int bA(int iDebut,int *piFin){
    //A->a
    int bSucces = sMOT[iDebut]=='a';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bA

int bB(int iDebut,int *piFin){
    //B->b
    int bSucces = sMOT[iDebut]=='b';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bB

int bK(int iDebut,int *piFin){
    //K->A.P
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bP(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bK

int bP(int iDebut,int *piFin){
    //P->K+A
	int iFin;
    int bSucces=bK(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->P.B
	int iA=iDebut,iB,iC;
    int bSucces=bP(iA,&iB) && bB(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->Q+B
	int iFin;
    int bSucces=bQ(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->B.Q
    int iA=iDebut,iB,iC;
    int bSucces=bB(iA,&iB) && bQ(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bU
