
import sys
sys.path.append("../")
from matplotlib import pyplot as plt

from pythonVers.headers.graph import Graph
from pythonVers.headers.vertex import Vertex
from pythonVers.headers.draw import draw_graph


def draw_graph_bfs(begin, end):
    graph = Graph()
    draw_graph(graph)
    ax = plt.axes()
    print("start drawing bfs ...")
    stack = [begin]
    arrived = False
    marked = {str(begin): True}
    father = {}
    while not arrived and len(stack) != 0:
        new_stack = []
        for current_point in stack:
            if str(end) != str(current_point):
                try:
                    for point in graph.ady(current_point):
                        try:
                            mark = marked[str(point)]
                        except:
                            mark = marked[str(point)] = False
                        if not mark:
                            x_values = [point.x, current_point.x]
                            y_values = [point.y, current_point.y]
                            plt.plot(x_values, y_values, color='blue')

                            ax.arrow(current_point.x, current_point.y,
                                     point.x-current_point.x, point.y - current_point.y,
                                     head_width=0.2, head_length=0.4, fc='k', ec='k')

                            marked[str(point)] = True
                            new_stack.append(point)
                            father[str(point)] = current_point
                except:
                    print("cache exception error, save the file and run again the program")
                    return -1
            else:
                arrived = True
        stack = new_stack
    print("end drawing bfs ...")

    regresive = end
    while str(regresive) != str(begin):
        try:
            regresive_next = father[str(regresive)]
        except:
            print('Excepction Error in Cache, saev the file and run again  the program')
            return -1
        x_values = [regresive.x, regresive_next.x]
        y_values = [regresive.y, regresive_next.y]
        plt.plot(x_values, y_values, color='red')
        regresive = regresive_next
    plt.show()


print('Ingrese la coordenada x del primer punto')
p1_x = int(input())
print('Ingrese la coordenada y del primer punto')
p1_y = int(input())
print('Ingrese la coordenada x del segundo punto')
p2_x = int(input())
print('Ingrese la coordenada y del segundo punto')
p2_y = int(input())

vertexbegin = Vertex(0, 0)
vertexend = Vertex(99, 99)
draw_graph_bfs(vertexbegin, vertexend)
