#include<bits/stdc++.h>

using namespace std;

vector<int> cur;

void sub(int i) {
  if (cur[i] == 1) {
    cur[i] = 0;
    return;
  }

  cur[i] = 1;
  sub(i - 1);
}

void add(int i) {
  if (cur[i] == 0) {
    cur[i] = 1;
    return;
  }

  cur[i] = 0;
  add(i - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("nextvector.in", "r", stdin);
  freopen("nextvector.out", "w", stdout);

  vector<int> vec;
  string s;
  getline(cin, s);

  int ed = 0;
  for (int i = 0; i < s.length(); i++) {
    vec.push_back(s[i] - '0');
    if (s[i] == '1') {
      ed++;
    }
  }

  if (ed == 0) {
    cout << "-";
  } else {
    cur = vec;
    sub((int)cur.size() - 1);
    for (int i = 0; i < (int)cur.size(); i++) {
      cout << cur[i];
    }
  }

  cout << '\n';

  if (ed == (int)vec.size()) {
    cout << "-";
  } else {
    cur = vec;
    add((int)cur.size() - 1);
    for (int i = 0; i < (int)cur.size(); i++) {
      cout << cur[i];
    }
  }
  return 0;
}
