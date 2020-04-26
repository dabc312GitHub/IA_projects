import pygame

from grid import Grid

import os
os.environ['SDL_VIDEO_WINDOW_POS'] = '400, 100'

surface = pygame.display.set_mode((600, 600))
pygame.display.set_caption('Tres en Raya')

grid = Grid()
# grid.set_cell_value(1, 1, 'X')

grid.print_grid()
running = True
player = "X"

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                pos = pygame.mouse.get_pos()
                # print(pos)
                # print(pos[0] // 200, pos[1] // 200)
                pos_0 = pos[0] // 200
                pos_1 = pos[1] // 200
                grid.get_mouse(pos_0, pos_1, player)
                print(pos_0, pos_1)

                if player == "X":
                    player = "O"
                else:
                    player = "X "

                grid.print_grid()

    surface.fill((80, 80, 80))
    grid.draw(surface)
    pygame.display.flip()
