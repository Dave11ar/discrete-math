#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextpartition.in", "r", stdin);
  freopen("nextpartition.out", "w", stdout);


  string s;
  cin >> s;

  int n = s.length();
  int k = 0;
  while (s[k] != '=') {
    k++;
  }

  bool no_sol = true;
  for (int i = k; i < n; i++) {
    if (s[i] == '+') {
      no_sol = false;
      break;
    }
  }

  if (no_sol) {
    cout << "No solution";
    return 0;
  }

  string tmp;
  vector<int> vec;
  tmp.clear();
  for (int i = k + 1; i < n; i++) {
    if (s[i] == '+') {
      vec.push_back(stoi(tmp));
      tmp.clear();
      continue;
    }

    tmp.push_back(s[i]);
  }
  vec.push_back(stoi(tmp));
  int siz = vec.size();

  vec[siz - 2]++;
  vec[siz - 1]--;

  if (vec[siz - 2]  > vec[siz - 1]) {
    vec[siz - 2] += vec[siz - 1];
    vec.pop_back();
  } else if (2 * vec[siz - 2] <= vec[siz - 1]) {
    int t = vec[siz - 1];
    vec.pop_back();
    while (2 * vec[siz - 2] <= t) {
      vec.push_back(vec[siz - 2]);
      t -= vec[siz - 2];
    }

    vec.push_back(t);
  }

  k = 0;
  while (s[k] != '=') {
    cout << s[k];
    k++;
  }
  cout << '=';

  for (int i = 0; i < vec.size() - 1; i++) {
    cout << vec[i] << '+';
  }
  cout << vec[vec.size() - 1];

  return 0;
}
