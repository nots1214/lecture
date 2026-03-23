import pandas as pd
from sklearn.datasets import load_iris
from sklearn.feature_selection import RFE
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestClassifier
import matplotlib.pyplot as plt
import umap
import numpy as np
df = pd.read_excel('feature selection_data.xlsx')
X=df[[f"feature{i}" for i in range(1, 21)]]
y=df[["label"]]
print(X.shape)
print(X.columns)
rfe = RFE(estimator=LinearRegression(),n_features_to_select=6)#2or67
rfe.fit(X, y.to_numpy().ravel())
rfeData = pd.DataFrame(rfe.transform(X), columns=X.columns.values[rfe.support_])
print(rfeData.shape)
print(rfeData.columns)
data = rfeData
labels = y["label"]
reducer = umap.UMAP(random_state=42)
reducer.fit(data)
embedding = reducer.transform(data)
plt.scatter(embedding[:, 0],embedding[:, 1],c=labels, cmap='Spectral',s=5)
plt.gca().set_aspect('equal','datalim')
plt.colorbar(boundaries=np.arange(11)-0.5).set_ticks(np.arange(10))
plt.title('UMAP projection of the Digits dataset', fontsize=10)
plt.show()