#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("brackets.in", "r", stdin);
  freopen("brackets.out", "w", stdout);

  int n;
  cin >> n;

  string s;
  for (int i = 0; i < n; i++) s.push_back('(');
  for (int i = 0; i < n; i++) s.push_back(')');

  bool ready = true;
  do {
    int d = 0;
    cout << s << '\n';

    ready = false;
    for (int i = 2 * n - 1; i > 0; i--) {
      if (s[i] == '(') {
        d--;
      } else {
        d++;
      }
      if (s[i] == '(' && d > 0) {
        s[i] = ')';
        d--;
        int num = 2 * n - i - 1;
        int open = (num - d) / 2;
        int close = num - open;

        for (int j = i + 1; j <= i + open; j++) s[j] = '(';
        for (int j = i + open + 1; j < 2 * n; j++) s[j] = ')';
        ready = true;
        break;
      }
    }


  } while (ready);

  return 0;
}
