enum eErreur {eLimite0,
	eAlex0,eAlexInconnu,eAlexEntieR,eAlexReel,eAlex1,
	eSynt0,eSyntChosE,eSyntInstruction,eSyntLivre,eSyntNom,eSyntProgramme,eSyntSeparateur,eSyntSuite,eSyntTerme,eSynt1,
	eSem0,eSemAffectation,eSemAffichage,eSemDate,eSemDelaiTropLong,eSemDoublon,eSemHoraire,eSemIdentifiant,eSemInscrit,eSemLivreDispo,eSemLivreInconnu,eSemLivrePris,eSemNonInscrit,eSemPrix,eSem1,
	eLimite1};
void ErreurAfficher(int uLigne);
void ErreurAfficherTout();
void ErreurAMORCER();
void ErreurEmpiler(int nErreurNumero, int nLexeme);
int bErreurEmpiler(int nErreurNumero, int nLexeme);
int nErreurEnTout();
void ErreurINITIALISER();
void ErreurTESTER(int iTest);