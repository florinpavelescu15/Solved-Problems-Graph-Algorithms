Pavelescu Florin, grupa 324CC

1. Curatare multi-agent
Am generat, folosind metdoda backtracking, toate repartizarile posibile
ale spatiilor murdare pe fiecare robot. Pentru calculul timpilor necesari,
am folosit algoritmul lui Lee [1], pornind din fiecare robot, apoi din
fiecare spatiu murdar. Astfel, daca robotul r are de curatat spatiile
s1, s2, ..., sk, timpul necesar pentru curatare este
t(r) = d(r, s1) + d(s1, s2) + ... + d(s(k-1), sk).
Pentru o anumita repartizare, timpul necasar va fi maximul timpilor t(r)
asociati robotilor, intrucat acestia lucreaza simultan, iar curatarea se termina
atunci cand termina ultimul robot. Pentru determinarea timpului minim de curatare,
am determinat minimul timpilor asociati tuturor repartizarilor.

Complexitate temporala: O(R ^ S + (S + R) * M * N + R * S)
Complexitate spatiala: O(N * M)

2. Fortificatii
Am pornit de la urmatoarele observatii:
2.1. Barbarii nu pot ajunge in capitala decat trecand printr-o licalitate vecina.
2.2. Daca pentru a ajunge in capitala barbarii trebuie sa treaca prin mai multe
localitati cucerite, ultima localitate cucerita este cea mai aproape de capitala,
deci fortificatiile vor fi construite pe calea de la ultima localitate cucerita la
capitala, intrucat impiedicand barbarii din ultima localitate sa ajunga in capitala
ii vom impiedica si pe barbarii din localitatile anterioare.
2.3 Din 2.2 deducem ca fortificatiile vor fi construite pe caile de la barbari la
capitala care nu contin localitati cucerite.
2.4 Dupa ce barbarii au trecut de fortificatii, ei merg in capitala pe drumul cel
mai scurt.

Astfel, pentru a calcula toate rutele posibile prin care barbarii pot ajunge
in capitala, tinand cont ca reteaua de localitati este un graf neorientat cu costuri,
am aplicat algoritmul lui Dijkstra pornind din sursa pe graful fara localitatile
cucerite, din motivele prezentate la 2.2 si 2.3, si am obtinut un vector d de distante
minime. Daca barbarii se afla in localitatea x cu vecinii nebarbari v1, v2, ..., vr,
atunci drumurile posibile pentru a ajunge in capitala au lungimile l(i) = w(x, vi) + d(vi).
Pentru fiecare dintre localitatile barbare, determin drumurile posibile si le ordonez
crescator, intrucat drumurile cele mai scurte sunt prioritare la construirea
fortificatiilor. Folosesc un algoritm Greedy pe vectorul sortat, pentru determinarea 
timpului minim in care barbarii ajung in capitala.

Complexitate temporala: O((N + M) * log(N) + N * M)
Complexitate spatiala: O(N * M)

3. Beamdrone
Am folosit algoritmul Dijkstra [2] modificat. Practic, nu am un graf, ci o matrice in
care vecinii unui nod (i, j) sunt (i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)
(daca sunt liberi). In plus, am retinut, pentru fiecare nod si nodul parinte, astfel
ca de fiecare data cand scot un nod din coada am acces si la parintele lui, pentru
a determina natura miscarii (intoarcere, viraj sau mers inainte).
Fie (i, j) nodul curent, (iv, jv) un vecin si (ip, jp) parintele.
- Daca (iv, jv) = (ip, jp), atunci are loc o intoarcere, deci coartul w = 2.
- Daca |iv - ip| = |jv - jp| si (iv, jv) != (ip, jp), practic daca vecinul si
parintele se afla pe diagonala, atunci are loc un viraj la stanga sau la dreapta,
deci costul w = 1.
- Altfel, se merge inainte, deci w = 0.
Spre deosebire de algoritmul Dijkstra clasic, aici costurile se calculeaza la fiecare
miscare.

Complexitate temporala: O(N ^ 2 * log(N))
Complexitate spatiala: O(N * M)

4. Curse
Am parcurs pistele in ordine cresactoare si daca am gasit o relatie pe pista i,
intre antrenamentele j si j + 1, P(s) > P(t), am adaugat muchia (s, t) intr-un
graf orientat si am marcat linia j pentru a nu mai fi folosita la o comparatie
ulterioara. Dupa ce am dedus toate reatiile pe piste, am folosit algoritmul lui
Kahn [3] pentru a obtine o sortare topologica a grafului format, ordinea obtinuta
fiind ordinea ceruta in enunt.

Complexitate temporala: O(N * A + M)
Complexitate spatiala: O(N * A + M)


[1] https://www.pbinfo.ro/articole/18589/algoritmul-lui-lee
[2] laboratorul 9 rezolvat
[3] https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/