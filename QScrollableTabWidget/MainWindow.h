#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Visual/QScrollableTabWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QScrollableTabWidget *tabs;

    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
