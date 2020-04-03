#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("choose.in", "r", stdin);
  freopen("choose.out", "w", stdout);

  int n, k;
  cin >> n >> k;
  vector<vector<int>> vec;

  for (int i = 0; i < (1 << n); i++) {
    int cur = i ^ (i / 2);
    int sc = 0;
    vector<int> s;

    for (int j =  n - 1; j >= 0; j--) {
      if (((cur / (1 << j)) % 2) == 1) {
        sc++;
        s.push_back(j + 1);
      }
    }

    if (sc == k) {
      reverse(s.begin(), s.end());
      vec.push_back(s);
    }
  }

  sort(vec.begin(), vec.end());

  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      cout << vec[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
