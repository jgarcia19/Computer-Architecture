#include <stdio.h>
#include <string.h>

int main() {
  int i, j;
  char interpret(char n[], char p[]);
  int size, runs;
  scanf("%d", &size);
  scanf("%d", &runs);
  char a[size], b[size], t[9];
  scanf("%s", &t);

  for (i = 0; i < size; i++) {
    if (i == size / 2) {
      a[i] = '*';
    } else {
      a[i] = '.';
    }
    printf("%c", a[i]);
  }
  printf("\n");

  for (i = 0; i < runs; i++) {

    for (j = 0; j < size; j++) {
      if (j == 0) {
        char s[4] = {a[size - 1], a[j], a[j + 1], '\0'};
        b[j] = interpret(s, t);
        printf("%c", b[j]);
      } else if (j == size - 1) {
        char s[4] = {a[j - 1], a[j], a[0], '\0'};
        b[j] = interpret(s, t);
        printf("%c", b[j]);
      } else {
        char s[4] = {a[j - 1], a[j], a[j + 1], '\0'};
        b[j] = interpret(s, t);
        printf("%c", b[j]);
      }
    }

    for (j = 0; j < size; j++) {
      a[j] = b[j];
    }

    printf("\n");
  }

  return 0;
}

char interpret(char n[], char p[]) {
  if (strcmp(n, "...") == 0) {
    return p[0];
  } else if (strcmp(n, "..*") == 0) {
    return p[1];
  } else if(strcmp(n, ".*.") == 0) {
    return p[2];
  } else if(strcmp(n, ".**") == 0) {
    return p[3];
  } else if(strcmp(n, "*..") == 0) {
    return p[4];
  } else if(strcmp(n, "*.*") == 0) {
    return p[5];
  } else if(strcmp(n, "**.") == 0) {
    return p[6];
  } else if(strcmp(n, "***") == 0) {
    return p[7];
  }
}
