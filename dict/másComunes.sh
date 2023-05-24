#!/bin/bash

cat Clave_Legible.txt | tr " " "\n" | sort | uniq -c | sort -k1,1nr -k2b | head -n 70
