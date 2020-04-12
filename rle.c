#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {
  int i = 0;
  int x = strlen(argv[1]);
  char s[x + 1];
  int sptr = 0;
  char ns[x + 1];
  int nsptr = 0;
  strcpy(s, argv[1]);
  char c = s[0];
  int n = 1;
  for (int i = 1; i < sizeof(s); i++) {
    if (c >= '0' && c <= '9') {
      printf("error");
      return 0;
    }
    if (c == s[i]) {
      n++;
      continue;
    }
    if (nsptr >= x) {
      printf("%s\n", s);
      return 0;
    }
    ns[nsptr] = c;
    nsptr++;
    ns[nsptr] = n + '0';
    nsptr++;
    c = s[i];
    n = 1;
  }
  ns[nsptr] = '\0';
  printf("%s\n", ns);
}
