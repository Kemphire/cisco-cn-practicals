#include <limits.h>
#include <stdio.h>

#define V 5

int min_key(int key[], int mst_set[]) {
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++) {
    if (mst_set[v] == 0 && key[v] < min) {
      min = key[v], min_index = v;
    }
  }
  return min_index;
}

void print_mst(int parent[], int graph[V][V]) {
  int total_weight = 0;
  printf("Edge weight\n");
  for (int i = 1; i < V; i++) {
    printf("%d - %d %d \n", parent[i], i, graph[i][parent[i]]);
    total_weight += graph[i][parent[i]];
  }
  printf("Total wieight of MST: %d\n", total_weight);
}

void primMST(int graph[V][V]) {

  int parent[V];
  int key[V];
  int mst_set[V];

  for (int i = 0; i < V; i++) {
    key[i] = INT_MAX, mst_set[i] = 0;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < V - 1; count++) {
    int u = min_key(key, mst_set);
    mst_set[u] = 1;

    for (int v = 0; v < V; v++) {
      if (graph[u][v] && mst_set[v] == 0 && graph[u][v] < key[v]) {
        parent[v] = u, key[v] = graph[u][v];
      }
    }
  }
  print_mst(parent, graph);
}

int main() {
  int graph[V][V] = {{0, 0, 1, 0, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 1},
                     {6, 8, 0, 0, 1},
                     {0, 5, 5, 100, 0}};

  primMST(graph);

  return 0;
}
