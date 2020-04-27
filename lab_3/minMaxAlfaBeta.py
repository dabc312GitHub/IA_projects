
from gameVar import*
from settings import*

def minMaxAlfaBeta(tablero, turno_player, profundidad = 5):
    if ganador(tablero) == MAQUINA: 
        return (+10 - profundidad, None) 
    elif ganador(tablero) == JUGADOR: 
        return (-10 - profundidad, None) 
    elif VACIO not in tablero or profundidad < 1: return (0, None) 
    elif turno_player: 
        best = (+11, None)
        for a in range(9):
            if tablero[a] == " ":
                valor = minMaxAlfaBeta(tablero[:a] + JUGADOR + tablero[a + 1:], not turno_player, profundidad - 1)[0]
                if valor < best[0]: best = (valor, a) 
        return best
    else: 
        best = (-11, None)
        for a in range(9):
            if tablero[a] == " ":
                valor = minMaxAlfaBeta(tablero[:a] + MAQUINA + tablero[a + 1:], not turno_player, profundidad - 1)[0]
                if valor > best[0]: best = (valor, a)
        return best