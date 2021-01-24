#include <bits/stdc++.h>

using namespace std;

int n, m;
unordered_set<bitset<10>> I;
vector<bitset<10>> I_iterate;
vector<int> size_of_set;
void input() {
  cin >> n >> m;

  size_of_set.resize(m);

  for (int i = 0; i < m; i++) {
    int siz;
    cin >> siz;

    bitset<10> st;
    for (int j = 0; j < siz; j++) {
      int tmp;
      cin >> tmp;
      tmp--;

      st.set(tmp);
    }

    size_of_set[i] = siz;
    I_iterate.push_back(st);
    I.insert(st);
  }
}

bool check_1() {
  return any_of(I.begin(), I.end(), [](bitset<10> const &a) {return a == 0;});
}

bool check_subsets(bitset<10> const& a) {
  if (I.count(a) == 0) {
    return false;
  }

  int siz = 0;
  for (int i = 0; i < n; i++) {
    siz += a[i];
  }

  if (siz == 1) {
    return true;
  }

  bitset<10> b(a);

  for (int i = 0; i < n; i++) {
    if (b[i]) {
      b.reset(i);
      if (!check_subsets(b)) {
        return false;
      }
      b.set(i);
    }
  }

  return true;
}

bool check_2() {
  return !any_of(I.begin(), I.end(), [](bitset<10> const &a) {return !check_subsets(a);});
}

// |a| < |b|
bool check_subset(bitset<10> &a, bitset<10> const &b) {
  for (int i = 0; i < n; i++) {
    if (b[i] && !a[i]) {
      a.set(i);
      if (I.count(a) != 0) {
        a.reset(i);
        return true;
      }

      a.reset(i);
    }
  }
  return false;
}

bool check_3() {
  for (int i = 0; i < m; i++) {
    bitset<10> tmp(I_iterate[i]);

    for (int j = 0; j < m; j++) {
      if (size_of_set[i] < size_of_set[j] && !check_subset(tmp, I_iterate[j])) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("check.in", "r", stdin);
  freopen("check.out", "w", stdout);

  input();
  cout << (check_1() && check_2() && check_3() ? "YES" : "NO");

  return 0;
}
