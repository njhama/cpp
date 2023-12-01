import networkx as nx
import matplotlib.pyplot as plt

def kruskal_step_by_step(graph):
    edges = sorted(graph.edges(data=True), key=lambda t: t[2].get('weight', 1))
    subsets = {v: v for v in graph.nodes()}
    mst = []

    for u, v, w in edges:
        root1 = find(subsets, u)
        root2 = find(subsets, v)

        if root1 != root2:
            mst.append((u, v, w))
            subsets[root1] = root2
            yield mst

def find(subsets, i):
    if subsets[i] != i:
        subsets[i] = find(subsets, subsets[i])
    return subsets[i]

def update_visualization(step):
    plt.clf()
    nx.draw(G, pos, with_labels=True, font_weight='bold', node_color='lightblue')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    if step:  # Check if step is not empty
        mst_edges = [(u, v) for u, v, d in step]
        nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='r', width=2)

    plt.draw()

def on_key_press(event):
    global current_step_index, steps

    if event.key == 'right':
        if current_step_index < len(steps) - 1:
            current_step_index += 1
        elif current_step_index == len(steps) - 1:
            try:
                next_step = next(kruskal_steps)
                steps.append(next_step)
                current_step_index += 1
            except StopIteration:
                pass
    elif event.key == 'left':
        if current_step_index > 0:
            current_step_index -= 1

    update_visualization(steps[current_step_index])


G = nx.Graph()
G.add_edge('A', 'B', weight=4)
G.add_edge('A', 'H', weight=8)
G.add_edge('B', 'C', weight=8)
G.add_edge('B', 'H', weight=11)
G.add_edge('C', 'D', weight=7)
G.add_edge('C', 'F', weight=4)
G.add_edge('C', 'I', weight=2)
G.add_edge('D', 'E', weight=9)
G.add_edge('D', 'F', weight=14)
G.add_edge('E', 'F', weight=10)
G.add_edge('F', 'G', weight=2)
G.add_edge('G', 'H', weight=1)
G.add_edge('G', 'I', weight=6)
G.add_edge('H', 'I', weight=7)


pos = nx.spring_layout(G)
edge_labels = nx.get_edge_attributes(G, 'weight')

fig, ax = plt.subplots()
plt.gcf().canvas.mpl_connect('key_press_event', on_key_press)

kruskal_steps = kruskal_step_by_step(G)
steps = [[]]
current_step_index = 0

update_visualization(steps[current_step_index])
plt.show()
