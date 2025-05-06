#include <stdio.h>
#include <stdlib.h>

int *sort(int *arr, int n, int k) {
  int *brr = calloc(n, sizeof(int));
  int *crr = calloc(k + 1, sizeof(int));

  for (int i = 0; i < n; i++) {
    crr[arr[i]] += 1;
  }
  for (int i = 1; i <= k; i++) {
    crr[i] += crr[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    brr[crr[arr[i]] - 1] = arr[i];
    crr[arr[i]] -= 1;
  }
  return brr;
}

int main(void) {
  int arr[] = {1, 9, 13, 0, 3};
  int size = sizeof(arr) / sizeof(arr[0]);

  int *result = sort(arr, size, 13);

  for (int i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }
}
