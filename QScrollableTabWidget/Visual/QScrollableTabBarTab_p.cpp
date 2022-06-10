#include "QScrollableTabBarTab_p.h"
#include "QScrollableTabBarTab.h"

QScrollableTabBarTabPrivate::QScrollableTabBarTabPrivate() {
}

QScrollableTabBarTabPrivate::~QScrollableTabBarTabPrivate() {
}

void QScrollableTabBarTabPrivate::init() {
    Q_Q(QScrollableTabBarTab);
    q->setAttribute(Qt::WA_StyledBackground);

    layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    iconButton = new QToolButton();
    iconButton->setAttribute(Qt::WA_TransparentForMouseEvents);
    iconButton->setObjectName("icon-button");

    textLabel = new QLabel();
    textLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    textLabel->setObjectName("text-label");

    closeButton = new QToolButton();
    closeButton->setObjectName("close-button");

    layout->addWidget(iconButton);
    layout->addWidget(textLabel);
    layout->addWidget(closeButton);

    // Empty
    iconButton->hide();
    textLabel->hide();

    q->setLayout(layout);
}