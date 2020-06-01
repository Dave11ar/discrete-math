#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

string s;
set<int> allowed;
vector<map<char, vector<int>>> edges;
set<pair<int, int>> was;

void go(int v, int cur) {
  if (was.count({ v, cur })) return;
  was.insert({ v, cur });

  if (cur == s.length() && allowed.count(v)) {
    cout << "Accepts";
    exit(0);
  }
  int count = edges[v][s[cur]].size();
  for (int i = 0; i < count; i++) {
    go(edges[v][s[cur]][i], cur + 1);
  }
}

int main() {
  freopen("problem2.in", "r", stdin);
  freopen("problem2.out", "w", stdout);

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
    edges[a][c].push_back(b);
  }

  go(0, 0);

  cout << "Rejects";

  return 0;
}
