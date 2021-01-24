#include <bits/stdc++.h>

#include <random>

using namespace std;

int n;
bool matrix[4010][4010];
deque<int> deq;

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

bool check() {
  bool ham = true;
  for (auto it = ++deq.begin(); it != deq.end(); it++) {
    auto tmp = it;
    tmp--;
    if (!matrix[*it][*tmp]) {
      ham = false;
      break;
    }
  }

  if (!matrix[deq.front()][deq.back()]) {
    ham = false;
  }

  return ham;
}

void solution() {
  for (int i = 0; i < n; i++) {
    deq.push_back(i);
  }

  do {
    shuffle(deq.begin(), deq.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < n * (n - 1); i++) {
      auto it = deq.begin();
      if (!matrix[*it][*++it]) {
        int fir = deq.front();
        int sec = *++deq.begin();

        while (*it != deq.back()) {
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
  } while (!check());

  for (int &it : deq) {
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
