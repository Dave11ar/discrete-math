#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

string s;
set<int> allowed;
vector<map<char, int>> edges;

void go(int v, int cur) {
  if (cur == s.length()) {
    cout << (allowed.count(v) ? "Accepts" : "Rejects");
    exit(0);
  }

  if (!edges[v].count(s[cur])) {
    cout << "Rejects";
    exit(0);
  }
  go(edges[v][s[cur]], cur + 1);
}

int main() {
  freopen("problem1.in", "r", stdin);
  freopen("problem1.out", "w", stdout);

  int n, m, k;
  cin >> s >> n >> m >> k;

  edges.resize(n);
  for (int i = 0; i < k; ++i) {
    int t;
    cin >> t;
    t--;
    allowed.insert(t);
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    a--; b--;
    edges[a].insert({ c, b });
  }


  go(0, 0);

  return 0;
}
