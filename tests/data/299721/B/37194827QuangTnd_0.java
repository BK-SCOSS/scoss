n = int(input()) 

num = 1
x = []

for i in range(0, n): 
    ele = int(input()) 
  
    x.append(ele)

for i in range(0, n):
  num *= x[i]

num %= 1000000007

print(num)