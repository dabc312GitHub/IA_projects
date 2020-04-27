import pygame, time
from settings import *

pygame.init()
clock = pygame.time.Clock()

img = {"X" : pygame.transform.smoothscale(pygame.image.load("X_1.png"), (dimension_img, dimension_img)),
       "O" : pygame.transform.smoothscale(pygame.image.load("O_1.png"), (dimension_img, dimension_img))}

screen = pygame.display.set_mode(resolucion)
pygame.display.set_caption("Tres en raya")