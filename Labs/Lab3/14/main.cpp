#include<bits/stdc++.h>

using namespace std;

int n;
long long ans = 0;
vector<int> perm, vec;

long long fact(int n) {
  long long res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }

  return res;
}

void numPerm(int v) {
  if (v == n){
    return;
  }

  for (int i = (int)vec.size() - 1; i >= 0; i--) {
    if (perm[v] == vec[i]) {
      ans += i * fact(n - v - 1);
      vec.erase(vec.begin() + i);
      numPerm(v + 1);
      break;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("perm2num.in", "r", stdin);
  freopen("perm2num.out", "w", stdout);

  cin >> n;
  perm.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> perm[i];
  }

  for (int i = 1; i <= n; i++) {
    vec.push_back(i);
  }

  numPerm(0);

  cout << ans;

  return 0;
}
