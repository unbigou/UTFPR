#include <stdio.h>
#include <stdlib.h>
#include "shunting_yard.h"
#include "exprtree.h"


int main(int argc, char** argv)
{
    char* in_fixa = argv[1]; // Expressão infixa: (3*5)+2
    char* pos_fixa = shunting_yard(in_fixa); // Expressão posfixa: 35*2+
    printf("%s\n", pos_fixa);

    ExprTree* et = ET_FromPosfixa(pos_fixa);

    int resultado = ET_Avaliar(et);
    printf("%d\n", resultado);

    ET_Destruir(et);
    free(et);

    return 0;
}