#ifndef BUTTONSTACK_H
#define BUTTONSTACK_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QHBoxLayout>

#include <QQuickWidget>
#include <QQuickItem>

#include <QMap>
#include <QPair>


#include <unordered_map>

#include "stackbutton.h"

class ButtonStack : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonStack(QWidget *parent = nullptr);
    /* Constructor
     *
     * @param background color
     * @param parent widget
     */
    explicit ButtonStack(const QColor&, QWidget *parent = nullptr);
    virtual ~ButtonStack();

    bool addButton(StackButton* btn, QWidget* widget = nullptr);

   /** remove button
    *
    * @param button
    */
    void removeButton(StackButton* btn);

    /** set widget background color */
    void setBackgroundColor(const QColor&);

    /** switch button*/
    void switchButton(StackButton* btn1, StackButton* btn2);

    /** set space between buttonstack and widget
     *
     * @param nSpace
     */
    void setLayoutSpacing(int);

    /** set content margin */
    void setContentsMargins(int);

    /** set content margin
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
