import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import numpy as np

def input_triangle(name="T"):
    print(f"Введите координаты вершин треугольника {name} (формат: x y z):")
    A = list(map(float, input("A: ").split()))
    B = list(map(float, input("B: ").split()))
    C = list(map(float, input("C: ").split()))
    return np.array([A, B, C])

def plot_triangles(tri1, tri2):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    poly1 = Poly3DCollection([tri1], alpha=0.6, facecolor='cyan', edgecolor='k')
    poly2 = Poly3DCollection([tri2], alpha=0.6, facecolor='magenta', edgecolor='k')
    
    ax.add_collection3d(poly1)
    ax.add_collection3d(poly2)
    
    all_pts = np.vstack((tri1, tri2))
    x_min, x_max = all_pts[:,0].min(), all_pts[:,0].max()
    y_min, y_max = all_pts[:,1].min(), all_pts[:,1].max()
    z_min, z_max = all_pts[:,2].min(), all_pts[:,2].max()
    
    margin = 0.1 * max(x_max-x_min, y_max-y_min, z_max-z_min)
    ax.set_xlim(x_min-margin, x_max+margin)
    ax.set_ylim(y_min-margin, y_max+margin)
    ax.set_zlim(z_min-margin, z_max+margin)
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title('Два треугольника в 3D')
    
    plt.show()

def main():
    tri1 = input_triangle("T1")
    tri2 = input_triangle("T2")
    plot_triangles(tri1, tri2)

if __name__ == "__main__":
    main()
