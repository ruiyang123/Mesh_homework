#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connex_mode,SIGNAL(clicked()),this,SLOT(test_atta_select()));
    connect(ui->cir_mode,SIGNAL(clicked()),this,SLOT(test_cir_select()));
    connect(ui->original_mode,SIGNAL(clicked()),this,SLOT(original_select()));
    connect(ui->check_create_mesh,SIGNAL(clicked()),this,SLOT(create_mesh_select()));
    connect(ui->check_loc,SIGNAL(clicked()),this,SLOT(check_loc_select()));
    connect(ui->draw_curv,SIGNAL(clicked()),this,SLOT(draw_curv_selecct()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::test_cir_select()
{
    ui->widget->changeMode(2);
}

void MainWindow::test_atta_select()
{
    ui->widget->changeMode(1);
}
void MainWindow::original_select()
{
    ui->widget->changeMode(0);
}
void MainWindow::create_mesh_select()
{
    ui->widget->changeMode(3);
}

void MainWindow::check_loc_select()
{
    ui->widget->changeMode(4);
}
void MainWindow::draw_curv_selecct()
{
    ui->widget->changeMode(5);
}

void MainWindow::on_load_button_clicked()
{
    ui->widget->loadFile();
}

void MainWindow::on_flip_edge_clicked()
{
    ui->widget->flip_edge();
}

void MainWindow::on_incre_delaunay_clicked()
{
    ui->widget->incre_delaunay();
}

void MainWindow::on_loc_point_clicked()
{
    ui->widget->loc_point();
}
