#include <bits/stdc++.h>

#define RS_MAX 5

using namespace std;

/* vectori ce contin cele patru directii posibile
de exemplu, ca sa merg in jos, de pe pozitia (i, j)
trebuie sa trec in (i - 1, j) = (i + di[0], j + dj[0]) */
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};

/* repartizare a spatiilor murdare pe fiecare robot,
curr[s] = r <=> robotul r curata spatiul murdar s */
vector<int> curr(RS_MAX);

/* matrice ce contine, pe linii, toate configuratiile
posibile pentru curr */
vector<vector<int>> res;

/* genereaza toate configuratiile posibile pentru curr
folosesind metoda backtracking, adauga fiecare configuratie
ca linie in matricea res */
void bkt(int k, int r, int s) {
  for (int i = 0; i < r; i++) {
    curr[k] = i;
    if (k == s - 1)
      res.push_back(curr);
    else
      bkt(k + 1, r, s);
  }
}

/* algoritmul lui Lee
calculeaza, folosind o parcurgere in latime, timpul de
la pozitia de start la tote celelalte pozitii disponibile
din tabla A, reprezentata astfel:
A[i][j] = -1 <=> pozitia (i, j) este ocupata
A[i][j] = 0 <=> pozitia (i, j) este libera si nevizitata
A[i][j] = t > 0 <=> pozitia (i, j) a fost vizitata, iar
timpul de la start la ea este t - 1 */
vector<vector<int>> lee(int istart, int jstart, int n, int m,
                        vector<vector<int>> A) {
  queue<pair<int, int>> q;

  // pun pozitia de start in coada
  q.push({istart, jstart});

  A[istart][jstart] = 1;

  while (!q.empty()) {
    // extrag pozitia curenta din coada
    int i = q.front().first, j = q.front().second;
    q.pop();

    // ii parcurg toti vecinii liberi
    for (int k = 0; k < 4; k++) {
      int iv = i + di[k], jv = j + dj[k];
      if (iv >= 1 && iv <= n && jv >= 1 && jv <= m && A[iv][jv] == 0) {
        // actualizez timpul si adaug vecinii in coada
        A[iv][jv] = A[i][j] + 1;
        q.push({iv, jv});
      }
    }
  }
  return A;
}

int main() {
  char x;
  int N, M, istart, jstart, t, max_time;
  ifstream fin("curatare.in");
  ofstream fout("curatare.out");
  fin >> N >> M;

  // pozitiile robotilor si spatiilor murdare pe tabla
  vector<pair<int, int>> r, s;

  /* rs[r][s] = t <=> timpul de la robotul r la
  la spatiul murdar s este t */
  vector<vector<int>> rs(RS_MAX, vector<int>(RS_MAX));

  /* ss[s1][s2] = t <=> timpul de la spatiul murdar s1
  la spatiul murdar s2 este t */
  vector<vector<int>> ss(RS_MAX, vector<int>(RS_MAX));

  /* A[i][j] = -1 <=> spatiul (i, j) este ocupat
     A[i][j] = 0 <=> spatiul (i, j) este liber, un robot
  sau un spatiu murdar */
  vector<vector<int>> A(N + 2, vector<int>(M + 2));

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      fin >> x;
      if (x == 'X') {
        A[i][j] = -1;
      } else {
        A[i][j] = 0;
        if (x == 'R')
          r.push_back({i, j});

        if (x == 'S')
          s.push_back({i, j});
      }
    }

  /* folosesc algoritmul lui Lee pentru a calcula timpii
  de la fiecare robot la fiecare spatiu murdar */
  for (int k = 0; k < r.size(); k++) {
    vector<vector<int>> D = lee(r[k].first, r[k].second, N, M, A);
    for (int l = 0; l < s.size(); l++)
      rs[k][l] = D[s[l].first][s[l].second] - 1;
  }

  /* folosesc algoritmul lui Lee pentru a calcula timpii
  dintre spatiile murdare */
  for (int k = 0; k < s.size(); k++) {
    vector<vector<int>> D = lee(s[k].first, s[k].second, N, M, A);
    for (int l = 0; l < s.size(); l++)
      ss[k][l] = D[s[l].first][s[l].second] - 1;
  }

  /* generez toate repartizarile psibile ale spatiilor
  murdare pe fiecare robot */
  bkt(0, r.size(), s.size());

  int min_time = INT_MAX;

  // parcurg repartizarile posibile
  for (int i = 0; i < res.size(); i++) {
    /* repartizarea propriu-zisa
    rep[r] = multimea spatiilor murdare pe care le curata
    robotul r */
    vector<vector<int>> rep(r.size());
    for (int j = 0; j < s.size(); j++)
      rep[res[i][j]].push_back(j);

    /* pentru aceasta repartizare
    calculez timpul necesar fiecarui robot sa-si termine treaba */
    max_time = 0;
    for (int k = 0; k < rep.size(); k++) {
      t = 0;
      // daca robotul k nu are de curatatniciun spatiu murdar
      if (rep[k].size() == 0) {
        t = 0;
      } else {
        // timpul de la robot pana la primul spatiu murdar repartizat
        t = t + rs[k][rep[k][0]];
        // timpii dintre spatiile murdare
        for (int l = 0; l < rep[k].size() - 1; l++)
          t = t + ss[rep[k][l]][rep[k][l + 1]];
      }

      /* maximul acestor timpi va fi timpul asociat repartizarii curente,
      deoarece robotii lucreaza simultan */
      if (t > max_time)
        max_time = t;
    }

    /* timpul minim necesar intregii operatiuni este minimul timpilor
    asociati repartizarilor */
    if (min_time > max_time)
      min_time = max_time;
  }

  fout << min_time << endl;

  return 0;
}
