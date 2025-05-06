#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

typedef struct Heap {
  int *arr;
  int heap_size;
  int n;
} Heap;

int no_of_comp = 0;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void max_heapify(Heap *heap, int i) {
  int l = LEFT(i);
  int r = RIGHT(i);
  int largest = i;

  if (l <= heap->heap_size - 1 && heap->arr[largest] <= heap->arr[l]) {
    largest = l;
    no_of_comp++;
  }
  if (r <= heap->heap_size - 1 && heap->arr[largest] <= heap->arr[r]) {
    largest = r;
    no_of_comp++;
  }
  if (largest != i) {
    swap(&heap->arr[i], &heap->arr[largest]);
    max_heapify(heap, largest);
  }
}

Heap *build_max_heap(int *arr, int size) {
  Heap *heap = calloc(1, sizeof(Heap));
  heap->arr = arr;
  heap->heap_size = size;
  heap->n = size;

  for (int i = size / 2; i >= 0; i--) {
    max_heapify(heap, i);
  }
  return heap;
}

void heap_sort(Heap *heap) {
  heap = build_max_heap(heap->arr, heap->n);
  for (int i = heap->n - 1; i >= 1; i--) {
    swap(&heap->arr[i], &heap->arr[0]);
    heap->heap_size--;
    max_heapify(heap, 0);
  }
}

int main(void) {
  int arr[] = {-1, 0, 293, 7, 1};
  int size = sizeof(arr) / sizeof(arr[0]);
  Heap heap = {.arr = arr, .n = size, .heap_size = size};

  heap_sort(&heap);

  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }

  printf("\nNo of comparisons = %d", no_of_comp);
}
