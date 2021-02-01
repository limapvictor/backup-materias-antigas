def simetrica(M):
    centro = len(M) // 2
    simetrica = True
    for linha in M:
        for i in range(1,centro + 1):
            if(linha[centro + i] != linha[centro - i]):
                simetrica = False
    return simetrica

def recorta(M,k,i,j):
    espaco = k // 2
    numLin,numCol = len(M),len(M[0])
    for lin in range(numLin-1,-1,-1):    
        for col in range(numCol-1,-1,-1):
            if(col != j and (col != j + espaco) and (col != j - espaco)):
                del M[lin][col]
        if(lin!=i and (lin != i + espaco) and (lin != i - espaco)):
            del M[lin]
    return M

def recortaBinario(M):
    numLin,numCol = len(M),len(M[0])
    for lin in range(numLin-1,-1,-1):
        zerada = True
        for col in range(numCol-1,-1,-1):
            if(M[lin][col] == 1):
                zerada = False
        if(zerada):
            del M[lin]
    for col in range(numCol-1,-1,-1):
        zerada = True
        for lin in range(len(M)-1,-1,-1):
            if(M[lin][col] == 1):
                zerada = False
        if(zerada):
            for lin in range(len(M)):
                del M[lin][col]
    return M

def main():
    esqu = [[8,1,0,1,8],[0,2,1,2,0],[0,3,2,3,0],[0,4,3,4,0],[0,5,4,5,0]]
    dire = [[8,1,0,1,8],[0,2,1,2,0],[0,3,2,0,3],[0,4,3,4,0],[0,5,4,5,0]]
    print(simetrica(esqu))
    print(simetrica(dire))
    rec = [[2,1,0,1,2],[3,2,0,2,3],[4,3,0,4,3],[5,4,0,4,5]]
    print(recorta(rec,3,2,1))
    bina = [[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0],[0,0,1,0,1,0,0,0],
            [0,1,0,1,1,1,0,0],[0,1,1,1,1,0,0,0],[0,0,0,1,0,0,0,0],[0,0,0,1,0,0,0,0],
            [0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0]]
    print(recortaBinario(bina))

main()
