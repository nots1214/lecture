# ファイル plotstar.py
# ★で描く
#from figure_template import FigureTemplate
from xyrange import XYRange


class PlotStar():

    # 内側なら"*", 外側なら" "
    def plot_inside(self):
        print("★", end="")

    def plot_outside(self):
        print("　", end="")

    def next_line(self):
        print()
        print()

