#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;
char S;

vector<vector<bool>> terminal(26, vector<bool>(26));
vector<vector<pair<int, int>>> non_terminal(26);
string s;

vector<vector<vector<ll>>> dp;

void input() {
  cin >> n >> S;

  for (int i = 0; i < n; i++) {
    char from;
    string to;
    cin >> from >> to >> to;

    if (to.size() == 1) {
      terminal[from - 'A'][to[0] - 'a'] = true;
    } else {
      non_terminal[from - 'A'].push_back({to[0] - 'A', to[1] - 'A'});
    }
  }
  cin >> s;
}

void set_terminals() {
  dp.resize(26, vector<vector<ll>>(s.size(), vector<ll>(s.size())));
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < 26; j++) {
      if (terminal[j][s[i] - 'a']) dp[j][i][i] = 1;
    }
  }
}

void get_dp() {
  for (int m = 1; m < s.size(); m++) {
    int l = 0, r = m;

    for ( ; r < s.size(); l++, r++) {
      for (int k = l; k < r; k++) {
        for (int A = 0; A < 26; A++) {
          for (int BC = 0; BC < non_terminal[A].size(); BC++) {
            int B = non_terminal[A][BC].first;
            int C = non_terminal[A][BC].second;

            dp[A][l][r] += dp[B][l][k] * dp[C][k + 1][r];
            dp[A][l][r] %= 1000000007;
          }
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("nfc.in", "r", stdin);
  freopen("nfc.out", "w", stdout);

  input();
  set_terminals();
  get_dp();

  cout << dp[S - 'A'][0][s.size() - 1];
  return 0;
}
