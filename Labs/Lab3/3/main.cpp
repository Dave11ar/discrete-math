#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("antigray.in", "r", stdin);
  freopen("antigray.out", "w", stdout);

  int n;
  cin >> n;

  for (int i = 0; i < (pow(3, n - 1)); i++) {
    for (int shift = 0; shift < 3; shift++) {
      for (int j = n - 1; j >= 0; j--) {
        cout << (int) (i / pow(3, j) + shift) % 3;
      }

      cout << '\n';
    }
  }

  return 0;
}
