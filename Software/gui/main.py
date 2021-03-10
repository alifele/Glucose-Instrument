import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from layout import *
import serial
import json
import matplotlib.pyplot as plt


class myApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.DATA = {}

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.dcapture.clicked.connect(self.run_DAQ)

        self.show()

    def run_DAQ(self):
        self.get_info()
        self.get_data()

    def get_info(self):
        self.DATA['name'] = self.ui.name.text()
        self.DATA['phone'] = self.ui.phone.text()
        self.DATA['GlucoseVal'] = self.ui.gvalue.text()

    def reset(self):
        self.ui.name.clear()
        self.ui.phone.clear()
        self.ui.gvalue.clear()

    def get_data(self):
        serialPort = serial.Serial(port = "/dev/ttyUSB0", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
        serialString = ""
        data_channels = ['red\r\n','green\r\n','blue\r\n','orange\r\n','white\r\n','pink\r\n']
        color_list = ["red","blue","k","pink","orange"]                         # Used to hold data coming over UART
        data_list = []
        data_counter = 0

        serialPort.write(b"start")
        while 1:
            if(serialPort.in_waiting > 0):
                serialString = serialPort.readline()
                if serialString.decode('Ascii') == 'AllDone!':
                    break
                data_list.append(serialString.decode('Ascii'))
                print("getting data ... ")
                #print(data_list[-1])



        print("parssing data ... ")

        for elem in data_list:
            if elem in data_channels:
                channel_name = elem
                self.DATA[channel_name] = []
                continue

            self.DATA[channel_name].append(elem)



        #self.DATA['a'] = data_list

        # while data_counter<10:
        #     if(serialPort.in_waiting > 0):
        #         serialString = serialPort.readline()
        #         data_counter += 1
        #         data_list.append(serialString.decode('Ascii'))

        print('data is going to be saved ... ')
        with open('{}.json'.format(self.DATA['name']), 'w') as outfile:
            json.dump(self.DATA, outfile)
        print('data have been saved!')
        print("#########################")
        print("now you can start capturing new values")

        plt.figure()
        color_index = 0
        for color in self.DATA.keys():
            if color in data_channels:
                plt.plot(self.DATA[color], label=color.strip(), color = color_list[color_index])
                color_index +=1

        plt.legend()
        plt.show()

        self.reset()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = myApp()
    window.show()
    sys.exit(app.exec_())
