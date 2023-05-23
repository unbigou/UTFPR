#pragma once

typedef enum ExprTreeTipoNo
{
    ETTN_CONSTANTE,
    ETTN_OPERADOR
} ExprTreeTipoNo;


typedef struct ExprTree{
    struct ExprTree *esq;
    struct ExprTree *dir;
    ExprTreeTipoNo tipo_no;
    char operador;
    int valor_constante;
}ExprTree;

void ET_Destruir(ExprTree *A);
void ET_GenDOT(ExprTree *A, const char* arq_saida);
ExprTree* ET_FromPosfixa(char* pos_fixa);
int ET_Avaliar(ExprTree* et);