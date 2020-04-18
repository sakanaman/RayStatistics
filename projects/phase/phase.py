import phase_module
import numpy as np
from matplotlib import cm
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("darkgrid")
from mpl_toolkits.mplot3d import Axes3D

#scattering parametor
g = 0.1

# phase sampling
n = 1000
X = np.zeros(n)
Y = np.zeros(n)
Z = np.zeros(n)
for i in range(0, n):
    wi = phase_module.henyey_greenstein_sample(g, np.random.rand(), np.random.rand())
    X[i] = wi[0]
    Y[i] = wi[2]
    Z[i] = wi[1]

# draw sampling point
fig=plt.figure(figsize=(8,8))
ax = fig.add_subplot(111, projection='3d')
# ax.plot_surface(x,y,z, alpha=1) # hemisphere
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

ax.scatter(X,Y,Z,marker="o",linestyle='None') # sample point

# draw sphere
u,v=np.mgrid[0:2*np.pi:50j, 0:np.pi:25j]
x=np.cos(u)*np.sin(v)
y=np.sin(u)*np.sin(v)
z=np.cos(v)
ax.plot_wireframe(x, y, z, color='dimgrey', linewidth=0.2)

# draw vector(incident ray)->Vec(0,-1,0)
ax.quiver(0,-1,0,0,1,0,color="orchid")

plt.title("Henyey-Greenstein phase function:  g = {}".format(g))
plt.show()