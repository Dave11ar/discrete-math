#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  //freopen("num2part.in", "r", stdin);
  //freopen("num2part.out", "w", stdout);

  int n, r;
  cin >> n >> r;

  vector<vector<int>> dp(n + 1, vector<int>(n + 1));

  for (int i = 1; i <= n; i++) {
    dp[i][i] = 1;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      for (int k = j; k <= n; k++) {
        dp[i][j] += dp[i - j][k];
      }
    }
  }
  int mn = n;
  vector<int> ans;
  for (int i = 1; i <= n;) {
    if (r == 0) {
      ans.push_back(i);
      break;
    }
    for (int j = 0; j <= mn; j++) {
      if (r - dp[i][j] >= 0) {
        r -= dp[i][j];
      } else {
        ans.push_back(j);
        i -= j;
        mn = j;
        break;
      }
    }
  }

  reverse(ans.begin(), ans.end());
  cout << ans[0];
  for (int i = 1; i < ans.size(); i++) {
    cout << '+' << ans[i];
  }

  return 0;
}
