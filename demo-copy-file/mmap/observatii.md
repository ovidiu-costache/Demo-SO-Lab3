mmap() sau malloc()?

malloc() pentru siguranta si confort, atunci cand nu ne intereseaza proprietatiile maparii. malloc() fiind un wrapper e mai simplu de folosit.
mmap() controleaza direct o mapare pe care trebuie sa o gestionam manual. Alegem mmap() cand ne trebuie prop. maparii