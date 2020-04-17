import diffuse_module
import numpy as np 
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("darkgrid")
from mpl_toolkits.mplot3d import Axes3D


n = 1000
X = [0] * n
Y = [0] * n
Z = [0] * n
for i in range(0, n):
    wi = diffuse_module.sample_diffuse(np.random.rand(), np.random.rand())
    X[i] = wi[0]
    Y[i] = wi[1]
    Z[i] = wi[2]



fig = plt.figure(figsize=plt.figaspect(0.54))
ax = Axes3D(fig)


ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.plot(X,Y,Z,marker="o",linestyle='None')


plt.show()