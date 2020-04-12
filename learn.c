#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {
  FILE *fp1;

  fp1 = fopen(argv[1], "r");

  int n, m, o, p, i, j;
  char c[6], s[6];
  fscanf(fp1, "%s", c);
  fscanf(fp1, "%d", &n);
  fscanf(fp1, "%d", &m);

  double **a = (double**) malloc(m * sizeof(double));
  for (i = 0; i < m; i++) {
    a[i] = (double*) malloc((n + 1) * sizeof(double));
  }

  double *y = (double*) malloc(m * sizeof(double));

  for (i = 0; i < m; i++) {
    for (j = 0; j < n + 1; j++) {
      if (j == 0) {
        a[i][j] = 1;
        continue;
      }
      fscanf(fp1, "%lf", &a[i][j]);
      if (j == n) {
        fscanf(fp1, "%lf", &y[i]);
      }
    }
  }

  double **at = (double**) malloc((n + 1) * sizeof(double));
  for (i = 0; i < n + 1; i++) {
    at[i] = (double*) malloc(m * sizeof(double));
  }

  for (i = 0; i < n + 1; i++) {
    for (j = 0; j < m; j++) {
      at[i][j] = a[j][i];
    }
  }

  double **sq = (double**) malloc((n + 1) * sizeof(double));
  for (i = 0; i < n + 1; i++) {
    sq[i] = (double*) malloc((n + 1) * sizeof(double));
  }
  for (i = 0; i < n + 1; i++) {
    for (j = 0; j < n + 1; j++) {
      int k;
      double sum = 0;
      for (k = 0; k < m; k++) {
        sum = sum + (at[i][k] * a[k][j]);
      }
      sq[i][j] = sum;
    }
  }

  free(a);

  double **inv = (double**) malloc((n + 1) * sizeof(double));
  for (i = 0; i < n + 1; i++) {
    inv[i] = (double*) malloc((n + 1) * sizeof(double));
  }
  for (i = 0; i < n + 1; i++) {
    for (j = 0; j < n + 1; j++) {
      if (i == j) {
        inv[i][j] = 1;
      } else {
        inv[i][j] = 0;
      }
    }
  }

  for (i = 0; i < n + 1; i++) {
    double scal;
    if (sq[i][i] != 1) {
      scal = 1 / sq[i][i];
      for (j = 0; j < n + 1; j++) {
        sq[i][j] = sq[i][j] * scal;
        inv[i][j] = inv[i][j] * scal;
      }
    }

    for (j = i + 1; j < n + 1; j++) {
      int k;
      scal = -1 * sq[j][i];
      for (k = 0; k < n + 1; k++) {
        sq[j][k] = sq[j][k] + (sq[i][k] * scal);
        inv[j][k] = inv[j][k] + (inv[i][k] * scal);
      }
    }
  }

  for (i = n; i >= 0; i--) {
    for (j = i - 1; j >= 0; j--) {
      double scal = -1 * sq[j][i];
      int k;
      for (k = n; k >= 0; k--) {
        sq[j][k] = sq[j][k] + (sq[i][k] * scal);
        inv[j][k] = inv[j][k] + (inv[i][k] * scal);
      }
    }
  }

  for (i = 0; i < n + 1; i++) {
    for (j= 0; j < n + 1; j++) {
    }
  }

  free(sq);

  double **prod = (double**) malloc((n + 1) * sizeof(double));
  for (i = 0; i < n + 1; i++) {
    prod[i] = malloc(m * sizeof(double));
  }

  for (i = 0; i < n + 1; i++) {
    for (j = 0; j < m; j++) {
      double sum = 0;
      int k;
      for (k = 0; k < n + 1; k++) {
        sum = sum + (inv[i][k] * at[k][j]);
      }
      prod[i][j] = sum;
    }
  }

  free(inv);


  double *weights = (double*) malloc((n + 1) * sizeof(double));
  for (i = 0; i < n + 1; i++) {
    double sum = 0;
    for (j = 0; j < m; j++) {
      sum = sum + (prod[i][j] * y[j]);
    }
    weights[i] = sum;
  }

  free(prod);
  free(y);

  FILE *fp2;
  fp2 = fopen(argv[2], "r");

  fscanf(fp2, "%s", s);
  fscanf(fp2, "%d", &o);
  fscanf(fp2, "%d", &p);

  double **b = (double**) malloc(p * sizeof(double));
  for (i = 0; i < p; i++) {
    b[i] = (double*) malloc((o + 1) * sizeof(double));
  }

  for (i = 0; i < p; i++) {
    for (j = 0; j < o + 1; j++) {
      if (j == 0) {
        b[i][j] = 1;
        continue;
      }
      fscanf(fp2, "%lf ", &b[i][j]);
    }
  }

  double *prices = (double*) malloc(p * sizeof(double));

  for (i = 0; i < p; i++) {
    double sum = 0;
    for (j = 0; j < n + 1; j++) {
      sum = sum + (b[i][j] * weights[j]);
    }
    prices[i] = sum;
  }

  free(b);
  free(weights);

  for (i = 0; i < p; i++) {
    printf("%.0f\n", prices[i]);
  }
  free(prices);

  return 0;
}
