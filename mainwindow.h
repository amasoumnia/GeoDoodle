#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;

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


    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_cartoon1_clicked();
    void on_cartoon2_clicked();
    void on_cartoon3_clicked();
    void on_cartoon4_clicked();
    void on_cartoon5_clicked();

    void on_pushButton_3_clicked();
    void on_restartButton_clicked();
private:
    Ui::MainWindow *ui;
    int radius;
    QString s;
    QString url;

//    vector<double> toronto = {43.684921, -79.477013};
    vector<double> toronto = {43.686988, -79.440325};

    // predefined shapes
    vector<vector<float>> pentagon = {
        {0, 2}, {1, 0}, {3, 0}, {4, 2}, {2, 3}, {0, 2}
    };
    vector<vector<float>> triangle = {
        {1, 1}, {-1, 1}, {0, -1}, {1, 1}
    };
    vector<vector<float>> square = {
        {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}
    };
    vector<vector<float>> hexagon = {
        {1, 4}, {0, 2}, {1, 0}, {4, 0}, {5, 2}, {4, 4}, {1, 4}
    };
    vector<vector<float>> rhombus = {
        {2, 0}, {0, 2}, {-2, 0}, {0, -2}, {2, 0}
    };
#endif // MAINWINDOW_H
