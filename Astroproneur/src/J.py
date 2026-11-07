import math
t=int(input())
for _ in range(t):
    n=int(input())
    a=list(map(int,input().split()))
    mi=0
    b=0
    for i in range(len(a)-1):
        if a[i]>a[i+1]:
            mi=math.ceil((a[i]+a[i+1])/2)
            break

    a = [abs(a[i] - mi) for i in range(len(a))]

    for i in range(len(a)-1):
        if a[i]>a[i+1]:
            b=1
            break

    print(mi) if b==0 else print(-1)
    
    


        
