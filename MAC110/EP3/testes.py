def determinarCaminho(caminhos,livre):
    n = len(caminhos)
    caminho, toro = [], livre
    while(caminhos[toro[0]][toro[1]] != 1):
        vizinhos = [ [(toro[0]+1)%n,toro[1]], [(toro[0]-1)%n,toro[1]],
                      [toro[0],(toro[1]+1)%n], [toro[0],(toro[1]-1)%n] ]
        for vizinho in vizinhos:
            if(caminhos[vizinho[0]][vizinho[1]] == caminhos[toro[0]][toro[1]] - 1):
                print(toro)
                caminho.append(toro)
                toro = vizinho
    return caminho    

def construirCaminho(mundo,pos):
    n = len(mundo)
    caminhos = []
    contV = 0
    for i in range(n):
        linha = []
        for j in range(n):
            linha.append(0)
            if('V' not in mundo[i][j]):
                contV += 1
        caminhos.append(linha)
    caminhos[pos[0]][pos[1]] = 1
    m, i = [pos], 0
    while(len(m) < n*n - contV):
        vizinhos = [ [(m[i][0]+1)%n,m[i][1]], [(m[i][0]-1)%n,m[i][1]],
                        [m[i][0],(m[i][1]+1)%n], [m[i][0],(m[i][1]-1)%n] ]
        for vizinho in vizinhos: 
            if(vizinho not in m and 'V' in mundo[vizinho[0]][vizinho[1]]):
                m.append(vizinho)
                caminhos[vizinho[0]][vizinho[1]] = caminhos[m[i][0]][m[i][1]] + 1
        i += 1
    return caminhos    

def teste(x):
    if(x>3):
        return 'a'
    else:
        print('a')

def main():    
    mundo = [ ['V','P','P','V','V'],
             ['V','','V','V',''],
             ['V','V','V','V',''],
             ['P','','V','V','V'],
             ['W','','V','V','V'], ]
    pos = [0,0]
    livre = [4,2]
    print(determinarCaminho(construirCaminho(mundo,pos),livre))    
    if(teste(4) == 'a'):
        print('hum')
    y = 5
    if(y == 5):
        print(y)
        y = 4
    if(y < 5):
        print(y)

    if(mundoCompartilhado[i][j] != []):
        for infoComp in mundoCompartilhado[i][j]:
            if(infoComp not in mundo[i][j] and "V" not in mundo[i][j]):
                if(infoComp == "L"):
                    salasLivres.append([i,j])
                mundo[i][j] += infoComp + 'c'
    print("".join(mundo[i][j]),end="\t|")

main()