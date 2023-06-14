library(tidyverse)

tabela <- read.table("/home/unbigou/Documents/UTFPR/Probabilidade e Estatistica/tabela_compMB.csv", sep = ";", head = TRUE) # nolint: line_length_linter.

tabela[c(10, 15), c(5, 6)]

tabela[tabela$Grau_de_instrucao == "ensino medio", ]
#Separa as variaveis que cumprem a condição

sd(tabela$Salario)
#Calcula o desvio padrão da tabel

ggplot(
    tabela, color = factor(Grau_de_instrucao)
) + geom_point(
    aes(x = Salario, y = Idade_em_anos, color = Grau_de_instrucao), size = 5
) + geom_smooth(
    aes(x = Salario, y = Idade_em_anos), method = lm
)
#Cria uma tabela de pontos com os respectivos eixos Salario e Idade
# e com atributos escolhidos. Cada comando segue o padrão do anterior