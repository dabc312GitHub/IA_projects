
from matplotlib import pyplot as plt


def draw_graph(graph):
    print("start drawing graph (this can take several seconds) ....")
    for vertex in graph.vertices:
        for ady_vertex in graph.ady(vertex):
            x_values = [vertex.x, ady_vertex.x]
            y_values = [vertex.y, ady_vertex.y]
            plt.plot(x_values, y_values, color='#E3DFDD')
    print("end drawing graph ....")
