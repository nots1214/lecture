
# ファイル xyrange.py
# xの動く範囲[x1, x2]と動く間隔xstep
# yの動く範囲[y1, y2]と動く間隔ystep の6つの数の組を表す．

class XYRange:
    x1: float
    x2: float
    xstep: float

    y1: float
    y2: float
    ystep: float

    def __init__(self, x1: float, x2: float, xstep: float, y1: float, y2: float, ystep: float) -> None:
        self.x1 = x1
        self.x2 = x2
        self.xstep = xstep

        self.y1 = y1
        self.y2 = y2
        self.ystep = ystep