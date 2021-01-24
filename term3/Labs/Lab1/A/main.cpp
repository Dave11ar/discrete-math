#include <bits/stdc++.h>

using namespace std;

int n;
bool matrix[4010][4010];

void input() {
  cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      char tmp;
      cin >> tmp;

      if (tmp == '1') {
        matrix[i][j] = true;
        matrix[j][i] = true;
      }
    }
  }
}

void solution() {
  deque<int> deq;

  for (int i = 0; i < n; i++) {
    deq.push_back(i);
  }

  for (int i = 0; i < n * (n - 1); i++) {
    auto it = deq.begin();
    if (!matrix[*it][*++it]) {
      int fir = deq.front();
      int sec = *++deq.begin();

      while (true) {
        if (!matrix[fir][*it]) {
          it++;
          continue;
        }
        if (!matrix[sec][*++it]) {
          continue;
        }

        break;
      }
      reverse(++deq.begin(), it);
    }

    deq.push_back(deq.front());
    deq.pop_front();
  }

  for (int & it : deq) {
    cout << it + 1 << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}
