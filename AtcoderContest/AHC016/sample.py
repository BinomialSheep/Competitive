M, eps = input().split()
M = int(M)
eps = float(eps)
print(4)
#for k in range(M):
#    print("000000")
    # print("1" * k + "0" * (6 - k))
print("000000")
print("000001")
print("000011")
print("000111")
print("001111")
print("011111")
print("111111")
print("000000")
print("000000")
print("000000")


for q in range(100):
    H = input()
    t = min(H.count('1'), M - 1)
    print(t)
