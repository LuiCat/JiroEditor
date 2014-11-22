#ifndef JIROEDITER_H
#define JIROEDITER_H

#include <QMainWindow>
#include <QSettings>

class JiroEditer : public QMainWindow
{
    Q_OBJECT

public:

    explicit JiroEditer(QWidget *parent = 0);

signals:

public slots:

protected:

    int windowHeight;
    int windowWidth;

    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *e);

private:

    QSettings *settings;

};

#endif // JIROEDITER_H
