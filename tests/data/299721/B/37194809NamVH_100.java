n = int(input())

a = list(int(x) for x in input().split())
mul = 1
mod = 10**9 + 7
for i in range(0, n):
    mul = (mul % mod * a[i] % mod) % mod
print(mul % mod)
