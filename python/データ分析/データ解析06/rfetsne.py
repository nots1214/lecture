import pandas as pd
from sklearn.datasets import load_iris
from sklearn.feature_selection import RFE
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestClassifier
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
import numpy as np
df = pd.read_excel('feature selection_data.xlsx')
X=df[[f"feature{i}" for i in range(1, 21)]]
y=df[["label"]]
print(X.shape)
print(X.columns)
rfe = RFE(estimator=LinearRegression(),n_features_to_select=2)
rfe.fit(X, y.to_numpy().ravel())
rfeData = pd.DataFrame(rfe.transform(X), columns=X.columns.values[rfe.support_])
print(rfeData.shape)
print(rfeData.columns)
data = rfeData
labels = y["label"]
tsne = TSNE(n_components=2, random_state=0)
transformed_data = tsne.fit_transform(data)
plt.figure()
scatter = plt.scatter(transformed_data[:, 0],transformed_data[:, 1],c=labels,cmap='Spectral',s=5)
plt.colorbar(boundaries=np.arange(3)-0.5).set_ticks(np.arange(2))
plt.title('t-SNE visualization')
plt.xlabel('t-SNE axis 1')
plt.ylabel('t-SNE axis 2')
plt.show()