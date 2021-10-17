#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <stddef.h>
#include <sstream>
#include <codecvt>
#include <iostream>
#include <locale>

using namespace std;

class ConvertToCyrillic
{
public:
    wstring resultString;
    ConvertToCyrillic() {}
    bool setInputString(string inputstring)
    {
        //Input string must be UTF-8, check for validity here
        this->inputstring = inputstring;
        return false;
    }

    //Only do conversion upon request to delay CPU time
    wstring getOutputString() {
        return this->convertToCyr(this->inputstring);
    }
private:
    string inputstring;
    wstring convertToCyr(string in) {
        wstring innerString;
        wstring secondString;
        wstringstream sec;
        wstringstream outputString;

        for (char& c : in) {
            //cout << c;  //TODO this is just to display original string, remove
            //int tblval = table[(int)(0x7f & c)];
            int tblval = (int)((unsigned char)c + 0x0400);
            innerString += (wchar_t)tblval;

            wstringstream wss;
            wss << " ";
            secondString += wss.str();

            secondString += c;
            wstringstream wss2;
            wss2 << "=";
            secondString += wss2.str();
            secondString += (wchar_t)tblval;

        }

        innerString += secondString;

        return innerString;
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translateButton_clicked()
{
    string inputString;
    wstring outputString;

    inputString = ui->textboxInput->toPlainText().toStdString();
    if(inputString.length() == 0)
        return;

    ConvertToCyrillic converter;
    converter.setInputString(inputString);
    wstring cyrillicOut = converter.getOutputString();
    ui->textboxOutput->clear();
    ui->textboxOutput->append(QString::fromStdWString(cyrillicOut));
}

