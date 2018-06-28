#ifndef STACKBUTTON_H
#define STACKBUTTON_H
#include <QObject>
#include <QUrl>
#include <QColor>
#include <QString>
#include <QQuickItem>
#include <QPointer>


class StackButton : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QUrl iconUrl READ iconUrl WRITE setIconUrl NOTIFY iconUrlChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor NOTIFY hoverColorChanged)
    Q_PROPERTY(QColor pressColor READ pressColor WRITE setPressColor NOTIFY pressColorChanged)
    Q_PROPERTY(bool focus READ hasFocus NOTIFY focusChanged)

public:
    explicit StackButton(QObject* parent = nullptr) : QObject(parent) {}
    explicit StackButton(QString text, QObject* parent = nullptr) :
        QObject(parent),
        m_text(qMove(text))
    {}

    virtual ~StackButton()
    {
        destroyItem();
    }
    const QString& text() const
    {
        return m_text;
    }

    const QUrl& iconUrl()
    {
        return m_iconUrl;
    }

    const QColor& backgroundColor() const
    {
        return m_background;
    }

    const QColor& hoverColor() const
    {
        return m_hoverColor;
    }

    const QColor& pressColor() const
    {
        return m_pressColor;
    }


    bool hasFocus() const
    {
        if(m_item) {
            return m_item->hasFocus();
        }
        return false;
    }

    bool isValid()
    {
        return !m_item.isNull();
    }

signals:
    void pressed();
    void released();
    void clicked();
    void focusChanged(bool);
    void textChanged(const QString&);
    void iconUrlChanged(const QUrl&);
    void backgroundColorChanged(const QColor&);
    void hoverColorChanged(const QColor&);
    void pressColorChanged(const QColor&);

public slots:
    StackButton& setText(QString text)
    {
        m_text = qMove(text);
        updateText();
        emit textChanged(m_text);
        return *this;
    }

    StackButton& setIconUrl(QUrl url)
    {
        m_iconUrl = qMove(url);
        updateIconUrl();
        emit iconUrlChanged(m_iconUrl);
        return *this;
    }

    StackButton& setBackgroundColor(QColor color)
    {
        m_background = qMove(color);
        updateBackgroundColor();
        emit backgroundColorChanged(m_background);
        return *this;
    }

    StackButton& setHoverColor(QColor color)
    {
        m_hoverColor = qMove(color);
        updateHoverColor();
        emit hoverColorChanged(m_hoverColor);
        return *this;
    }

    StackButton& setPressColor(QColor color)
    {
        m_pressColor = qMove(color);
        updatePressColor();
        emit pressColorChanged(m_hoverColor);
        return *this;
    }

    void click()
    {
        if(m_item) {
            QMetaObject::invokeMethod(m_item.data(), "click");
        } else {
            emit clicked();
        }
    }

private:
    void destroyItem()
    {
        if(m_item) {
            m_item->deleteLater();
        }
    }

    void setQuickItem(QQuickItem* item)
    {
        destroyItem();
        m_item = item;
        updateItem();

        connect(m_item.data(), SIGNAL(focusChanged(bool)), this, SIGNAL(focusChanged(bool)));
        connect(m_item.data(), SIGNAL(pressed()), this, SIGNAL(pressed()));
        connect(m_item.data(), SIGNAL(released()), this, SIGNAL(released()));
        connect(m_item.data(), SIGNAL(clicked()), this, SIGNAL(clicked()));
    }

private:
    void updateText()
    {
        if(m_item) {
            Q_ASSERT(m_item->setProperty("text", text()));
        }
    }

    void updateIconUrl()
    {
        if(m_item) {
            Q_ASSERT(m_item->setProperty("iconSource", iconUrl()));
        }
    }

    void updateBackgroundColor()
    {
        if(m_item) {
            Q_ASSERT(m_item->setProperty("backgroundColor", backgroundColor()));
        }
    }

    void updateHoverColor()
    {
        if(m_item) {
            Q_ASSERT(m_item->setProperty("hoverColor", hoverColor()));
        }
    }

    void updatePressColor()
    {
        if(m_item) {
            Q_ASSERT(m_item->setProperty("pressColor", pressColor()));
        }
    }

    void updateItem()
    {
        updateText();
        updateIconUrl();
        updateBackgroundColor();
        updateHoverColor();
        updatePressColor();
    }

private:
    QString m_text;
    QUrl m_iconUrl;
    QColor m_background = "#1E1E1E";
    QColor m_pressColor = "#333333";
    QColor m_hoverColor = "#cccccc";

    friend class ButtonStack;
    QPointer<QQuickItem> m_item;
};
#endif // STACKBUTTON_H
