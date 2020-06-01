#include <bits/stdc++.h>

using namespace std;

vector<int> allowed;
vector<vector<int>> reverseEdges;
vector<int> used;
vector<long long> num;

long long MOD = 1e9 +  7;

vector<bool> u;

bool dfs(int v) {
  u[v] = true;
  if (v == 0) return true;

  for (int to : reverseEdges[v]) {
    if (!u[to]) {
      if (dfs(to)) return true;
    }
  }
  return false;
}

void go(int v) {
  if (used[v] == 2) return;

  used[v] = 1;

  for (int to : reverseEdges[v]) {
    if (used[to] == 1) {
      if (dfs(v)) {
        cout << -1;
        exit(0);
      }
    } else {
      go(to);
      num[v] = (num[v] + num[to]) % MOD;
    }
  }

  used[v] = 2;
}

int main() {
  freopen("problem3.in", "r", stdin);
  freopen("problem3.out", "w", stdout);

  int n, m, k;
  cin >> n >> m >> k;

  used.resize(n);
  reverseEdges.resize(n);
  num.resize(n);
  allowed.resize(k);
  num[0] = 1;
  u.resize(n);

  for (int i = 0; i < k; ++i) {
    int t;
    cin >> t;
    t--;
    allowed[i] = t;
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    a--; b--;
    reverseEdges[b].push_back(a);
  }

  long long ans = 0;
  for (int vert : allowed) {
    go(vert);
    ans = (ans + num[vert]) % MOD;
  }

  cout << ans;

  return 0;
}
