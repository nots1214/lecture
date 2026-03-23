import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.manifold import TSNE
# 手書き数字データセットをロード(1797 samples, 64 features)
digits = datasets.load_digits()
data = digits.data
labels = digits.target
# t-SNEのインスタンス化と低次元への変換実行
tsne = TSNE(n_components=2, random_state=0)
transformed_data = tsne.fit_transform(data)
# 結果のプロット
plt.figure()
scatter = plt.scatter(transformed_data[:, 0],transformed_data[:, 1],c=labels,cmap='Spectral',s=5)
plt.colorbar(boundaries=np.arange(11)-0.5).set_ticks(np.arange(10))
plt.title('t-SNE visualization of digits dataset')
plt.xlabel('t-SNE axis 1')
plt.ylabel('t-SNE axis 2')
plt.show()