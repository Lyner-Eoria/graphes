#define knGrapheCouleurMax 9
#define kuGrapheSommetLim 300000//360 frontiere8
#define kuGrapheArcLim (kuGrapheSommetLim*3)
//attributs pour l'algorithme de Dijkstra
#define grCheminLePlusCourt 1
#define grCheminLePlusLarge 2
#define grCheminLePlusLong 3
#define grCheminLePlusCourtEnMoyenne 4
#define grArbreCouvrant 5
//attributs de GrapheVoir0
#define grCapaMax 1
#define grCapaMin 2
#define grCouleur 4
#define grCout 8
#define grPoids 16
#define grPhi 32
#define GrapheNom  "grAlpha,gr2Aile,gr2Croix,gr2Diam,gr2P,grC,grC4b,grD,grE2,grE3,grK,grL4,grP,grPt,grPtr,grQ0,grQ1,grS,grT,grT2,grU,grW,grXor,grX,grXX,grXY,grZ,grOmega"
#define GrapheType {grAlpha,gr2Aile,gr2Croix,gr2Diam,gr2P,grC,grC4b,grD,grE2,grE3,grK,grL4,grP,grPt,grPtr,grQ0,grQ1,grS,grT,grT2,grU,grW,grXor,grX,grXX,grXY,grZ,grOmega}
enum eGrapheOrientation    {goAlpha,goMixte,goOrienteh,goNonOrienteh,goOmega};
#define sGrapheOrientation "goAlpha,goMixte,goOrienteh,goNonOrienteh,goOmega"
typedef struct{
	int nSommetEnTout;
	int nArcEnTout;
	int aHed[kuGrapheSommetLim];//numéros d'arcs
	int sSuk[kuGrapheArcLim];//sommet destination de l'arc courant
	int aDeh[kuGrapheSommetLim];//numéros d'arcs ds le graphe inverse
	int sKus[kuGrapheArcLim];//sommet origine de l'arc courant;ATTENTION: a=(X,Y) et sSuk[a]=Y n'implique pas sKus[a]=X.
	int aInv[kuGrapheArcLim];//arc inverse aL associé à l'arc direct aK
	int nCapaMax[kuGrapheArcLim];//capacité maximale de l'arc courant
	int nCapaMin[kuGrapheArcLim];//capacité maximale de l'arc courant
	int nCout[kuGrapheArcLim];//poids ou coût n°1 associé à l'arc courant
	int nPoids[kuGrapheArcLim];//poids ou coût n°2 associé à l'arc courant
	int aArcTo[kuGrapheArcLim];
	int nAugVal[kuGrapheArcLim];
	int coulh[kuGrapheArcLim];
	int sPer[kuGrapheSommetLim];
	int nPhi[kuGrapheArcLim];//disponible
	int nVal[kuGrapheArcLim];//disponible
} graf;
int bGraphe(graf *pgG);//O(A)
char *sGraphe(int tGrapheType);//rend le nom du graphe de type tGrapheType,cf GrapheNom et GrapheType plus haut
void GrapheAMORCER();
int nGrapheApparier(int nAttribut,graf **ppgG);//O(A)
int bGrapheArc(graf *pgG,int sOrigine,int sDestination);//O(S)
int nGrapheArc(graf *pgG,int sOrigine,int sDestination);//O(S)
char *sGrapheArc(graf *pgG,int aArcNumero);//O(S)
void GrapheAntisymetriser(graf *pgG);//O(A)
void GrapheAreter(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheAreter0(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc);//O(A)
void GrapheAreter1(graf *pgG,int sOrigine,int sDestination,int nCouleur);//O(A)
void GrapheAreter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
void GrapheArquer(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheArquer0(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc);//O(A)
void GrapheArquer2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
void GrapheArquer3(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCout);//O(A)
int bGrapheBiparti(graf *pgG);//O(A)
int bGrapheBipartiOuAfficherCycleImpair(graf *pgG);//O(A)
void GrapheBipartitionne(graf *pgG);//O(A). X devient X' et X"=X+pgG->nSommetEnTout,contrairt à GrapheBipartitionner()
void GrapheBipartitionner(graf *pgG);//O(A). X devient X' et X"=X+1,contrairt à GrapheBipartitionne()
void GrapheBipartir(graf *pgG,int bBipartir);//O(A)
void GrapheCadufoua();
int nGrapheCardinal(int tQuadripole);//rend le nbre de sommets du graphe tQuadripole censé être un quadripôle
int bGrapheCheminerAuLarge(graf *pgG,int sSource,int sTrappe,int tCheminAfficher);//O(S2)
int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bTas,int tCheminAfficher,int *pnComplexiteh);//O(S2)
int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int tCheminAfficher,int *pnComplexiteh);//O(S2)
int bGrapheCircuite(graf *pgG);//O(A)
void GrapheCircuiterAuMieux(graf *pgFortementConnexe); 
void GrapheCliquer(graf *pgG,int uCliqueTaille);
void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur);
int nGrapheComposanteConnexe(graf *pgG);//O(A)
int nGrapheComposanteFortementConnexe(graf *pgG);//O(SA)
void GrapheConnecter(graf *pgG,int bArete,int sOrigine,int sDestination);//O(A)
void GrapheConnecter0(graf *pgG,int bArete,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc);//O(A)
void GrapheConnecter1(graf *pgG,int bArete,int sOrigine,int sDestination,int nCouleur);//O(A)
void GrapheConnecter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
int bGrapheConnexe(graf *pgG);//O(A)
int nGrapheCouleur(graf *pgG,int sOrigine,int sDestination);//O(S)
char *sGrapheCouple(graf *pgG,int sX,int sY,int nAttribut);//O(A)
void GrapheCouvrir(graf *pgG,int tPerformanceComparer,int bAfficher);
void GrapheCreer(int nSommet,graf **ppgG);
void GrapheCreer1(graf **ppgG,int nGrapheForme,int nGrapheTaille,int bCreer);
void GrapheCreer0(graf **ppgG,int bCreer);
void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]);
int nGrapheCycle2(graf *pgG);
void GrapheDecrire(graf *pgG);//O(A)
void GrapheDedoubler(int sSommet,graf **ppgG);//O(A)
int nGrapheDegreh(graf *pgG,int sSommet,int tMode);//O(A) -1:degré entrant,0:entrant+sortant,+1:sortant.
void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination);//O(A). rend les sommets qui délimitent l'arc considéré
void GrapheDerouler(graf *pgG);//O(SA)
float fGrapheDensiteh(graf *pgG);//O(1)
void GrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheDesarquerTout(graf *pgG,int sAccroche);//retire tout arc lié à sAccroche
int bGrapheDesareter(graf *pgG,int sExtremiteh0,int sExtremiteh1);//O(A)
void GrapheDupliquer(graf *pgOriginal,graf **ppgCopie);
void GrapheEmpiler(graf *pgEmpilota,int nAttribut,graf *pgG);
void GrapheEtoiler(graf *pgG,int uEtoile,int uBrancheParEtoile);
int bGrapheEulerien(graf *pgG,int szSource,int szTrappe);//O(A);sz:sommet ou 0
int bGrapheEulerier(graf *pgG,int szSource,int szTrappe);//O(A);sz:sommet ou 0
void GrapheExplorer(graf *pgG,int bLargeurSinonProfondeur);//O(A)
void GrapheGenerer(char kcArc[],int nAttribut,graf **ppgG);
int bGrapheFortementConnexe(graf *pgG);//O(SA)
void GrapheINITIALISER();
void GrapheInverser(graf *pgG);//O(A)
int bGrapheOrdonnancer(graf *pgG,int bStrict,int bAfficher);//O(A)
int iGraphePoids(graf *pgG,int nArc,int nAttribut);//O(A)
void GraphePolariser(graf *pgG,int *psSource,int *psTrappe);//O(A)
void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nAttribut,int iValeurSurArc);//O(A)
void GraphePonderer1(graf *pgG,int nArcPoids);//O(A)
void GraphePonderer0(graf *pgG,int nArcCout);//O(A)
void GraphePonderer2(graf *pgG,int uCapaMax,int uCoutMax);//O(A)
void GraphePonderer3(graf *pgG,int uCapaMin,int uCapaMax,int uCoutMax);//O(A)
void GraphePonderer5(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCoutMax);//O(A)
void GraphePondererDistinctement(graf *pgG,int iOffset);//O(A)
void GraphePondererAleatoirement(graf *pgG,int uBorneMax);//O(A)
int bGrapheQuadripole(int nTypeDeMotif);//O(1)
int nGrapheQuadripoler(graf *pgSansMotif,int nMotifForme,int nMotifTaille,int bCroiser,int nAttribut,graf **ppgAvecMotif);//O(A);rend le nb de sommets par motif
void GrapheQuintesser(graf *pgG,int nSommet);
void GrapheRenumeroter(graf **ppgG,int sSommetAvant,int sSommetApres);//O(A)
void GrapheRenumeroterTout(int sListe[],graf *pgG);//O(A)
void GrapheRetourner(graf *pgG,int bRetourner,graf **ppgH);//si bRetourner,alloue et rend le graphe inverse de pgG;sinon,restitue pgH
int bGrapheSimple(graf *pgG);//O(A)
void GrapheSommer(graf *pgG,int inEmpilerSinonDepiler);//empile inEmpilerSinonDepiler sommets si >0, les dépile,si <0, avec leurs arcs incidents. 
int bGrapheSommet(graf *pgG,int sSommet);
int bGrapheSymetrique(graf *pgG);//O(A)
void GrapheSymetriser(graf *pgG,int nAttribut);//O(A)
void GrapheTESTER(int iTest);
void GrapheTranslater(graf *pgG,int nOffset);
void GrapheTrierTopologiquement(graf *pgG,int bAfficher);//O(A)
void GrapheVoir(graf *pgG,char *sMessage);//affiche tous les arcs
void GrapheVoir0(graf *pgG,char *sMessage,int nAttribut);//affiche les arcs de pgG avec les attributs listés ds nAttribut (voir identifiants en haut de ce module)
void GrapheVoir1(graf *pgG,int bDontCouleur,char *sMessage);
void GrapheVoir2(graf *pgG,char *sMessage);
void GrapheVoir3(graf *pgG,char *sMessage);
