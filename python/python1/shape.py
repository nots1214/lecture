
# ファイル shape.py
from abc import ABC, abstractmethod
from xyrange import XYRange


class Shape(ABC):
    # 抽象メソッド inside(x, y)
    # (x, y)が図形の内側ならtrueを，そうでなければfalseを返すものとする．
    # ちょうど境界線上は内側とみなす約束とする．
    @abstractmethod
    def inside(self, x: float, y: float) -> bool:
        pass

    # 抽象メソッド get_range()
    # xの動く範囲[x1, x2]と動く間隔xstep
    # yの動く範囲[y1, y2]と動く間隔ystep の6つの数の組を返す．
    @abstractmethod
    def get_range(self) -> XYRange:
        pass