#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("vectors.in", "r", stdin);
  freopen("vectors.out", "w", stdout);

  int n;
  cin >> n;
  vector<string> vec;
  vec.push_back("");
  for (int i = 0; i < n; i++) vec[0].push_back('0');

  for (int i = 1; i < (1 << n); i++) {
    bool last = false;
    bool ans = true;

    int siz = (int)vec.size();
    vec.push_back("");
    for (int j =  n - 1; j >= 0; j--) {
      int num = (i / (1 << j)) % 2;
      vec[siz].push_back(num + '0');

      if (num == 1) {
        if (last) {
          ans = false;
          vec.pop_back();
          break;
        }
        last = true;
      } else {
        last = false;
      }
    }
  }

  cout << (int)vec.size() << '\n';

  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << '\n';
  }

  return 0;
}
