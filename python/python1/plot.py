# ファイル plot.py
from abc import ABC, abstractmethod
from xyrange import XYRange


class Plot(ABC):
    # 抽象メソッド plot_inside()
    # 図形の内側を表す文字を描く．画面上のx座標を１つ右へ動かす．
    @abstractmethod
    def plot_inside(self) -> None:
        pass

    # 抽象メソッド plot_outside()
    # 図形の外側を表す文字を描く．画面上のx座標を１つ右へ動かす．
    @abstractmethod
    def plot_outside(self) -> None:
        pass

    # 抽象メソッド next_line()
    # 画面上のy座標を１つ下へ動かし，x座標を左端にリセットする．
    @abstractmethod
    def next_line(self) -> None:
        pass