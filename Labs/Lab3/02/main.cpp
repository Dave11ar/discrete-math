#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("gray.in", "r", stdin);
  freopen("gray.out", "w", stdout);

  int n;
  cin >> n;

  for (int i = 0; i < (1 << n); i++) {
    int cur = i ^ (i / 2);

    for (int j =  n - 1; j >= 0; j--) {
      cout << (cur / (1 << j)) % 2;
    }
    cout << '\n';
  }

  return 0;
}
