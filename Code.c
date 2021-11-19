#include "Kit.h" 
void CodeExecuter(){ 
    Appel0("CodeExecuter"); 
        int Sept = 7 ; 
        int Dix = 3 + Sept ; 
        printf(" Dix = %d.\n", Dix ); 
        printf(" Sept = %d.\n", Sept ); 
        int Cent = Dix * ( Sept + 3 ) ; 
        printf(" Cent = %d.\n", Cent ); 
    Appel1("CodeExecuter"); 
} 
