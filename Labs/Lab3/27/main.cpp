#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextbrackets.in", "r", stdin);
  freopen("nextbrackets.out", "w", stdout);

  string s, ans;
  cin >> s;
  ans = s;

  int open = 0;
  int close = 0;
  for (int i = s.length() - 1; i >= 0; i--) {
    if (s[i] == '(') {
      if (open < close - 1) {
        ans[i] = ')';

        for (int j = i + 1; j <= i + open + 1; j++) {
          ans.push_back('(');
        }
        for (int j = i + open + 2; j < s.length(); j++) {
          ans.push_back(')');
        }

        break;
      }

      open++;
    } else {
     close++;
    }

    ans.pop_back();
  }

  if (ans.empty()) {
    cout << '-';
    return 0;
  }

  cout << ans;
  return 0;
}
