import random

from collections import defaultdict
from sys import argv, exit

def print_graph(graph,size):
    maze = list(' ')
    
    for x in range(size):
        maze.append('_ ')
    maze.append('\n')
    default = size-1;
    for j in range(size):
        maze.append('|')
        for i in range(size):
            if (i, (default-j-1)) not in graph[(i,default-j)]:
                maze.append('_')
            else:
                maze.append(' ')
            if (i+1, default-j) not in graph[(i,default-j)]:
                maze.append('|')
            else:
                maze.append(' ')
        maze.append('\n')
    maze_printout = ''.join(maze)
    print (maze_printout)

def add_cycles(graph, size):
    for i in range(size):
        for j in range(size):
            if len(graph[(i,j)]) < 3:
                chance = random.randint(1,10)
                if chance > 9:
                    for node in [(i+1,j),(i-1,j),(i,j+1),(i,j-1)]:
                        if node in graph:
                            graph[(i,j)].add(node)
                            graph[node].add((i,j))
                        break

def make_maze(graph, neighbors):
    next_set = set()
    visited = set()
    start = (0,0)
    second = (0,1)
    graph[start].add(second)
    graph[second].add(start)

    #Implementation of a growing tree algorithm to decide how nodes are connected
    seed = random.choice(tuple(neighbors))
    visited.add(seed)
    next_set.add(seed)
    while next_set:
        next_node = random.choice(tuple(next_set))
        if all(n in visited for n in neighbors[next_node]):
            next_set.remove(next_node)
        else:
            for n in neighbors[next_node]:
                if n not in visited:
                    next_set.add(n)
                    visited.add(n)
                    graph[next_node].add(n)
                    graph[n].add(next_node)
                    break            

def build_graph(neighbors, size):
    for node in [(x,y) for x in range(size) for y in range(size)]:
        x, y = node
        if x != 0:
            neighbors[node].add((x-1,y))
        if y != 0:
            neighbors[node].add((x,y-1))
        if x != size-1:
            neighbors[node].add((x+1,y))
        if y != size-1:
            neighbors[node].add((x,y+1))

if __name__ == "__main__":
    if len(argv) < 2:
        print ('Usage: maze_gen length_of_side_of_maze')
        exit(1)

    size = int(argv[1])

    if size < 6 or size%2 == 1:
        print ('Incorrect size. Must be even. Min: 6')
        exit(1)

    neighbors = defaultdict(set)
    graph = defaultdict(set)
    
    build_graph(neighbors, size)

    make_maze(graph, neighbors)
    add_cycles(graph, size)

    print_graph(graph,size)