# ファイル strategytest.py
import sys

from xyrange import XYRange
from shape import Shape
from rects import RectS
from circles import CircleS
from plot import Plot
from plotdot import PlotDot
from plotstar import PlotStar


def error():
    print("使い方: python3 strategytest.py [rectまたはcircle] [dotまたはstar]")
    exit(1)

# x座標: x1からx2までxstep刻み
# y座標: y1からy2までystep刻み の各点について，
# (x, y)が図形の内側かどうかに従って文字を描画する．


def draw(shape: Shape, plot: Plot) -> None:
    r: XYRange = shape.get_range()
    y = r.y2
    while y >= r.y1:
        x = r.x1
        while x <= r.x2:
            if shape.inside(x, y):
                plot.plot_inside()
            else:
                plot.plot_outside()
            x += r.xstep
        plot.next_line()
        y -= r.ystep


args = sys.argv[1:]
if (len(args) != 2):
    error()

shape: Shape
if args[0] == "rect":
    shape = RectS()
elif args[0] == "circle":
    shape = CircleS()
else:
    error()

plot: Plot
if args[1] == "star":
    plot = PlotStar()
elif args[1] == "dot":
    plot = PlotDot()
else:
    error()

draw(shape, plot)