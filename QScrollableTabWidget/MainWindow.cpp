#include "MainWindow.h"
#include "Visual/QScrollableTabBar.h"

#include <QApplication>
#include <QDebug>
#include <QDropEvent>
#include <QFile>
#include <QMimeData>
#include <QLabel>

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

    tabs->addTab(new QLabel("1"), "tab-1");
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

    connect(tabs, &QScrollableTabWidget::tabCloseRequested, this,
            [&](int index) { tabs->removeTab(index); });

    setAcceptDrops(true);
}

MainWindow::~MainWindow() {
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mime = event->mimeData();
    auto formats = mime->formats();
    for (auto it = formats.begin(); it != formats.end(); ++it) {
        auto format = *it;
        qDebug().noquote() << format << mime->data(format);
    }
}
