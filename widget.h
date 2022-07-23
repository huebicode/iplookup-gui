#ifndef WIDGET_H
#define WIDGET_H

#include <QShortcut>
#include <QWidget>
#include <QDate>
#include <QDir>

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

    void on_btn_refreshDBs_clicked();

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

    QDate currentDate;
    QString currentMonth;
    QDate lastMonthDate;
    QString lastMonth;

    QString torPublished;
    QVector<QString> torDataVec;

    QVector<QString> fetch_tor_data();
    QByteArray download_tor_json();
    void download_mmdbs();
    void download_asn();
    void download_country();
    QString truncate(QString input, int width, QChar fillchar, bool trunc);
    bool mmdb_check();

    QString fetch_urlhaus(QByteArray host);
    QString fetch_threatfox(QByteArray search);

    QByteArray gUncompress(const QByteArray &data);

    int padASN;
    int padISO;
    int padCOUNTRY;
    int padURLHAUS;
    int padTHREATFOX;
    int padTOR;

    QString programDataPath;
    void createProgramDataDir();
    void copyFiles(QString srcDir, QString dstDir);

};
#endif // WIDGET_H
