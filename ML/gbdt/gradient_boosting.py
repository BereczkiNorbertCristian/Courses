
import pandas as pd

from decision_tree import DecisionTree

class GradientBoosting:


    def __init__(self, n_estimators):
        self.n_estimators = n_estimators
        self.estimators = []


    def fit(self, df, target):
        self.estimators = []
        df['yi'] = df[target]
        df['predf'] = 0
        for _ in range(self.n_estimators):

            dt = DecisionTree(ignore_columns=['predf',target])
            dt.build_tree(df,'yi')

            predi = pd.Series([
                dt.predict(df.iloc[i])
                for i in range(df.shape[0])
            ])

            df['predf'] = df['predf'] + predi
            df['yi'] = df[target] - df['predf']

            self.estimators.append(dt)


    def predict(self, x):
        return sum([
            dt.predict(x)
            for dt in self.estimators
        ])
