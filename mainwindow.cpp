#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nlohmann::json json_change;
    std::string change_path = "../../res/cent-change.json";
    bool status = read_json(change_path, json_change);
    if (!status)
    {
        qDebug() << "change json open error";
    }
    status = json_to_map(json_change);
    if (!status)
    {
        qDebug() << "json to map error";
    }
    int map_size = _money_map.size();
    for (std::map<std::string, double>::iterator iter = _money_map.begin();
         iter != _money_map.end(); ++iter)
    {
        std::string key = iter->first;
        double value = iter->second;
        if (key == "1000sats")
        {
            continue;
        }
        ui->comboBox_in->addItem(QString::fromStdString(key));
        ui->comboBox_out->addItem(QString::fromStdString(key));
    }
    std::string eur_str = "eur";
    ui->comboBox_in->addItem(QString::fromStdString(eur_str));
    ui->comboBox_out->addItem(QString::fromStdString(eur_str));
    compute_rate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::read_json(const std::string &file_path, nlohmann::json &json_file)
{
    std::ifstream file_stream(file_path);
    if (file_stream.is_open())
    {
        file_stream >> json_file;
        file_stream.close();
        return true;
    }
    return false;
}

bool MainWindow::json_to_map(const nlohmann::json &json)
{
    if (json.empty())
    {
        return false;
    }
    std::string eru = "eur";
    _money_map[eru] = 1.0;
    for (const auto &item : json[eru].items())
    {
        const std::string key = item.key();
        double value = item.value().get<double>();
        _money_map[key] = value;
    }

    return true;
}

bool MainWindow::compute_rate()
{
    int change_num = ui->spinBox->value();

    QString input = ui->comboBox_in->currentText();
    std::string input_std = input.toStdString();

    QString output = ui->comboBox_out->currentText();
    std::string output_std = output.toStdString();

    double result = change_num * _money_map[output_std] / _money_map[input_std];
    QString show = QString::number(result);

    ui->lineEdit->setText(show);

    return true;
}

bool MainWindow::download_change_file()
{
    QString url_str = "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/eur.json";
    QUrl url(url_str);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = manager->get(request);

    QMetaObject::Connection connRet = QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(request_finished(QNetworkReply *)));

    Q_ASSERT(connRet);

    return true;
}

void MainWindow::request_finished(QNetworkReply *reply)
{
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (!statusCode.isValid())
    {
        qDebug() << "status code=" << statusCode.toInt();
        return;
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if (!reason.isValid())
    {
        qDebug() << "reason=" << reason.toString();
        return;
    }

    QNetworkReply::NetworkError err = reply->error();
    if (err != QNetworkReply::NoError)
    {
        qDebug() << "Failed: " << reply->errorString();
        return;
    }
    else
    {
        // 获取返回内容
        // qDebug() << reply->readAll();
        QByteArray data = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(data);

        // 保存文件
        QFile file(QApplication::applicationDirPath() + "test.json");
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "file open error";
            return;
        }
        file.write(json_doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    compute_rate();
    return;
}

void MainWindow::on_comboBox_in_activated(int index)
{
    compute_rate();
    return;
}

void MainWindow::on_comboBox_out_activated(int index)
{
    compute_rate();
    return;
}

void MainWindow::on_comboBox_out_currentIndexChanged(int index)
{
    compute_rate();
}

void MainWindow::on_pushButton_clicked()
{
    QString input = ui->comboBox_in->currentText();
    QString output = ui->comboBox_out->currentText();
    ui->comboBox_in->setCurrentText(output);
    ui->comboBox_out->setCurrentText(input);
    compute_rate();
}

void MainWindow::on_pushButton_2_clicked()
{
    download_change_file();
}
