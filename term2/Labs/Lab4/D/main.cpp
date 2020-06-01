#include <bits/stdc++.h>

using namespace std;

int n, m, k, l;
vector<int> allowed;
vector<vector<int>> vec;
vector<vector<long long>> dp;
int MOD = 1e9 + 7;

int main() {
  freopen("problem4.in", "r", stdin);
  freopen("problem4.out", "w", stdout);
  cin >> n >> m >> k >> l;
  vec.resize(n);
  dp.resize(n, vector<long long>(l + 1));
  dp[0][0] = 1;

  for (int i = 0; i < k; i++) {
    int t;
    cin >> t;
    allowed.push_back(t - 1);
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    vec[b - 1].push_back(a - 1);
  }

  for (int len = 1; len <= l; len++) {
    for (int vertex = 0; vertex < n; vertex++) {
      for (int from = 0; from < vec[vertex].size(); from++) {
        dp[vertex][len] = (dp[vertex][len] + dp[vec[vertex][from]][len - 1]) % MOD;
      }
    }
  }

  long long ans = 0;

  for (int i : allowed) {
    ans = (ans + dp[i][l]) % MOD;
  }

  cout << ans;

  return 0;
}