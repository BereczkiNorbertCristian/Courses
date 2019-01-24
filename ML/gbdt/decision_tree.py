
import numpy as np

from nodes import DecisionNode, LeafNode, FeatureType

# Please transform all integer features that you want to represent as
# continuous variables into floats, otherwise they will be treated as
# categorical features
#
# We will treat D as a dataframe, so please convert it to a data frame
# if you haven't

DEB_ITER = 0
LENGTH = 0

class DecisionTree:


    def __init__(self, ignore_columns):
        self.root = None
        self.target_name = None
        self.EPS = 0.01
        self.MIN_STOP_SIZE = 10
        self.ignore_columns = ignore_columns


    # We will consider the target type as a float
    def build_tree(self, D, target_name):
        self.root = DecisionNode()
        self.target_name = target_name
        self.build_subtree(self.root, D)


    def build_subtree(self, node, D):
        DL, DR = self.split_best(node, D)
        print(node)
        if self.stopping_criterion(DL):
            node.left = LeafNode(self.find_prediction(DL))
        else:
            node.left = DecisionNode()
            self.build_subtree(node.left, DL)
        if self.stopping_criterion(DR):
            node.right = LeafNode(self.find_prediction(DR))
        else:
            node.right = DecisionNode()
            self.build_subtree(node.right, DR)


    def find_prediction(self, D):
        return D[self.target_name].mean()


    def stopping_criterion(self, D):
        global LENGTH
        if D[self.target_name].var() < self.EPS or \
            D.shape[LENGTH] < self.MIN_STOP_SIZE:
            return True
        return False


    def compute_var(self, D, DL, DR):
        global LENGTH
        var_split = D.shape[LENGTH] * D[self.target_name].var()
        adder = DL.shape[LENGTH] * DL[self.target_name].var()
        if np.isnan(adder):
            adder = 0
        var_split -= adder
        adder = DR.shape[LENGTH] * DR[self.target_name].var()
        if np.isnan(adder):
            adder = 0
        var_split -= adder
        return var_split


    def update_best_dict(self, best, D, split_column, split_value):
        global LENGTH
        if D[split_column].dtype == np.float64:
            DL = D[D[split_column] < split_value]
            DR = D[D[split_column] >= split_value]
            var_split = self.compute_var(D, DL, DR)
            feature_type = FeatureType.CONTINUOUS
        else:
            DL = D[D[split_column] == split_value]
            DR = D[D[split_column] != split_value]
            var_split = self.compute_var(D, DL, DR)
            feature_type = FeatureType.CATEGORICAL


        if ((best['var'] is None or best['var'] < var_split) and
                DL.shape[LENGTH] != 0 and DR.shape[LENGTH] != 0):
            best['var'] = var_split
            best['feature'] = split_column
            best['value'] = split_value
            best['feature_type'] = FeatureType.CONTINUOUS
        return best


    def split_best(self, node, D):
        global DEB_ITER
        global LENGTH
        best = {
            'var': None,
            'feature': None,
            'value': None,
            'feature_type': None,
            'idx': None,
        }

        for c in D.columns:

            if c == self.target_name: continue
            if c in self.ignore_columns: continue
            if len(D[c].unique()) == 1: continue

            if D[c].dtype == np.float64:
                # Treat as continuous feature
                if D[c].shape[LENGTH] <= 11:
                    # We have a few number of examples
                    unique_values = D[c].unique()
                    for i in range(1,unique_values.shape[LENGTH]):
                        split_value = unique_values[i]
                        best = self.update_best_dict(best, D, c, split_value)
                else:
                    # Take only 9 splits based on quantiles because we have
                    # a larger number of examples
                    for i in range(1,10):
                        split_value = D[c].quantile(1.0 * i / 10)
                        best = self.update_best_dict(best, D, c, split_value)
            else:
                # Treat as categorical feature
                for split_value in D[c].unique():
                    best = self.update_best_dict(best, D, c, split_value)

        node.update(best)
        return (
            D[
                D[best['feature']] < best['value']
                if best['feature_type'] == FeatureType.CONTINUOUS
                else D[best['feature']] == best['value']
            ],
            D[
                D[best['feature']] >= best['value']
                if best['feature_type'] == FeatureType.CONTINUOUS
                else D[best['feature']] != best['value']
            ]
        )


    def predict(self, x):
        current_node = self.root
        while isinstance(current_node, DecisionNode):
            current_node = current_node.next(x)
        return current_node.prediction_value
