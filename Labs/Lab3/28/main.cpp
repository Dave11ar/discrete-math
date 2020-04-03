#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextmultiperm.in", "r", stdin);
  freopen("nextmultiperm.out", "w", stdout);

  int n;
  cin >> n;
  vector<int> vec(n);

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  for (int i = n - 2; i >= 0; i--) {
    if (vec[i] < vec[i + 1]) {
      pair<int, int> mn = {1e9, 1e9};
      for (int j = n - 1; j > i; j--) {
        if (vec[j] > vec[i] && vec[j] < mn.first) {
          mn = {vec[j], j};
        }
      }

      swap(vec[i], vec[mn.second]);
      sort(vec.begin() + i + 1, vec.end());
      for (int j = 0; j < n; j++) {
        cout << vec[j] << ' ';
      }
      return 0;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << "0 ";
  }

  return 0;
}
