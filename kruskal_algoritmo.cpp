#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;
typedef tuple <int, int, int> iii;
typedef vector <iii> vtuple;

vtuple edge_list;
vi parent;
vi depth;

int find_parent(int i) {
  if(parent[i] != i) parent[i] = find_parent(parent[i]);
  return parent[i];
}

int same_parent(int i, int j) {
    return find_parent(i) == find_parent(j);
}

void Union(int i, int j) {
  int parent_i = find_parent(i);
  int parent_j = find_parent(j);

  if(depth[parent_i] > depth[parent_j]) parent[parent_j] = parent_i;
  else {
    parent[parent_i] = parent_j;
    if(depth[parent_i] == depth[parent_j]) depth[parent_j] += 1;
  }
}

int kruskal() {
  int source, destiny, cost, minimum_cost = 0;

  sort(edge_list.begin(), edge_list.end());

  for(auto edge: edge_list) {
    cost = get<0>(edge);
    source = get<1>(edge);
    destiny = get<2>(edge);

    if(!same_parent(source, destiny)) {
      minimum_cost += cost;
      Union(source, destiny);
    }
  }    
  return minimum_cost;
}

int main() {
  int vertex, edges;
  cin >> vertex >> edges;

  parent.resize(vertex + 1);
  depth.resize(vertex + 1, 0);

  for (int i=0; i < parent.size(); ++i) {
    parent[i] = i;
  }

  int source, destiny, cost;

  for (int i=0; i < edges; ++i) {
    cin >> source >> destiny >> cost;
    edge_list.push_back(make_tuple(cost, source, destiny));
  }

  cout << kruskal() << endl;

  return 0;
}