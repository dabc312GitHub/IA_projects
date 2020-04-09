
import random

from pythonVers.settings import base as settings


class Vertex():
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def near_vertices(self):
        near = []
        variation_x = [-1, 0 ,1, 0, 1, -1, 1, -1]
        variation_y = [0, -1, 0, 1, -1, 1, 1, -1]
        for (var_x, var_y) in zip(variation_x, variation_y):
            x = self.x + var_x
            y = self.y + var_y
            if -1 < x < settings.size_w and -1 < y < settings.size_h:
                near.append(Vertex(x, y))
        return near

    def __str__(self):
        return '({}, {})'.format(self.x,self.y)

    x=0
    y=0


class VertexList():
    vertices = []
    dict = {}

    def append(self, vertex):
        self.vertices.append(vertex)
        self.dict[str(vertex)] = True

    def is_inside(self, vertex):
        try:
            result = self.dict[str(vertex)]
        except:
            result = self.dict[str(vertex)] = False
        return result

    def __getitem__(self, index):
        return self.vertices[index]


def generate_rand_vertex():
    vertex = Vertex(random.randint(0, settings.size_w - 1),
                    random.randint(0, settings.size_h - 1))
    return vertex


def generate_rand_vertices():
    random.seed()
    vertices = VertexList()
    for num in range(settings.num_delete_vertices):
        vertex = generate_rand_vertex()
        while vertices.is_inside(vertex):
            vertex = generate_rand_vertex()
        vertices.append(vertex)
    return vertices
