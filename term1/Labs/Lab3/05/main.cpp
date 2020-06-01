#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("telemetry.in", "r", stdin);
  freopen("telemetry.out", "w", stdout);

  int n, k;
  cin >> n >> k;
  vector<string> vec;

  for (int i = 0; i < k; i++) {
    vec.push_back(to_string(i));
  }

  for (int i = 1; i < n; i++) {
    int siz = (int)vec.size();
    int last = siz - 1;

    for (int j = 0; j < k - 1; j++) {
      for (int p = last; p > last - siz; p--) {
        vec.push_back(vec[p]);
      }
      last += siz;
    }

    last = -1;
    for (int j = 0; j < vec.size(); j++) {
      if (j % (int)pow(k, i) == 0) {
        last++;
      }
      vec[j] = to_string(last) + vec[j];
    }
  }

  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << '\n';
  }

  return 0;
}
