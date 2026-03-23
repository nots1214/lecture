import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import Lasso
from sklearn.datasets import load_iris
import umap
from sklearn.manifold import TSNE
df = pd.read_excel('feature selection_data.xlsx')
X=df[[f"feature{i}" for i in range(1, 21)]]
y=df[["label"]]
lasso = Lasso(alpha=0.02)
lasso.fit(X, y)
coefficients = lasso.coef_
feature_importance = np.abs(coefficients)
sorted_index = np.argsort(feature_importance)[::-1]
print("Feature importance sorted:")
for idx in sorted_index:
    print(f"feature {idx+1}: {feature_importance[idx]}")
threshold = 0.01
selected_features = X.columns[feature_importance >= threshold]
print("Selected features:")
print(selected_features)
X_selected = X[selected_features]
data = X_selected
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