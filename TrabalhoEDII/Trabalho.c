#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <ctype.h> 

#include "TADTrab.h"

int main(){
    TpLista *pProgram = NULL;
    PilhaM *pilhaM = NULL;

    CarregaL(&pProgram);
    exibe(pProgram);
    
    compilar(pProgram, &pilhaM);
    
    mostrarPilhaMem(pilhaM);
}
