#/usr/bin/python3

import sys
import os

from PySide2.QtWidgets import QApplication, QMainWindow
import pyplotter
import shiboken2

if __name__ == "__main__":
    app = QApplication([])

    # a = QMainWindow()
    # print(shiboken2.isValid(a))
    # a.show()

    pyplotter.init()

    a = pyplotter.mainWindow()
    repr(a)
    a.show()

    pyplotter.fin()

    sys.exit(app.exec_())
