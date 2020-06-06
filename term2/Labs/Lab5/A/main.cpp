#include <bits/stdc++.h>

using namespace std;

int n, m;
char S;

vector<vector<vector<int>>> g(26, vector<vector<int>>(26));
vector<vector<bool>> vec(26, vector<bool>(26));
string s;

bool dfs(int v, int w) {
  if (w == (int)s.size() - 1) {
    return vec[v][s[w] - 'a'];
  }

  bool ans = false;
  for (int i = 0; i < (int)g[v][s[w] - 'a'].size(); i++) {
    ans |= dfs(g[v][s[w] - 'a'][i], w + 1);
  }
  return ans;
}

void input() {
  cin >> n >> S;

  for (int i = 0; i < n; i++) {
    string from, to;
    cin >> from >> to >> to;

    if (to.size() == (size_t)2) {
      g[from[0] - 'A'][to[0] - 'a'].push_back(to[1] - 'A');
    } else {
      vec[from[0] - 'A'][to[0] - 'a'] = true;
    }
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> s;

    cout << (dfs(S - 'A', 0) ? "yes" : "no") << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("automaton.in", "r", stdin);
  freopen("automaton.out", "w", stdout);

  input();

  return 0;
}
