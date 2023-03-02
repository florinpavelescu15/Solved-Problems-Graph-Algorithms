#include <bits/stdc++.h>

#define INFTY (long)1e12

using namespace std;

void add_edge(vector<pair<int, long>> adj[], int s, int d, long w) {
  adj[s].push_back({d, w});
  adj[d].push_back({s, w});
}

// algoritmul lui Dijkstra
vector<long> dijkstra(int n, vector<pair<int, long>> adj[], int source) {
  vector<long> d(n + 2, INFTY);
  set<pair<long, int>> pq;

  d[source] = 0;

  pq.insert({d[source], source});

  while (!pq.empty()) {
    auto top = pq.begin();
    pair<long, int> node = *top;
    pq.erase(top);

    if (node.first > d[node.second])
      continue;

    for (int i = 0; i < adj[node.second].size(); i++) {
      if (d[node.second] + adj[node.second][i].second <
          d[adj[node.second][i].first]) {
        d[adj[node.second][i].first] =
            d[node.second] + adj[node.second][i].second;
        pq.insert({d[adj[node.second][i].first], adj[node.second][i].first});
      }
    }
  }

  return d;
}

/* primeste un vector sortat si
incearca sa egaleze primele p elemente din vector folosind k,
maximizand valoarea acestora si mentinand vectorul sortat;
intoarce valoarea minima din acest vector, dupa epuizarea lui k;
folosesc metoda Greedy */
long get_min_dist(vector<long> v, int k) {
  int i = 0;
  while (i < v.size() - 1 && k >= (i + 1) * (v[i + 1] - v[i])) {
    k = k - (i + 1) * (v[i + 1] - v[i]);
    i++;
  }

  return v[i] + k / (i + 1);
}

int main() {
  int N, M, K, B, x, y;
  long t;
  ifstream fin("fortificatii.in");
  ofstream fout("fortificatii.out");

  fin >> N >> M >> K >> B;
  vector<int> b(B + 2);

  // graful din cerinta
  vector<pair<int, long>> adj[N + 2];

  // graful fara barbari
  vector<pair<int, long>> adj1[N + 2];

  // r[x] = true <=> localitatea x este ocupata de barbari
  vector<bool> r(N + 2, false);

  for (int i = 0; i < B; i++) {
    fin >> b[i];
    r[b[i]] = true;
  }

  for (int i = 0; i < M; i++) {
    fin >> x >> y >> t;
    add_edge(adj, x, y, t);

    // adaug muchia doar daca nu are niciun capat barbar
    if (!r[x] && !r[y])
      add_edge(adj1, x, y, t);
  }

  vector<long> v;

  // Dijkstra pe graful fara barbari, incepand din capiatala
  vector<long> d = dijkstra(N, adj1, 1);

  /* calculez lungimile tuturor rutelor posibile prin care
  barbarii pot ajunge in capitala in mod optim, adica
  merg pana la vecinii nebarbari si de acolo in capitala
  pe drumul cel mai scurt pe care nu exista barbari */
  for (int i = 0; i < B; i++) {
    for (int j = 0; j < adj[b[i]].size(); j++)
      if (!r[adj[b[i]][j].first])
        v.push_back(d[adj[b[i]][j].first] + adj[b[i]][j].second);
  }

  /* sortez crescator aceste lungimi,
  drumurile de lungime mai mica au prioritate mai mare
  la construirea fortificatiilor */
  sort(v.begin(), v.end());

  fout << get_min_dist(v, K);

  return 0;
}
