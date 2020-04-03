#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> ans, vec;

long long fact(int n) {
  long long res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }

  return res;
}

void perm(int v, long long k) {
  if (v > n) {
    return;
  }
  for (int i = (int)vec.size() - 1; i >= 0; i--) {
    long long numPerm = i * fact(n - v);

    if (numPerm <= k) {
      ans.push_back(vec[i]);
      vec.erase(vec.begin() + i);
      perm(v + 1, k - numPerm);
      break;
    }
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("num2perm.in", "r", stdin);
  freopen("num2perm.out", "w", stdout);

  long long k;
  cin >> n >> k;

  for (int i = 1; i <= n; i++) {
    vec.push_back(i);
  }

  perm(1, k);

  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
