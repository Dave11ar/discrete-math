#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> deg, pruf;
vector<pair<int, int>> edges;
set<int> leaves;

void input() {
  cin >> n;
  deg.resize(n);
  pruf.resize(n - 2);

  for (int i = 0; i < n - 2; i++) {
    int t;
    cin >> t;
    t--;

    pruf[i] = t;
    deg[t]++;
  }
}

void get_leaves() {
  for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
      leaves.insert(i);
    }
  }
}

void solution() {
  for (int i = 0; i < n - 2; i++) {
    int leaf = *leaves.begin();
    leaves.erase(leaf);

    edges.emplace_back(leaf, pruf[i]);
    deg[pruf[i]]--;

    if (deg[pruf[i]] == 0) {
      leaves.insert(pruf[i]);
    }
  }

  edges.emplace_back(*leaves.begin(), *++leaves.begin());

  for (pair<int, int>  &cur : edges) {
    cout << cur.first + 1 << ' ' << cur.second + 1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  get_leaves();
  solution();

  return 0;
}
