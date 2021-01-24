#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> w;
vector<vector<int>> g;
void input() {
  cin >> n;

  w.resize(n);
  g.resize(n * 2);

  for (int i = 0; i < n; i++) {
    int weight;
    cin >> weight;

    w[i] = {abs(weight), i};
  }

  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;

    for (int j = 0; j < num; j++) {
      int to;
      cin >> to;
      to = n + to - 1;

      g[i].push_back(to);
      g[to].push_back(i);
    }
  }
}

int timer = 1;
vector<int> used, matching;

bool dfs(int v) {
  if (used[v] == timer) {
    return false;
  }
  used[v] = timer;

  for (int to : g[v]) {
    if (matching[to] == -1 || dfs(matching[to])) {
      matching[to] = v;
      matching[v] = to;
      return true;
    }
  }
  return false;
}

void kuhn() {
  used.resize(n * 2);
  matching.resize(n * 2, -1);

  sort(w.begin(), w.end(), [](pair<int, int> const &a, pair<int, int> const &b) {
    return a.first > b.first;
  });

  for (int i = 0; i < n; i++) {
    int cur = w[i].second;
    if (matching[cur] == -1) {
      dfs(cur);
      timer++;
    }
  }
}

void solution() {
  for (int i = 0; i < n; i++) {
    cout << (matching[i] == -1 ? 0 : matching[i] + 1 - n) << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);

  input();
  kuhn();
  solution();

  return 0;
}
