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

void push_stack(int **stack, int *size, int value) {
  *stack = realloc(*stack, (*size + 1) * sizeof(int));
  (*stack)[*size] = value;
  ++(*size);
}

int pop_stack(int **stack, int *size) {
  int result = (*stack)[*size - 1];
  *stack = realloc(*stack, (*size - 1) * sizeof(int));
  --(*size);
  return result;
}

void dfs(Graph *graph) {
  int source = 0;

  int no_vertex = graph->num_vertices;
  int *result = malloc(no_vertex * sizeof(int));
  int size_of_result = 0;
  int *visited = calloc(no_vertex, sizeof(int));

  int *stack = malloc(sizeof(int));
  int size_of_stack = 0;
  push_stack(&stack, &size_of_stack, source);

  while (size_of_stack) {
    int curr = pop_stack(&stack, &size_of_stack);

    if (!visited[curr]) {
      visited[curr] = 1;
      result[size_of_result++] = curr;

      Node *temp = graph->adj_list[curr];
      while (temp != NULL) {
        int neighor = temp->vertex;
        if (!visited[neighor]) {
          push_stack(&stack, &size_of_stack, neighor);
        }
        temp = temp->next;
      }
    }
  }
  for (int i = 0; i < size_of_result; i++) {
    printf("%d ", result[i]);
  }
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
  dfs(graph);
}
