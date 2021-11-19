#include "Kit.h"
#include "Tp1.h"
char *sMOT;
int bTp1AmorceR=kF;
// L3 = am.bn.am, 0<m<n, remonter nb de a en S
	// L3' = am.bm.b+.am, m>0
		//L3'' = a+.b+.a+
// Grammaire algébrique:
			// (a) S(x+z)->K(x).P(y).K(z).R(x,y,z)
			// (b) K(x)->K1(x)+K2(x)
			// (c) K1(x+1)->A.K(x)
			// (d) K2(1)->A
			// (e) P(x)->P1(x)+P2(x)
			// (f) P1(x+1)->B.P(x)
			// (g) P2(1)->B
			// (h) A->a
			// (i) B->b
// Grammaire homogène:
			// (1) S(x+z)->K(x).P(y).K(z).R(x,y,z)
			// (2) K(x)->U(x)+Q(x)
			// (4) P(x)->V(x)+W(x)
			// (5) Q(1)->A+A
			// (6) U(x+1)->A.K(x)
			// (7) V(x+1)->B.P(x)
			// (8) W(1)->B+B
			// (9) A->a
			// (10) B->b

int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin, int *paN);
int bM(int iDebut,int *piFin);
int bN(int iDebut,int *piFin);
int bP(int iDebut,int *piFin, int *paN);
int bQ(int iDebut,int *piFin, int *paN);
int bS(int iDebut,int *piFin, int *paN);
int bU(int iDebut,int *piFin, int *paN);
int bV(int iDebut,int *piFin, int *paN);
int bW(int iDebut,int *piFin, int *paN);
int bX(int iDebut,int *piFin);
int bZ(int iDebut,int *piFin);

int bR(int aX,int aY,int aZ);

void Tp1AMORCER(){
	bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1INITIALISER(){
	Assert1("Tp1INITIALISER",bTp1AmorceR);
}//Tp1INITIALISER

void Tp1TesteR(char *sMot,int nLgMax){
	int bEngendre,iFin,bSucces, aN;
	sMOT=sMot;
	bSucces=bS(0,&iFin, &aN);
	bEngendre=bSucces && nChaineLg(sMOT)==iFin;
	if (bEngendre)
		printf("%s: %s %s engendré par la grammaire décrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
	if (nChaineLg(sMot)<nLgMax){
		Tp1TesteR(sC2(sMot,"a"),nLgMax);
		Tp1TesteR(sC2(sMot,"b"),nLgMax);
	}
}//Tp1TesteR

void Tp1TESTER(int iTest){
	int bEngendre,iFin,bSucces, aN;
	Assert1("Tp1TESTER0",bTp1AmorceR);
	//sMOT:=mot à tester selon iTest
		switch(iTest){
			case 0: Tp1TesteR("",10);break;
			case 1: sMOT="aab";break;
			case 2: sMOT="aaba";break;
			default:Assert1("Tp1TESTER1",0);break;
		}
	if (iTest>0){
		bSucces=bS(0,&iFin, &aN);
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
	//K(x)->U(x)+Q(x)
	int iFin;
	int bSucces=bU(iDebut,&iFin, paN) || bQ(iDebut,&iFin, paN);
	*piFin=(bSucces)?iFin:iDebut;
	return(bSucces);
}//bK

int bP(int iDebut,int *piFin, int *paN){
	//P(x)->V(x)+W(x)
	int iFin;
	int bSucces=bV(iDebut,&iFin, paN) || bW(iDebut,&iFin, paN);
	*piFin=(bSucces)?iFin:iDebut;
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

int bS(int iDebut,int *piFin, int *paN){
	//S(x+z)->K(x).P(y).K(z).R(x,y,z)
	int aX,aY,aZ;
	int iA=iDebut,iB,iC,iD;
	int bSucces=bK(iA,&iB, &aX) && bP(iB,&iC, &aY) && bK(iC,&iD, &aZ) && bR(aX,aY,aZ);
	*piFin=(bSucces)?iD:iDebut;
	*paN = aX+aY;
	return(bSucces);
}//bS

int bU(int iDebut,int *piFin, int *paN){
	//U(x+1)->A.K(x)
	int aX;
	int iA=iDebut,iB,iC;
	int bSucces=bA(iA,&iB) && bK(iB,&iC, &aX);
	*piFin=(bSucces)?iC:iDebut;
	*paN = aX+1;
	return(bSucces);
}//bU

int bV(int iDebut,int *piFin, int *paN){
	//V(x+1)+>B.P(x)
	int aX;
	int iA=iDebut,iB,iC;
	int bSucces=bB(iA,&iB) && bP(iB,&iC, &aX);
	*piFin=(bSucces)?iC:iDebut;
	*paN = aX+1;
	return(bSucces);
}//bV

int bW(int iDebut,int *piFin, int *paN){
	//W(1)->B+B
	int iFin;
	int bSucces=bB(iDebut,&iFin) || bB(iDebut,&iFin);
	*piFin=(bSucces)?iFin:iDebut;
	*paN = 1;
	return(bSucces);
}//bW

int bR(int aX,int aY, int aZ) {
	return aX == aZ && aY > aX;
}