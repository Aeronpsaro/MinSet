#!/bin/zsh

regex=$(cat regexDef.txt)   

pcre2grep -Mo $regex Todos_los_diccionarios_lematizados.txt |\
tr "\n" "<" | tr "#" "\n" |\
perl -p -e 's/<([a-zA-ZñÑáéíóúÁÉÍÓÚ]+)<.*<(.*)<>([a-zA-ZñÑáéíóúÁÉÍÓÚ]+).*<.*/\1:\3\n\2/' |\
perl -p -e 's/^\n//' |\
sed "s/:sustantivo/:1000/" |\
sed "s/:adjetivo/:1100/" |\
sed "s/:adverbio/:1202/" |\
sed "s/:verbo/:3000/"
