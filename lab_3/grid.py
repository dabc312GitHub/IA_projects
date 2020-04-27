import pygame
import os

# current_path = os.path.dirname(__file__)  # the resources folder path
# print(current_path)

letter_X = pygame.image.load('X_1.png')
letter_O = pygame.image.load('O_1.png')
# letter_O = pygame.image.load(os.path.join('coding', 'O_1.png'))

class Grid:
    def __init__(self):
        self.grid_lines = [
            ((0, 200), (600, 200)),  # 1st row line
            ((0, 400), (600, 400)),  # 2nd row line
            ((200, 0), (200, 600)),  # 1st col line
            ((400, 0), (400, 600))   # 2nd col line
        ]

        self.grid = [ [0 for x in range(3)] for y in range(3) ]
        # print(self.grid)
        self.switch_player = True
        #Buscar posicion en cada sector 3x3 de la cuadricula
        self.search_dirs = [
            (0, -1), (-1, -1), (-1, 0), (-1, 1), 
            (0, 1), (1, 1), (1, 0), (1, -1)
            ]

        self.game_over = False


    def draw (self, surface):
        for line in self.grid_lines:
            pygame.draw.line(surface, (200, 200, 200), line[0], line[1], 20)

        for y in range (len(self.grid)):
            for x in range (len(self.grid[y])): 
                if self.get_cell_value(x, y) == "X":
                    surface.blit(letter_X, (x*200, y*200))
                elif self.get_cell_value(x, y) == "O":
                    surface.blit(letter_O, (x*200, y*200))

    def get_cell_value(self, x, y):
        return self.grid[y][x]

    def set_cell_value(self, x, y, value):
        self.grid[y][x] = value

    def get_mouse(self, x, y, player):
        if self.get_cell_value(x, y) == 0:
            self.swich_player = True

            if player == "X":
                self.set_cell_value(x, y, "X")
            elif player == "O":
                self.set_cell_value(x, y, "O")
            self.check_grid(x, y, player)
        else:
            self.switch_player = False

    def is_within_bounds(self, x, y):
        return x >= 0 and x < 3 and y >= 0 and y < 3

    def check_grid(self, x, y, player):
        count = 1
        for index, (dir_x, dir_y) in enumerate(self.search_dirs):
            if self.is_within_bounds(x + dir_x, y + dir_y) \
                and self.get_cell_value(x + dir_x, y + dir_y) == player:
                count += 1
                xx = x + dir_x
                yy = y + dir_y

                if self.is_within_bounds(xx + dir_x, yy + dir_y) \
                    and self.get_cell_value(xx + dir_x, yy + dir_y) == player:
                    count +=1 
                    if count == 3:
                        break
                if count < 3:
                    new_dir = 0
                    # mapear indice a su direccion opuesta
                    if index == 0:
                        new_dir = self.search_dirs[4] 
                    elif index == 1:
                        new_dir = self.search_dirs[5] 
                    elif index == 2:
                        new_dir = self.search_dirs[6]   
                    elif index == 3:
                        new_dir = self.search_dirs[7] 
                    elif index == 4:
                        new_dir = self.search_dirs[0] 
                    elif index == 5:
                        new_dir = self.search_dirs[1]
                    elif index == 6:
                        new_dir = self.search_dirs[2]
                    elif index == 7:
                        new_dir = self.search_dirs[3]

                    if self.is_within_bounds(x + new_dir[0], y + new_dir[1]) \
                        and self.get_cell_value(x + new_dir[0], y + new_dir[1]) == player:
                        count += 1
                        if count == 3:
                            break
                    else:
                        count = 1
        if count == 3:
            print(player, 'GANASTE!')
            self.game_over = True
        else:
            self.game_over = self.is_grid_full()

    def is_grid_full(self):
        for row in self.grid:
            for value in row:
                if value == 0:
                    return False
        return True

    def clear_grid(self):
        for y in range (len(self.grid)):
            for x in range (len(self.grid[y])):
                self.set_cell_value(x, y, 0)

    def print_grid(self):
        for row in self.grid:
            print(row)
        print("\n")
