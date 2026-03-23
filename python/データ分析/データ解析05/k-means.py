from sklearn.cluster import KMeans
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_excel('circles_data.xlsx',header = 0)
X=data.iloc[:,:2].values
#plt.scatter(data.iloc[:,0],data.iloc[:,1],c=data.iloc[:,2])
#plt.show()
#K-meansクラスタリングの実行
kmeans = KMeans(n_clusters=3) #クラスタ数を指定
kmeans.fit(X)
#クラスタリング結果を取得
cluster_labels = kmeans.labels_

plt.figure(figsize=(6,6))
plt.scatter(X[:,0],X[:,1],c=cluster_labels)
plt.xlabel('feature1')
plt.ylabel('feature2')
plt.title("K-means method")
plt.savefig("kmeans_result.png") 
plt.show()