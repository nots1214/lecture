# ファイル plotdot.py
# *で描く
from xyrange import XYRange


class PlotDot():

    # 内側なら"*", 外側なら" "
    def plot_inside(self):
        print("*", end="")

    def plot_outside(self):
        print(" ", end="")

    def next_line(self):
        print()


