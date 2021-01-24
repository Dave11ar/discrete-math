#include <bits/stdc++.h>

using namespace std;

int n;
vector<set<int>> g;
set<int> leaves;

void input() {
  cin >> n;
  g.resize(n);

  for (int i = 0; i < n - 1; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].insert(r);
    g[r].insert(l);
  }
}

void get_leaves() {
  for (int i = 0; i < n; i++) {
    if (g[i].size() == 1) {
      leaves.insert(i);
    }
  }
}

void solution() {
  for (int i = 0; i < n - 2; i++) {
    int leaf = *leaves.begin();
    leaves.erase(leaf);

    int parent = *g[leaf].begin();
    cout << parent + 1 << ' ';

    g[leaf].erase(parent);
    g[parent].erase(leaf);

    if (g[parent].size() == 1) {
      leaves.insert(parent);
    }
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
