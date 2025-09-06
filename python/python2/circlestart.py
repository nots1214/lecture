
# ファイル rectdott.py
# 円を★で描く
from figure_template import FigureTemplate
from xyrange import XYRange


class CircleStarT(FigureTemplate):
    # 中心が(0,0)半径が3.0の円
    def _inside(self, x: float, y: float) -> bool:
        return x*x+y*y <= 9.0

    # 描画範囲は，xが[-5.0, 5.0], 0.25刻み．yが[-5.0, 5.0]，0.5刻み．
    def _get_range(self) -> XYRange:
        return XYRange(-5.0, 5.0, 0.25, -5.0, 5.0, 0.5)

    # 内側なら"★", 外側なら"　"
    def _plot_inside(self):
        print("★", end="")

    def _plot_outside(self):
        print("　", end="")

    def _next_line(self):
        print()
        print()


if __name__ == "__main__":
    CircleStarT().draw()