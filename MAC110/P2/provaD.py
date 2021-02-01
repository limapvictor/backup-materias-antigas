def K(r):
    k = 0
    for i in range(r+1):
        k = k + (((-1) ** i) * 1 / ( (2 * i) + 1 ))
    return k

def f(x,eps):
    fx = 0
    r = 0
    primeira = True
    while(fx > eps or pimeira):
        expoente = 4 * r + 2
        fx = fx + x ** expoente * K(r) / expoente
        r += 1
    
        

print(K(0))
print(K(1))
print(K(2))
print(K(3))
