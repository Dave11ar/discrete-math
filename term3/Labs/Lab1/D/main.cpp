#include <bits/stdc++.h>

using namespace std;

int n;

vector<vector<bool>> matrix;
deque<int> path, cycle;

void input() {
  cin >> n;
  matrix.resize(n, vector<bool>(n));

  for (int i = 0; i < n; i++) {
    path.push_back(i);
    for (int j = 0; j < i; j++) {
      char tmp;
      cin >> tmp;

      if (tmp == '1') {
        matrix[i][j] = true;
      } else {
        matrix[j][i] = true;
      }
    }
  }
}

void find_path() {
  stable_sort(path.begin(), path.end(),
              [](int const &a, int const &b) {return matrix[a][b];});
}

void get_path_cycle() {
  auto last = path.begin();
  for (auto it = path.begin(); it != path.end(); it++) {
    if (matrix[*it][path.front()]) {
      last = it;
    }
  }
  last++;

  for (auto it = path.begin(); it != last; it++) {
    cycle.push_back(*it);
  }
  path.erase(path.begin(), last);
}

auto find_ins(int fir) {
  auto it = cycle.begin();
  bool last = matrix[cycle.back()][fir];

  while (!(last && matrix[fir][*it]) && it != cycle.end()) {
    last = matrix[*it][fir];
    it++;
  }

  return it;
}

void find_cycle() {
  while (!path.empty()) {
    auto it = find_ins(path.front());

    if (it != cycle.end()) {
      cycle.insert(it, path.front());
      path.erase(path.begin());
    } else {
      auto cur_it = --path.end();

      while (true) {
        auto res = path.begin();
        for (res = path.begin(); res != path.end(); res++) {
          if (matrix[*cur_it][*res]) {
            break;
          }
        }

        if (res != cycle.end()) {
          cur_it++;
          cycle.insert(res, path.begin(), cur_it);
          path.erase(path.begin(), cur_it);
          break;
        }
      }
    }
  }

  for (int &i : cycle) {
    cout << i + 1 << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  find_path();
  get_path_cycle();
  find_cycle();

  return 0;
}
