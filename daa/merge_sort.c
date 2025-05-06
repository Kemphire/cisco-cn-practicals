#include <stdio.h>
#include <stdlib.h>

int no_of_comp = 0;

void merge(int *arr, int left, int mid, int right) {
  int length_left = mid - left + 1;
  int length_right = right - mid;

  int *left_array = calloc(length_left, sizeof(int));
  int *right_array = calloc(length_right, sizeof(int));

  for (int i = 0; i < length_left; i++) {
    left_array[i] = arr[left + i];
  }
  for (int i = 0; i < length_right; i++) {
    right_array[i] = arr[mid + 1 + i];
  }

  int i = 0, j = 0, k = left;

  while (i < length_left && j < length_right) {
    if (left_array[i] <= right_array[j]) {
      no_of_comp++;
      arr[k] = left_array[i];
      i++;
    } else {
      no_of_comp++;
      arr[k] = right_array[j];
      j++;
    }
    k++;
  }

  while (i < length_left) {
    no_of_comp++;
    arr[k] = left_array[i];
    i++;
    k++;
  }
  while (j < length_right) {
    no_of_comp++;
    arr[k] = right_array[j];
    j++;
    k++;
  }

  free(right_array);
  free(left_array);
}

void merge_sort(int *arr, int left, int right) {
  if (left >= right)
    return;
  int mid = left + ((right - left) / 2);
  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

void sort(int *arr, int n) { return merge_sort(arr, 0, n - 1); }

int main(void) {
  int arr[] = {-1, 9, 0, 2, 1};
  int n = sizeof(arr) / sizeof(arr[0]);

  sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  printf("\nNo of comp = %d", no_of_comp);
}
