#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void on_btnClicked(bool checked);
private:

    QTreeWidgetItem * createHeadTreeItem(QTreeWidget *w,QString name);

    QWidget *createHorizontialRotate(double number, QWidget *parent = nullptr);
     QWidget *createHorizontialRotate(double from, double to, QWidget *parent = nullptr);
     QWidget *createVerticalRotate(double number , QWidget *parent = nullptr);
     QWidget *createVerticalRotate(double from, double to, QWidget *parent = nullptr);
    Ui::MainWindow *ui;
     QTreeWidget *t ;

    void updateStateByQss(QWidget *w, QVariant var);
};
#endif // MAINWINDOW_H
