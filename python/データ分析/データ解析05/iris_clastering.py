import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.spatial.distance import pdist
from scipy.cluster.hierarchy import linkage, dendrogram
from scipy.cluster.hierarchy import fcluster
from sklearn.metrics import normalized_mutual_info_score
from sklearn.datasets import load_iris


import numpy as np

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
#print(data)
similarity = pdist(data,metric='euclidean')

linkage_matrix = linkage(similarity,method='single')

dendrogram(linkage_matrix)
plt.xlabel('Data Points')
plt.ylabel('Distance')
plt.title('Hierarchical Clustering Dendrogram')
plt.show()

num_clusters = 3
clusters = fcluster(linkage_matrix,num_clusters,criterion='maxclust')
column_label=[1]*50+[2]*50+[3]*50
dfout = pd.DataFrame({ 'true label' : column_label, 'cluster label': clusters})
dfout.to_excel('iris_cluster_result.xlsx',index=False)

plt.figure(figsize=(6,6))
plt.scatter(data[:, 0], data[:, 1], c=clusters)
plt.xlabel('feature1')
plt.ylabel('feature2')
plt.title('Iris k-means')
plt.savefig("Iris k-means result.png") 
plt.show()

# NMIを計算
nmi = normalized_mutual_info_score(column_label, clusters)
print("NMI:", nmi)
pr = purity_score(np.array(column_label),np.array(clusters))
print("PURITY:",pr)