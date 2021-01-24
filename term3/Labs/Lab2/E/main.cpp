#include <bits/stdc++.h>

using namespace std;

constexpr int N = 20;
int n, m;
unordered_set<bitset<N>> I;
vector<pair<int, int>> w;
vector<bitset<N>> I_iterate;

void input() {
  cin >> n >> m;

  w.resize(n);
  for (int i = 0; i < n; i++) {
    int cost;
    cin >> cost;
    w.emplace_back(cost, i);
  }

  for (int i = 0; i < m; i++) {
    int siz;
    cin >> siz;

    bitset<N> st;
    for (int j = 0; j < siz; j++) {
      int tmp;
      cin >> tmp;
      tmp--;

      st.set(tmp);
    }

    I.insert(st);
    I_iterate.push_back(st);
  }
}

void add(bitset<N> const& a, bool start) {
  if (!start && I.count(a) != 0) {
    return;
  }

  I.insert(a);

  int siz = 0;
  for (int i = 0; i < n; i++) {
    siz += a[i];
  }

  if (siz == n) {
    return;
  }

  bitset<N> b(a);

  for (int i = 0; i < n; i++) {
    if (!b[i]) {
      b.set(i);
      add(b, false);
      b.reset(i);
    }
  }
}

void add_dependent() {
  for (int i = 0; i < m; i++) {
    add(I_iterate[i], true);
  }
}

void rado_edmonds() {
  sort(w.begin(), w.end(), [](pair<int, int> const &a, pair<int, int> const &b) {
    return a.first > b.first;
  });

  int ans = 0;
  bitset<N> base;
  for (int i = 0; i < n; i++) {
    base.set(w[i].second);
    if (I.count(base) == 0) {
      ans += w[i].first;
    } else {
      base.reset(w[i].second);
    }
  }

  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("cycles.in", "r", stdin);
  freopen("cycles.out", "w", stdout);

  input();
  add_dependent();
  rado_edmonds();

  return 0;
}