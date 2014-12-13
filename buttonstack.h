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

#include <QDebug>

#define Q_DEBUG_SP(x) qDebug(x)<<"BUTTONSATCK_DEBUG:"
#define Q_DEBUG qDebug()<<"BUTTONSATCK_DEBUG:"
#define Q_DEBUG_FUNINF Q_DEBUG << Q_FUNC_INFO;

class ButtonStack : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonStack(QWidget *parent = 0);
    /* Constructor
     *
     * @param background color
     * @param parent widget
     */
    explicit ButtonStack(const QColor&, QWidget *parent = 0);    
    virtual ~ButtonStack();

    /** add new button to the stack
     *
     * @param button name
     * @param button icon source path
     * @paramthe color of button
     * @param the color of button when clicked
     * @param the color of button when hover over
     *
     * @return success
     */
    bool addButton(const QString& , const QUrl & ImageSource= QUrl("") ,const QColor & button= "",  const QColor & onClick= "", const  QColor & onHover= "");

    /** add new button to the stack
     *
     * @param button name
     * @param qwidget to control
     * @param button icon source path
     * @paramthe color of button
     * @param the color of button when clicked
     * @param the color of button when hover over
     *
     * @return success
     */
    bool addButton(const QString& , QWidget*, const QUrl & ImageSource= QUrl("") ,const QColor & button= "",  const QColor & onClick= "", const  QColor & onHover= "");

    /** remove button*/
    void removeButton(const QString &);

    /** set focus on button*/  
    void setButtonFocus(const QString &);

    /** set widget background color */
    void setBackgroundColor(const QColor&);

    /** switch button*/
    void switchButton(const QString &, const QString &);

    /* set space between buttonstack and widget */
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

protected:
    QQuickWidget * rootWidg;
    QQuickItem *   rootItem;
    QMap<QString, QPair<QWidget*, QQuickItem*> > buttonMap;

private:
    void Init();  
    QHBoxLayout * m_layout;

signals:
    void clicked(const QString&);
    void focusChanged(const QString&, const QString&);

private slots:
    void buttonClicked(QString);
    void buttonFocusChanged(QString, QString);
    void stackWidthChanged();
};

#endif // BUTTONSTACK_H
