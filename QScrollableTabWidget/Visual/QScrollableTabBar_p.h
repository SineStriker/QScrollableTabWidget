#ifndef QSCROLLABLETABBARPRIVATE_H
#define QSCROLLABLETABBARPRIVATE_H

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QHBoxLayout>
#include <QLabel>
#include <QScrollBar>
#include <QSlider>
#include <QTabBar>
#include <QtGlobal>

#include "QScrollableTabBarTab.h"

class QScrollableTabBar;

class QScrollableTabBarPrivate {
    Q_DECLARE_PUBLIC(QScrollableTabBar)
public:
    QScrollableTabBarPrivate();
    ~QScrollableTabBarPrivate();

    void init();

    void layoutScroll();
    void updateScroll();

    void runOpacityTween(bool visible);

    void startDrag();

    QScrollableTabBarTab *tabAtIndex(int index) const;
    void setCurrentTab(QScrollableTabBarTab *tab);

    QScrollableTabBar *q_ptr;

    // Tabs Entity
    QHBoxLayout *entityLayout;
    QWidget *entity;

    // Scroll Bar
    QScrollBar *scrollBar;

    QPropertyAnimation *opacityTween;
    QGraphicsOpacityEffect *opacityEffect;

    // Tab Bar Properties
    QTabBar::SelectionBehavior selectionBehaviorOnRemove;

    // Realtime Status
    QScrollableTabBarTab *current, *previous;
};

#endif // QSCROLLABLETABBARPRIVATE_H
