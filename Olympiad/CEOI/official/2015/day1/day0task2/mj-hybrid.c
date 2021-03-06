/* O(min(N, L^3 log N)) cas, O(L^2) pamet */

#include <stdio.h>

#define MAXL 205
#define M 4000000009U

typedef unsigned long long u64;

u64 x[MAXL], y[MAXL], r[MAXL][MAXL], z[MAXL][MAXL], tmp[MAXL][MAXL];
int n, l, k;

static void mm(u64 a[MAXL][MAXL], u64 b[MAXL][MAXL])
{
  for (int i=1; i<l; i++)
    for (int j=1; j<l; j++)
      {
	u64 t = 0;
	for (int p=1; p<l; p++)
	  t += a[i][p] * b[p][j] % M;
	tmp[i][j] = t % M;
      }

  for (int i=1; i<l; i++)
    for (int j=1; j<l; j++)
      a[i][j] = tmp[i][j];
}

int main(void)
{
  scanf("%d%d%d", &n, &l, &k);
  if (!n) { printf("1\n"); return 0; }

  x[1] = 1;
  u64 s = 1;
  for (int i=2; i<l; i++)
    s += x[i] = x[i-1]*k % M;
  if (n<l) { printf("%llu\n", x[n]*k % M); return 0; }

  unsigned lg = 1;
  while ((1<<lg) < n)
    lg++;
  if ((u64)l*l*l*lg*2 > (u64)n)
    {
      unsigned p = l-1;
      for (int i=l; i<=n; i++)
	{
	  p = (p+1) % MAXL;
	  x[p] = s*(k-1) % M;
	  s = (s + x[p] - x[(p-l+1+MAXL) % MAXL] + M) % M;
	}
      printf("%llu\n", (x[p]*k) % M);
      return 0;
    }

  for (int i=1; i<=l-2; i++)
    z[i][i+1] = 1;
  for (int i=1; i<=l-1; i++)
    z[l-1][i] = k-1;
  for (int i=1; i<=l-1; i++)
    r[i][i] = 1;

  unsigned nn = n-1;
  while (nn)
    {
      if (nn % 2)
	mm(r, z);
      mm(z, z);
      nn /= 2;
    }

  u64 t = 0;
  for (int i=1; i<l; i++)
    t += r[1][i] * x[i] % M;
  printf("%llu\n", t*k%M);
  return 0;
}
