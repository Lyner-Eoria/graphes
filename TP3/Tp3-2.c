#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L2 = (a+b)+, 2x plus de a que de b
	// L2' = (a+b)+
// Grammaire algébrique:
			// (a) S->K(x,y).R(x,y)
			// (b) K(x,y)->K1(x,y)+K2(x,y)+A(x,y)+B(x,y)
			// (c) K1(x+1,y)->A(m,n)K(x,y)
			// (d) K2(x,y+1)->B(m,n)K(x,y)
			// (e) A(1,0)->a
			// (f) B(0,1)->b
// Grammaire homogène:
			// (1) S->K(x,y).R(x,y)
			// (2) K(x,y)->P(x,y)+Q(x,y)+A(x,y)+B(x,y)
			// (4) P(x+1,y)->A(m,n).K(x,y)
			// (5) Q(x,y+1)->B(m,n).K(x,y)
			// (6) A(1,0)->a
			// (7) B(0,1)->b

int bA(int iDebut,int *piFin, int *paX, int *paY);
int bB(int iDebut,int *piFin, int *paX, int *paY);
int bK(int iDebut,int *piFin, int *paX, int *paY);
int bM(int iDebut,int *piFin, int *paX, int *paY);
int bN(int iDebut,int *piFin, int *paX, int *paY);
int bP(int iDebut,int *piFin, int *paX, int *paY);
int bQ(int iDebut,int *piFin, int *paX, int *paY);
int bS(int iDebut,int *piFin);
int bU(int iDebut,int *piFin, int *paX, int *paY);
int bV(int iDebut,int *piFin, int *paX, int *paY);
int bW(int iDebut,int *piFin, int *paX, int *paY);
int bX(int iDebut,int *piFin, int *paX, int *paY);
int bZ(int iDebut,int *piFin, int *paX, int *paY);

int bR(int aX,int aY);

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

int bA(int iDebut,int *piFin, int *paX, int *paY){
	//A->a
	int bSucces = sMOT[iDebut]=='a';
	*piFin = (bSucces) ? iDebut+1 : iDebut;
	*paX = 1;
	*paY = 0;
	return(bSucces);
}//bA

int bB(int iDebut,int *piFin, int *paX, int *paY){
	//B->b
	int bSucces = sMOT[iDebut]=='b';
	*piFin = (bSucces) ? iDebut+1 : iDebut;
	*paX = 0;
	*paY = 1;
	return(bSucces);
}//bB

int bK(int iDebut,int *piFin, int *paX, int *paY){
	//K(x,y)->P(x,y)+Q(x,y)+A(x,y)+B(x,y)
	int iFin;
	int bSucces=bP(iDebut,&iFin, paX, paY) || bQ(iDebut,&iFin, paX, paY) || bA(iDebut,&iFin, paX, paY) || bB(iDebut,&iFin, paX, paY);
	*piFin=(bSucces)?iFin:iDebut;
	return(bSucces);
}//bK

int bP(int iDebut,int *piFin, int *paX, int *paY){
	//P(x+1,y)->A(m,n).K(x,y)
	int iA=iDebut,iB,iC, aM, aN, aX, aY;
	int bSucces=bA(iA,&iB, &aM, &aN) && bK(iB,&iC, &aX, &aY);
	*piFin=(bSucces)?iC:iDebut;
	*paX = aX + 1;
	*paY = aY;
	return(bSucces);
}//bP

int bQ(int iDebut,int *piFin, int *paX, int *paY){
	//Q(x,y+1)->B(m,n).K(x,y)
	int iA=iDebut,iB,iC, aM, aN, aX, aY;
	int bSucces=bB(iA,&iB, &aM, &aN) && bK(iB,&iC, &aX, &aY);
	*piFin=(bSucces)?iC:iDebut;
	*paX = aX;
	*paY = aY + 1;
	return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
	//S->K(x,y).R(x,y)
	int aX,aY;
	int iA=iDebut,iB;
	int bSucces=bK(iA,&iB, &aX, &aY) && bR(aX,aY);
	*piFin=(bSucces)?iB:iDebut;
	return(bSucces);
}//bS

int bR(int aX,int aY) {
	return aY * 2 == aX;
}