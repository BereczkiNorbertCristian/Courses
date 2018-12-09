
from enum import Enum

class FeatureType(Enum):
    CATEGORICAL = 0
    CONTINUOUS = 1


class Node:

    def __init__(self):
        pass


class LeafNode(Node):

    def __init__(self, prediction_value):
        self.prediction_value = prediction_value


class DecisionNode(Node):

    def __init__(self):
        self.feature = None
        self.feature_type = None
        self.value = None
        self.left = None
        self.right = None


    def update(self, best):
        self.feature = best['feature']
        self.feature_type = best['feature_type']
        self.value = best['value']


    def set_left(self, node):
        self.left = node


    def set_right(self, node):
        self.right = node


    # using next one can iterate in the tree when doing prediction
    def next(self, x):
        if x is None:
            return self.left
        if self.attr_type == FeatureType.CATEGORICAL:
            if type(x[self.attr_name]) == type(self.value) and \
                x[self.attr_name] == self.value:
                return self.left
            else:
                return self.right
        if self.attr_type == FeatureType.CONTINUOUS:
            if type(x[self.attr_name]) == type(self.value) and \
                x[self.attr_name] < self.value:
                return self.left
            else:
                return self.right

        raise Exception("No node returned")
