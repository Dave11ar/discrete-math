#include <bits/stdc++.h>

using namespace std;

int n;
char S;

set<int> good, in;
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
    bool term = true;
    for (int j = 5; j < str.size(); j++) {
      if (str[j] <= 90) {
        term = false;
        to.push_back(str[j] - 'A');
        in.insert(str[j] - 'A');
      }
    }

    if (term) {
      good.insert(str[0] - 'A');
    } else {
      vec[str[0] - 'A'].push_back(to);
    }
  }
}

void get_good() {
  bool modif = true;
  while (modif) {
    modif = false;

    for (int i = 0; i < 26; i++) {
      if (!in.count(i) || good.count(i)) continue;

      bool gd = false;
      for (int j = 0; j < vec[i].size(); j++) {
        bool cur_gd = true;
        for (int cur = 0; cur < vec[i][j].size(); cur++) {
          if (!good.count(vec[i][j][cur])) {
            cur_gd = false;
            break;
          }
        }

        if (cur_gd) {
          gd = true;
          break;
        }
      }

      if (gd) {
        good.insert(i);
        modif = true;
      }
    }
  }
}

void remove_trash() {
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      bool gd = true;
      for (int k = 0; k < vec[i][j].size(); k++) {
        if (!good.count(vec[i][j][k])) {
         gd = false;
        }
      }

      if (!gd) {
        vec[i].erase(vec[i].begin() + j);
        j--;
      }
    }
  }
}

set<int> reachable;

void remove_unreachable() {
  bool modif = true;
  reachable.insert(S - 'A');

  while (modif) {
    modif = false;

    for (int i = 0; i < 26; i++) {
      if (!reachable.count(i)) continue;

      for (int j = 0; j < vec[i].size(); j++) {
        for (int cur = 0; cur < vec[i][j].size(); cur++) {
          if (!reachable.count(vec[i][j][cur])) {
            reachable.insert(vec[i][j][cur]);
            modif = true;
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

  freopen("useless.in", "r", stdin);
  freopen("useless.out", "w", stdout);

  input();
  get_good();
  remove_trash();
  remove_unreachable();

  for (int cur : in) {
    if (!good.count(cur) || !reachable.count(cur)) {
      cout << (char)(cur + 'A') << ' ';
    }
  }

  return 0;
}
