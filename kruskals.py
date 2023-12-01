import networkx as nx
import matplotlib.pyplot as plt

def find(subsets, i):
    if subsets[i] != i:
        subsets[i] = find(subsets, subsets[i])
    return subsets[i]

def kruskal(graph):
    mst = []
    edges = sorted(graph.edges(data=True), key=lambda t: t[2].get('weight', 1))
    subsets = {v: v for v in graph.nodes()}

    for u, v, w in edges:
        root1 = find(subsets, u)
        root2 = find(subsets, v)
        if root1 != root2:
            mst.append((u, v, w))
            subsets[root1] = root2

    return mst

# Example graph creation
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

# Kruskal's Algorithm
mst_edges = kruskal(G)

# Drawing the original graph
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, font_weight='bold')

# Edge labels
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

# Highlighting the MST edges
mst_edges = [(u, v) for u, v, d in mst_edges]
nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='r', width=2)

# Show plot
plt.show()
