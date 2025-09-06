# ファイル figure_template.py
from abc import ABC, abstractmethod
from xyrange import XYRange


class FigureTemplate(ABC):
    # 抽象メソッド _inside(x, y)
    # (x, y)が図形の内側ならtrueを，そうでなければfalseを返すものとする．
    # ちょうど境界線上は内側とみなす約束とする．
    @abstractmethod
    def _inside(self, x: float, y: float) -> bool:
        pass

    # 抽象メソッド _get_range()
    # xの動く範囲[x1, x2]と動く間隔xstep
    # yの動く範囲[y1, y2]と動く間隔ystep の6つの数の組を返す．
    @abstractmethod
    def _get_range(self) -> XYRange:
        pass

    # 抽象メソッド _plot_inside()
    # 図形の内側を表す文字を描く．画面上のx座標を１つ右へ動かす．
    @abstractmethod
    def _plot_inside(self) -> None:
        pass

    # 抽象メソッド _plot_outside()
    # 図形の外側を表す文字を描く．画面上のx座標を１つ右へ動かす．
    @abstractmethod
    def _plot_outside(self) -> None:
        pass

    # 抽象メソッド _next_line()
    # 画面上のy座標を１つ下へ動かし，x座標を左端にリセットする．
    @abstractmethod
    def _next_line(self) -> None:
        pass

    # テンプレートメソッド draw()
    # x座標: x1からx2までxstep刻み
    # y座標: y1からy2までystep刻み の各点について，
    # (x, y)が図形の内側かどうかに従って文字を描画する．
    def draw(self) -> None:
        r = self._get_range()
        y = r.y2
        while y >= r.y1:
            x = r.x1
            while x <= r.x2:
                if self._inside(x, y):
                    self._plot_inside()
                else:
                    self._plot_outside()
                x += r.xstep
            self._next_line()
            y -= r.ystep