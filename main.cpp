#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "buttonstack.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    window.setWindowTitle("Button stack");
    window.resize(480, 480);

    ButtonStack* bs = new ButtonStack(&window);
    bs->move(0, bs->y());
    bs->addButton("Button 1", QUrl(), QColor(0, 255, 0), QColor(255, 0, 0), QColor(0, 0, 255));
    bs->addButton("Button 2");
    bs->addButton("Button 3");
    bs->addButton("Button 4");

    window.setCentralWidget(bs);
    window.show();
    return a.exec();
}
