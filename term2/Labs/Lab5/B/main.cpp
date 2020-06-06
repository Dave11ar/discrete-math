#include <bits/stdc++.h>

using namespace std;

int n;
char S;

set<int> st;
set<int> in;

vector<int> ans;

vector<vector<vector<int>>> vec(26);

void input() {
  cin >> n >> S;

  in.insert(S - 'A');
  string str;
  getline(cin, str);

  for (int i = 0; i < n; i++) {
    getline(cin, str);
    in.insert(str[0] - 'A');

    vector<int> to;
    bool b = true;
    for (int j = 5; j < str.size(); j++) {
      if (str[j] > 90) {
        b = false;
        break;
      }

      to.push_back(str[j] - 'A');
    }

    if (b) {
      vec[str[0] - 'A'].push_back(to);
    }
  }
}

void solution() {
  bool b = true;

  while (b) {
    b = false;

    for (int i = 0; i < 26; i++) {
      if (st.count(i) || !in.count(i)) continue;

      bool t = false;
      for (int j = 0; j < vec[i].size(); j++) {
        bool bruh = false;
        for (int k = 0; k < vec[i][j].size(); k++) {
          if (!st.count(vec[i][j][k])) {
            bruh = true;
          }
        }

        if (!bruh) {
          st.insert(i);
          t = true;
          break;
        }
      }

      if (t) {
        st.insert(i);
        ans.push_back(i);
        b = true;
      }
    }
  }

  sort(ans.begin(), ans.end());

  for (int i = 0; i < ans.size(); i++) {
    cout << (char)(ans[i] + 'A') << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("epsilon.in", "r", stdin);
  freopen("epsilon.out", "w", stdout);

  input();
  solution();

  return 0;
}
