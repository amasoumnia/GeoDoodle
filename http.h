#ifndef HTTP_H
#define HTTP_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QApplication>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include "ui_mainwindow.h"

class Http : public QObject
{
    Q_OBJECT

public:
    Http(QString, std::vector<std::vector<float>>, Ui::MainWindow); // constructor, sends a url to request, keyword that identifies the content, and ui to print content to
    ~Http(); // destructor
    void graphShape();
    QString createRouteURL();
    void displayURL(QString);
private slots:
    void getResponse(QNetworkReply *); // gets and prepares response
private:
    void sendRequest(QString);
    //
    void parseUserLocationResponse(QNetworkReply *); // gets and prepares response
    void parseSearchLocationResponse(QNetworkReply *);
    void parseSnapRoadsResponse(QNetworkReply *);

    Ui::MainWindow ui; // ui will be modified within aync process
    double latitude; // json object saved from response
    double longitude;
    QString typeOfRequest;
    std::vector<std::vector<float>> shape;
    QVector<struct cartesianCoordinate> snappedPoints;
};
#endif // HTTP_H
