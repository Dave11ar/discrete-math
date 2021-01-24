#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    vec[i] = i + 1;
  }

  stable_sort(vec.begin(), vec.end(), [](int const &a, int const &b) {
    string s;
    cout << "1 " << a << ' ' << b << '\n';
    cin >> s;

    return s == "YES";
  });

  cout << "0 ";
  for (int &i : vec) {
    cout << i << ' ';
  }

  return 0;
}
