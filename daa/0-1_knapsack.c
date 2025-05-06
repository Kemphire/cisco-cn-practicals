#include <stdio.h>

int knapsack(int weights[], int values[], int n, int W) {
  int dp[n + 1][W + 1];

  for (int i = 0; i <= n; i++) {
    for (int w = 0; w <= W; w++) {
      if (i == 0 || w == 0)
        dp[i][w] = 0;
      else if (weights[i - 1] <= w)
        dp[i][w] =
            (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w])
                ? (values[i - 1] + dp[i - 1][w - weights[i - 1]])
                : dp[i - 1][w];
      else
        dp[i][w] = dp[i - 1][w];
    }
  }

  int res = dp[n][W];
  int w = W;

  printf("Items included : ");
  for (int i = n; i > 0 && res > 0; i--) {
    if (res == dp[i - 1][w])
      continue;
    else {
      printf("%d ", i - 1);
      res -= values[i - 1];
      w -= weights[i - 1];
    }
  }
  printf("\n");

  return dp[n][W];
}

int main() {
  int weights[] = {2, 3, 4, 5};
  int values[] = {3, 4, 5, 6};
  int W = 5;
  int n = sizeof(weights) / sizeof(weights[0]);

  int maxValue = knapsack(weights, values, n, W);
  printf("Maximum value in knapsack: %d\n", maxValue);
  return 0;
}
