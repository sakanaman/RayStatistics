import diffuse_module
import numpy as np 
from matplotlib import cm
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("darkgrid")
from mpl_toolkits.mplot3d import Axes3D

# diffuse sampling
n = 1000
X = np.zeros(n)
Y = np.zeros(n)
Z = np.zeros(n)
for i in range(0, n):
    wi = diffuse_module.sample_diffuse(np.random.rand(), np.random.rand())
    X[i] = wi[0]
    Y[i] = wi[1]
    Z[i] = wi[2]

# sampling point
fig=plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, projection='3d')
# ax.plot_surface(x,y,z, alpha=1) # hemisphere
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.scatter(X,Y,Z,marker="o",linestyle='None',c=Z) # sample point

# sphere
u,v=np.mgrid[0:2*np.pi:50j, 0:np.pi:25j]
x=np.cos(u)*np.sin(v)
y=np.sin(u)*np.sin(v)
z=np.cos(v)
ax.plot_wireframe(x, y, z, color='lightskyblue', linewidth=0.5)

plt.show()