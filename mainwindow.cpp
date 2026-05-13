#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), graphicsScene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(graphicsScene);

    auto reader = std::make_unique<FileReader>();
    auto drawer = std::make_unique<QtSceneDrawer>(graphicsScene);
    facade = std::make_unique<Facade>(std::move(reader), std::move(drawer));

    bindControls();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bindControls() {
    connect(ui->filePushButton, &QPushButton::clicked, this, &MainWindow::chooseCsvFile);
    connect(ui->uploadPushButton, &QPushButton::clicked, this, &MainWindow::loadCsvScene);

    connect(ui->rotateXPlusButton, &QPushButton::clicked, this, &MainWindow::rotateXForward);
    connect(ui->rotateXMinusButton, &QPushButton::clicked, this, &MainWindow::rotateXBackward);
    connect(ui->rotateYPlusButton, &QPushButton::clicked, this, &MainWindow::rotateYForward);
    connect(ui->rotateYMinusButton, &QPushButton::clicked, this, &MainWindow::rotateYBackward);
    connect(ui->rotateZPlusButton, &QPushButton::clicked, this, &MainWindow::rotateZForward);
    connect(ui->rotateZMinusButton, &QPushButton::clicked, this, &MainWindow::rotateZBackward);

    connect(ui->translateXPlusButton, &QPushButton::clicked, this, &MainWindow::shiftXForward);
    connect(ui->translateXMinusButton, &QPushButton::clicked, this, &MainWindow::shiftXBackward);
    connect(ui->translateYPlusButton, &QPushButton::clicked, this, &MainWindow::shiftYForward);
    connect(ui->translateYMinusButton, &QPushButton::clicked, this, &MainWindow::shiftYBackward);
    connect(ui->translateZPlusButton, &QPushButton::clicked, this, &MainWindow::shiftZForward);
    connect(ui->translateZMinusButton, &QPushButton::clicked, this, &MainWindow::shiftZBackward);

    connect(ui->zoomInButton, &QPushButton::clicked, this, &MainWindow::enlargeScene);
    connect(ui->zoomOutButton, &QPushButton::clicked, this, &MainWindow::shrinkScene);
}

void MainWindow::chooseCsvFile() {
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Open CSV File",
                                                    "C:/Users/User/Documents/Qt/OOP/module2/lab4/sample_csv",
                                                    "CSV Files (*.csv)");

    if (filePath.isEmpty())
        return;

    QString fileName = filePath.section('/', -1);
    ui->pathLabel->setText(fileName);
    ui->pathLabel->setToolTip(filePath);
}

void MainWindow::loadCsvScene() {
    NormalizationParameters params{ui->normBSpinBox->value(), ui->normASpinBox->value(), ui->stepSpinBox->value()};
    std::filesystem::path path = ui->pathLabel->toolTip().toStdString();
    auto result = facade->loadScene(path, params);

    if (!result.isSuccess())
        showCritical(result);
    else {
        repaintScene();
        showInfo(result);
    }

}

void MainWindow::repaintScene() {
    graphicsScene->clear();
    facade->drawScene();
}

void MainWindow::rotateXForward() {
    auto result = facade->rotateScene(Constants::UNIT_OF_ROTATION, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::rotateXBackward() {
    auto result = facade->rotateScene(-Constants::UNIT_OF_ROTATION, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::rotateYForward() {
    auto result = facade->rotateScene(Constants::DEFAULT_VALUE, Constants::UNIT_OF_ROTATION, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::rotateYBackward() {
    auto result = facade->rotateScene(Constants::DEFAULT_VALUE, -Constants::UNIT_OF_ROTATION, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::rotateZForward() {
    auto result = facade->rotateScene(Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, Constants::UNIT_OF_ROTATION);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::rotateZBackward() {
    auto result = facade->rotateScene(Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, -Constants::UNIT_OF_ROTATION);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftXForward() {
    auto result = facade->moveScene(Constants::UNIT_OF_TRANSLATE, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftXBackward() {
    auto result = facade->moveScene(-Constants::UNIT_OF_TRANSLATE, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftYForward() {
    auto result = facade->moveScene(Constants::DEFAULT_VALUE, Constants::UNIT_OF_TRANSLATE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftYBackward() {
    auto result = facade->moveScene(Constants::DEFAULT_VALUE, -Constants::UNIT_OF_TRANSLATE, Constants::DEFAULT_VALUE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftZForward() {
    auto result = facade->moveScene(Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, Constants::UNIT_OF_TRANSLATE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shiftZBackward() {
    auto result = facade->moveScene(Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, -Constants::UNIT_OF_TRANSLATE);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::enlargeScene() {
    auto result = facade->scaleScene(Constants::COEFFICIENT_ZOOM_IN,
                                     Constants::COEFFICIENT_ZOOM_IN,
                                     Constants::COEFFICIENT_ZOOM_IN);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::shrinkScene() {
    auto result = facade->scaleScene(Constants::COEFFICIENT_ZOOM_OUT,
                                     Constants::COEFFICIENT_ZOOM_OUT,
                                     Constants::COEFFICIENT_ZOOM_OUT);

    if (result.isSuccess())
        repaintScene();
    else
        showWarning(result);
}

void MainWindow::showInfo(const FacadeOperationResult& result) {
    QMessageBox::information(this, "Успех", result.getMessage().c_str());
}

void MainWindow::showCritical(const FacadeOperationResult& result) {
    QMessageBox::critical(this, "Ошибка", result.getMessage().c_str());
}

void MainWindow::showWarning(const FacadeOperationResult& result) {
    QMessageBox::warning(this, "Ошибка", result.getMessage().c_str());
}
