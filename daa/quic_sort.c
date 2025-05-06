#include <stdio.h>

int no_of_comp = 0;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *arr, int left, int right) {
  int key = arr[right];
  int j = left - 1;
  for (int i = left; i < right; i++) {
    if (arr[i] <= key) {
      no_of_comp++;
      j++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[j + 1], &arr[right]);
  return j + 1;
}

void q_sort(int *arr, int left, int right) {

  if (left < right) {
    int q = partition(arr, left, right);
    q_sort(arr, left, q - 1);
    q_sort(arr, q + 1, right);
  }
}

void sort(int *arr, int n) { return q_sort(arr, 0, n - 1); }

int main(void) {
  int arr[] = {2, -1, 0, 5};
  int n = sizeof(arr) / sizeof(arr[0]);
  sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\nNo of comparisons = %d", no_of_comp);
}
