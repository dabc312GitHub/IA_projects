import pygame
import os

# current_path = os.path.dirname(__file__)  # the resources folder path
# print(current_path)

letter_X = pygame.image.load('X_1.png')
letter_O = pygame.image.load('O_1.png')
# letter_O = pygame.image.load(os.path.join('coding', 'O.png'))

class Grid:
    def __init__(self):
        self.grid_lines = [
            ((0, 200), (600, 200)),  # 1st hori line
            ((0, 400), (600, 400)),  # 2nd hori line
            ((200, 0), (200, 600)),  # 1st vert line
            ((400, 0), (400, 600))   # 2nd vert line
        ]

        self.grid = [ [0 for x in range(3)] for y in range(3) ]
        print(self.grid)

    def draw (self, surface):
        for line in self.grid_lines:
            pygame.draw.line(surface, (200, 200, 200), line[0], line[1], 20)

        # for y in range (len(self.grid)):
        #     for x in range (len(self.grid[y])): 
        #         if self.get_cell_value(x, y) == "X":
        #             surface.blit(letter_X, (x*200, y*200))
        #         elif self.get_cell_value(x, y) == "O":
        #             surface.blit(letter_O, (x*200, y*200))

    def get_cell_value(self, x, y):
        return self.grid[y][x]

    def set_cell_value(self, x, y, value):
        self.grid[y][x] = value

    def get_mouse(self, x, y, player):
        if player == "X":
            self.set_cell_value(x, y, "X")
        elif player == "O":
            self.set_cell_value(x, y, "O")

    def print_grid(self):
        for row in self.grid:
            print(row)
        print("\n")
