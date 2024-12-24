#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlError>
#include <QUrlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xCoordinate(0), yCoordinate(0), zCoordinate(0),
    xTranslation(0), yTranslation(0), zTranslation(0),
    scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f)  // Initialize scale
{
    ui->setupUi(this);

    // Initialisation du QLabel pour afficher les coordonnées
    coordinatesLabel = ui->coordinatesLabel;  // Automatiquement lié par Qt Designer

    // Définir le texte initial du QLabel (coordonnées = (0, 0, 0))
    updateCoordinates(0, 0, 0);

    // Initialisation des positions des sliders (assumer la valeur 0 initialement)
    ui->verticalSlider->setValue(0);         // Rotation X
    ui->verticalSlider_2->setValue(0);       // Rotation Y
    ui->verticalSlider_3->setValue(0);       // Rotation Z
    ui->translationSliderX->setValue(0);     // Translation X
    ui->translationSliderY->setValue(0);     // Translation Y
    ui->translationSliderZ->setValue(0);     // Translation Z
    ui->scaleSliderX->setValue(100);         // Scale X (100% as default)
    ui->scaleSliderY->setValue(100);         // Scale Y
    ui->scaleSliderZ->setValue(100);
    ui->translationSliderX->setRange(0,100);
    ui->translationSliderY->setRange(0,100);
    ui->translationSliderZ->setRange(0,100);    // Scale Z

    // Connexions des signaux et des slots des sliders
    connect(ui->verticalSlider, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_actionTriggered);
    connect(ui->verticalSlider_2, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_2_actionTriggered);
    connect(ui->verticalSlider_3, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_3_actionTriggered);
    connect(ui->translationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderX_actionTriggered);
    connect(ui->translationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderY_actionTriggered);
    connect(ui->translationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderZ_actionTriggered);
    connect(ui->scaleSliderX, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderX_actionTriggered);
    connect(ui->scaleSliderY, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderY_actionTriggered);
    connect(ui->scaleSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderZ_actionTriggered);

    // Connexion du bouton Save
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
    // Connexion du bouton Load
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoordinates(double x, double y, double z)
{
    // Mettre à jour le QLabel avec les coordonnées
    QString coordinatesText = QString("X: %1, Y: %2, Z: %3").arg(x).arg(y).arg(z);
    coordinatesLabel->setText(coordinatesText);  // Mettre à jour les coordonnées affichées
}

void MainWindow::on_verticalSlider_actionTriggered(int action)
{
    // Mise à jour de la rotation X selon la valeur du slider
    ui->widget->rotate_x = ui->verticalSlider->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_verticalSlider_2_actionTriggered(int action)
{
    // Mise à jour de la rotation Y selon la valeur du slider
    ui->widget->rotate_y = ui->verticalSlider_2->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_verticalSlider_3_actionTriggered(int action)
{
    // Mise à jour de la rotation Z selon la valeur du slider
    ui->widget->rotate_z = ui->verticalSlider_3->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_translationSliderX_actionTriggered(int action)
{
    // Mise à jour de la translation X selon la valeur du slider
    xTranslation = ui->translationSliderX->value()/100.0;
    ui->widget->setTranslationX(xTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderY_actionTriggered(int action)
{
    // Mise à jour de la translation Y selon la valeur du slider
    yTranslation = ui->translationSliderY->value()/100.0;
    ui->widget->setTranslationY(yTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la translation Z selon la valeur du slider
    zTranslation = ui->translationSliderZ->value()/100.0;
    ui->widget->setTranslationZ(zTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_scaleSliderX_actionTriggered(int action)
{
    // Mise à jour de l'échelle X selon la valeur du slider
    scaleX = ui->scaleSliderX->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleX(scaleX); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderY_actionTriggered(int action)
{
    // Mise à jour de l'échelle Y selon la valeur du slider
    scaleY = ui->scaleSliderY->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleY(scaleY); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderZ_actionTriggered(int action)
{
    // Mise à jour de l'échelle Z selon la valeur du slider
    scaleZ = ui->scaleSliderZ->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleZ(scaleZ); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

// Fonction pour enregistrer les coordonnées dans la base de données
void MainWindow::on_saveButton_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL corrigée du script PHP
    QUrl url("http://localhost/php/save_coordinates.php"); // Assurez-vous que "localhost" pointe vers votre serveur WAMP

    // Préparer les données à envoyer
    QUrlQuery params;
    params.addQueryItem("x", QString::number(xTranslation));
    params.addQueryItem("y", QString::number(yTranslation));
    params.addQueryItem("z", QString::number(zTranslation));

    // Préparer la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj["success"].toBool()) {
                QMessageBox::information(nullptr, "Succès", jsonObj["message"].toString());
            } else {
                QMessageBox::critical(nullptr, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher l'erreur détaillée
            QMessageBox::critical(nullptr, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater();
    });
}
void MainWindow::on_loadButton_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL du script PHP (assurez-vous que l'URL pointe vers le bon emplacement de votre serveur)
    QUrl url("http://localhost/php/load_coordinates.php"); // Remplacez par l'URL de votre serveur PHP

    // Préparer la requête
    QNetworkRequest request(url);

    // Envoyer la requête GET
    QNetworkReply *reply = manager->get(request);

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            // Vérifier si l'objet contient des données valides
            if (jsonObj.contains("error")) {
                QMessageBox::critical(this, "Erreur", jsonObj["error"].toString());
            } else {
                // Extraire les coordonnées du JSON
                double x = jsonObj["x"].toDouble();
                double y = jsonObj["y"].toDouble();
                double z = jsonObj["z"].toDouble();

                // Mettre à jour les sliders avec les nouvelles coordonnées
                ui->translationSliderX->setValue(x * 100);
                ui->translationSliderY->setValue(y * 100);
                ui->translationSliderZ->setValue(z * 100);

                // Mettre à jour les coordonnées affichées dans le QLabel
                updateCoordinates(x, y, z);
            }
        } else {
            // Afficher l'erreur détaillée
            QMessageBox::critical(this, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater();
    });
}
