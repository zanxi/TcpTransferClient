#ifndef EXTENDQTABLEWIDGET_H
#define EXTENDQTABLEWIDGET_H

#include <QTableWidget>

class ExtendQTableWidget : public QTableWidget
{
public:
    ExtendQTableWidget(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *event);

    QAction *add_action;
    QAction *Delete_action;

public slots:
    void show();
    void on_tableWidget_cellEntered2(int row, int column);
};

#endif // EXTENDQTABLEWIDGET_H
