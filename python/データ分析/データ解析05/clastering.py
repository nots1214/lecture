import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.spatial.distance import pdist
from scipy.cluster.hierarchy import linkage, dendrogram
from scipy.cluster.hierarchy import fcluster

df = pd.read_excel('example_score.xlsx',header = 0,index_col = 0)

data=df.values
similarity = pdist(data,metric='euclidean')

linkage_matrix = linkage(similarity,method='single')

dendrogram(linkage_matrix)
plt.xlabel('Data Points')
plt.ylabel('Distance')
plt.title('Hierarchical Clustering Dendrogram')
plt.show()

num_clusters = 2
clusters = fcluster(linkage_matrix,num_clusters,criterion='maxclust')
column_index=['0','1','2','3','4','5','6']
dfout = pd.DataFrame({'学籍番号': column_index, 'cluster label': clusters})
dfout.to_excel('cluster_result.xlsx',index=False)