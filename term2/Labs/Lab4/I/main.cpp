#include <bits/stdc++.h>

using namespace std;

int n, m, k;
set<int> source_allowed;
vector<vector<vector<int>>> source_reversed_edges;
vector<vector<int>> source_straight_edges;

vector<set<pair<int, int>>> min_reversed_edges;
vector<set<pair<int, int>>> min_straight_edges;

set<int> min_allowed;
vector<set<int>> classes;
vector<int> vertex_to_class;

void hopcroft() {
  vertex_to_class.resize(n + 1);
  classes.resize(2);

  queue<pair<int, int>> requests;

  for (int i = 0; i <= n; i++) {
    if (!source_allowed.count(i)) {
      classes[0].insert(i);
      vertex_to_class[i] = 0;
    } else {
      classes[1].insert(i);
      vertex_to_class[i] = 1;
    }
  }

  if (classes[0].empty()) {
    for (int cur_vertex : classes[1]) vertex_to_class[cur_vertex] = 0;
    swap(classes[0], classes[1]);
  }
  if (classes[1].empty()) classes.pop_back();

  for (int i = 0; i < classes.size(); i++) {
    for (int j = 0; j < 26; j++) {
      requests.push({i, j});
    }
  }

  while (!requests.empty()) {
    pair<int, int> cur_request = requests.front();
    requests.pop();

    map<int, set<int>> involved;
    for (int vertex : classes[cur_request.first]) {
      for (int cur_edge : source_reversed_edges[vertex][cur_request.second]) {
        involved[vertex_to_class[cur_edge]].insert(cur_edge);
      }
    }

    for (pair<int, set<int>> cur_class : involved) {
      if (cur_class.second.size() < classes[cur_class.first].size()) {
        int index = classes.size();
        classes.emplace_back();

        for (int cur_vertex : cur_class.second) {
          classes[cur_class.first].erase(cur_vertex);
          classes[index].insert(cur_vertex);
        }

        if (classes[index].size() > classes[cur_class.first].size()) {
          swap(classes[index], classes[cur_class.first]);
        }

        for (int cur_vertex : classes[index]) {
          vertex_to_class[cur_vertex] = index;
        }

        for (int j = 0; j < 26; j++) requests.push({index, j});
      }
    }
  }
}

void make_start_0() {
  if (vertex_to_class[0] != 0) {
    swap(classes[0], classes[vertex_to_class[0]]);

    for (int cur_vertex : classes[vertex_to_class[0]]) {
      vertex_to_class[cur_vertex] = vertex_to_class[0];
    }
    for (int cur_vertex : classes[0]) {
      vertex_to_class[cur_vertex] = 0;
    }
  }
}

void convert_to_automata() {
  min_reversed_edges.resize(classes.size());
  min_straight_edges.resize(classes.size());

  vector<bool> checked(classes.size(), false);

  for (int i = 0; i <= n; i++) {
    if (checked[vertex_to_class[i]]) continue;
    if (source_allowed.count(i)) min_allowed.insert(vertex_to_class[i]);

    for (int j = 0; j < 26; j++) {
      min_reversed_edges[vertex_to_class[source_straight_edges[i][j]]].insert(
          {vertex_to_class[i], j});

      min_straight_edges[vertex_to_class[i]].insert(
          {vertex_to_class[source_straight_edges[i][j]], j});
    }
    checked[vertex_to_class[i]] = true;
  }
}

vector<bool> used;
void dfs_term(int v) {
  used[v] = true;
  for (pair<int, int> to : min_reversed_edges[v]) {
    if (!used[to.first]) dfs_term(to.first);
  }
}

void dfs_start(int v) {
  used[v] = true;
  for (pair<int, int> to : min_straight_edges[v]) {
    if (!used[to.first]) dfs_start(to.first);
  }
}

set<int> trash;
void find_trash() {
  // check if achievable from start
  used.resize(classes.size(), false);
  dfs_start(0);

  for (int i = 0; i < classes.size(); i++) {
    if (!used[i]) {
      min_allowed.erase(i);
      trash.insert(i);
    }
    used[i] = false;
  }

  // check if we can go to term
  for (int i = 0; i < classes.size(); i++) {
    if (!used[i] && min_allowed.count(i)) dfs_term(i);
  }
  for (int i = 0; i < classes.size(); i++) {
    if (!used[i]) {
      trash.insert(i);
    }
    used[i] = false;
  }
}

vector<int> squeezed_min_automata;
int min_m = 0;
void squeeze_automata() {
  squeezed_min_automata.resize(classes.size());
  int cur_number = 0;
  for (int i = 0; i < classes.size(); i++) {
    if (!trash.count(i)) {
      squeezed_min_automata[i] = cur_number++;
    }
  }

  for (int i = 0; i < classes.size(); i++) {
    if (trash.count(i)) continue;

    set<pair<int, int>> sq_edges = min_reversed_edges[i];
    for (pair<int, int> cur_edge : min_reversed_edges[i]) {
      if (trash.count(cur_edge.first)) {
        sq_edges.erase(cur_edge);
        //min_reversed_edges[i].erase(cur_edge);
      } else {
        min_m++;
      }
    }
    min_reversed_edges[i] = sq_edges;
  }
}

void input() {
  cin >> n >> m >> k;
  source_reversed_edges.resize(n + 1, vector<vector<int>>(26));
  source_straight_edges.resize(n + 1, vector<int>(26, n));

  for (int i = 0; i < k; i++) {
    int tmp;
    cin >> tmp;
    source_allowed.insert(tmp - 1);
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    char c;
    cin >> a >> b >> c;

    source_straight_edges[a - 1][c - 'a'] = b - 1;
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < 26; j++) {
      source_reversed_edges[source_straight_edges[i][j]][j].push_back(i);
    }
  }
}

void output() {
  cout << (int)classes.size() - (int)trash.size() << ' ' << min_m << ' ' << min_allowed.size() << '\n';

  for (int cur_class : min_allowed) {
    cout << squeezed_min_automata[cur_class] + 1 << ' ';
  }
  cout << '\n';

  for (int i = 0; i < classes.size(); i++) {
    if (trash.count(i)) continue;

    for (pair<int, int> cur_edge : min_reversed_edges[i]) {
      cout << squeezed_min_automata[cur_edge.first] + 1 << ' ' << squeezed_min_automata[i] + 1 <<
           ' ' << char(cur_edge.second + (int)('a')) << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  //freopen("minimization.in", "r", stdin);
  //freopen("minimization.out", "w", stdout);

  input();
  hopcroft();
  make_start_0();
  convert_to_automata();
  find_trash();
  squeeze_automata();
  output();

  return 0;
}
