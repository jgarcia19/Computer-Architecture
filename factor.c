#include<stdio.h>

int main(int argc, char *argv[]) {
  int atoi(char a[]);
  int isPrime(int n);
  int x = atoi(argv[1]);

  // Check the value given if it is prime
  if (isPrime(x) == 1) {
    printf("%d", x);
    return 0;
  }

  // Check if the value given is divisible by 2
  if (x % 2 == 0) {
    printf("%d\n", 2);
  }

  int i = 3;

  // Check all prime numbers if they can divide the value
  while (i <= x/2) {
    if (isPrime(i) == 1 && x % i == 0) {
      printf("%d\n", i);
    }
    i = i + 2;
  }
}

int isPrime(int n) {
  int i;
  for (i = 2; i <= n/2; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}
