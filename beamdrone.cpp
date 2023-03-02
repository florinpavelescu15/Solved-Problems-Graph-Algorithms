#include <bits/stdc++.h>

#define INFTY INT_MAX

using namespace std;

/* vectori ce contin cele patru directii posibile
de exemplu, ca sa merg in jos, de pe pozitia (i, j)
trebuie sa trec in (i - 1, j) = (i + di[0], j + dj[0]) */
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};

/* algoritmul lui Dijkstra modificat pentru calculul distantelor
pe o matrice, cu calculul costurilor muchiilor in place */
int dijkstra(int xi, int yi, int xf, int yf, int n, int m,
             vector<vector<int>> A) {
  vector<vector<int>> d(n + 2, vector<int>(m + 2, INFTY));

  /* pentru fiecare nod, pun in coada o pereche de forma (d, ((i, j), (ip,
  jp))), unde d e distanta pana la nodul curent (i, j), iar (ip, jp) e parintele
  nodului curent (nodul vizitat anterior nodului curent) */
  set<pair<int, pair<pair<int, int>, pair<int, int>>>> pq;

  d[xi][yi] = 0;

  // pun in coada vecinii nodului de start, cu distanta 0
  for (int k = 0; k < 4; k++) {
    int iv = xi + di[k], jv = yi + dj[k];
    if (iv >= 0 && iv < n && jv >= 0 && jv < m && A[iv][jv] == 0) {
      d[iv][jv] = 0;
      pq.insert({0, {{iv, jv}, {xi, yi}}});
    }
  }

  while (!pq.empty()) {
    // extrag pozitia curenta din coada cu prioritati
    auto top = pq.begin();
    int dst = (*top).first;
    int i = (*top).second.first.first, j = (*top).second.first.second;
    int ip = (*top).second.second.first, jp = (*top).second.second.second;
    pq.erase(top);

    if (dst > d[i][j])
      continue;

    // ii parcurg toti vecinii liberi
    for (int k = 0; k < 4; k++) {
      int iv = i + di[k], jv = j + dj[k];
      if (iv >= 0 && iv < n && jv >= 0 && jv < m && A[iv][jv] == 0) {
        /* calculez costul muchiei ((i, j), (iv, jv)) in functie de
        pozitia vecinului (iv, jv) fata de parinte (ip, jp) */
        int w;
        if (iv == ip && jv == jp) {     // intoarcere
          w = 2;
        } else if (abs(ip - iv) == 1 && abs(jp - jv) == 1) {    // viraj
          w = 1;
        } else {    // mres inainte
          w = 0;
        }

        // daca distanta se imbunatateste
        if (dst + w <= d[iv][jv]) {
          // actualizez distanta si adaug nodul in coada
          d[iv][jv] = dst + w;
          pq.insert({d[iv][jv], {{iv, jv}, {i, j}}});
        }
      }
    }
  }

  return d[xf][yf];
}

int main() {
  char ch;
  int N, M, xi, yi, xf, yf;
  ifstream fin("beamdrone.in");
  ofstream fout("beamdrone.out");
  fin >> N >> M;
  fin >> xi >> yi >> xf >> yf;

  vector<vector<int>> A(N + 2, vector<int>(M + 2));

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      fin >> ch;
      if (ch == 'W')
        A[i][j] = -1;
      else
        A[i][j] = 0;
    }

  fout << dijkstra(xi, yi, xf, yf, N, M, A);

  return 0;
}
