#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L5 = a(a*.b+b*.a+an.bn) n>1
// Grammaire algébrique:
            // (a) S->a.Q
            // (b) K->aK+B
			// (c) Q->K+P+W
			// (d) P->bP+a
			// (e) W->aWb+ab
// Grammaire homogène:
            // (1) S->A.Q
            // (2) K->U+B
            // (3) P->V+A
			// (4) Q->K+P+W
			// (5) U->A.K
			// (6) V->B.P
			// (7) W->A.X.B
			// (8) X->W+Z
			// (9) Z->A.B
            // (10) A->a
            // (11) B->b
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin);
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
    //K->U+B
	int iFin;
    int bSucces=bU(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bP(int iDebut,int *piFin){
    //P->V+A
	int iFin;
    int bSucces=bV(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->K+P+W
	int iFin;
    int bSucces=bK(iDebut, &iFin) || bP(iDebut,&iFin) || bW(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->A.Q
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bQ(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->A.K
    int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bK(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
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
    //W->A.X.B
	int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bX(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bW

int bX(int iDebut,int *piFin){
    //X->W+Z
	int iFin;
    int bSucces=bW(iDebut,&iFin) || bZ(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bX

int bZ(int iDebut,int *piFin){
    //Z->A.B
    int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bB(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bZ
