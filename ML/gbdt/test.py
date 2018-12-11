

import numpy as np
import pandas as pd

from random import uniform
from decision_tree import DecisionTree


def rmse(predictions, targets):
    return np.sqrt(((predictions - targets) ** 2).mean())


def label(f1,f2):
    if f1 <= 50 and f2 <= 50: return 1
    if f1 <= 50 and f2 > 50 : return 0
    if f1 > 50 and f2 <= 50: return 0
    if f1 > 50 and f2 > 50: return 1


def get_dataset():
    points = [
        (uniform(0,100),uniform(0,100))
        for _ in range(220)
    ]
    labeled_points = [
        [f1,f2,label(f1, f2)]
        for f1,f2 in points
    ]
    return pd.DataFrame(
        data=labeled_points,
        columns=['f1','f2','target'],
        dtype=np.float64,
    )

df = get_dataset()
dt = DecisionTree()

df = df[df['target'] != 2]

dt.build_tree(df, 'target')

predictions = [
    dt.predict(df.iloc[i])
    for i in range(df.shape[0])
]
targets = list(df['target'].values)

print("RMSE:")
print(rmse(np.array(predictions),np.array(targets)))
print("Predictions:")
print(predictions)
print("Targets:")
print(targets)
