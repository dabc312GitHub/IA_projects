import pygame

from gameVar import*
from settings import*
from imagenes import*
from menu import *

def make_board(screen, tablero):
    board = False
    for i in range(0, widthHeight * 3, widthHeight):
        for j in range(0, widthHeight * 3, widthHeight):
            board = board == False
            if board: 
                pygame.draw.rect(screen, (204,204,204), ((i, j), (widthHeight, widthHeight)))
            else: 
                pygame.draw.rect(screen, (50,50,50), ((i, j), (widthHeight, widthHeight)))
    for board in range(9):
        if tablero[board] == " ": 
            continue
        screen.blit(img[tablero[board]], (board % 3 * widthHeight + (widthHeight - dimension_img) / 2, board // 3 * widthHeight + (widthHeight - widthHeight) / 2))
       
def minMaxAlfaBeta(tablero, Ply_turn, depth = 5):
    if ganador(tablero) == Pc_Ply: 
        return (+10 - depth, None) 
    elif ganador(tablero) == Ply: 
        return (-10 - depth, None) 
    elif initialState not in tablero or depth < 1: 
        return (0, None) 
    elif Ply_turn: 
        best = (+11, None)
        for board in range(9):
            if tablero[board] == " ":
                valor = minMaxAlfaBeta(tablero[:board] + Ply + tablero[board + 1:], \
                        not Ply_turn, depth - 1)[0]
                if valor < best[0]: best = (valor, board) 
        return best
    else: 
        best = (-11, None)
        for board in range(9):
            if tablero[board] == " ":
                valor = minMaxAlfaBeta(tablero[:board] + Pc_Ply + tablero[board + 1:], \
                        not Ply_turn, depth - 1)[0]
                if valor > best[0]: 
                    best = (valor, board)
        return best
   
def ganador(tablero):
    for fila in jugadasGanar:
        if tablero[fila[0]] == initialState: 
            continue
        if len(set(tablero[casilla] for casilla in fila)) == 1: 
            return tablero[fila[0]]
    return False
       
def movimiento_pc(tablero):
    pygame.mouse.set_cursor(*pygame.cursors.broken_x)
    t0 = time.time() 
    if tablero[4] == initialState: 
        board = 4 
    elif dificultad < 1:
        board = set(i for i in range(9) if tablero[i] == initialState).pop() 
    elif dificultad >= 1:
        board = minMaxAlfaBeta(tablero, False, dificultad)[1] 
       
    if board is not None: tablero = tablero[:board] + Pc_Ply + tablero[board + 1:] 
    print( "La Pc_Ply ha tardado {:.5f} ms".format((time.time() - t0) * 1000))
    pygame.mouse.set_cursor(*pygame.cursors.arrow)
    return tablero


def main():
    global contador
    Ply_turn = True
    tablero = initialState * 9
    salir = False

    while not salir:
        clock.tick(FPS)
       
        if not Ply_turn and not ganador(tablero) and initialState in tablero:
            tablero = movimiento_pc(tablero)
            Ply_turn = True
   
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                raise SystemExit
               
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    raise SystemExit
                   
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    if ganador(tablero) or not initialState in tablero: salir = True
                    x = event.pos[0] // widthHeight + 3 * (event.pos[1] // widthHeight)
                    if tablero[x] == " ":
                        tablero = tablero[:x] + Ply + tablero[x + 1:]
                        Ply_turn = False
       
        make_board(screen, tablero)
        pygame.display.flip()
       
    if ganador(tablero):
        contador = contador + ganador(tablero)
        print("\n" * 100)
        print(ganador(tablero), "ha ganado!    TOTAL: ", "X", str(contador.count("X")) + "-" + str(contador.count("O")), "O")
        print("\n")
        salir = True    
    elif initialState not in tablero:
        print("\n" * 100)
        print("EMPATE!!    TOTAL: ", "X", str(contador.count("X")) + "-" + str(contador.count("O")), "O")
        print("\n")
        salir = True
       
while True: main()
raise SystemExit