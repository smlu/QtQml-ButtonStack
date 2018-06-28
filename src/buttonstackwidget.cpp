#include "buttonstack.h"

#include <QQmlComponent>
#include <QQmlEngine>

#include <QLoggingCategory>
#include <QDebug>
#include <QVariant>

Q_LOGGING_CATEGORY(lcBtnStack, "btn.stack.widget")

ButtonStack::ButtonStack(QWidget* parent) :
    QWidget(parent)
{
    /* set buttonstack qml */
    m_rootWidget = new QQuickWidget(QUrl("qrc:/qml/stack.qml"), this);
    //rootWidg->setResizeMode(QQuickWidget::SizeViewToRootObject);

    // get buttonstack item
    m_rootItem = m_rootWidget->rootObject();
    Q_CHECK_PTR(m_rootItem);

    // Get Button layout
    m_blayout = m_rootItem->findChild<QQuickItem*>("layout");
    Q_CHECK_PTR(m_blayout);

    /* set main layout */
    m_wlayout = new QHBoxLayout(this);
    m_wlayout->addWidget(m_rootWidget,0, Qt::AlignLeft);
    m_wlayout->setSpacing(0);
    m_wlayout->setMargin(0);
    m_wlayout->setStretch(0,0);
    this->setLayout(m_wlayout);
}

ButtonStack::ButtonStack(const QColor& color, QWidget* parent):
    ButtonStack(parent)
{
    setBackgroundColor(color);
}

ButtonStack::~ButtonStack()
{}

void ButtonStack::onButtonFocusChanged(StackButton* btn)
{
    QWidget* widget = m_mapBtnWdgts.value(btn);
    if(widget)
    {
        if(btn->hasFocus()) {
            widget->show();
        }
        else {
            widget->hide();
        }
    }

    emit buttonFocusChanged(btn);
}

bool ButtonStack::addButton(StackButton* btn, QWidget* widget)
{
    // Create Qml Button component
    QQmlComponent comp(m_rootWidget->engine());
    comp.loadUrl(QUrl("qrc:/qml/button.qml"));
    if(!comp.isReady())
    {
        qCCritical(lcBtnStack) << "Qml component not ready!";
        return false;
    }

    auto btnQmlItem = qobject_cast<QQuickItem*>(comp.beginCreate(m_rootWidget->rootContext()));
    if(!btnQmlItem)
    {
        qCCritical(lcBtnStack) << "Could not create button qml component!";
        return false;
    }

    Q_ASSERT(btnQmlItem->setProperty("stackObj", QVariant::fromValue(m_rootItem)));
    btnQmlItem->setParentItem(m_blayout);
    btnQmlItem->setParent(m_rootItem);
    comp.completeCreate();

    /* Add qml component to btn */
    btn->setQuickItem(btnQmlItem);

    /* Add widget to layout */
    if(widget)
    {
        m_wlayout->addWidget(widget);
        widget->hide();
    }

    /* Add btn and widget to map */
    m_mapBtnWdgts[btn] = widget;

    connect(btn, &StackButton::focusChanged, this, [this, btn](bool){
        onButtonFocusChanged(btn);
    });

    connect(btn, &StackButton::clicked, this, [this, btn](){
        emit buttonClicked(btn);
    });

    connect(btn, &StackButton::destroyed, this, [this](QObject* btn){
        removeButton(static_cast<StackButton*>(btn));
    });

    return true;
}

void ButtonStack::removeButton(StackButton* btn)
{
    if(m_mapBtnWdgts.contains(btn))
    {
        auto w = (m_mapBtnWdgts.value(btn));
        w->hide();
        m_wlayout->removeWidget(w);

        m_mapBtnWdgts.remove(btn);
        btn->disconnect(this);
        btn->destroyItem();
    }
}

void ButtonStack::setBackgroundColor(const QColor& color)
{
    setStyleSheet(QString("background-color: %1;").arg(color.name()));
    m_rootItem->setProperty("color", QVariant(color.name()));
}
#include <QAbstractButton>
void ButtonStack::switchButton(StackButton* btn1, StackButton* btn2)
{
    if(!btn1 || !btn2) {
        return;
    }

    if(!btn2->m_item || !btn2->m_item) {
        return;
    }

    auto pos1 = btn1->m_item->position();
    btn1->m_item->setPosition(btn2->m_item->position());
    btn2->m_item->setPosition(pos1);
}

void ButtonStack::setContentsMargins(int n)
{
    m_wlayout->setMargin(n);
}

void ButtonStack::setContentsMargins(int l, int t, int r, int b)
{
    m_wlayout->setContentsMargins(l, t, r ,b );
}

void ButtonStack::resizeEvent(QResizeEvent* e)
{
    e->ignore();
    m_rootItem->setHeight(e->size().height());

    if(m_rootItem->width() > 0)
    {
        auto rootSize = m_rootItem->size().toSize();
        m_rootWidget->setMinimumWidth(rootSize.width());
        m_rootWidget->resize(rootSize.width(), e->size().height());
    }
    //this->resize(e->size());

    for(auto& w : m_mapBtnWdgts)
    {
        if(w)
        {
            auto width = e->size().width() - m_rootWidget->width();
            w->resize(width, e->size().height());
        }
    }

    e->accept();
}

void ButtonStack::setLayoutSpacing(int n)
{
    m_wlayout->setSpacing(n);
}
