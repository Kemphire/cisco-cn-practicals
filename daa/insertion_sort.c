#include <stdio.h>

int no_of_comp = 0;

void sort(int *arr, int n) {
  int key, j;
  for (int i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      no_of_comp++;
      arr[j + 1] = arr[j];
      j--;
    }
    if (j >= 0)
      no_of_comp++;
    arr[j + 1] = key;
  }
}

int main(void) {
  int arr[] = {1, 3, 0, -1};
  int n = sizeof(arr) / sizeof(arr[0]);
  sort(arr, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  printf("\nNo of Comp = %d", no_of_comp);
}
