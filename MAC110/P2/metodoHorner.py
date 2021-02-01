def metodoHorner(x,p,grau):
    valor = p[grau]
    print(valor)
    for i in range(grau-1,-1,-1):
        print(p[i],'+',x,'x',valor)
        valor = p[i] + (x * valor)
        print(valor)
    return valor

def main():
    grau = int(input("Digite o grau do polinomio:"))
    p = []
    for i in range(grau+1):
        print("Digite o coeficiente do termo de grau",i,":",end='')
        coef = int(input())
        p.append(coef)
    x = int(input("Digite o valor de x:"))
    print(metodoHorner(x,p,grau))

main()
