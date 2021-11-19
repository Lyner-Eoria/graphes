#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L3 = a(aba*+(ab)*)
	// a+a2b(a+ + ab+)
// Grammaire algébrique:
			// (a) S->aabK+aabP+a
			// (b) K->aK+a
			// (c) P->abP+ab
// Grammaire homogène:
            // (1) S->Q+A
            // (2) K->M+A
			// (3) M->A.K
			// (4) N->A.B
			// (5) P->V+N
			// (6) Q->A.A.B.U
			// (7) U->K+P
			// (8) V->A.B.P
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
    //K->M+A
	int iFin;
    int bSucces=bM(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bM(int iDebut,int *piFin){
    //M->A.K
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bK(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bM

int bN(int iDebut,int *piFin){
    //N->A.B
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bB(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bN

int bP(int iDebut,int *piFin){
    //P->V+N
	int iFin;
    int bSucces=bV(iDebut,&iFin) || bN(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->A.A.B.U
	int iA=iDebut,iB,iC,iD,iE;
	int bSucces=bA(iA,&iB) && bA(iB,&iC) && bB(iC,&iD)&& bU(iD,&iE);
    *piFin=(bSucces)?iE:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->Q+A
	int iFin;
	int bSucces=bQ(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->P+K
	int iFin;
	int bSucces=bP(iDebut,&iFin) || bK(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bU

int bV(int iDebut,int *piFin){
    //V->A.B.P
	int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bB(iB,&iC) && bP(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bV

int bW(int iDebut,int *piFin){
    //W->A.U
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bU(iB,&iC);
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
    //Z->A.A.B
    int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bA(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bZ
