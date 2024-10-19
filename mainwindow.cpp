#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet(
        "QWidget {"
        "   background-color: #87CEFA;"
        "}"
        "QPushButton {"
        "   background-color: #Ffffff;"
        "   color: black;"
        "   border: 2px solid #808080;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #808080;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #004085;"
        "}"
        "QLineEdit {"
        "   background-color: #fff;"
        "   color: black;"
        "   font-size: 24px;"
        "   padding: 10px;"
        "   border: 2px solid #87CEFA;"
        "   border-radius: 5px;"
        "}"
        );

    QMap<Qt::Key, QPushButton*> operatorBTNs = {
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Minus, ui->btnMinus},
        {Qt::Key_Asterisk, ui->btnMulti},  // '*' 代表乘号
        {Qt::Key_Slash, ui->btnDivide},        // '/' 代表除号
        {Qt::Key_Equal, ui->btnEqual},        // '=' 代表等号
        {Qt::Key_C, ui->btnClear}              // 'C' 代表清除
    };

    // 连接运算符和功能按钮的点击信号到槽
    foreach(auto btn, operatorBTNs) {
        connect(btn, SIGNAL(clicked()), this, SLOT(operatorBtnClicked()));
    }

    // 如果您希望在按下这些键时也进行捕捉，可以在 keyPressEvent 中添加以下代码


    // ui->btnNum0->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum1->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum2->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum3->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum4->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum5->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum6->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum7->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum8->setFocusPolicy(Qt::NoFocus);
    // ui->btnNum9->setFocusPolicy(Qt::NoFocus);
    // ui->btnPlus->setFocusPolicy(Qt::NoFocus);
    // ui->btnDivide->setFocusPolicy(Qt::NoFocus);
    // ui->btnMinus->setFocusPolicy(Qt::NoFocus);
    // ui->btnMulti->setFocusPolicy(Qt::NoFocus);
    // ui->btnEqual->setFocusPolicy(Qt::NoFocus);
    // ui->btnSign->setFocusPolicy(Qt::NoFocus);
    // ui->btnSqrt->setFocusPolicy(Qt::NoFocus);
    // ui->btnPercentage->setFocusPolicy(Qt::NoFocus);
    // ui->btnSquare->setFocusPolicy(Qt::NoFocus);
    // ui->btnPeriod->setFocusPolicy(Qt::NoFocus);
    // ui->btnClear->setFocusPolicy(Qt::NoFocus);
    // ui->btnClearAll->setFocusPolicy(Qt::NoFocus);

    digitBTNs = {{Qt::Key_0,ui->btnNum0},
        {Qt::Key_1,ui->btnNum1},
        {Qt::Key_2,ui->btnNum2},
        {Qt::Key_3,ui->btnNum3},
        {Qt::Key_4,ui->btnNum4},
        {Qt::Key_5,ui->btnNum5},
        {Qt::Key_6,ui->btnNum6},
        {Qt::Key_7,ui->btnNum7},
        {Qt::Key_8,ui->btnNum8},
        {Qt::Key_9,ui->btnNum9},};

    foreach(auto btn,digitBTNs)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMulti,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));

    connect(ui->btnSign, SIGNAL(clicked()), this, SLOT(on_btnSign_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result =0;
    if(operands.size()==2&&opcodes.size()>0){
        //取操作数
        double operand1 =operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op =opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        }else if(op == "-"){
            result = operand1 - operand2;
        }else if(op == "×"){
            result = operand1 * operand2;
        }else if (op == "÷"){
            result =operand1 / operand2;
        }

        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("calculation is in progress: operands is%1,opcode is%2").
                                   arg(opcodes.size()).arg(opcodes.size()));
    }else
        ui->statusbar->showMessage(QString("operands is %1,opcode is%2").
                                 arg(opcodes.size()).arg(opcodes.size()));
    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    ui->display->setText(digit);
    if(digit=="0"&&operand=="0")
        digit ="";

    if(operand =="0" &&digit !="0")
        operand ="";

    operand +=digit;

    ui->display->setText(operand);


}

void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last operand"+operand);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    qDebug() <<opcode;

    if(operand!=" "){
        operands.push_back(operand);
        operand ="";

        opcodes.push_back(opcode);

        QString result =calculation();

        ui->display->setText(result);
    }

}

void MainWindow::on_btnPeriod_clicked()
{
    if(!operand.contains("."))
        operand+=qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    QString str = ui->display->text();
    str = str.left(str.length()-1);
    ui->display->setText(str);
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::on_btnEqual_clicked()
{
    if (!operand.isEmpty()) {
        operands.push(operand);
        operand.clear();
    }

    QString result = calculation();
    if (!result.isEmpty()) {
        ui->display->setText(result);
        operand = result;
        operands.clear();
        opcodes.clear();
    }
}

void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand !=""){
        double result = operand.toDouble();
        operand = "";

        QString op =qobject_cast<QPushButton*>(sender())->text();

        if(op=="%")
            result /=100.0;
        else if(op == "1/x")
            result =1/result;
        else if(op == "x^2")
            result *=result;
        else if(op =="√")
            result =sqrt(result);

        ui->display->setText(QString::number(result));
    }
}

void MainWindow::on_btnSign_clicked()
{
    if (!operand.isEmpty()) {
        // 将字符串操作数转换为双精度浮点数
        double value = operand.toDouble();
        // 取反操作数（即切换正负号）
        value = -value;
        // 将结果转换回字符串并更新操作数
        operand = QString::number(value);
        // 在显示屏上更新操作数
        ui->display->setText(operand);
    } else {
        // 如果操作数为空，可以考虑清空显示或设置为0等
        ui->display->setText("0");
    }
}

void MainWindow::keyPressEvent(QKeyEvent*event)
{
    QString key = event->text();
    foreach(auto btnKey , digitBTNs.keys())
    {
        if(event->key() ==btnKey)
            digitBTNs[btnKey]->animateClick();


            // 处理数字按键
            if (digitBTNs.contains(event->key())) {
                QPushButton *btn = digitBTNs[event->key()];
                btn->click();  // 模拟按钮点击
            }
            // 处理运算符按键
            else if (operatorBTNs.contains(event->key())) {
                QPushButton *btn = operatorBTNs[event->key()];
                btn->click();  // 模拟按钮点击
            }
            // 处理 Enter 键（计算结果）
            else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
                QPushButton *btn = operatorBTNs[Qt::Key_Equal];
                btn->click();  // 模拟等号按钮点击
            }
            // 处理 Backspace 键（清除最后输入）
            else if (event->key() == Qt::Key_Backspace) {
                QPushButton *btn = operatorBTNs[Qt::Key_C];
                btn->click();  // 模拟清除按钮点击
            }

    }


    // if(event->key()==Qt::Key_0)
    //     ui->btnNum0->animateClick(100);
    // else if(event->key()== Qt::Key_1)
    //             ui->btnNum0->animateClick(100);

}

