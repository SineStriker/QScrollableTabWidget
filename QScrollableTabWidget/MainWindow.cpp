#include "MainWindow.h"
#include "Visual/QScrollableTabBar.h"

#include "Visual/QCommandPalette.h"
#include "Visual/QCommandPaletteItem.h"

#include <QApplication>
#include <QDebug>
#include <QDropEvent>
#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QMimeData>
#include <QStandardPaths>

static void loadStyleSheet() {
    QFile qss(":/themes/default.qss");
    if (!qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QString data = qss.readAll();
    qApp->setStyleSheet(data);

    QFont font("Microsoft YaHei");
    font.setPixelSize(15);
    qApp->setFont(font);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    loadStyleSheet();

    tabs = new QScrollableTabWidget();
    setCentralWidget(tabs);

    auto w1 = new QCommandPaletteItemWidget();
    w1->setLeftTopText("CMake: Configure");
    w1->setLeftBottomText("CMake: Configure");
    w1->setRightTopText("Recently Used");

    auto cp = new QCommandPalette();
    cp->addWidget(w1);

    tabs->addTab(cp, "tab-1");
    tabs->addTab(new QLabel("2"), "tab-2");
    tabs->addTab(new QLabel("3"), "tab-3");
    tabs->addTab(new QLabel("11"), "tab-111111");
    tabs->addTab(new QLabel("22"), "tab-222222");
    tabs->addTab(new QLabel("33"), "tab-33333333");
    tabs->addTab(new QLabel("44"), "tab-4444");
    tabs->addTab(new QLabel("55"), "tab-555555");
    tabs->addTab(new QLabel("66"), "tab-666");
    tabs->addTab(new QLabel("77"), "tab-77777777");
    tabs->addTab(new QLabel("88"), "tab-8888888888");

    resize(1280, 720);

    connect(tabs, &QScrollableTabWidget::tabCloseRequested, this, [&](int index) {
        auto tab = tabs->widget(index);
        tabs->removeTab(index);
        tab->deleteLater();
    });

    setAcceptDrops(true);

    qDebug() << QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (int i = tabs->count() - 1; i >= 0; --i) {
        auto tab = tabs->widget(i);
        tabs->removeTab(i);
        tab->deleteLater();
    }
}
