#ifndef TITLEBARWINDOWSIMPLE_H
#define TITLEBARWINDOWSIMPLE_H

#include <QWidget>

namespace Ui {
class TitlebarWindowSimple;
}

class TitlebarWindowSimple : public QWidget
{
    Q_OBJECT

public:
    explicit TitlebarWindowSimple(QWidget *parent = nullptr);
    ~TitlebarWindowSimple();

private:
    Ui::TitlebarWindowSimple *ui;
};

#endif // TITLEBARWINDOWSIMPLE_H
