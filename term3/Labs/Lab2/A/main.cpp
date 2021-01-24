#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> dw;
set<int> free_place;

int64_t ans = 0;

void input() {
  cin >> n;

  for (int i = 0; i < n; i++) {
    free_place.insert(i);

    int d, w;
    cin >> d >> w;

    dw.emplace_back(w, d - 1);
  }
}

void solution() {
  sort(dw.begin(), dw.end(), [](pair<int, int> const &a, pair<int, int> const &b) {
    return (a.first != b.first ? a.first > b .first : a.second < b.second);
  });

  for (auto &cur : dw) {
    if (cur.second >= n) {
      continue;
    }

    auto it = free_place.lower_bound(cur.second);

    if (*it == cur.second || it != free_place.begin()) {
      free_place.erase(*it == cur.second ? *it : *--it);
    } else {
      ans += cur.first;
    }
  }

  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("schedule.in", "r", stdin);
  freopen("schedule.out", "w", stdout);

  input();
  solution();

  return 0;
}
