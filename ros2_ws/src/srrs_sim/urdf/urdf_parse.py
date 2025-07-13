"""
Depth-limited traversal of a URDF tree.

Dependencies
------------
pip install urdfpy networkx
"""
from urdfpy import URDF
import networkx as nx
from pathlib import Path
from collections import deque

def load_urdf(path: str | Path) -> URDF:
    return URDF.load(str(path))

def build_graph(robot: URDF) -> nx.DiGraph:
    """
    Convert the URDF’s joint/link relationships into a NetworkX
    directed graph: parent → child.
    """
    g = nx.DiGraph()
    for joint in robot.joints:
        g.add_edge(joint.parent, joint.child, joint=joint)
    return g



def descendants_at_depth(graph: nx.DiGraph, root: str, max_depth: int = 1):
    """
    Breadth-first expansion that stops once *max_depth* is reached.
    Returns (node_name, depth) tuples.
    """
    q = deque([(root, 0)])
    seen = {root}
    while q:
        node, d = q.popleft()
        if d > max_depth:
            continue
        yield node, d
        for child in graph.successors(node):
            if child not in seen:
                seen.add(child)
                q.append((child, d+1))



if __name__ == "__main__":
    urdf_path   = "robot.urdf"
    root_link   = "block0_fix"   # base link of robot
    depth_limit = 2             # deapth of tree creation

    robot  = load_urdf(urdf_path)
    graph  = build_graph(robot)

    print(f"Nodes ≤ depth {depth_limit} from {root_link}:")
    for name, d in descendants_at_depth(graph, root_link, depth_limit):
        print(f"{'  '*d}↳ {name}  (depth {d})")
