from sklearn.cluster import SpectralClustering
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.metrics import normalized_mutual_info_score
from sklearn.datasets import load_iris

def purity_score(y_true, y_pred):
    # y_true:  真のラベル（例: [1,1,1,2,2,2,3,3,3]）
    # y_pred:  クラスタラベル（KMeansのlabels_）

    # クラスタ数
    clusters = np.unique(y_pred)
    N = len(y_true)

    purity = 0
    for cluster in clusters:
        # クラスタ k のサンプルのインデックス
        idx = np.where(y_pred == cluster)[0]

        # そのクラスタ内の真のラベルを数える
        true_labels = y_true[idx]
        
        # 最頻値のラベルの数を加算
        purity += np.max(np.bincount(true_labels))

    return purity / N
iris = load_iris()

data=iris.data[:,0:4]

X=data
# Perform spectral clustering
spectral_clustering = SpectralClustering(n_clusters=3, n_neighbors=7, affinity='nearest_neighbors')
#spectral_clustering = SpectralClustering(n_clusters=3, gamma=20, affinity='rbf')
cluster_labels = spectral_clustering.fit_predict(X)

true_labels = [1]*50+[2]*50+[3]*50
# Visualize the clusters
plt.figure(figsize=(6,6))
plt.scatter(X[:, 0], X[:, 1], c=cluster_labels)
plt.xlabel('feature1')
plt.ylabel('feature2')
plt.title('Spectral Clustering (k-nearest neighbor)')
plt.savefig("Spectral Clustering result(knearest).png") 
plt.show()

nmi = normalized_mutual_info_score(true_labels, cluster_labels)
print("NMI:", nmi)
pr = purity_score(np.array(true_labels),np.array(cluster_labels))
print("PURITY:",pr)