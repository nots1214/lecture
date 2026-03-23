from sklearn.cluster import SpectralClustering
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_excel('circles_data.xlsx',header = 0)
X=data.iloc[:,:2].values
# Perform spectral clustering
spectral_clustering = SpectralClustering(n_clusters=3, n_neighbors=7, affinity='nearest_neighbors')
#spectral_clustering = SpectralClustering(n_clusters=3, gamma=20, affinity='rbf')
cluster_labels = spectral_clustering.fit_predict(X)

# Visualize the clusters
plt.figure(figsize=(6,6))
plt.scatter(X[:, 0], X[:, 1], c=cluster_labels)
plt.xlabel('feature1')
plt.ylabel('feature2')
plt.title('Spectral Clustering (k-nearest neighbor)')
plt.savefig("Spectral Clustering result(knearest).png") 
plt.show()