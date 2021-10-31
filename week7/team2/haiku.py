n= int(input())
s=[""]*n
stringmap={}
def work(x):
    if x=="":
        return [0]
    if x in stringmap:
        return stringmap[x]
    myret=set()
    for i in range(n):
        if x.startswith(s[i]):
            ret=work(x[len(s[i]):])
            for j in ret:
                if j<7:
                    myret.add(j+1)
    stringmap[x]=myret
    return myret

def solve(p, k):
    pieces=[]
    for i in p:
        pieces.append(list(work(i)))
    # print(pieces)
    f=[False]*(k+1)
    f[0]=True
    for i in pieces:
        for j in range(k,-1,-1):
            f[j]=False
            for ij in i:
                if j>=ij and f[j-ij]:
                    f[j]=True
    if f[k]:
        return True
    return False

for i in range(n):
    s[i]=input()
    # print(s[i])

poetry = [""]*3
poetry[0]=input().split()
# for i in poetry[0]:
#     print(i)
poetry[1]=input().split()
poetry[2]=input().split()
if solve(poetry[0],5) and solve(poetry[1],7) and solve(poetry[2],5):
    print('haiku')
else:
    print('come back next year')
