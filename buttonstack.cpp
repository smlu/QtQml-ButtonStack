#include "buttonstack.h"
#include <QVariant>

ButtonStack::ButtonStack(QWidget *parent) :
    QWidget(parent)
{
    Q_DEBUG_FUNINF
    Init();  
}

ButtonStack::ButtonStack(const QColor & color, QWidget *parent):
    QWidget(parent)
{
    Q_DEBUG_FUNINF
    Init();
    setBackgroundColor(color);
}

void ButtonStack::Init()
{
    Q_DEBUG_FUNINF

    /* set main layout */
    m_layout = new QHBoxLayout();
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setStretch(0,0);

    /* set qml buttonstack*/
    rootWidg = new QQuickWidget(QUrl("qrc:/stack.qml"));
    rootWidg->setResizeMode(QQuickWidget::SizeViewToRootObject);

    // get buttonstack
    rootItem = rootWidg->rootObject();

    /* connect buttonstack */
    connect(rootItem, SIGNAL(widthChanged()), SLOT(stackWidthChanged()));
    connect(rootItem, SIGNAL(implicitWidthChanged()), SLOT(stackWidthChanged()));
    connect(rootItem, SIGNAL(clicked(QString)), SLOT(buttonClicked(QString)));
    connect(rootItem, SIGNAL(focusChanged(QString, QString)), SLOT(buttonFocusChanged(QString, QString)));

    m_layout->addWidget(rootWidg);
    this->setLayout(m_layout);
}

ButtonStack::~ButtonStack()
{
    Q_DEBUG_FUNINF
    delete rootItem;
    delete rootWidg;
    delete m_layout;
}

void ButtonStack::buttonClicked(QString button)
{
    Q_DEBUG_FUNINF
    Q_DEBUG<<"button:" << button << "has been clicked";

    emit clicked(button);
}

void ButtonStack::buttonFocusChanged(QString fromButton, QString toButton)
{
    Q_DEBUG_FUNINF
    Q_DEBUG<<"focus has changed from button:"<< fromButton << "to button:"<<toButton;


    if(buttonMap[fromButton].first)
        buttonMap[fromButton].first->hide();

    if(buttonMap[toButton].first){
        Q_DEBUG <<  buttonMap[toButton].first->width();
        this->resize( rootWidg->width() + buttonMap[toButton].first->width(), this->height());
        buttonMap[toButton].first->show();
    }
    else
        this->resize( rootWidg->width() + 1, this->height());


    emit focusChanged(fromButton, toButton);
}

void ButtonStack::stackWidthChanged()
{
    Q_DEBUG_FUNINF
    qreal w = rootItem->width();
    Q_DEBUG<< w;

    rootWidg->setMinimumWidth(w);
    if (w != 0)
        rootWidg->setMaximumWidth(w+1);

    this->resize(w+1, this->height());
}

bool ButtonStack::addButton(const QString& name, const QUrl & ImageSource, const QColor & button,  const QColor & onClick, const  QColor & onHover)
{
    Q_DEBUG_FUNINF
    return addButton(name, NULL, ImageSource, button, onClick, onHover);
}

bool ButtonStack::addButton(const QString& name, QWidget* qwidget, const QUrl & ImageSource, const QColor & button,  const QColor & onClick, const  QColor & onHover)
{
    Q_DEBUG_FUNINF

    QVariant fSucceed;
    QMetaObject::invokeMethod(rootItem,
                              "addButton",
                              Q_RETURN_ARG(QVariant,fSucceed),
                              Q_ARG(QVariant, name),
                              Q_ARG(QVariant, ImageSource),
                              Q_ARG(QVariant, ((button.isValid())  ? button.name() : "")),
                              Q_ARG(QVariant, ((onClick.isValid()) ? onClick.name() : "")),

                              Q_ARG(QVariant, ((onHover.isValid()) ? onHover.name() : "")));

    if (fSucceed.value<bool>()){
        Q_DEBUG<< "Button" << name << "has been successfully created";
      QQuickWidget * Edg =qobject_cast<QQuickWidget *>( rootItem->findChild<QObject *>(name));

        QQuickItem * qButtonItem = rootItem->findChild<QQuickItem *>(name);
        if(qButtonItem){
            buttonMap[name] = QPair<QWidget*, QQuickItem*>(qwidget, qButtonItem);
            if(qwidget){
                m_layout->addWidget(qwidget);
                qwidget->hide();
            }
            Q_DEBUG << "Button" << name << "has been added to the map";
        }
        else
            qCritical( )<< "Could not find child" << name;
    }
    else
        qCritical()<< "Something went wrong while trying to create button" << name;

    return fSucceed.value<bool>();
}

void ButtonStack::removeButton(const QString & button)
{
    Q_DEBUG_FUNINF

    if(buttonMap.contains(button)){
         delete buttonMap[button].second;
         buttonMap.remove(button);
    }

    /* reset button size */
    rootItem->setProperty("numOfButtons", QVariant(buttonMap.count()));
}

void ButtonStack::setButtonFocus(const QString & button)
{
    Q_DEBUG_FUNINF
    QMetaObject::invokeMethod(buttonMap[button].second, "setFocus");
}

void ButtonStack::setBackgroundColor(const QColor & color)
{
    Q_DEBUG_FUNINF
    rootItem->setProperty("color", QVariant(color.name()));
}

void ButtonStack::switchButton(const QString & button1, const QString & button2)
{
    Q_DEBUG_FUNINF
    QQuickItem* tmp_btn = buttonMap[button1].second;
    buttonMap[button1].second->setPosition(buttonMap[button2].second->position());
    buttonMap[button2].second->setPosition(tmp_btn->position());
}

void ButtonStack::setContentsMargins(int n)
{
    Q_DEBUG_FUNINF
    m_layout->setMargin(n);
}

void ButtonStack::setContentsMargins(int l, int t, int r, int b)
{
    Q_DEBUG_FUNINF
    m_layout->setContentsMargins(l, t, r ,b );
}

void ButtonStack::setLayoutSpacing(int n)
{
    Q_DEBUG_FUNINF
    m_layout->setSpacing(n);
}
