def leMatriz(matriz):
    numLin = len(matriz)
    numCol = len(matriz[0])
    linZer = 0
    colZer = 0
    for i in range(numLin):
        zeradoLin = True
        for j in range(numCol):
            if(matriz[i][j] != 0):
                zerado = False
        if(zeradoLin):
            linZer += 1
    for j in range(numCol):
        

def main():
    matriz = []
    linZ,colZ = leMatriz(matriz)
    print("Linhas zeradas:"linZ)
    print("Colunas zeradas:"colZ)

main()
