import sys
sys.path.append("../../")

import turtle

from pythonVers.headers.graph import Graph


def draw_graph(graph):
    turtle.tracer(0)
    for vertex in graph.vertices:
        for ady_vertex in graph.ady(vertex):
            turtle.up()
            turtle.goto(vertex.x*6-350, vertex.y*6-300)
            turtle.down()
            turtle.goto(ady_vertex.x*6-350, ady_vertex.y*6-300)
    turtle.done()


graph = Graph()
draw_graph(graph)

