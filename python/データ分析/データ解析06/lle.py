import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.datasets import make_swiss_roll
from sklearn.manifold import LocallyLinearEmbedding
# データ生成 (スイスロールデータセット)
X, color = make_swiss_roll(n_samples=2000)
# 3次元データをプロット
fig = plt.figure(figsize=(15, 10))
ax = fig.add_subplot(211, projection='3d')
ax.scatter(X[:, 0], X[:, 1], X[:, 2], c=color, cmap=plt.cm.Spectral)
ax.set_title("Original 3D data")
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')
# LLEのインスタンス化
n_neighbors = 10 # 近傍点の数
n_components = 2 # 低次元空間の次元数
lle = LocallyLinearEmbedding(n_neighbors=n_neighbors, n_components=n_components, method='standard')
# LLEを使用してデータを変換
X_r = lle.fit_transform(X)
# LLEの結果を2次元でプロット
ax2 = fig.add_subplot(212)
ax2.scatter(X_r[:, 0], X_r[:, 1], c=color, cmap=plt.cm.Spectral)
plt.title('Locally Linear Embedding (LLE)')
plt.xlabel('Component 1')
plt.ylabel('Component 2')
plt.show()