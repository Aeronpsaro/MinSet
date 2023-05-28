#!/bin/zsh

regex=$(cat regexTodos.txt)

pcre2grep -Mo $regex Todos_los_diccionarios.txt |\
grep -v Clave |\
grep -vE '^[^>]+\.|###' |\
sed "s/>\([a-zA-ZñÑáéíóúÁÉÍÓÚ]*\).*/>\1/" |\
sed "s/^>/:/" |\
perl -p -e 's/^([^:]+)\n/\1/' |\
sed "s/:sustantivo/:1000/" |\
sed "s/:adjetivo/:1100/" |\
sed "s/:adverbio/:1202/" |\
sed "s/:verbo/:3000/"
