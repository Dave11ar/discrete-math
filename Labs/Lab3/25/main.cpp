#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextchoose.in", "r", stdin);
  freopen("nextchoose.out", "w", stdout);

  int n, k;
  cin >> n >> k;

  vector<int> vec(k);

  for (int i = 0; i < k; i++) {
    cin >> vec[i];
  }

  if (vec[0] == n - k + 1) {
    cout << -1;
    return 0;
  }

  for (int i = k - 1; i >= 0; i--) {
    if (vec[i] != n + i - k + 1) {
      for (int j = 0; j < i; j++) {
        cout << vec[j] << ' ';
      }
      vec[i]++;
      cout << vec[i] << ' ';

      for (int j = i + 1; j < k; j++){
        vec[j] = vec[j - 1] + 1;
        cout << vec[j] << ' ';
      }
      break;
    }
  }

  return 0;
}
