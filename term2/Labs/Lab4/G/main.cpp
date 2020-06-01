#include <bits/stdc++.h>

using namespace std;

int n[2];
int m[2];
int k[2];
set<int> allowed[2];
vector<vector<int>> edges[2];

void input() {
  for (int cur_auto = 0; cur_auto < 2; cur_auto++) {
    cin >> n[cur_auto] >> m[cur_auto] >> k[cur_auto];


    for (int i = 0; i < k[cur_auto]; i++) {
      int t;
      cin >> t;
      allowed[cur_auto].insert(t - 1);
    }

    edges[cur_auto].resize(n[cur_auto] + 1, vector<int>(26, -1));
    for (int i = 0; i < m[cur_auto]; i++) {
      int a, b;
      char c;
      cin >> a >> b >> c;

      edges[cur_auto][a - 1][c - 'a'] = b - 1;
    }
    for (int i = 0; i < n[cur_auto]; i++) {
      for (int j = 0; j < 26; j++) {
        if (edges[cur_auto][i][j] == -1) edges[cur_auto][i][j] = n[cur_auto];
      }
    }
    for (int j = 0; j < 26; j++) edges[cur_auto][n[cur_auto]][j] = n[cur_auto];
  }
}

void ans_no() {
  cout << "NO";
  exit(0);
}

void bfs() {
  queue<pair<int, int>> q;
  set<pair<int, int>> used;

  q.push({0,0 });
  used.insert({0,0});

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    if (allowed[0].count(cur.first) ^ allowed[1].count(cur.second)) ans_no();

    for (int i = 0; i < 26; i++) {
      pair<int, int> to = {edges[0][cur.first][i], edges[1][cur.second][i]};
      if (edges[0][cur.first][i] != -1 && edges[1][cur.second][i] != -1 &&
          !used.count(to)) {
        q.push(to);
        used.insert(to);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("equivalence.in", "r", stdin);
  freopen("equivalence.out", "w", stdout);

  input();

  bfs();

  cout << "YES";
  return 0;
}
