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

    /** add new button to the stack
     *
     * @param button name
     * @param button icon source path
     * @param the color of button
     * @param the color of button when clicked
     * @param the color of button when hover over
     *
     * @return success
     */
    bool addButton(const QString& , const QUrl& ImageSource= QUrl("") ,const QColor& button= "",  const QColor& onClick= "", const  QColor& onHover= "");

    /** add new button to the stack
     *
     * @param button name
     * @param qwidget to control
     * @param button icon source path
     * @param the color of button
     * @param the color of button when clicked
     * @param the color of button when hover over
     *
     * @return success
     */
    bool addButton(const QString&, QWidget*, const QUrl& ImageSource= QUrl("") ,const QColor& button= "",  const QColor& onClick= "", const QColor& onHover= "");

    /** remove button
     *
     * @param button name
     */
    void removeButton(const QString&);

    /** set focus on button
     *
     * @param button name
     */
    void setButtonFocus(const QString&);

    /** set widget background color */
    void setBackgroundColor(const QColor&);

    /** switch button*/
    void switchButton(const QString&, const QString&);

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

protected:
    QQuickWidget* rootWidg;
    QQuickItem*   rootItem;
    QMap<QString, QPair<QWidget*, QQuickItem*> > buttonMap;
    virtual void resizeEvent(QResizeEvent*);

private:
    void Init();
    QHBoxLayout* m_layout;

signals:
    void clicked(const QString&);
    void focusChanged(const QString&, const QString&);

private slots:
    void buttonClicked(const QString&);
    void buttonFocusChanged(const QString&, const QString&);
};

#endif // BUTTONSTACK_H
