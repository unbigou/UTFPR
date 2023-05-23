#include "exprtree.h"
#include "etstack.h" // Pilha de árvores
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> // Função isdigit()


ExprTree* ET_Criar(ExprTree* esq, ExprTree* dir)
{
    ExprTree* tree = malloc(sizeof(struct ExprTree));
    tree-> esq = esq;
    tree-> dir = dir;

    return tree;
}


ExprTree* ET_CriarNoConstante(int valor)
{
    ExprTree* tree = ET_Criar(NULL, NULL);
    tree-> tipo_no = ETTN_CONSTANTE;
    tree-> valor_constante = valor;

    return tree;
}


ExprTree* ET_CriarNoOperador(ExprTree* esq, ExprTree* dir, char operador)
{
    ExprTree* tree = ET_Criar(esq, dir);
    tree-> tipo_no = ETTN_OPERADOR;
    tree-> operador = operador;

    return tree;
}


ExprTree* ET_FromPosfixa(char* pos_fixa) // Converte uma string pra uma arvoré
{
    ETSTACK* pilha = ETSTACK_Criar(10);
    char* index = strtok(pos_fixa, " "); // strtok() obtém o primeiro caracter da string
    ExprTree* tmp, *log1, *log2;

    while(index != NULL)
    {
        if(isdigit(*index)) // Caso o caracter seja um digito, cria um nó constante 
        {
            tmp = ET_CriarNoConstante(atoi(index));
        }
        else // Do contrario cria um nó operador. Para isso, é necessário desempilhar os nós anteriores
        {
            log1 = ETSTACK_Desempilhar(pilha);
            log2 = ETSTACK_Desempilhar(pilha);
            tmp = ET_CriarNoOperador(log2, log1, *index);
        }

        ETSTACK_Empilhar(pilha, tmp);
        index = strtok(NULL, " ");
    }

    tmp = ETSTACK_Desempilhar(pilha);
    ETSTACK_Destruir(pilha);
    return tmp;
}


int ET_Avaliar(ExprTree* et)
{
    if(et != NULL) return 0; // Caso base

    if(et-> tipo_no == ETTN_CONSTANTE) // Também é caso base
    {
        return et-> valor_constante;
    }

    int esq = ET_Avaliar(et-> esq);
    int dir = ET_Avaliar(et-> dir);

    switch(et-> operador)
    {
        case '+': return esq + dir;
        case '-': return esq - dir;
        case '*': return esq * dir;
        case '/': return esq / dir;
    }
}


void ET_Destruir(ExprTree* tree)
{
    if(tree == NULL) return;

    ET_Destruir(tree-> esq);
    ET_Destruir(tree-> dir);
    free(tree);
}

// static int ET_GenDOT_R(ExprTree *A, FILE* saida, int *id){
//     int e, d, me;

//     if(A == NULL)
//         return 0;

//     e = ET_GenDOT_R(A->esq, saida, id);
//     d = ET_GenDOT_R(A->dir, saida, id);

//     me = (*id)++;

//     if(A->tipo_no == ETTN_CONSTANTE)
//         fprintf(saida, "%d [label=\"%d\"];\n", me, A->valor_constante);
//     else
//         fprintf(saida, "%d [label=\"%c\"];\n", me, A->operador);

//     if(e || d){
//         if(e)
//             fprintf(saida, "%d -> %d;\n", me, e);
//         if(d)
//             fprintf(saida, "%d -> %d;\n", me, d);
//     }

//     return me;

// }

// void ET_GenDOT(ExprTree *A, const char* arq_saida){

//     FILE* saida;
//     int id = 1;

//     saida = fopen(arq_saida, "w");

//     fprintf(saida, "digraph G {\n");

//     ET_GenDOT_R(A, saida, &id);

//     fprintf(saida, "}\n");

//     fclose(saida);

// }