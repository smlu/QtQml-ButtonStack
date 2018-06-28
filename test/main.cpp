#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QString>
#include <QLabel>

#include "../src/buttonstackwidget.h"
#include "../src/stackbutton.h"


void AddLabelToWidget(QWidget* w, QString labelText)
{
    QLabel* label = new QLabel(qMove(labelText), w);
    label->setAlignment(Qt::AlignCenter);
    auto font = label->font();
    font.setPointSize(14);
    label->setFont(font);

    QBoxLayout* layout = new QVBoxLayout(w);
    layout->addWidget(label);
}

class Widget4 : public QWidget
{
    Q_OBJECT
public:
    inline explicit Widget4(QWidget* parent = nullptr) :   QWidget(parent)
    {
        setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
        resize(250,250);
        setStyleSheet("background-color: rgb(0,150 ,255);");
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    window.setWindowTitle("Button stack");
    window.resize(480, 480);

    QWidget* w1 = new QWidget;
    AddLabelToWidget(w1, "Widget 1");
    w1->setStyleSheet("background-color: rgb(255,180 ,30);");

    QWidget* w2 = new QWidget;
    AddLabelToWidget(w2, "Widget 2");
    w2->setStyleSheet("background-color: rgb(255,255 ,0);");

    QWidget* w3 = new QWidget;
    AddLabelToWidget(w3, "Widget 3");
    w3->setStyleSheet("background-color: rgb(255,0,255);");

    Widget4* w4 = new Widget4;
    AddLabelToWidget(w4, "Widget 4");


    StackButton btn1;
    btn1.setText("Button1")
        .setIconUrl(QUrl("http://simpleicon.com/wp-content/uploads/smile-128x128.png"))
        .setBackgroundColor(QColor(0, 150, 0))
        .setPressColor(QColor(150, 0, 0))
        .setHoverColor(QColor(150, 150, 255));

    StackButton* btn2 = new StackButton("Button 2");
    StackButton btn3("Button 3");
    StackButton btn4("Button 4");

    // Init button stack
    ButtonStackWidget bs;
    bs.addButton(&btn1, w1);
    bs.addButton(btn2, w2);
    bs.addButton(&btn3, w3);
    bs.addButton(&btn4);

    window.setCentralWidget(&bs);
    window.show();

    btn2->click(); // Set btn2 checked
    QObject::connect(btn2, &StackButton::clicked, [&](){
        //bs.removeButton(&btn2);
        btn2->deleteLater();
    });

    QObject::connect(&btn3, &StackButton::clicked, [&](){
        bs.switchButton(&btn1, &btn3);
    });

    // Show w4 when btn4 focus is True
    QObject::connect(&btn4, &StackButton::focusChanged, w4, &Widget4::setVisible);

    return a.exec();
}

