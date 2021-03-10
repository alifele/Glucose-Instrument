# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'layout.ui'
#
# Created by: PyQt5 UI code generator 5.14.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_dialog(object):
    def setupUi(self, dialog):
        dialog.setObjectName("dialog")
        dialog.resize(400, 300)
        self.formLayout = QtWidgets.QFormLayout(dialog)
        self.formLayout.setObjectName("formLayout")
        self.label = QtWidgets.QLabel(dialog)
        self.label.setObjectName("label")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label)
        self.price_label = QtWidgets.QLabel(dialog)
        self.price_label.setObjectName("price_label")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.price_label)
        self.business_class = QtWidgets.QRadioButton(dialog)
        self.business_class.setObjectName("business_class")
        self.formLayout.setWidget(7, QtWidgets.QFormLayout.LabelRole, self.business_class)
        self.high_class = QtWidgets.QRadioButton(dialog)
        self.high_class.setObjectName("high_class")
        self.formLayout.setWidget(8, QtWidgets.QFormLayout.LabelRole, self.high_class)
        self.first_class = QtWidgets.QRadioButton(dialog)
        self.first_class.setObjectName("first_class")
        self.formLayout.setWidget(9, QtWidgets.QFormLayout.LabelRole, self.first_class)
        self.second_class = QtWidgets.QRadioButton(dialog)
        self.second_class.setEnabled(True)
        self.second_class.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.second_class.setObjectName("second_class")
        self.formLayout.setWidget(10, QtWidgets.QFormLayout.LabelRole, self.second_class)
        self.pushButton = QtWidgets.QPushButton(dialog)
        self.pushButton.setObjectName("pushButton")
        self.formLayout.setWidget(9, QtWidgets.QFormLayout.FieldRole, self.pushButton)

        self.retranslateUi(dialog)
        QtCore.QMetaObject.connectSlotsByName(dialog)

    def retranslateUi(self, dialog):
        _translate = QtCore.QCoreApplication.translate
        dialog.setWindowTitle(_translate("dialog", "Dialog"))
        self.label.setText(_translate("dialog", "The price is"))
        self.price_label.setText(_translate("dialog", "price ..."))
        self.business_class.setText(_translate("dialog", "Business Class"))
        self.high_class.setText(_translate("dialog", "High Class"))
        self.first_class.setText(_translate("dialog", "First Class"))
        self.second_class.setText(_translate("dialog", "Second Class"))
        self.pushButton.setText(_translate("dialog", "Calculate The Price"))
