Ce face `malloc` cu adevarat?
- Prima data allocatorul compara spatiul cerut cu threshold-ul configurat (de obicei 128KB, dar se poate configura):
- Cazul A: sptiul cerut este `>`:
    - Apeleaza `mmap()` pentru a cere pagini noi anonime de a kernel si ocoleste heap-ul;
- Cazul B: spatiul cerut `<`:
    - Cazul B1: Cauta daca are spatiu liber pe undeva pe heap;
    - Cazul B2: Daca nu gaseste spatiu deja pe heap, apeleaza `brk()` pentru a-l extinde;

NU TOATE alocarile dinamice ajung pe HEAP, dar e cert ca HEAP-ul este exclusiv pentru alocari dinamice.

De ce mai dam `free()` daca fisierul se copiaza corect si fara?
- Blocul de memorie ar ramane alocat si nu ar mai putea fi reutilizat la alte alocari. Intr-un program scurt ca asta, OS-ul recupereaza memoria la terminarea procesului. Intr-un program complex care ruleaza constant si repeta alocarile, memoria neeliberata se acumuleaza (SIGKILL)

`make`
`valgrind --leak-check=full ./copy_file copy_file.c paste_file.c`
`cmp copy_file.c paste_file.c`