#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("chaincode.in", "r", stdin);
  freopen("chaincode.out", "w", stdout);

  int n;
  cin >> n;

  set<string> st;
  string t;

  for (int i = 0; i < n; i++) t.push_back('0');

  cout << t << '\n';
  st.insert(t);

  for (int i = 1; i < (1 << n); i++) {
    t.erase(t.begin());

    if (st.find(t + "1") == st.end()) {
      t += '1';
    } else {
      t += '0';
    }
    st.insert(t);
    cout << t << '\n';
  }

  return 0;
}
