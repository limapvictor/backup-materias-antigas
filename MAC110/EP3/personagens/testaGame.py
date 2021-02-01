import pygame, random

def teste():
    pygame.init()
    size = 800
    tela = pygame.display.set_mode([size,size])
    imgs = ["livre.jpeg","muro.jpg","poco.jpg","wumpus.jpeg","personagem.png","compartilhe.png"]
    mundo = [[0,1,0,2,3],[3,2,1,0,0],[2,3,1,1,0],[0,0,0,3,2],[1,0,1,3,1]]
    superf = []
    for i in range(5):
        lin = []
        for j in range(5):
            tipo = mundo[i][j]
            img = pygame.image.load(imgs[tipo])
            img = pygame.transform.scale(img,(size//5, size//5))
            lin.append(img)
        superf.append(lin)
    per = pygame.image.load(imgs[4])
    per = pygame.transform.scale(per,(size//5, size//5))
    cp = pygame.image.load(imgs[5])
    cp = pygame.transform.scale(cp,(size//5, size//5))
    cp = pygame.transform.rotate(cp,-90)
    sair = False
    while(not sair):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sair = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_MINUS:
                    print("Diminuir")
                if event.key == pygame.K_EQUALS:
                    print("Aumentar")
                if event.key == pygame.K_COMMA:
                    print("/1.5")                 
                if event.key == pygame.K_PERIOD:
                    print("*1.5")
        for i in range(5):
            for j in range(5):
                if(i == j):
                    superf[i][j].blit(per, [0,0])
                if(i == 2*j):
                    superf[i][j].blit(cp,[0,0])
                tela.blit(superf[i][j], [(size/5)*i, (size/5)*j])
        pygame.display.update()
    pygame.quit()

def main():
    teste()

main()