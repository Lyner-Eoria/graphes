#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L5 = a2n.bp.(ab)q 0<n<q, p pair
// Grammaire algébrique:
            // (a) S->N.P.Q+P.Q
			// (b) K->P+N
			// (c) N->aa.K.ab+
			// (d) P->bbP+bb
			// (e) Q->ab
			// (d) U->
// Grammaire homogène:
            // (1) S->
            // (2) K->
			// (3) M->
			// (4) N->
			// (5) P->
			// (6) Q->
			// (7) U->
			// (8) V->
			// (9) W->
			// (10) X->
            // (11) A->a
            // (12) B->b
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
    //K->M+N
	int iFin;
    int bSucces=bM(iDebut,&iFin) || bN(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bM(int iDebut,int *piFin){
    //M->A.B.U
	int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bB(iB,&iC) && bU(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
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
    //P->X+N
	int iFin;
    int bSucces=bX(iDebut,&iFin) || bN(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->A.K
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bK(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->Q+V+A
	int iFin;
	int bSucces=bV(iDebut,&iFin) || bQ(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->W+A
	int iFin;
    int bSucces=bW(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bU

int bV(int iDebut,int *piFin){
    //V->A.P
    int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bP(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
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
    //Z->A.B.B
    int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bA(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bZ
