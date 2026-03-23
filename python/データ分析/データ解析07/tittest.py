#ライブラリーのインポート
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#データの読み込み（タイタニックデータ）
df = pd.read_excel('titanic.xlsx')
#データを確認
df['Age'].plot(kind='hist')
df.head()
plt.show()