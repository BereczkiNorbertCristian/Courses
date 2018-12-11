
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
        if self.feature_type == FeatureType.CATEGORICAL:
            if x[self.feature] == self.value:
                return self.left
            else:
                return self.right
        if self.feature_type == FeatureType.CONTINUOUS:
            #print(self.feature)
            #print(x)
            #print(x[self.feature])
            #print(self.value)
            if x[self.feature] < self.value:
                return self.left
            else:
                return self.right

        raise Exception("No node returned")


    def __str__(self):
        return """
            Feature {feature} splits on {value}
        """.format(
            feature=self.feature,
            value=self.value,
        )
