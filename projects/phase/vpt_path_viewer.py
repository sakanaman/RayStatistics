import phase_module
import numpy as np
from matplotlib import cm
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("darkgrid")
from mpl_toolkits.mplot3d import Axes3D
import mpl_toolkits.mplot3d.art3d as art3d

#param
g = 0.1
origin = np.array([0,-2.5,0])
direction = np.array([0,1,0])
sigma_a = 0
sigma_s = 5
radius = 2.0


fig=plt.figure(figsize=(8,8))
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_xlim(-2.0, 2.0)
ax.set_ylim(-2.0, 2.0)
ax.set_zlim(-2.0, 2.0)
ax.view_init(elev=20, azim=-21)

u,v=np.mgrid[0:2*np.pi:50j, 0:np.pi:25j]
x=radius * np.cos(u)*np.sin(v)
y=radius * np.sin(u)*np.sin(v)
z=radius * np.cos(v)
ax.plot_wireframe(x, y, z, color='dimgrey', linewidth=0.2)


n = 100
path_list_list = []
for i in range(0, n):
    path_list_list.append(np.array(phase_module.vpt_path(g, sigma_a, sigma_s, radius, origin, direction)))

for path_list in path_list_list:
    now_point = origin
    rnd_color = [np.random.rand(), np.random.rand(), np.random.rand()]
    for v in path_list:
        next_sc_point = now_point + v
        line = art3d.Line3D([now_point[0], next_sc_point[0]],[now_point[1], next_sc_point[1]],[now_point[2], next_sc_point[2]], color=rnd_color, linewidth=1.2)
        ax.add_line(line)
        now_point = next_sc_point

plt.title("free-path sampling with HG phase function: g = {}".format(g))
plt.show()