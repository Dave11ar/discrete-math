#include<bits/stdc++.h>

using namespace std;

vector<int> ans;

void output() {
  for (int i = (int)ans.size() - 1; i > 0; i--) {
    cout << ans[i] << "+";
  }

  cout << ans[0] << '\n';
}

void sol(int n, int j, int max_n) {
  if (j > n || j * max_n < n) {
    return;
  }
  if (n == 0 && j == 0) {
    output();
    return;
  }
  for (int i = max_n; i > 0; i--) {
    ans.push_back(i);
    sol(n - i,j - 1, i);
    ans.pop_back();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("partition.in", "r", stdin);
  freopen("partition.out", "w", stdout);

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    sol(n, i, n);
  }

  return 0;
}
