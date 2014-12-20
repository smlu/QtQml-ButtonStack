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

    /* set buttonstack qml */
    rootWidg = new QQuickWidget(QUrl("qrc:/qml/stack.qml"));
    //rootWidg->setResizeMode(QQuickWidget::SizeViewToRootObject);

    // get buttonstack item
    rootItem = rootWidg->rootObject();

    /* connect buttonstack */
    connect(rootItem, SIGNAL(clicked(QString)), SLOT(buttonClicked(QString)));
    connect(rootItem, SIGNAL(focusChanged(QString, QString)), SLOT(buttonFocusChanged(QString, QString)));

    /* set main layout */
    m_layout = new QHBoxLayout();
    m_layout->addWidget(rootWidg,0, Qt::AlignLeft);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setStretch(0,0);
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

    /* if previous button has widget, hide it*/
    if(buttonMap[fromButton].first)
        buttonMap[fromButton].first->hide();

    /* does current selected button has widget assignet to it*/
    if(buttonMap[toButton].first){
        Q_DEBUG <<  "widget width:" << buttonMap[toButton].first->width();

        /* resize our widget to width of buttonstack + width of widget assigned to selected button */
        this->setMinimumWidth(rootWidg->width() + buttonMap[toButton].first->width());

        /* show widget that is assigned to selected button */
        buttonMap[toButton].first->show();
    }

    emit focusChanged(fromButton, toButton);
}

bool ButtonStack::addButton(const QString& name, const QUrl & ImageSource, const QColor & button,  const QColor & onClick, const  QColor & onHover)
{
    Q_DEBUG_FUNINF
    return addButton(name, NULL, ImageSource, button, onClick, onHover);
}

bool ButtonStack::addButton(const QString& name, QWidget* qwidget, const QUrl & ImageSource, const QColor & button,  const QColor & onClick, const  QColor & onHover)
{
    Q_DEBUG_FUNINF

    /* call qml methode to create button */
    QVariant fSucceed;
    QMetaObject::invokeMethod(rootItem,
                              "addButton",
                              Q_RETURN_ARG(QVariant,fSucceed),
                              Q_ARG(QVariant, name),
                              Q_ARG(QVariant, ImageSource),
                              Q_ARG(QVariant, ((button.isValid())  ? button.name() : "")),
                              Q_ARG(QVariant, ((onClick.isValid()) ? onClick.name() : "")),
                              Q_ARG(QVariant, ((onHover.isValid()) ? onHover.name() : "")));

    /* if succeedd add button to buttonMap */
    if (fSucceed.value<bool>()){
        Q_DEBUG<< "Button" << name << "has been successfully created";

        QQuickItem * qButtonItem = rootItem->findChild<QQuickItem *>(name);
        if(qButtonItem){
            if(qwidget){
                qwidget->setMinimumHeight(this->height());
                //qwidget->setMaximumHeight(this->height());
                m_layout->addWidget(qwidget,1);                
                qwidget->hide();
            }
            buttonMap[name] = QPair<QWidget*, QQuickItem*>(qwidget, qButtonItem);
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
        m_layout->removeWidget(buttonMap[button].first);
        delete buttonMap[button].second;
        buttonMap.remove(button);
    }

    /* re-set button size */
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
    setStyleSheet(QString("background-color: %1;").arg(color.name()));
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

void ButtonStack::resizeEvent(QResizeEvent * e)
{
    Q_DEBUG_FUNINF
    e->ignore();
    Q_DEBUG<<e->size();
    rootItem->setHeight(e->size().height());

    if(rootItem->width() > 0){
        rootWidg->setMinimumWidth(rootItem->width());
        rootWidg->resize(rootItem->width(), e->size().height());
    }
    //this->resize(e->size());

    QPair<QWidget*, QQuickItem*>b;
    foreach( b,buttonMap){
        if(b.first) b.first->resize(e->size().width() - rootWidg->width(), e->size().height());
    }

    e->accept();
}

void ButtonStack::setLayoutSpacing(int n)
{
    Q_DEBUG_FUNINF
    m_layout->setSpacing(n);
}
