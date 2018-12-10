

import numpy as np
import pandas as pd

from random import uniform
from decision_tree import DecisionTree


def label(f1,f2):
    if f1 <= 50 and f2 <= 50: return 1
    if f1 <= 50 and f2 > 50 : return 0
    if f1 > 50 and f2 <= 50: return 2
    if f1 > 50 and f2 > 50: return 2


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

print("Predictions:")
print(dt.predict(df.iloc[3]))
print(df.iloc[3])
