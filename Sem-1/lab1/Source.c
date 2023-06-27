#include <stdio.h>

void fib(int *a, int *b, int n) {
  printf("1: 1\n");
  for (int i = 2; i <= n; ++i) {
    int c = *a + *b;
    *a = *b;
    *b = c;
    printf("%d: %d\n", i, *b);
  }
}

int main() {
  int n;
  int res = scanf("%d", &n);
  if (res == EOF)
    return 1;
  if (n < 2 || n > 45) {
    printf("Input must be between 2 and 45!");
    return 2;
  }

  int a = 0, b = 1;
  fib(&a, &b, n);
  float ratio = (float)b / (float)a;
  printf("Last ratio: %f", ratio);

  return 0;
}
