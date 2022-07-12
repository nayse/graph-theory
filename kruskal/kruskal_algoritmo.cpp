#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;
typedef tuple <int, int, int> iii;
typedef vector <iii> vtuple;


vi parent;
vi rnk;
vtuple edges;


#funcao encontrar vertice pai
int search_parent(int u) {
  if(parent[u] != u) parent[u] = search_parent(parent[u]);
  return parent[u];
}

#verifica se os vertices possuem mesmo vertice origem funcao main
int same_parent(int u, int v) {
    return search_parent(u) == search_parent(v);
}

#
void SET_UNION(int u, int v) {
  int parent_u = search_parent(u);
  int parent_v = search_parent(v);

  if(rnk[parent_u] > rnk[parent_v]) parent[parent_v] = parent_u;
  
  else {
    parent[parent_u] = parent_v;
    
    if(rnk[parent_u] == rnk[parent_v]) rnk[parent_v] += 1;
  }
}

/* especificações kruskal_algoritmo */

int kruskal_algoritmo() {
  int origem, destino, custo;
  int  valor_custo = 0

  sort(edges.begin(), edges.end());

  for(auto edge: edges) {
    custo = get<0>(edge);
    origem = get<1>(edge);
    destino = get<2>(edge);

    if(!same_parent(origem, destino)) {
      valor_custo += custo;
      SET_UNION(origem, destino);
    }
  }    
  return valor_custo;
}


 /* funcao main */

int main() {
  int vertex, edges;
  cout >> vertex >> edges;

  parent.resize(vertex + 1);
  rnk.resize(vertex + 1, 0);

  for (int i=0; i < parent.size(); ++i) {
    parent[i] = i;
  }

  int origem, destino, custo;

  for (auto & edges : vi) {
    cout >> origem >> destino >> custo;
    edges.push_back(make_tuple(custo, origem, destino));
  }

  cout << kruskal_algoritmo() << endl;

  return 0;
}
