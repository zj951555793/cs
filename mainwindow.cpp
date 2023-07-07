#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QPushButton>
#include <QStyleFactory>
#include <QFile>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t = ui->treeWidget;


    QFile f(":/tree.qss");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QString s = f.readAll();
    this->setStyleSheet(s);
    f.close();

    t->setHeaderHidden(true);
    t->setRootIsDecorated(false);
    t->setColumnCount(3);
   // t->header()->setStretchLastSection(true);
    //t->setStyle(QStyleFactory::create("windows"));
    t->setProperty("expandsOnDoubleClick", false);

  //  t->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
//    t->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    QTreeWidgetItem * h1  = createHeadTreeItem(t,tr("vertical course"));

    QTreeWidgetItem *ch1 = new QTreeWidgetItem(h1,QStringList());
    t->setItemWidget(ch1, 0,createHorizontialRotate(-30,t));
     t->setItemWidget(ch1, 1, createVerticalRotate(-180,180,t));
    h1->addChild(ch1);

 //   QTreeWidgetItem *ch2 = new QTreeWidgetItem(h1,QStringList());
//    t->setItemWidget(ch2, 0,createHorizontialRotate(0,t));
//    t->setItemWidget(ch2, 1, createVerticalRotate(-180,180,t));
//    h1->addChild(ch2);

//    QTreeWidgetItem *ch3 = new QTreeWidgetItem(h1,QStringList());
//    t->setItemWidget(ch3, 0,createHorizontialRotate(0,t));
//    t->setItemWidget(ch3, 1, createVerticalRotate(-180,180,t));
//    h1->addChild(ch3);

  // QTreeWidgetItem * h2 = createHeadTreeItem(t,tr("horizontal course"));
//   QTreeWidgetItem *h2_ch1 = new QTreeWidgetItem(h2,QStringList());
//    t->setItemWidget(h2_ch1, 0,createHorizontialRotate(-45,45,t));
//    t->setItemWidget(h2_ch1, 1,createVerticalRotate(-120,t));

//    QTreeWidgetItem *h2_ch2 = new QTreeWidgetItem(h2,QStringList());
//     t->setItemWidget(h2_ch2, 0,createHorizontialRotate(-45,45,t));
//     t->setItemWidget(h2_ch2, 1,createVerticalRotate(0,t));


//     QTreeWidgetItem *h2_ch3 = new QTreeWidgetItem(h2,QStringList());
//     t->setItemWidget(h2_ch3, 0,createHorizontialRotate(-45,45,t));
//    t->setItemWidget(h2_ch3, 1,createVerticalRotate(120,t));

//   h2->addChild(h2_ch1);
//   h2->addChild(h2_ch2);
//   h2->addChild(h2_ch3);
      t->setColumnWidth(0,140);
      t->setColumnWidth(1,120);
    t->setColumnWidth(2,20);
    t->setFocusPolicy(Qt::NoFocus);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClicked(bool checked)
{
    int line = qobject_cast<QPushButton *>(sender())->property("line").toInt();
    if(checked)
    {
        t->expandItem(t->topLevelItem(line));
    }else{
        t->collapseItem(t->topLevelItem(line));
    }
    t->update();
}

QTreeWidgetItem *MainWindow::createHeadTreeItem(QTreeWidget* widget, QString name)
{

  QTreeWidgetItem *header = new QTreeWidgetItem(widget);

   t->insertTopLevelItem(t->topLevelItemCount(),header);
   QWidget* w = new QWidget(widget);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
   QPushButton *box = new QPushButton(w);
   box->setFixedSize(16,16);
   box->setCheckable(true);
  box->setChecked(false);
  updateStateByQss(box,"0");
   box->update();

   QLabel *lbl = new QLabel(t) ;
   lbl->setText(name);
   QPushButton * ptn = new QPushButton(t);
   ptn->setProperty("line", t->topLevelItemCount()-1);
   ptn->setFixedSize(16,16);
   updateStateByQss(ptn,"1");
   ptn->setCheckable(true);
   ptn->setChecked(false);
   ptn->setAutoRepeat(true);
   layout->addWidget(box) ;
   layout->addWidget(lbl);
    w->setLayout(layout);
   connect(ptn, &QPushButton::clicked, this, &MainWindow::on_btnClicked);
   header->setBackground(0, QColor(40,10,10));
      header->setBackground(1, QColor(40,10,10));
   t->setItemWidget(header,0,w);
   t->setItemWidget(header,2,ptn);
   return header;
}

QWidget *MainWindow::createHorizontialRotate(double number,QWidget *parent)
{
    QWidget *w = new QWidget(parent);
    w->setFixedHeight(24);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    QLabel *lab = new QLabel(parent);
     updateStateByQss(lab, "0");
    QLineEdit *edit = new QLineEdit(parent);
    edit->setText(QString::number(number));

    edit->update();
    layout->addWidget(lab);
    layout->addWidget(edit);
    QLabel *lab2 = new QLabel(parent);
    lab2->setText( QStringLiteral("'"));
    layout->addWidget(lab2);
    layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    w->setLayout(layout);
    return w;
}

QWidget *MainWindow::createHorizontialRotate(double from, double to, QWidget *parent)
{
    QWidget *w = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    QLabel *lab = new QLabel(parent);
    updateStateByQss(lab, "0");
    QLineEdit *edit1 = new QLineEdit(parent);
    edit1->setText(QString::number(from));
    QLabel *degree1 = new QLabel( QStringLiteral("'"),parent);
    QLabel *tilde  = new QLabel( QStringLiteral("~"),parent);
    QLineEdit *edit2 = new QLineEdit(parent);
    edit2->setText(QString::number(from));
    QLabel *degree2 = new QLabel(QStringLiteral("'"),parent);
    layout->addWidget(lab);
    layout->addWidget(edit1);
    layout->addWidget(degree1);
    layout->addStretch();
    layout->addWidget(tilde);
    layout->addWidget(edit2);
    layout->addWidget(degree2);
    layout->addStretch();
    w->setLayout(layout);

    return w;

}

QWidget *MainWindow::createVerticalRotate(double number,QWidget *parent)
{
    QWidget *w = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    QLabel *lab = new QLabel(parent);
    updateStateByQss(lab, "1");
    QLineEdit *edit =new  QLineEdit(parent);
    edit->setText(QString::number(number));
    QLabel *degree = new QLabel(parent);
    degree->setText( u8"`");
    layout->addWidget(lab);
    layout->addWidget(edit);
    layout->addWidget(degree);
    w->setLayout(layout);
    return w;
}



QWidget *MainWindow::createVerticalRotate(double from, double to,QWidget *parent)
{
    QWidget *w = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    QLabel *lab = new QLabel(parent);
    updateStateByQss(lab, "1");
    QLineEdit *edit_from =new  QLineEdit(parent);
    edit_from->setText(QString::number(from));
    QLabel *lab2 = new QLabel(parent);
    lab2->setText( u8"`");
    QLabel *edit_tiled = new QLabel(parent);
    edit_tiled->setText(QStringLiteral("~"));
    QLineEdit *edit_to =new  QLineEdit(parent);
    edit_to->setText(QString::number(to));
    QLabel *lab3 = new QLabel(parent);
    lab3->setText( u8"`");
    layout->addWidget(lab);
    layout->addWidget(edit_from);
    layout->addWidget(lab2);
    layout->addStretch();
    layout->addWidget(edit_tiled);
    layout->addWidget(edit_to);
    layout->addWidget(lab3);
    layout->addStretch();
    w->setLayout(layout);
    return w;
}

void MainWindow::updateStateByQss(QWidget *w, QVariant var)
{
    w->setProperty("state", var);
    w->style()->unpolish(w);
    w->style()->polish(w);
    w->update();
}

