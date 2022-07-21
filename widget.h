#ifndef WIDGET_H
#define WIDGET_H

#include <QShortcut>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_about_clicked();
    void on_btn_search_clicked();

    void slot_shortcutCtrlReturn();
    void slot_finished_tordownload();

    void on_btn_refreshTOR_clicked();

private:
    Ui::Widget *ui;
    QSet<QString> inputSet;

    QShortcut *keyCtrlReturn;

    QString mmdbinspect_path;
    QString asndb_path;
    QString countrydb_path;

    QString divider;

    QString colorOrange;
    QString colorRed;
    QString colorGreen;
    QString colorBlue;
    QString colorPurple;

    QString torPublished;
    QVector<QString> torDataVec;

    QVector<QString> fetch_tor_data();
    QByteArray download_tor_json();
    QString truncate(QString input, int width, QChar fillchar, bool trunc);
    bool mmdb_check();

    QString fetch_urlhaus(QByteArray host);
    QString fetch_threatfox(QByteArray search);

    int padASN;
    int padISO;
    int padCOUNTRY;
    int padURLHAUS;
    int padTHREATFOX;
    int padTOR;
};
#endif // WIDGET_H
