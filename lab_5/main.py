from dependencies.data import Perceptron
import time

digitos = Perceptron()
#digitos.showPatterns()
#digitos.showWeights()

while True:
    time.sleep(5)
    digitos.TestFromImg("Patterns/test/pat.png")


