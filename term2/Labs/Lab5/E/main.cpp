#include <bits/stdc++.h>

using namespace std;

int n;
char S;
string s;

vector<vector<vector<char>>> vec(26);
vector<vector<vector<bool>>> a;
vector<vector<vector<vector<vector<bool>>>>> h;

void init() {
  a.resize(26, vector<vector<bool>>(s.size() + 1, vector<bool>(s.size() + 1)));
  h.resize(26);
  for (int i = 0; i < 26; i++) {
    h[i].resize(vec[i].size(), vector<vector<vector<bool>>>(s.size() + 1, vector<vector<bool>>(s.size() + 1, vector<bool>(1))));
  }
}

void input() {
  cin >> n >> S;

  string str;
  getline(cin, str);
  for (int i = 0; i < n; i++) {
    getline(cin, str);

    vector<char> to;
    for (int j = 5; j < str.size(); j++) {
      to.push_back(str[j]);
    }

    vec[str[0] - 'A'].push_back(to);
  }

  cin >> s;
  init();
}

bool terminal(char cur) {
  return 'a' <= cur && cur <= 'z';
}

void dp_base() {
  for (int border = 0; border <= s.size(); border++) {
    for (int left = 0; left < 26; left++) {
      for (int right = 0; right < vec[left].size(); right++) {
        if (vec[left][right].size() == 0) {
          // A ->
          a[left][border][border] = true;
        } else if (border != s.size() && vec[left][right].size() == 1 && vec[left][right][0] == s[border]) {
          // A -> a
          a[left][border][border + 1] = true;
        }

        h[left][right][border][border][0] = true;
      }
    }
  }
}

void dp_count() {
  for (int shift = 0; shift <= s.size(); shift++) {
    for (int i = 0; i <= s.size() - shift; i++) {
      //count h
      for (int repeat = 0; repeat < 27; repeat++) {
        for (int left = 0; left < 26; left++) {
          for (int right = 0; right < vec[left].size(); right++) {
            for (int k = 0; k < vec[left][right].size(); k++) {
              for (int r = 0; r <= shift; r++) {
                if (terminal(vec[left][right][k])) {
                  if (r == shift - 1) {
                    h[left][right][i][i + shift][k + 1] = h[left][right][i][i + shift][k + 1] ||
                        (h[left][right][i][i + r][k] && (vec[left][right][k] == s[i + r]));
                  }
                  continue;
                }
                h[left][right][i][i + shift][k + 1] = h[left][right][i][i + shift][k + 1] ||
                    (h[left][right][i][i + r][k] && a[vec[left][right][k] - 'A'][i + r][i + shift]);
              }
            }
          }
        }

        //count a
        for (int left = 0; left < 26; left++) {
          for (int right = 0; right < vec[left].size(); right++) {
            a[left][i][i + shift] = a[left][i][i + shift] ||
                h[left][right][i][i + shift][vec[left][right].size()];
          }
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("cf.in", "r", stdin);
  freopen("cf.out", "w", stdout);

  input();
  dp_base();
  dp_count();

  cout << (a[S - 'A'][0][s.size()] ? "yes" : "no");

  return 0;
}