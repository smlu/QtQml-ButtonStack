#ifndef BUTTONSTACK_H
#define BUTTONSTACK_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QHBoxLayout>

#include <QQuickWidget>
#include <QQuickItem>
#include <QMap>

#include "stackbutton.h"

class ButtonStackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonStackWidget(QWidget *parent = nullptr);
   /**
    * Constructor
    *
    * @param Background color
    * @param Parent widget
    */
    explicit ButtonStackWidget(const QColor&, QWidget* parent = nullptr);
    virtual ~ButtonStackWidget();

    bool addButton(StackButton* btn, QWidget* widget = nullptr);

   /**
    * Removes button
    *
    * @param Button
    */
    void removeButton(StackButton* btn);

   /**
    * Sets widget background color
    *
    * @param Color
    */
    void setBackgroundColor(const QColor&);

   /**
    * Changes bosition of button btn1 with button btn2 and vice versa
    *
    * @param Button
    * @param Button
    */
    void switchButton(StackButton* btn1, StackButton* btn2);

   /**
    * Sets space between buttonstack and widget
    *
    * @param Space
    */
    void setLayoutSpacing(int);

   /**
    * Sets content margin
    *
    * @param Margin
    */
    void setContentsMargins(int);

   /**
    * Sets content margin
    *
    * @param left
    * @param top
    * @param right
    * @param bottom
    */
    void setContentsMargins(int, int, int, int);

signals:
    void buttonClicked(StackButton* btn);
    void buttonFocusChanged(StackButton* btn);

protected:
    QQuickWidget* m_rootWidget;
    QQuickItem*   m_rootItem;
    QMap<StackButton*, QWidget*> m_mapBtnWdgts;
    virtual void resizeEvent(QResizeEvent*);

private:
    QQuickItem* m_blayout;
    QHBoxLayout* m_wlayout;

private slots:
    void onButtonFocusChanged(StackButton* btn);
};


#endif // BUTTONSTACK_H
