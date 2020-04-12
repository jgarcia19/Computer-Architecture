#include<stdio.h>

int main(int argc, char *argv[]) {
  int k, i, j, exp;
  int a[k][k];

  for (i = 0; i < k; i++) {
    for (j = 0; j < k; j++) {
      scanf("%d", &a[j][i]);
    }
  }

  scanf("%d", &exp);
  int n;
  int c[k][k], p[k][k];

  for (i = 0; i < k; i++) {
    for (j = 0; j < k; j++) {
      c[j][i] = a[j][i];
      p[j][i] = c[j][i];
    }
  }
  int l;
  if (exp == 0) {
    for (i = 0; i < k; i++) {
      for (j = 0; j < k; j++) {
        if (i == j) {
          printf("1 ");
        } else {
          printf("0 ");
        }
      }
      printf("\n");
    }
    return 0;
  }
  for (l = 0; l < exp - 1; l++) {
    for (i = 0; i < k; i++) {
      for (j = 0; j < k; j++) {
        int sum = 0;
        for (n = 0; n < k; n++) {
          sum = sum + (p[n][i] * a[j][n]);
        }
        c[j][i] = sum;
      }
    }
    for (i = 0; i < k; i++) {
      for (j = 0; j < k; j++) {
        p[j][i] = c[j][i];
      }
    }
  }

  for (i = 0; i < k; i++) {
    for (j = 0; j < k; j++) {
      printf("%d ", c[j][i]);
    }
    printf("\n");
  }
  return 0;
}
