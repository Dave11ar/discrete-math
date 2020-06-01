#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("permutations.in", "r", stdin);
  freopen("permutations.out", "w", stdout);

  int n;
  cin >> n;

  vector<int> vec(n);
  int k = 1;

  for (int i = 0; i < n; i++) {
    vec[i] = i + 1;
    k *= i + 1;
  }

  for (int i = 0; i < k; i++) {
    for (int i = 0; i < n; i++) {
      cout << vec[i] << ' ';
    }
    cout << '\n';

    for (int j = n - 1; j >= 0; j--) {
     pair<int, int> mn = {10, 1};
     for (int t = n - 1; t > j; t--) {
       if (vec[t] > vec[j] && mn.first > vec[t]) {
         mn = { vec[t], t };
       }
     }

     if (mn.first != 10) {
       swap(vec[j], vec[mn.second]);
       sort(vec.begin() + j + 1, vec.end());
       break;
     }
    }
  }

  return 0;
}
