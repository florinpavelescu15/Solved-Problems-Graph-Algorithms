#include <bits/stdc++.h>

using namespace std;

void add_edge(int n, vector<int> adj[], int s, int d) { adj[s].push_back(d); }

// algoritmul lui Kahn de sortare topologica
vector<int> topsort(int n, vector<int> adj[], vector<int> indegree) {
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (indegree[i] == 0)
      q.push(i);

  vector<int> vs;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vs.push_back(u);

    for (int i = 0; i < adj[u].size(); i++)

      if (--indegree[adj[u][i]] == 0)
        q.push(adj[u][i]);
  }

  return vs;
}

int main() {
  int N, M, A;
  ifstream fin("curse.in");
  ofstream fout("curse.out");
  fin >> N >> M >> A;
  vector<int> adj[M + 2];
  vector<vector<int>> m(A + 2, vector<int>(N + 2));
  vector<bool> used(A + 2, false);
  vector<int> indegree(M + 2, 0);

  for (int i = 1; i <= A; i++)
    for (int j = 1; j <= N; j++)
      fin >> m[i][j];

  // parcurg pistele in oradine crescatoare
  for (int j = 1; j <= N; j++)
    for (int i = 1; i < A; i++) {
      // daca gasesc o relatie intre doua masini pe pista j
      if (m[i][j] != m[i + 1][j] && !used[i]) {
        // adaug relatia ca muchie intr-un graf orientat
        add_edge(M, adj, m[i][j], m[i + 1][j]);
        indegree[m[i + 1][j]]++;
        /* marchez antreanmentul pentru a nu mai deduce
        relatii cu el pe pistele urmatoare */
        used[i] = true;
      }
    }

  // ordinea ceruta este data de sortarea tologica
  vector<int> vs = topsort(M, adj, indegree);
  for (int i = 0; i < vs.size(); i++)
    fout << vs[i] << " ";
  fout << endl;

  return 0;
}
