import umap
import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt
# 手書き数字データセットをロード
digits = datasets.load_digits()
data = digits.data
labels = digits.target
# umapを実行、2次元に削減
reducer = umap.UMAP(random_state=42)
reducer.fit(data)
embedding = reducer.transform(data)
#結果のプロット
plt.scatter(embedding[:, 0],embedding[:, 1],c=labels, cmap='Spectral',s=5)
plt.gca().set_aspect('equal','datalim')
plt.colorbar(boundaries=np.arange(11)-0.5).set_ticks(np.arange(10))
plt.title('UMAP projection of the Digits dataset', fontsize=10)
plt.show()