- Bufferul global evita costurile alocarii dinamice
- Bufferul global e stocat in .bss cu dimensiune fixa si exista pe toata durata executiei
- Rezerva 1MB de memorie virtuala, nu neaparat si fizica

Memoria bufferului global: `size ./copy_file`

Identificarea bufferului: `nm -S ./copy_file | grep -w buffer`:
- prima valoare: adresa
- 100000 in hexa = 1MB
- b/B inseamna un simbol din .bss (static sau non-static)

Diferenta dintre spatiul din memorie si dimensiunea executabilului: `ls -lh ./copy_file`
Executabilul are mai putin de 1MB