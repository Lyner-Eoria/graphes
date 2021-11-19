#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L4 = an.b*.an n>1
// Grammaire algébrique:
            // (a) S->aaKaa+aaaa
			// (b) K->aKa+P
			// (c) P->bP+b
// Grammaire homogène:
            // (1) S->Q+U
            // (2) K->N+P+W
			// (3) N->A.K.A
			// (4) P->V+B
			// (5) Q->A.A.K.A.A
			// (6) U->A.A.A.A
			// (7) V->B.P
			// (8) W->A.A
            // (9) A->a
            // (10) B->b
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin);
int bM(int iDebut,int *piFin);
int bN(int iDebut,int *piFin);
int bP(int iDebut,int *piFin);
int bQ(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bU(int iDebut,int *piFin);
int bV(int iDebut,int *piFin);
int bW(int iDebut,int *piFin);
int bX(int iDebut,int *piFin);
int bZ(int iDebut,int *piFin);

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
    //K->N+P+W
	int iFin;
    int bSucces=bN(iDebut,&iFin) || bP(iDebut,&iFin) || bW(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bM(int iDebut,int *piFin){
    //M->A.U
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bU(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bM

int bN(int iDebut,int *piFin){
    //N->A.K.A
	int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bK(iB,&iC) && bA(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bN

int bP(int iDebut,int *piFin){
    //P->V+B
	int iFin;
    int bSucces=bV(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->A.A.K.A.A
	int iA=iDebut,iB,iC,iD,iE,iF;
    int bSucces=bA(iA,&iB) && bA(iB,&iC) && bK(iC,&iD) && bA(iD,&iE) && bA(iE,&iF);
    *piFin=(bSucces)?iF:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->Q+U
	int iFin;
    int bSucces=bQ(iDebut,&iFin) || bU(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->A.A.A.A
	int iA=iDebut,iB,iC,iD,iE;
    int bSucces=bA(iA,&iB) && bA(iB,&iC) && bA(iC,&iD) && bA(iD,&iE);
    *piFin=(bSucces)?iE:iDebut;
    return(bSucces);
}//bU

int bV(int iDebut,int *piFin){
    //V->B.P
    int iA=iDebut,iB,iC;
    int bSucces=bB(iA,&iB) && bP(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bV

int bW(int iDebut,int *piFin){
    //W->A.A
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bA(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bW

int bX(int iDebut,int *piFin){
    //X->A.B.P
	int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bB(iB,&iC) && bP(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bX

int bZ(int iDebut,int *piFin){
    //Z->A.B
    int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bA(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bZ
