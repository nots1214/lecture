import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import SpectralClustering
from keras.datasets import mnist
from sklearn.metrics import normalized_mutual_info_score
from sklearn.linear_model import Lasso
from sklearn.feature_selection import RFE
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestClassifier
import pandas as pd
from sklearn.manifold import LocallyLinearEmbedding
import umap
def purity_score(y_true, y_pred):
    clusters = np.unique(y_pred)
    N = len(y_true)
    purity = 0
    for cluster in clusters:
        idx = np.where(y_pred == cluster)[0]
        true_labels = y_true[idx]
        purity += np.max(np.bincount(true_labels))
    return purity / N
(X,y),(X_test,y_test)=mnist.load_data()
X2 = X[4::60]
X2 = X2.reshape(len(X2),-1)
y2 = y[4::60]
spectral_clustering = SpectralClustering(n_clusters=10, n_neighbors=7, affinity='nearest_neighbors')
cluster_labels = spectral_clustering.fit_predict(X2)
nmi = normalized_mutual_info_score(y2, cluster_labels)
print("NMI:", nmi)
pr = purity_score(np.array(y2),np.array(cluster_labels))
print("PURITY:",pr)
lasso = Lasso(alpha=0.3)
lasso.fit(X2, y2)
coefficients = lasso.coef_
feature_importance = np.abs(coefficients)
sorted_index = np.argsort(feature_importance)[::-1]
threshold = 0.0001
X2_df = pd.DataFrame(X2)
selected_features = X2_df.columns[feature_importance >= threshold]
X3 = X2_df[selected_features]
spectral_clustering = SpectralClustering(n_clusters=10, n_neighbors=7, affinity='nearest_neighbors')
cluster_labels = spectral_clustering.fit_predict(X3)
nmi = normalized_mutual_info_score(y2, cluster_labels)
print("NMI:", nmi)
pr = purity_score(np.array(y2),np.array(cluster_labels))
print("PURITY:",pr)
data = X2
reducer = umap.UMAP(n_components=100,n_neighbors=7,min_dist=0.0,random_state=42)
reducer.fit(data)
embedding = reducer.transform(data)
spectral_clustering = SpectralClustering(n_clusters=10, n_neighbors=7, affinity='nearest_neighbors')
cluster_labels = spectral_clustering.fit_predict(embedding)
nmi = normalized_mutual_info_score(y2, cluster_labels)
print("NMI:", nmi)
pr = purity_score(np.array(y2),np.array(cluster_labels))
print("PURITY:",pr)