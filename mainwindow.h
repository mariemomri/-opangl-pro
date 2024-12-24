#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QSlider>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    double scaleX, scaleY, scaleZ;

public slots:
    void on_saveButton_clicked();  // Slot pour le bouton Save
    void on_loadButton_clicked();  // Nouveau slot pour le bouton Load
    void updateCoordinates(double x, double y, double z); // Slot pour mettre à jour les coordonnées

    // Slots pour sliders
    void on_verticalSlider_actionTriggered(int action);
    void on_verticalSlider_2_actionTriggered(int action);
    void on_verticalSlider_3_actionTriggered(int action);
    void on_translationSliderX_actionTriggered(int action);
    void on_translationSliderY_actionTriggered(int action);
    void on_translationSliderZ_actionTriggered(int action);
    void on_scaleSliderX_actionTriggered(int action);
    void on_scaleSliderY_actionTriggered(int action);
    void on_scaleSliderZ_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    QLabel *coordinatesLabel;

    double xCoordinate, yCoordinate, zCoordinate;
    double xTranslation, yTranslation, zTranslation;
    int initialSliderValue;

    QNetworkAccessManager *networkManager; // Déclaration du gestionnaire réseau
};

#endif // MAINWINDOW_H
