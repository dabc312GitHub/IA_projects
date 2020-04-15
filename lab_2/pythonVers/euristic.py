
import sys
sys.path.append("../")
from matplotlib import pyplot as plt
import math

from pythonVers.headers.graph import Graph
from pythonVers.headers.vertex import Vertex
from pythonVers.headers.draw import draw_graph


def distance(p1, p2):
    return math.sqrt((p1.x-p2.x)**2 + (p1.y-p2.y)**2)


def draw_graph_euristic(begin, end):
    graph = Graph()
    draw_graph(graph)
    ax = plt.axes()
    print("start drawing euristic algorithm ...")
    current = begin
    while str(current) != str(end):
        next = current
        min_distance = math.inf
        for ady in graph.ady(current):
            if distance(ady, end) < min_distance:
                next = ady
                min_distance = distance(ady, end)

        x_values = [current.x, next.x]
        y_values = [current.y, next.y]
        plt.plot(x_values, y_values, color='red')

        ax.arrow(current.x, current.y,
                 next.x - current.x, next.y - current.y,
                 head_width=0.2, head_length=0.4, fc='k', ec='k')
        current = next

    print("end drawing euristic ...")
    plt.show()

vertexbegin = Vertex(0, 0)
vertexend = Vertex(99, 99)
draw_graph_euristic(vertexbegin, vertexend)


