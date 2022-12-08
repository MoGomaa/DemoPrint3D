#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_MainWindow.h"

#include <vtkNamedColors.h>

#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkCylinderSource.h>
#include <vtkConeSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>


namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT

private:
	Ui::MainWindow* ui;

	vtkSmartPointer<vtkPolyDataAlgorithm>			mSource;
	vtkSmartPointer<vtkPolyDataMapper>				mMapper;
	vtkSmartPointer<vtkActor>						mActor;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow>	mRenderWindow;
	vtkSmartPointer<vtkRenderer>					mRenderer;

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

public slots:
	void onCubeButtonClick();
	void onSphereButtonClick();
	void onCylinderButtonClick();
	void onConeButtonClick();

private:
	void updateSource();
};

#endif // MAINWINDOW_H