#include <bits/stdc++.h>

using namespace std;

int n, m, k, l;
set<int> allowed;
vector<vector<vector<int>>> vec;
vector<vector<long long>> dp;
int MOD = 1e9 + 7;

map<set<int>, int> dka;
vector<vector<int>> bruhEdges(10000);
set<int> swallowAllowed;
int number = 0;

void tompson() {
  queue<set<int>> queueVertex;
  set<int> s;
  s.insert(0);
  queueVertex.push(s);

  dka.insert({ s, number++ });

  while (!queueVertex.empty()) {
    set<int> curVertex = queueVertex.front();
    queueVertex.pop();

    for (int curAllow : allowed) {
      if (curVertex.count(curAllow)) {
        swallowAllowed.insert(dka[curVertex]);
        break;
      }
    }

    for (int i = 0; i < 26; i++) {
      set<int> go;

      for (int cur : curVertex) {
        for (int j : vec[cur][i]) {
          go.insert(j);
        }
      }

      if (!dka.count(go)) {
        dka.insert({ go, number++ });
        queueVertex.push(go);
      }
      bruhEdges[dka[go]].push_back(dka[curVertex]);
    }
  }
}

int main() {
  freopen("problem5.in", "r", stdin);
  freopen("problem5.out", "w", stdout);

  cin >> n >> m >> k >> l;
  vec.resize(n, vector<vector<int>>(26));

  for (int i = 0; i < k; i++) {
    int t;
    cin >> t;
    allowed.insert(t - 1);
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    vec[a - 1][c - 'a'].push_back(b - 1);
  }

  //-------
  tompson();
  //-------

  dp.resize(number, vector<long long>(l + 1));
  dp[0][0] = 1;
  for (int len = 1; len <= l; len++) {
    for (int vertex = 0; vertex < number; vertex++) {
      for (int from = 0; from < bruhEdges[vertex].size(); from++) {
        dp[vertex][len] = (dp[vertex][len] + dp[bruhEdges[vertex][from]][len - 1]) % MOD;
      }
    }
  }

  long long ans = 0;

  for (int cur : swallowAllowed) {
    ans = (ans + dp[cur][l]) % MOD;
  }

  cout << ans;

  return 0;
}