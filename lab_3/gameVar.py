initialState = " "
contador = ""
jugadasGanar = ((0, 1, 2), (3, 4, 5), (6, 7, 8), (1, 4, 7), (2, 5, 8), (0, 4, 8), (0, 3, 6), (2, 4, 6))

colisionan = lambda punto, pos, dimensiones: pos[0] <= punto[0] <= pos[0] + dimensiones[0] and pos[1] <= punto[1] <= pos[1] + dimensiones[1]
