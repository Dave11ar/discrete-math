#include<bits/stdc++.h>

using namespace std;

int n, k;
vector<int> perm;
long long m = 0;
long long C[40][40];
int v = 0;

void sol(int first) {
  if (k == 0) {
    return;
  }

  int lastGood = first;
  long long lost = 0;
  for (int i = first; i <= n; i++) {
    long long cur = C[n - i][k - 1];
    if (perm[v] != i) {
      lost += cur;
    } else {
      lastGood = i;
      break;
    }
  }

  m += lost;
  v++;
  k--;
  sol(lastGood + 1);
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("choose2num.in", "r", stdin);
  freopen("choose2num.out", "w", stdout);

  cin >> n >> k;
  perm.resize(n);
  for (int i = 0; i < k; i++) {
    cin >> perm[i];
  }

  C[0][0]= 1;

  for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }

  sol(1);

  cout << m;

  return 0;
}
