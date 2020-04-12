#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[]) {
  int toupper(int k);
  int i;
  strcat(argv[1], " ");
  for (i = 2; i < argc; i++) {
    strcat(argv[1], argv[i]);
    if (i == argc - 1) break;
    strcat(argv[1], " ");
  }
  int x = strlen(argv[1]);
  char s[x + 1];
  strcpy(s, argv[1]);
  int q = 0;
  for (i = 0; i < sizeof(s); i++) {
    if (islower(s[i]) == 0) {
      continue;
    }
    if (q == 0) {
      q = 1;
      continue;
    }
    s[i] = toupper(s[i]);
    q = 0;
  }
  printf("%s", s);
}
