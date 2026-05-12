#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include "facade.h"
#include "ui_mainwindow.h"
#include "file_reader.h"
#include "qt_scene_drawer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void chooseCsvFile();
    void loadCsvScene();
    void closeWindow();
    void rotateXForward();
    void rotateXBackward();
    void rotateYForward();
    void rotateYBackward();
    void rotateZForward();
    void rotateZBackward();
    void shiftXForward();
    void shiftXBackward();
    void shiftYForward();
    void shiftYBackward();
    void shiftZForward();
    void shiftZBackward();
    void enlargeScene();
    void shrinkScene();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* graphicsScene;
    std::unique_ptr<Facade> facade;

    void bindControls();
    void repaintScene();
    void eraseScene();
    void acceptLoadedScene(const FacadeOperationResult& result);
    void showInfo(const FacadeOperationResult& result);
    void showCritical(const FacadeOperationResult& result);
    void showWarning(const FacadeOperationResult& result);
};

#endif // MAINWINDOW_H
