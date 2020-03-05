#ifndef GLDISPLAYWIDGET_H
#define GLDISPLAYWIDGET_H

#include <QGLWidget>
#include <QtWidgets>
#include <QTimer>
#include "mesh.h"

enum test_mode
{
    original_mode = 0,
    connextion_mode = 1,
    cir_mode = 2,
    check_create_mesh = 3,
    check_loc = 4,
    draw_curv = 5
};

class GLDisplayWidget : public QGLWidget
{
public:
    explicit GLDisplayWidget(QWidget *parent = nullptr);

    void initializeGL(); // The scene may be initialized in this function since the mesh is a data member...
    void paintGL(); // Display the scene Gl
    void resizeGL(int width, int height);
    void changeMode(int i);
    inline void loadFile() {_mesh.create_mesh_plot();};
    inline void flip_edge(){_mesh.test_flip();};
    inline void incre_delaunay(){_mesh.test_incre_delaunay();}
    inline void loc_point(){_mesh.test_location_point();}
protected:
    // Mouse Management
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    test_mode _mode;

private:

    QTimer _timer; // To update the scene
    float _X, _Y ,_Z; // Translation
    float _angle; // Rotation

    QPoint _lastPosMouse; // To keep the last position of the mouse

    Mesh _mesh; // The object to be displayed, may be replaced by a scene if there are several objects....
};

#endif // GLDISPLAYWIDGET_H
