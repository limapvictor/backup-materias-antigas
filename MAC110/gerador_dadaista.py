##  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
##  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
##  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
##  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES
##  DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA
##  OU PLÁGIO.  
##  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS
##  DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
##  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E
##  DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS
##  DIVULGADOS NA PÁGINA DA DISCIPLINA.
##  ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E,
##  AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA.
##
##  Nome :Victor Pereira Lima
##  NUSP :10737028
##  Turma:BCC 2018
##  Prof.:Marcelo Queiroz
##
##  Referências: Com exceção das rotinas fornecidas no enunciado
##  e em sala de aula, caso você tenha utilizado alguma referência,
##  liste-as abaixo para que o seu programa não seja considerado
##  plágio ou irregular.
##  
##  Exemplo:
##  - O algoritmo Heapsort foi baseado em
##  https://rosettacode.org/wiki/Sorting_algorithms/Heapsort#Python

from random import randint

def verificaVerbo(verso,ordem):
    """ Função que faz as modificações necessarias em relação ao verbo do verso.
    """
    preposicoes = [" a a "," à "," a o "," ao ",
                   " de a "," da "," de o "," do ",
                   " por a "," pela "," por o "," pelo ",
                   " em a "," na "," em o "," no "] #vetor com as preposições a serem substituidas ja na ordem precisa -> substituir
    if(ordem == 1 and type(verso) == list): #como na ordem 1 o verbo é o ultimo termo fica mais facil mais facil mexer com o verso ainda em array
        finalVerbo = verso[2].find(' ') #essa parte procura a separação entre o verbo e sua preposição
        verso[1] = verso[2][finalVerbo + 1:] + ' ' + verso[1] #coloco a preposição do verbo no elemento do meio assim como no executavel
        verso[2] = verso[2].replace(verso[2][finalVerbo:],'')#retiro a preposição do verbo
    for i in range(len(preposicoes)):     
        if(i % 2 == 0 and preposicoes[i] in verso): #as preposições a serem substituidas estão nos indices pares 
            verso = verso.replace(preposicoes[i], preposicoes[i+1]) #troca a preposição pela adequação necessaria
    if (' -' in verso):
        verso = verso.replace(' -','')
    return verso

def insereConjuncao(verso):
    """Função que insere a conjunção se necessario no verso.
    """
    conjuncoes = ['como','e','enquanto','quando','porque','se','contudo',
                 'assim que','toda vez que','portanto','entretanto','mas',]
    if(randint(0,2) == 0): #1/3 de chance de a frase começar com uma conjunção, assim como 1/3 de chance do 0 ser sorteado
        conjSort = randint(0,len(conjuncoes) - 1)
        verso.insert(0,conjuncoes[conjSort])#insiro a conjunção no começo da frase
    return verso

def formatacaoSaida(verso,indiceFrase,numVersos):
    """Função que formata as frase pares ou impares como especificado no enunciado do ep.
    """
    if(indiceFrase % 2 == 0 or indiceFrase == numVersos):
        verso = verso + '.'
    if(indiceFrase % 2 == 1):
        verso = verso.capitalize()
    return verso 

def produzVersos(substantivos,verbos,numVersos,rimar):        
    """Gera (na tela) um poema, usando as listas de substantivos e verbos e com o número de versos desejado,com ou sem rima,
    dependendo do valor do parâmetro booleano rima.
    """
    poema = []
    substUsados = 0 #contador de quantos substantivos ja foram usados que sera necessario para a não repetição
    verbosUsados = 0
    numSubst = len(substantivos)
    numVerbos = len(verbos)
    for i in range(numVersos):
        verso = [] #reinicio o verso a cada iteração do for
        ordem = randint(0,2) #sorteio de qual ordem de elementos o verso tera                
        for j in range(2): # o for é usado pois a frase contém dois substantivos
            substSorteado = randint(0,numSubst - 1)#sorteio um substantivo aleatorio e vejo se ele cumpre as condições de rima e não repetição 
            if((rimar) and (i + 1) % 2 == 0 and ordem !=1 and j == 1): #corrijo o i para frases pares,a ordem não termina com verbo e só faço isso no 2º substantivo
                tentativaRimar = 0
                while(substantivos[substSorteado][0][-2:] != rima and (substantivos[substSorteado][1]) and tentativaRimar < numSubst + numVerbos): # se as duas ultimas letras são diferentes da rima necessaria e o contador se encaixa no parametro de tentativas tento um novo sorteio
                    substSorteado = randint(0,numSubst - 1)
                    tentativaRimar +=1
            else:
                while ((substantivos[substSorteado][1]) and substUsados < numSubst): #caso não precise rimar apenas a condição de não repetição é usada
                    substSorteado = randint(0,numSubst - 1)                
            verso.append(substantivos[substSorteado][0])#insiro o substantivo que cumpriu as condições necessarias ou simplesmente pego o ultimo
            substantivos[substSorteado][1] = True #atualizo essa posição para mostrar que aquele substantivo ja foi usado
            substUsados += 1 #incremento o numero de substantivos usados
        verboSorteado = randint(0,numVerbos - 1) #sorteio do verbo(identico ao do substantivo)
        if((rimar) and (i + 1) % 2 == 0 and ordem ==1):
            tentativaRimar = 0
            finalVerbo = verbos[verboSorteado][0].find(' ')
            while(verbos[verboSorteado][0][:finalVerbo][-2:] != rima and (verbos[verboSorteado][1]) and tentativaRimar < numVerbos + numSubst):
                verboSorteado = randint(0,numVerbos - 1)
                tentativaRimar +=1
        else:
            while((verbos[verboSorteado][1]) and verbosUsados < numVerbos):
                verboSorteado = randint(0,numVerbos - 1)
        verbos[verboSorteado][1] = True
        verbosUsados += 1
        if(ordem == 0): #sujeito-verbo-objeto
            verso.insert(1,verbos[verboSorteado][0])    
        elif(ordem == 1): #sujeito-objeto-verbo
            verso.append(verbos[verboSorteado][0])
            verso = verificaVerbo(verso,ordem) #fica mais facil tratar essa ordem como array então ja verifico o verso antes de transforma-lo em string
        elif(ordem == 2): #verbo-objeto-sujeito
            verso.insert(0,verbos[verboSorteado][0])
        verso = insereConjuncao(verso)
        verso = " ".join(verso) #transformo a lista em uma string
        verso = verificaVerbo(verso,ordem + 2) #verificação mais completa do verso quando ja transformado em string
        verso = formatacaoSaida(verso,i+1,numVersos) 
        if((rimar) and (i + 1) % 2 == 1): # se a frase for impar devemos guardar as duas ultimas letras caso a rima esteja ativa
            rima = verso[-2:]
        poema.append(verso) #inserimos o verso ja verificado e formatado no poema
    return poema

def main():
    substantivos = []
    numSub = int(input("Quantos substantivos você deseja utilizar? "))
    print("Digite um substantivo (com artigo) por linha:")
    for i in range(numSub):
        substantivos.append([input(),False]) # o array substantivos em cada posição possui um substantivo e a informação se ele ja foi usado(logo todos começam com false)
    print()
    verbos = []
    numVerbos = int(input("Quantos verbos você deseja utilizar? "))
    print("Digite um verbo (com preposição) por linha:")
    for j in range(numVerbos):
        verbos.append([input(),False])
    pergunta = input("Você deseja uma poesia com rima? Responda sim ou não: ")
    if(pergunta == "sim" or pergunta == 'Sim'):
        rimar = True
    else:
        rimar = False
    numVersos = int(input("Quantos versos você deseja que a poesia tenha? "))
    poema = produzVersos(substantivos,verbos,numVersos,rimar)
    print("")
    for k in range(len(poema)):
        print(poema[k])
        if((k + 1) % 4 == 0): # correção do k e a formatação de pular linha a cada 4 caracteres
            print("")

main()
