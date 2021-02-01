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

""" O MUNDO DE WUMPUS

    Esta é uma versão adaptada do jogo criado por Gregory Yob em 1975.
    Nesta versão o mundo é um tabuleiro em forma de toro NxN em que cada
    sala pode estar livre, conter um muro, um poço sem fundo ou um
    terrível Wumpus. As personagens nesse mundo devem se unir para 
    eliminar todos os Wumpus e assim poderem voltar sãs e salvas para
    casa. Ao percorrerem as salas do mundo, as personagens recebem dados
    sensoriais que as ajudarão a compreender o que pode estar nas salas
    adjacentes, e assim evitar alguns destinos trágico, como cair em um
    poço sem fundo ou ser devoradas por um terrível Wumpus. Cada
    personagem possui uma flecha, que pode ser disparada uma única vez,
    preferencialmente quando a personagem tiver acumulado evidências
    suficientes de que existe um Wumpus à sua frente. Personagens também
    podem se encontrar, e trocar conhecimento sobre as partes do mundo
    que já exploraram.
"""

# use apenas para depuração
__DEBUG__ = False
# o mundo não deve ser importado como módulo
if __name__!="__main__":
    print("Por favor execute o Mundo de Wumpus com o comando\n",
          "    python3 mundo.py")
    exit()

import math, sys, random, glob, pygame, time

# tratamento dos argumentos default e possiveis parametros opcionais passados pelo usuario.
arg = ['mundo.py',800, 5, 0.2, 0.2, 0.9, 0.5]
for i in range(len(sys.argv)):
    arg[i] = sys.argv[i]
M, S, alpha, beta, gama, omega = arg[1], arg[2], arg[3], arg[4], arg[5], arg[6] 
# associa números/nomes aos 4 tipos de salas do mundo de Wumpus
LIVRE,MURO,POCO,WUMPUS = range(4)
salas = ["L","M","P","W"]
# associa números/nomes aos 5 tipos de ações possíveis
ANDAR,GIRARDIREITA,GIRARESQUERDA,ATIRAR,COMPARTILHAR = range(5)
acoes = ["A","D","E","T","C"]

class MundoDeWumpus:
    """ Classe principal: define um Mundo de Wumpus, cria personagens,
        faz a simulação e anuncia o final do jogo.
    """
    def __init__(self):
        """ Construtor: inicializa a representação do mundo,
            inclui as personagens NUSP e dummy e passa a simular o jogo.
        """
        # número de personagens de acordo com a quantidade de módulos de personagens diferentes.
        self.nPersonagens = 51
        # número de Wumpus de acordo com o número de personagens.
        self.nWumpus = math.floor(self.nPersonagens * gama)
        # tamanho do mundo
        self.N = math.ceil((gama * self.nPersonagens/(1-alpha-beta-omega))**0.5)
        # criacao do mundo chamando uma função por questão de organização
        self.mundo = self.constroiMundo()
        self.imprimeMundo()
        # criação da lista com as personagens.
        self.personagens = ListaDePersonagens(self.N,self.nPersonagens,self.mundo)
        # faz o processamento do jogo
        self.processaJogo()
        # anuncia o final do jogo
        self.finalizaJogo()
    
    def processaJogo(self):
        """ Método processaJogo: controla o laço principal, processando uma
            personagem por vez, enquanto o jogo não tiver acabado.
        """
        # criação da interface
        self.interface = Interface(self.N,self.mundo,self.personagens.personagens)
        # criação da flag do urro
        self.urro = False
        # Repete o laço principal enquanto existirem Wumpus e personagens vivos.
        while (self.nWumpus>0 and self.personagens.nPersonagens >= 1):
            #chama o método que processa a percepção de cada personagem no mundo.
            self.personagens.processaPercepcoes(self)
            # reinicializa a flag urro, que já foi usada nas percepções.
            self.urro = False
            # chama o método de planejamento das personagens.
            self.personagens.processaPlanejamentos()
            # processa as possiveis ações dos personagens, dando atenção especial aos compartilhamentos e aos tiros.
            self.personagens.processaAcoes(self)
            # processa os comandos do usuário na interface
            self.interface.processaComando(self)
            # atualiza a tela de acordo com as ações dos personagens e dos comandos do usuário na interface.
            self.interface.atualizaTela(self.mundo, self.personagens.personagens)
            # delay controlado pelo usuário
            time.sleep(self.interface.deltaT)

    def finalizaJogo(self):
        """ O jogo termina quando não há mais personagens vivas,
            ou quando todos os Wumpus foram mortos.
        """
        if(self.nWumpus == 0):
            print('Parabéns vcs ganharam o jogo')
        if(self.personagens.nPersonagens < 1):
            print('Todas personagens morreram.')
        pygame.quit()
    
    def constroiMundo(self):
        # esse vetor tem correspondencia com os indices do tipo da sala(0->livre,1->muro...) e cada posição indica quantas daquele tipo ainda 
        # precisam ser alocadas no mundo.
        qtdMuros, qtdPocos = math.floor(alpha * self.N ** 2), math.floor(beta * self.N ** 2)
        preencheSalas = [(self.N**2) - qtdMuros - qtdPocos - self.nWumpus, qtdMuros, qtdPocos, self.nWumpus]
        mundo = []
        for i in range(self.N):
            linha = []
            for j in range(self.N):
                # a parte abaixo realiza uma espécie de sorteio enviesado.A variavel total representa o total de casas a serem sorteadas ainda 
                # e é manipulada a para verificação dos pesos de tipo da sala.
                total = preencheSalas[0] + preencheSalas[1] + preencheSalas[2]
                tipo = 3
                # sorteio do total de casas a serem sorteadas ainda
                sorteio = random.randint(1,total + preencheSalas[tipo])
                # se o número sorteado for menor do que o o valor da variavel total, quer dizer que o tipo da sala é abaixo do atual.
                while(sorteio <= total):
                    # assim decremento o tipo e retiro da variavel total o peso daquele tipo.
                    tipo -= 1
                    total -= preencheSalas[tipo]
                # se o número sorteado for maior do que o total, quer dizer que ele se encaixa naquele peso e então posso inserir
                # aquele tipo na sala referida e decrementar a quantidade de salas daquele tipo a serem preenchidas.
                linha.append(tipo)
                preencheSalas[tipo] -= 1
            mundo.append(linha)
        return mundo

    def imprimeMundo(self):
        for i in range(self.N):
            for j in range(self.N):
                print(self.mundo[i][j],end='\t')
            print('')

class Personagem:
    """ Meta-classe para processar as ações de cada personagem:
        andar, girarDireita, girarEsquerda, atirar e compartilhar.
        Essas ações são métodos da personagem que recebem também
        o objeto MundoDeWumpus, pois potencialmente podem alterar
        o estado do mundo (por exemplo, ao se matar um Wumpus).
        Essas ações devolvem True/False indicando se foram realizadas.
        Cada personagem em particular além desses métodos também
        precisa definir as funções:
            def __init__(self,N):
            def planejar(self,percepcao):
            def agir(self):
    """
    def __init__(self,N,arquivo,mundo):
        #importo o módulo correspondente
        self.modulo = __import__(arquivo[:-3])
        self.nome = arquivo[10:-3]
        # inicializa a personagem
        self.estaviva = True # bem-vinda ao Mundo de Wumpus, personagem!
        self.N = N # copia a dimensão do mundo, pra facilitar
        # sorteio da posição de nascimento da personagem em uma sala livre.
        iPos, jPos = random.randint(0,self.N-1), random.randint(0,self.N-1)
        while(mundo[iPos][jPos] != 0 ):
            iPos, jPos = random.randint(0,self.N-1), random.randint(0,self.N-1)
        self.posicaoNasc, self.posicao = [iPos,jPos], [iPos,jPos]  # o atributo posicaoNasc será utilizado para o manejo da visão de mundo da personagem
        #sorteio da orientação de nascimento da personagem. a orientação é constituida de 0 na linha ou coluna e de 1/-1 no outro indice.
        self.orientacaoNasc = [0,0] # essa não é uma orientação valida e ja será modificada
        # primeiro sorteio randomicamente que coordenada da orientação sera modificada, e depois sorteio se a modificação será 1 ou -1.
        self.orientacaoNasc[random.randint(0,1)] =[1,-1][random.randint(0,1)]
        self.orientacao = self.orientacaoNasc.copy()
        self.nFlechas = 1 # primeiro chá de bebê da personagem
        self.modulo.inicializa(N) # chama a inicialização do módulo
        # define os valores que a personagem conhece
        self.modulo.nFlechas = self.nFlechas # copia nFlechas para o módulo
        self.modulo.mundoCompartilhado = [] # cria matriz NxN de listas vazias
        for i in range(N) :
            linha = []
            for j in range(N) :
                linha.append([]) # começa com listas vazias
            self.modulo.mundoCompartilhado.append(linha)
        self.modulo.__DEBUG__ = False
        self.impacto = False
        self.compartilhou = False 
        # Usa um vetor com as funções acima para facilitar o processamento das ações.
        # Os índices correspondem aos valores atribuídos aos símbolos respectivos
        # ("A"<->0, "D"<->1, etc.)
        self.processe = [ self.ande, self.gireDireita, self.gireEsquerda]

    def perceber(self,percepcao,MundoW):    
        pos = self.posicao
        vizinhos = [ [(pos[0]+1)%self.N,pos[1]],
                     [(pos[0]-1)%self.N,pos[1]],
                     [pos[0],(pos[1]+1)%self.N],
                     [pos[0],(pos[1]-1)%self.N] ]
        for viz in vizinhos:
            if(MundoW.mundo[viz[0]][viz[1]] == WUMPUS and "F" not in percepcao):
                percepcao.append("F") # fedor
            if(MundoW.mundo[viz[0]][viz[1]] == POCO and "B" not in percepcao):
                percepcao.append("B") # brisa
        if(self.impacto):
            percepcao.append("I")
            self.impacto = False
        if(MundoW.urro and "U" not in percepcao):
            percepcao.append("U")
        percepcao.append(self.nome)
        return percepcao

    def planejar(self,percep):
        """ Método planejar (implementado pelo módulo)
        """
        percepcao = percep.copy()
        if(self.nome in percepcao):
            percepcao.remove(self.nome) #a percepção enviada ao personagem não contém o nome dele próprio a fim de não bugar o compartilhamento.      
        print(self.posicao,self.modulo.posicao,self.nome,percepcao)
        self.modulo.planejar(percepcao)

    def agir(self,acao,MundoW):
        """ Método agir (implementado pelo módulo).
        """
        self.processe[acoes.index(acao)](MundoW)
    
    def morrer(self,MundoW):
        self.estaviva = False
        self.posicao = []
        self.modulo = None
        if(self in MundoW.personagens.personagens):
            MundoW.personagens.personagens.remove(self)
            MundoW.personagens.nPersonagens -= 1

    def ande(self,MundoW):
        """ Função ande: verifica se é possível mover a personagem
            na direção indicada por sua orientação, e as consequências
            disso.
        """
        # posicao e orientacao atuais da personagem
        pos = self.posicao
        ori = self.orientacao
        # calcula a posição nova
        posnova = [(pos[0]+ori[0])%self.N,
                   (pos[1]+ori[1])%self.N]
        # se houver um muro, não dá para andar
        mundo = MundoW.mundo
        if mundo[posnova[0]][posnova[1]] == MURO:
            self.impacto = True
            MundoW.interface.reproduzSom('impacto')
        else:
            pos[0],pos[1] = posnova[0],posnova[1]
            # se houver wumpus ou poço, é game over para a personagem
            if mundo[pos[0]][pos[1]] == WUMPUS:
                MundoW.interface.reproduzSom('wumpus')
                self.morrer(MundoW)
            elif mundo[pos[0]][pos[1]] == POCO:
                MundoW.interface.reproduzSom('poco')
                self.morrer(MundoW)
        # tentar andar é sempre realizável
        return True

    def gireDireita(self,MundoW):
        """ Corrige a orientação através de um giro no sentido horário.
        """
        ori = self.orientacao
        if ori[1]==0:
            ori[0] = -ori[0]
        ori[0],ori[1] = ori[1],ori[0]
        # girar é sempre realizável
        return True

    def gireEsquerda(self,MundoW):
        """ Corrige a orientação através de um giro no sentido anti-horário.
        """
        ori = self.orientacao
        if ori[0]==0:
            ori[1] = -ori[1]
        ori[0],ori[1] = ori[1],ori[0]
        # girar é sempre realizável
        return True

    def atire(self,MundoW):
        """ Atira uma flecha, se possível, na direção indicada pela
            orientação da personagemNUSP, e verifica se acertou um Wumpus.
        """
        # personagem só pode atirar se tiver flechas...
        if self.nFlechas==0:
            print("Lamento, "+self.nome+", você não tem mais flechas...", sep="")
            return False
        # processa o tiro
        self.nFlechas -= 1
        self.modulo.nFlechas = self.nFlechas
        # calcula destino do tiro
        pos = self.posicao
        ori = self.orientacao
        posnova = [(pos[0]+ori[0])%self.N,
                   (pos[1]+ori[1])%self.N]
        MundoW.interface.reproduzSom('tiro')
        # verifica se acertou um Wumpus e atualiza o mundo
        mundo = MundoW.mundo
        if mundo[posnova[0]][posnova[1]] == WUMPUS:
            mundo[posnova[0]][posnova[1]] = LIVRE # atualiza a sala com Wumpus
            MundoW.nWumpus -= 1 # contabiliza a morte
            MundoW.urro = True # propaga o som da morte do Wumpus
            MundoW.interface.reproduzSom('morteWumpus')
        # informa que o tiro foi realizado
        return True

    def compartilhe(self,infoComp):
        """ O personagem recebe uma matriz mundoComp que contém todas as informações 
            compartilhadas dos personagens naquela sala naquele instante e insere os valores 
            no atributo mundoCompartilhado, deixando a cargo do módulo lidar com as informações.
        """
        # atribuição dos atributos de nascimento do personagem que serão utilizados na conversão dos sistemas de coordenadas.
        i0, j0 = self.posicaoNasc[0], self.posicaoNasc[1]
        ori0, ori1 = self.orientacaoNasc[0], self.orientacaoNasc[1] 
        for i in range(self.N):
            for j in range(self.N):
                # fazendo a conversão entre os sistemas de coordenadas, verificando se ele é basedo em linhas ou colunas.
                if(ori1 == 0):
                    for info in infoComp[i][j]:
                        if(info not in self.modulo.mundoCompartilhado[ori0*(i-i0)][j-j0]):
                            self.modulo.mundoCompartilhado[ori0*(i-i0)][j-j0] += info
                elif(ori0 == 0):
                    for info in infoComp[i][j]:
                        if(info not in self.modulo.mundoCompartilhado[ori1*(j-j0)][i0-i]):
                            self.modulo.mundoCompartilhado[ori1*(j-j0)][i0-i] += info
        return True

    def adicionarInfoComp(self,matriz):
        """Essa função pega a matriz infoComp, que tem o objetivo de abrigar toda 
           a informação compartilhada de cada usuário, e no final será repassada a cada usuário para
           que ele insira as informações no atributo mundoCompartilhado.
        """
        i0,j0 = self.posicaoNasc[0], self.posicaoNasc[1]
        ori0,ori1 = self.orientacaoNasc[0], self.orientacaoNasc[1]
        for i in range(self.N):
            for j in range(self.N):
                if(ori1 == 0):
                    for info in self.modulo.mundo[ori0*(i-i0)][j-j0]:
                        if(info == "V"):
                            matriz[i][j] += "L"
                        elif(info not in matriz[i][j]):
                            matriz[i][j] += info
                elif(ori0 == 0):
                    for info in self.modulo.mundo[ori1*(j-j0)][i0-i]:
                        if(info == "V"):
                            matriz[i][j] += "L"
                        elif(info not in matriz[i][j]):
                            matriz[i][j] += info 
        return matriz 

class ListaDePersonagens:
    """
    """
    def __init__(self,N,nPersonagens,mundo):
        self.N = N
        self.nPersonagens = nPersonagens
        self.mundo = mundo
        # crio a lista vazia de Personagens 
        self.personagens = []
        # importo todos os arquivos de personagens necessários
        arquivos = glob.glob('personagem*.py')
        for arquivo in arquivos:
            # para cada arquivo crio um novo objeto da classe Personagem e insiro na lista de personagens
            self.personagens.append(Personagem(self.N,arquivo,self.mundo))
        # vou criar um dicionario dos personagens também para facilitar no processo de compartilhamento.
        self.dicPersonagens = {}
        for personagem in self.personagens:
            self.dicPersonagens[personagem.nome] = personagem

    def processaPercepcoes(self,MundoW):
        """
        """
        self.percepcoes = []
        for i in range(self.N):
            linha = []
            for j in range(self.N):
                linha.append([])
            self.percepcoes.append(linha)
        for personagem in self.personagens:
            if(personagem.estaviva):
                pos = [personagem.posicao[0], personagem.posicao[1]]
                self.percepcoes[pos[0]][pos[1]] = personagem.perceber(self.percepcoes[pos[0]][pos[1]],MundoW).copy()

    def processaPlanejamentos(self):
        """
        """
        for personagem in self.personagens:
            personagem.planejar(self.percepcoes[personagem.posicao[0]][personagem.posicao[1]])
    
    def processaCompartilhamentos(self):
        """
        """
        salas = [] # salas em que ocorrerá o compartilhamento
        for i in range(self.nPersonagens):
            if(self.acoes[i] == "C" and self.percepcoes[self.personagens[i].posicao[0]][self.personagens[i].posicao[1]] not in salas):
               salas.append(self.percepcoes[self.personagens[i].posicao[0]][self.personagens[i].posicao[1]].copy())
        for sala in salas:
            infoComp = []
            for i in range(self.N):
                lin = []
                for j in range(self.N):
                    lin.append([])
                infoComp.append(lin)    
            for k in range(2):
                for percepcao in sala:
                    if(percepcao not in ["F","B","I","U"]):
                        if(k == 0):
                            infoComp = self.dicPersonagens[percepcao].adicionarInfoComp(infoComp)
                        else:
                            self.dicPersonagens[percepcao].compartilhe(infoComp)

    def processaTiros(self,MundoW):
        """
        """
        for i in range(self.nPersonagens):
            if(self.acoes[i] == "T"):
                self.personagens[i].atire(MundoW)
        
    def processaAcoes(self,MundoW):
        """
        """
        self.acoes = []
        for personagem in self.personagens:
            acao = personagem.modulo.agir()
            self.acoes.append(acao)
        print(self.acoes)
        self.processaCompartilhamentos()
        self.processaTiros(MundoW)
        for i in range(self.nPersonagens):
            if(self.acoes[i] != "C" and self.acoes[i] != "T"):
                self.personagens[i].agir(self.acoes[i],MundoW)

class Interface:
    """
    """
    def __init__(self,N,mundo,personagens):
        self.N = N 
        self.M = M # indica o número de pixels da janela.
        self.S = S # número de salas que o usuário visualiza na janela.
        self.i0, self.j0 = 0, 0
        self.deltaT = 2 # controla a taxa de atualização da interface.
        pygame.init()
        self.imagens = [pygame.image.load("livre.jpeg"), pygame.image.load("muro.jpg"),
                        pygame.image.load("poco.jpg"), pygame.image.load("wumpus.jpg"),
                        pygame.image.load("personagem.png"), pygame.image.load("seta.png"),
                        pygame.image.load("compartilhe.png")]
        self.tela = pygame.display.set_mode([self.M,self.M])
        pygame.display.set_caption("Mundo de Wumpus Copa do Mundo 2018 Edition")
        self.atualizaTela(mundo,personagens)

    def atualizaTela(self, mundo, personagens):
        """
        """
        for i in range(self.i0,self.S):
            for j in range(self.j0,self.S):
                tam = self.M // self.S
                tipo = mundo[(self.i0+i)%self.N][(self.j0+j)%self.N]
                sala = pygame.transform.scale(self.imagens[tipo], (tam, tam))
                self.tela.blit(sala, [tam*j,tam*i])
        orientacoes = [[0,1],[-1,0],[0,-1],[1,0]] #
        salas = []
        for personagem in personagens:
            if(self.i0 <= personagem.posicao[0] < self.S and self.j0 <= personagem.posicao[1] < self.S):
                tam = self.M // self.S
                if(personagem.posicao in salas):
                    imgCompartilhe = pygame.transform.scale(self.imagens[6], (tam,tam))
                    self.tela.blit(imgCompartilhe, [tam*personagem.posicao[1],tam*personagem.posicao[0]])        
                else:
                    imgPersonagem = pygame.transform.scale(self.imagens[4], (tam, tam))
                    self.tela.blit(imgPersonagem, [tam*personagem.posicao[1],tam*personagem.posicao[0]])
                    imgOrientacao = pygame.transform.scale(self.imagens[5], (tam//2, tam//2))
                    imgOrientacao = pygame.transform.rotate(imgOrientacao, 90 * orientacoes.index(personagem.orientacao))
                    self.tela.blit(imgOrientacao, [(tam*personagem.posicao[1]) + tam//4, (tam*personagem.posicao[0]) + tam//4])
                    salas.append(personagem.posicao)
        pygame.display.update()
    
    def processaComando(self, MundoW):
        """
        """
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                MundoW.finalizaJogo()
            if evento.type == pygame.KEYDOWN:
                if evento.key == pygame.K_MINUS:
                    self.S += 1
                if evento.key == pygame.K_EQUALS:
                    if self.S > 1:
                        self.S -= 1
                if evento.key == pygame.K_COMMA:
                    self.deltaT = self.deltaT / 1.5
                if evento.key == pygame.K_PERIOD:
                    self.deltaT = self.deltaT * 1.5
                if evento.key == pygame.K_ESCAPE:
                    MundoW.finalizaJogo()    
                if evento.key == pygame.K_SPACE:
                    pass

    def reproduzSom(self, som):
        """
        """
        self.sons = {'wumpus':pygame.mixer.Sound("wumpus.wav"),'morteWumpus':pygame.mixer.Sound("morteWumpus.wav"),
                    'tiro':pygame.mixer.Sound("tiro.wav"),'impacto':pygame.mixer.Sound("impacto.ogg"),
                    'poco':pygame.mixer.Sound("poco.ogg")}
        self.sons[som].play()        

# Chamada principal... é aqui que toda a mágica acontece!

m = MundoDeWumpus()

