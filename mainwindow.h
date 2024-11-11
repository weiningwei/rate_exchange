#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

#include <QMainWindow>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "nlohmann/json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_in_activated(int index);

    void on_comboBox_out_activated(int index);

    void on_comboBox_out_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    bool read_json(const std::string &file_path, nlohmann::json &json_file);
    bool json_to_map(const nlohmann::json &json);
    bool compute_rate();
    bool download_change_file();

    Ui::MainWindow *ui;
    std::set<std::string> _money_name;
    std::map<std::string, double> _money_map;
};
#endif // MAINWINDOW_H
