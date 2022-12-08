#include <MainWindow.h>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mSource(nullptr), mMapper(nullptr), mActor(nullptr),
	/*mActor(vtkSmartPointer<vtkActor>::New()),*/
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New())
{
	ui->setupUi(this);

	// Set up the rendering
	mRenderWindow->AddRenderer(mRenderer);
	ui->openGLWidget->setRenderWindow(mRenderWindow);
	
	mRenderer->SetBackground(0.5, 0.5, 0.5);

	// Set the UI connections
	QObject::connect(ui->cubeButton, &QPushButton::clicked, this, &MainWindow::onCubeButtonClick);
	QObject::connect(ui->sphereButton, &QPushButton::clicked, this, &MainWindow::onSphereButtonClick);
	QObject::connect(ui->cylinderButton, &QPushButton::clicked, this, &MainWindow::onCylinderButtonClick);
	QObject::connect(ui->coneButton, &QPushButton::clicked, this, &MainWindow::onConeButtonClick);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::onCubeButtonClick() {
	mRenderer->RemoveActor(mActor);

	mSource = vtkSmartPointer<vtkCubeSource>::New();
	
	updateSource();
}
void MainWindow::onSphereButtonClick() {
	mRenderer->RemoveActor(mActor);

	mSource = vtkSmartPointer<vtkSphereSource>::New();
	static_cast<vtkSphereSource*>(mSource.GetPointer())->SetRadius(5);
	
	updateSource();
}
void MainWindow::onCylinderButtonClick() {
	mRenderer->RemoveActor(mActor);

	mSource = vtkSmartPointer<vtkCylinderSource>::New();
	static_cast<vtkCylinderSource*>(mSource.GetPointer())->SetHeight(10.0);
	static_cast<vtkCylinderSource*>(mSource.GetPointer())->SetRadius(5);
	static_cast<vtkCylinderSource*>(mSource.GetPointer())->SetResolution(10);
	
	updateSource();
}
void MainWindow::onConeButtonClick() {
	mRenderer->RemoveActor(mActor);

	mSource = vtkSmartPointer<vtkConeSource>::New();
	static_cast<vtkConeSource*>(mSource.GetPointer())->SetHeight(3.0);
	static_cast<vtkConeSource*>(mSource.GetPointer())->SetRadius(1.0);
	static_cast<vtkConeSource*>(mSource.GetPointer())->SetResolution(10);
	
	updateSource();
}

void MainWindow::updateSource() {
	mSource->Update();

	mMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mMapper->SetInputData(mSource->GetOutput());

	mActor = vtkSmartPointer<vtkActor>::New();
	mActor->SetMapper(mMapper);

	mRenderer->AddViewProp(mActor);
	mRenderer->ResetCamera();
	mRenderWindow->Render();
}
