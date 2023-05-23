#include <stdio.h>
#include <string.h>

typedef struct no
{
    int num;
    char* op;
    struct no* right;
    struct no* left;
} No;


int operation(int num1, int num2, char* op)
{
    if(op == "+") return num1 + num2;
    if(op == "-") return num1 - num2;
    if(op == "x") return num1 * num2;
    if(op == "/") return num1 / num2;
}


int shunting_yard(No* tree)
{
    if(tree-> right == NULL || tree-> left == NULL)
    {   
        return tree-> num;
    }
    
    tree-> num = operation(shunting_yard(tree-> right), shunting_yard(tree-> left), tree-> op);
    return tree-> num;
}


int main()
{
    No* tree;
    tree-> num = 0;
    tree-> op = "+";
    tree-> right-> num = 1;
    tree-> left-> num = 3; 

    printf("%d", shunting_yard(tree));

    return 0;
}