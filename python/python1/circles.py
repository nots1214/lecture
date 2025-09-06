# ファイル circles.py
# 円を★で描く
from xyrange import XYRange


class CircleS():
    # 中心が(0,0)　半径が3.0の円
    def inside(self, x: float, y: float) -> bool:
        return x*x+y*y<=9.0

    # 描画範囲は，xが[-5.0, 5.0], 0.25刻み．yが[-5.0, 5.0]，0.5刻み．
    def get_range(self) -> XYRange:
        return XYRange(-5.0, 5.0, 0.25, -5.0, 5.0, 0.5)



