#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

typedef struct Graph {
  int num_vertices;
  struct Node **adj_list;
} Graph;

Node *create_node(int v) {
  Node *node = malloc(sizeof(Node));
  node->vertex = v;
  node->next = NULL;
  return node;
}

Graph *create_graph(int vertices) {
  Graph *graph = malloc(sizeof(Graph));
  Node **adj_list = malloc(vertices * sizeof(Node *));
  graph->num_vertices = vertices;
  graph->adj_list = adj_list;

  for (int i = 0; i < vertices; i++) {
    graph->adj_list[i] = NULL;
  }
  return graph;
}

void add_edge(Graph *graph, int src, int dest) {
  // src and dest join
  Node *new_node = create_node(dest);
  new_node->next = graph->adj_list[src];
  graph->adj_list[src] = new_node;

  // dest and src join
  new_node = create_node(src);
  new_node->next = graph->adj_list[dest];
  graph->adj_list[dest] = new_node;
}

void print_graph(Graph *graph) {
  for (int i = 0; i < graph->num_vertices; i++) {
    Node *temp = graph->adj_list[i];
    printf("Vertex %d\n", i);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("Null\n");
  }
}

int pop_queue(int *q, int *size) {
  int res = q[0];
  for (int i = 1; i < *size; i++) {
    q[i - 1] = q[i];
  }
  --(*size);
  return res;
}

void pushback_queue(int **q, int *size, int value) {
  *q = realloc(*q, (*size + 1) * sizeof(int));
  (*q)[*size] = value;
  ++(*size);
}

bool is_visited(int *res, int vertex, int size_of_res) {
  for (int i = 0; i < size_of_res; i++) {
    if (res[i] == vertex)
      return true;
  }
  return false;
}

void bfs(Graph *graph) {
  int source = 0;
  int num_vertices = graph->num_vertices;
  int *res = calloc(num_vertices, sizeof(int));
  int size_of_result = 0;

  bool *visited = calloc(num_vertices, sizeof(bool));

  for (int i = 0; i < num_vertices; i++) {
    visited[i] = false;
  }

  visited[source] = true;

  int *queue = calloc(1, sizeof(int));
  queue[0] = source;
  int size_of_queue = 1;

  while (size_of_queue) {
    int curr = pop_queue(queue, &size_of_queue);
    res[size_of_result++] = curr;

    Node *temp = graph->adj_list[curr];
    while (temp) {
      if (!visited[temp->vertex]) {
        visited[temp->vertex] = true;
        pushback_queue(&queue, &size_of_queue, temp->vertex);
      }
      temp = temp->next;
    }
  }

  for (int i = 0; i < size_of_result; i++) {
    printf("%d ", res[i]);
  }

  free(res);
  free(visited);
  free(queue);
}

int main(void) {
  struct Graph *graph = create_graph(5);

  add_edge(graph, 0, 1);
  add_edge(graph, 0, 4);
  add_edge(graph, 1, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 3);
  add_edge(graph, 3, 4);

  print_graph(graph);
  bfs(graph);
}
