seq(1, 10, 2)
rep(5,10)

rep(c("A", "B"), 5)
rep(c("A", "B"), each= 5)
rep(c("Três", "Dois", "Sete", "Quatro"), c(3,2,7,4)) #Comentário

letras <- c("a", "b", "c", "da", "edw")
length(letras)

#runif(n, min, max)
runif(10, 0, 10)

temp <- runif(200, 80, 100)
#hist(x) #histograma

normal.padrao <- rnorm(1000, 0, 1)
hist(normal.padrao)

sample(1:100, 2) #pega 2 amostras aleatórias

sum(sample(0:1, 15, replace=T))