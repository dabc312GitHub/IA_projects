from settings import *

print("ingrese dificultad del juego")
dificultad = int(input())
print("ingrese su jugador X u O")
Ply = input()
if (Ply == "X"):
    Pc_Ply = "O"
else:
    Pc_Ply = "X"
print("INGRESE A LA VENTANA DE JUEGO")