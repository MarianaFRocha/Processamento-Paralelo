#!/bin/bash

#*********************************************************************#
# Antes de executar ./run.sh vocÃª deve dar perminsÃ£o para o arquivo   #
# possa ser executado. Para isso, execute o seginte comando:          #
#              chmod +x run.sh                                        #
#*********************************************************************#

numeroExecucoes=30

tamanhoMatriz="100 200 300 500 700"
threads="1 2 3 4 5 7 8"


for N in $tamanhoMatriz
do
	echo "N = "$N
	for T in $threads
	do
		echo "T = "$T>>saida$N.txt

		for (( i=1; i<=numeroExecucoes; i++ ))
		do
		./pthread $T A_$N.txt B_$N.txt >>saida$N.txt
		done	
		echo "">>saida$N.txt
		echo "">>saida$N.txt

	done
	echo ""
	echo ""
done
