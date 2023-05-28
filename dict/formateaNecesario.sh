#!/bin/zsh

regex=$(cat regexDef.txt)   

pcre2grep -Mo $regex Todos_los_diccionarios_lematizados.txt |\
tr "\n" '<' | tr "#" "\n" |\
perl -p -e 's/<([a-zA-ZñÑáéíóúÁÉÍÓÚ]+)<.*<(.*)<>([a-zA-Z]+).*<.*/#\1:\3\n\2/' |\
perl -p -e 's/^\n//' |\
sed "s/:sustantivo/:1000/" |\
sed "s/:adjetivo/:1100/" |\
sed "s/:adverbio/:1202/" |\
sed "s/:verbo/:3000/" |\
sed -E 's/[][a-zA-ZñÑáéíóúÁÉÍÓÚ0-9.,)(";¿?¡!«»+-/:º°´`='\''_]+:((10[1-9]0)|(100[1-9])|(10[1-9][1-9])|(11[1-9][0-9])|(110[1-9])|(12[1-9][0-9])|(120(0|[3-9]))|(1[4-9]([0-9])*)|(([0-9]){2,3})|(2|[4-9])[0-9]*)([^0-9]|\n)//g' |\
tr "\n" '<' |\
perl -p -e 's/[a-zA-ZñÑáéíóúÁÉÍÓÚ0-9:]+<<//g' |\
tr "<" "\n" |\
sed 's/ $//'
