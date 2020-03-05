#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void test_atta_select();
    void test_cir_select();
    void original_select();
    void create_mesh_select();
    void check_loc_select();
    void draw_curv_selecct();
private slots:
    void on_load_button_clicked();
    void on_flip_edge_clicked();
    void on_incre_delaunay_clicked();
    void on_loc_point_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
