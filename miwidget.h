#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QOpenGLFramebufferObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class miWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit miWidget(QWidget *parent = nullptr);

    // Méthodes pour les translations
    void setTranslationX(float value);
    void setTranslationY(float value);
    void setTranslationZ(float value);

    // Méthodes pour l'échelle
    void setScaleX(float value);
    void setScaleY(float value);
    void setScaleZ(float value);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void graficarLineas();  // Dessiner des lignes

public:
    // Variables de rotation
    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

private:
    // Variables de translation
    int translationX = 0;
    int translationY = 0;
    int translationZ = 0;

    // Variables d'échelle
    float scaleX = 1.0;
    float scaleY = 1.0;
    float scaleZ = 1.0;
};

#endif // MIWIDGET_H
