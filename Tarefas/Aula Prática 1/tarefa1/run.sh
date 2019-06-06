#!/bin/bash

#*********************************************************************#
# Antes de executar ./run.sh vocÃª deve dar perminsÃ£o para o arquivo   #
# possa ser executado. Para isso, execute o seginte comando:          #
#              chmod +x run.sh                                        #
#*********************************************************************#

numeroExecucoes=30

tamanhoMatriz="100 200 300 500"


for N in $tamanhoMatriz
do
	echo "N = "$N
	for (( i=1; i<=numeroExecucoes; i++ ))
	do
		./teste $N >>saida$N.txt
	done
	echo ""
	echo ""
done
