#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L1 = an, n carré
	// L1' = a+
// Grammaire algébrique:
            // (a) S->K(n).R(n)
			// (b) K(n)->K1(n)+K2(n)
			// (c) K1(n+1)->a.K(n)
			// (d) K2(1)->a
// Grammaire homogène:
            // (1) S->K(n).R(n)
            // (2) K(n)->P(n)+Q(n)
			// (4) P(n+1)->A.K(n)
			// (5) Q(1)->A+A
            // (6) A->a
            // (7) B->b

int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin, int *paN);
int bM(int iDebut,int *piFin, int *paN);
int bN(int iDebut,int *piFin, int *paN);
int bP(int iDebut,int *piFin, int *paN);
int bQ(int iDebut,int *piFin, int *paN);
int bS(int iDebut,int *piFin);
int bU(int iDebut,int *piFin, int *paN);
int bV(int iDebut,int *piFin, int *paN);
int bW(int iDebut,int *piFin, int *paN);
int bX(int iDebut,int *piFin, int *paN);
int bZ(int iDebut,int *piFin, int *paN);

int bR(int N);

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

int bK(int iDebut,int *piFin, int *paN){
    //K(n)->P(n)+Q(n)
	int iFin;
    int bSucces=bP(iDebut,&iFin, paN) || bQ(iDebut,&iFin, paN);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bM(int iDebut,int *piFin, int *paN){
    //M->A.U
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bA(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bM

int bN(int iDebut,int *piFin, int *paN){
    //N->A.K.A
	int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bA(iB,&iC) && bA(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bN

int bP(int iDebut,int *piFin, int *paN){
    //P(n+1)->A.K(n)
	int iA=iDebut,iB,iC, aK;
    int bSucces=bA(iA,&iB) && bK(iB,&iC, &aK);
    *piFin=(bSucces)?iC:iDebut;
	*paN = aK + 1;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin, int *paN){
    //Q(1)->A+A
	int iFin;
    int bSucces=bA(iDebut,&iFin) || bA(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
	*paN = 1;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->K(n).R(n)
	int aN;
	int iA=iDebut,iB;
    int bSucces=bK(iA,&iB, &aN) && bR(aN);
    *piFin=(bSucces)?iB:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin, int *paN){
    //U->A.A.A.A
	int iA=iDebut,iB,iC,iD,iE;
    int bSucces=bA(iA,&iB) && bA(iB,&iC) && bA(iC,&iD) && bA(iD,&iE);
    *piFin=(bSucces)?iE:iDebut;
    return(bSucces);
}//bU

int bV(int iDebut,int *piFin, int *paN){
    //V->B.P
    int iA=iDebut,iB,iC;
    int bSucces=bB(iA,&iB) && bA(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bV

int bW(int iDebut,int *piFin, int *paN){
    //W->A.A
	int iA=iDebut,iB,iC;
    int bSucces=bA(iA,&iB) && bA(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bW

int bX(int iDebut,int *piFin, int *paN){
    //X->A.B.P
	int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bB(iB,&iC) && bA(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bX

int bZ(int iDebut,int *piFin, int *paN){
    //Z->A.B
    int iA=iDebut,iB,iC,iD;
	int bSucces=bA(iA,&iB) && bA(iB,&iC) && bB(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bZ

int bR(int aN) {
	return bCarreh(aN);
}