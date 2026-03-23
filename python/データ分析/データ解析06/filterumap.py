import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import umap
df = pd.read_excel('feature selection_data.xlsx')
X=df[[f"feature{i}" for i in range(1, 21)]]
y=df[["label"]]
cor = pd.concat([X, y], axis=1).corr()
target_cor = abs(cor["label"])
print(target_cor)
c = 0.3
X_selected = target_cor[target_cor>c]
X_selected = X_selected.drop("label").index
print(X_selected)
cor2 = X[X_selected].corr().abs()
print(cor2)
threshold = 0.9
while True:
    max = 0
    for i in range(len(X_selected)):
        for j in range(i+1,len(X_selected)):
            f1 = X_selected[i]
            f2 = X_selected[j]
            if max < cor2.loc[f1,f2]:
                max = cor2.loc[f1,f2]
                idx1 = f1
                idx2 = f2
    if max < threshold:
        break
    X_selected = X_selected.drop(idx2)
print(X[X_selected].corr().abs())
data = X[X_selected]
labels = y["label"]
reducer = umap.UMAP(random_state=42)
reducer.fit(data)
embedding = reducer.transform(data)
plt.scatter(embedding[:, 0],embedding[:, 1],c=labels, cmap='Spectral',s=5)
plt.gca().set_aspect('equal','datalim')
plt.colorbar(boundaries=np.arange(3)-0.5).set_ticks(np.arange(2))
plt.title('UMAP projection', fontsize=10)
plt.show()