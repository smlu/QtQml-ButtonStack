#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QString>

#include "buttonstack.h"

class Widget4 : public QWidget
{
    Q_OBJECT
public:
    inline explicit Widget4(QWidget *parent=0) :   QWidget(parent){
        setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
        this->resize(250,250);
        setStyleSheet("background-color: rgb(0,0 ,255);");
        m_btnName  = "Button 4";
    }

    inline const QString getBtnName() const{
        return m_btnName;
    }

public slots:
    inline void focusChangeSet(QString fromBtn, QString toBtn){
        if(toBtn == m_btnName)
            this->show();
        else
            this->hide();
    }

private:
    QString  m_btnName;
};
#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    window.setWindowTitle("Button stack");
    window.resize(480, 480);

    QWidget* w1 = new QWidget;
    w1->setStyleSheet("background-color: rgb(255,180 ,30);");

    QWidget* w2 = new QWidget;
    w2->setStyleSheet("background-color: rgb(255,255 ,0);");

    QWidget* w3 = new QWidget;
    w3->setStyleSheet("background-color: rgb(255,0,255);");

    Widget4* w4 = new Widget4;

    ButtonStack* bs = new ButtonStack;
    bs->addButton("Button 1", w1, QUrl(), QColor(0, 150, 0), QColor(150, 0, 0), QColor(150, 150, 255));
    bs->addButton("Button 2", w2);
    bs->addButton("Button 3", w3);
    bs->addButton(w4->getBtnName());



    bs->setButtonFocus("Button 1");
    QObject::connect(bs, SIGNAL(focusChanged(QString,QString)), w4, SLOT(focusChangeSet(QString,QString)));

    window.setCentralWidget(bs);

 //bs->resize(bs->width(), window.height());
    window.show();
    return a.exec();
}

