#include "QScrollableTabBar_p.h"
#include "QScrollableTabBar.h"

#include <QPainter>

QScrollableTabBarPrivate::QScrollableTabBarPrivate() {
}

QScrollableTabBarPrivate::~QScrollableTabBarPrivate() {
}

void QScrollableTabBarPrivate::init() {
    Q_Q(QScrollableTabBar);
    q->setAttribute(Qt::WA_StyledBackground);

    current = nullptr;
    previous = nullptr;

    selectionBehaviorOnRemove = QTabBar::SelectPreviousTab;

    entityLayout = new QHBoxLayout();
    entityLayout->setMargin(0);
    entityLayout->setSpacing(0);

    entity = new QWidget(q);
    entity->setObjectName("entity");
    entity->setLayout(entityLayout);
    entity->installEventFilter(q);

    scrollBar = new QScrollBar(Qt::Horizontal, q);
    scrollBar->setObjectName("scroll-bar");
    scrollBar->setSingleStep(40);

    scrollBar->installEventFilter(q);

    QObject::connect(scrollBar, &QScrollBar::valueChanged, q,
                     &QScrollableTabBar::_q_scrollBarValueChanged);
    QObject::connect(scrollBar, &QScrollBar::rangeChanged, q,
                     &QScrollableTabBar::_q_scrollBarRangeChanged);

    opacityEffect = new QGraphicsOpacityEffect(scrollBar);
    scrollBar->setGraphicsEffect(opacityEffect);

    opacityTween = new QPropertyAnimation(q, "scrollOpacity");
    opacityTween->setEasingCurve(QEasingCurve::OutCubic);

    updateScroll();
}

void QScrollableTabBarPrivate::layoutScroll() {
    Q_Q(QScrollableTabBar);
    scrollBar->setGeometry(0, q->height() - scrollBar->height(), q->width(), scrollBar->height());
}

void QScrollableTabBarPrivate::updateScroll() {
    Q_Q(QScrollableTabBar);

    int dw = entity->width() - q->width();
    if (dw <= 0) {
        scrollBar->hide();

        // Stop animation
        opacityTween->stop();
        opacityEffect->setOpacity(0);
    } else {
        scrollBar->show();
        scrollBar->setRange(0, dw);
    }
}

void QScrollableTabBarPrivate::runOpacityTween(bool visible) {
    opacityTween->stop();

    double endValue = visible ? 1 : 0;
    double duration = visible ? 200 : 1000;

    opacityTween->setStartValue(opacityEffect->opacity());
    opacityTween->setEndValue(endValue);
    opacityTween->setDuration(qAbs(opacityEffect->opacity() - visible) * duration);

    opacityTween->start();
}

QScrollableTabBarTab *QScrollableTabBarPrivate::tabAtIndex(int index) const {
    auto item = entityLayout->itemAt(index);
    if (!item) {
        return nullptr;
    }
    return qobject_cast<QScrollableTabBarTab *>(item->widget());
}

void QScrollableTabBarPrivate::setCurrentTab(QScrollableTabBarTab *tab) {
    Q_Q(QScrollableTabBar);

    if (current) {
        if (current == tab) {
            return;
        }
        current->setSelected(false);
    }
    tab->setSelected(true);
    previous = current;
    current = tab;

    emit q->currentChanged(entityLayout->indexOf(tab));
}
