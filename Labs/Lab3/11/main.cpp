#include<bits/stdc++.h>

using namespace std;

vector<int> vec;
int n;

void output() {
  for (int i = 0; i < (int)vec.size(); i++) {
    cout << vec[i] << ' ';
   }
  cout << '\n';
}

void sol(int v) {
  if (v > n) {
    return;
  }
  vec.push_back(v);
  output();
  sol(v + 1);
  vec.pop_back();

  if (v == n) {
    return;
  }
  sol(v + 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("subsets.in", "r", stdin);
  freopen("subsets.out", "w", stdout);

  cin >> n;

  cout << '\n';
  sol(1);

  return 0;
}
