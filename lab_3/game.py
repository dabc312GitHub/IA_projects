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
        if event.type == pygame.MOUSEBUTTONDOWN \
            and not grid.game_over:
            if pygame.mouse.get_pressed()[0]:
                pos = pygame.mouse.get_pos()
                print(pos[0] // 200, pos[1] // 200)
                grid.get_mouse(pos[0] // 200, pos[1] // 200, player)
                if grid.switch_player:
                    if player == "X":
                        player = "O"
                    else:
                        player = "X"
                    # mi debug por consola del tablero
                    grid.print_grid()

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE \
                and grid.game_over:
                grid.clear_grid()
                grid.game_over = False
            elif event.key == pygame.K_SPACE:
                running = False

    surface.fill((80, 80, 80))
    grid.draw(surface)
    pygame.display.flip()
