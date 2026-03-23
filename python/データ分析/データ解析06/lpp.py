from sklearn.datasets import make_blobs
import matplotlib.pyplot as plt
#人工データ生成 
X, y = make_blobs(n_samples=1000, n_features=300, centers=4,cluster_std=8, random_state=42)
#最初の２次元をプロット
plt.scatter(X[:, 0], X[:, 1], c = y)
plt.title("First 2 dimensions of original data")
plt.xlabel('Dimention 1')
plt.ylabel('Dimention 2')
from lpproj import LocalityPreservingProjection
# LPPのインスタンス化
lpp = LocalityPreservingProjection(n_components=2, n_neighbors = 10)
# LPPを使用してデータを変換
X_2D = lpp.fit_transform(X)
# LPPの結果を2次元でプロット
plt.scatter(X_2D[:, 0], X_2D[:, 1], c=y)
plt.title("Projected from 300->2 dimensions");
plt.show()