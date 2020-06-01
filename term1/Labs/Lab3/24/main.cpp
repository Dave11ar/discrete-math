#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> vec, ans;

void prev() {
  ans = vec;
  int first;

  for (int i = n - 2; i >= 0; i--) {
    if (vec[i] > vec[i + 1]) {
      first = i;
      break;
    }
  }

  pair<int, int> lesser = {-1e9, -1};
  for (int i = n - 1; i > first; i--) {
    if (vec[i] < vec[first] && vec[i] > lesser.first) {
      lesser = {vec[i], i};
    }
  }

  int tmp = ans[first];
  ans[first] = ans[lesser.second];
  ans[lesser.second] = tmp;
  reverse(ans.begin() + first + 1, ans.end());
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
}

void next() {
  ans = vec;
  int first;

  for (int i = n - 2; i >= 0; i--) {
    if (vec[i] < vec[i + 1]) {
      first = i;
      break;
    }
  }

  pair<int, int> bigger = {1e9, 1};
  for (int i = n - 1; i > first; i--) {
    if (vec[i] > vec[first] && vec[i] < bigger.first) {
      bigger = {vec[i], i};
    }
  }

  swap(ans[first], ans[bigger.second]);
  reverse(ans.begin() + first + 1, ans.end());
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextperm.in", "r", stdin);
  freopen("nextperm.out", "w", stdout);

  cin >> n;
  vec.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  bool first = true;
  bool last = true;
  for (int i = 1; i < n; i++) {
    if (vec[i] > vec[i - 1]) {
      first = false;
    } else {
      last = false;
    }
  }

  if (last) {
    for (int i = 0; i < n; i++) {
      cout << "0 ";
    }
  } else {
    prev();
  }

  cout << '\n';

  if (first) {
    for (int i = 0; i < n; i++) {
      cout << "0 ";
    }
  } else {
    next();
  }

  return 0;
}
