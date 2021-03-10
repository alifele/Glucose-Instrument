import sys
from PyQt5.QtWidgets import QDialog, QApplication
from lay import *

class My_app(QDialog):

    def __init__(self):
        super().__init__()
        self.ui = Ui_dialog()
        self.ui.setupUi(self)

        self.ui.business_class.toggled.connect(self.dispFare)
        self.ui.first_class.toggled.connect(self.dispFare)
        self.ui.high_class.toggled.connect(self.dispFare)
        self.ui.second_class.toggled.connect(self.dispFare)
        self.ui.pushButton.clicked.connect(self.show_price)
        self.show()

    def dispFare(self):

        if self.ui.business_class.isChecked() == True:
            self.fare = 150
        if self.ui.first_class.isChecked() == True:
            self.fare = 250
        if self.ui.high_class.isChecked() == True:
            self.fare = 350
        if self.ui.second_class.isChecked() == True:
            self.fare = 450

    def show_price(self):

        self.ui.price_label.setText('Air Fare is : {} '.format(self.fare))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = My_app()
    window.show()
    sys.exit(app.exec_())

