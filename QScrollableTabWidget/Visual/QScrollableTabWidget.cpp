#include "QScrollableTabWidget.h"
#include "QScrollableTabWidget_p.h"

QScrollableTabWidget::QScrollableTabWidget(QWidget *parent)
    : QScrollableTabWidget(*new QScrollableTabWidgetPrivate(), parent) {
}

QScrollableTabWidget::~QScrollableTabWidget() {
}

QScrollableTabBar *QScrollableTabWidget::tabBar() const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar;
}

int QScrollableTabWidget::addTab(QWidget *widget, const QString &label) {
    return insertTab(-1, widget, label);
}

int QScrollableTabWidget::addTab(QWidget *widget, const QIcon &icon, const QString &label) {
    return insertTab(-1, widget, icon, label);
}

int QScrollableTabWidget::insertTab(int index, QWidget *widget, const QString &label) {
    return insertTab(index, widget, QIcon(), label);
}

int QScrollableTabWidget::insertTab(int index, QWidget *widget, const QIcon &icon,
                                    const QString &label) {
    Q_D(QScrollableTabWidget);
    if (!widget) {
        return -1;
    }

    index = d->stack->insertWidget(index, widget);
    d->tabBar->insertTab(index, icon, label);
    tabInserted(index);
    return index;
}

void QScrollableTabWidget::removeTab(int index) {
    Q_D(QScrollableTabWidget);
    if (QWidget *w = d->stack->widget(index)) {
        d->stack->removeWidget(w);
    }
}

QString QScrollableTabWidget::tabText(int index) const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar->tabText(index);
}

void QScrollableTabWidget::setTabText(int index, const QString &label) {
    Q_D(QScrollableTabWidget);
    d->tabBar->setTabText(index, label);
}

QIcon QScrollableTabWidget::tabIcon(int index) const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar->tabIcon(index);
}

void QScrollableTabWidget::setTabIcon(int index, const QIcon &icon) {
    Q_D(QScrollableTabWidget);
    d->tabBar->setTabIcon(index, icon);
}

QString QScrollableTabWidget::tabToolTip(int index) const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar->tabToolTip(index);
}

void QScrollableTabWidget::setTabToolTip(int index, const QString &tip) {
    Q_D(QScrollableTabWidget);
    d->tabBar->setTabToolTip(index, tip);
}

int QScrollableTabWidget::currentIndex() const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar->currentIndex();
}

void QScrollableTabWidget::setCurrentIndex(int index) {
    Q_D(QScrollableTabWidget);
    d->tabBar->setCurrentIndex(index);
}

QWidget *QScrollableTabWidget::currentWidget() const {
    Q_D(const QScrollableTabWidget);
    return d->stack->currentWidget();
}

void QScrollableTabWidget::setCurrentWidget(QWidget *widget) {
    Q_D(const QScrollableTabWidget);
    d->tabBar->setCurrentIndex(indexOf(widget));
}

QWidget *QScrollableTabWidget::widget(int index) const {
    Q_D(const QScrollableTabWidget);
    return d->stack->widget(index);
}

int QScrollableTabWidget::indexOf(QWidget *w) const {
    Q_D(const QScrollableTabWidget);
    return d->stack->indexOf(w);
}

int QScrollableTabWidget::count() const {
    Q_D(const QScrollableTabWidget);
    return d->tabBar->count();
}

QSize QScrollableTabWidget::iconSize(int index) const {
    return d_func()->tabBar->iconSize(index);
}

void QScrollableTabWidget::setIconSize(int index, const QSize &size) {
    d_func()->tabBar->setIconSize(index, size);
}

void QScrollableTabWidget::clear() {
    while (count() != 0) {
        removeTab(0);
    }
}

void QScrollableTabWidget::tabInserted(int index) {
    Q_UNUSED(index)
}

void QScrollableTabWidget::tabRemoved(int index) {
    Q_UNUSED(index)
}

void QScrollableTabWidget::setTabBar(QScrollableTabBar *tabBar) {
    Q_D(QScrollableTabWidget);

    if (d->tabBar) {
        d->barLayout->replaceWidget(d->tabBar, tabBar);
        d->tabBar->deleteLater();
    } else {
        d->barLayout->insertWidget(0, tabBar);
    }

    d->tabBar = tabBar;
    tabBar->show();
    setFocusProxy(tabBar);

    connect(d->tabBar, &QScrollableTabBar::currentChanged, this, &QScrollableTabWidget::_q_showTab);
    connect(d->tabBar, &QScrollableTabBar::tabMoved, this, &QScrollableTabWidget::_q_tabMoved);

    // Proxy Signals
    connect(d->tabBar, &QScrollableTabBar::tabBarClicked, this,
            &QScrollableTabWidget::tabBarClicked);
    connect(d->tabBar, &QScrollableTabBar::tabCloseRequested, this,
            &QScrollableTabWidget::tabCloseRequested);
}

QScrollableTabWidget::QScrollableTabWidget(QScrollableTabWidgetPrivate &d, QWidget *parent)
    : QWidget(parent), d_ptr(&d) {
    d.q_ptr = this;
    d.init();
}

void QScrollableTabWidget::_q_showTab(int index) {
    Q_D(QScrollableTabWidget);
    if (index < d->stack->count() && index >= 0) {
        d->stack->setCurrentIndex(index);
        emit currentChanged(index);
    }
}

void QScrollableTabWidget::_q_removeTab(int index) {
    Q_D(QScrollableTabWidget);
    d->tabBar->removeTab(index);
    tabRemoved(index);
}

void QScrollableTabWidget::_q_tabMoved(int from, int to) {
    Q_D(QScrollableTabWidget);
    const QSignalBlocker blocker(d->stack);
    QWidget *w = d->stack->widget(from);
    d->stack->removeWidget(w);
    d->stack->insertWidget(to, w);
}
