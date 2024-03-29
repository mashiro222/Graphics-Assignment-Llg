#include "minidraw.h"

#include <QToolBar>
#include <QIcon>  

MiniDraw::MiniDraw(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	view_widget_ = new ViewWidget();//实例化viewwidget控件窗口
	Creat_Action();
	Creat_ToolBar();
	Creat_Menu();

	setCentralWidget(view_widget_);// 将 ViewWidget 控件设置为主窗口的中心位置
}

void MiniDraw::Creat_Action() {
	// 创建 QAction 时，为每个 QAction 分别关联图标
	Action_About = new QAction(tr("&About"), this);
	connect(Action_About, &QAction::triggered, this, &MiniDraw::AboutBox);

	//new QAction(QIcon(":MiniDraw/images/haah.bmp", tr("当选中前面那个图标时显示这行文字"), this)

	Action_Line = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Line.bmp"), tr("&Line"), this);
	connect(Action_Line, SIGNAL(triggered()), view_widget_, SLOT(setLine()));

	Action_Rect = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Rectangle.bmp"), tr("&Rectangle"), this);
	connect(Action_Rect, &QAction::triggered, view_widget_, &ViewWidget::setRect);

	Action_Ellip = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Ellipse.bmp"), tr("&Ellipse"), this);
	connect(Action_Ellip, &QAction::triggered, view_widget_, &ViewWidget::setEllip);

	Action_Poly = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Polygon.bmp"), tr("&Polygon"), this);
	connect(Action_Poly, &QAction::triggered, view_widget_, &ViewWidget::setPoly);

	Action_Freehand = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Freehand.bmp"), tr("&Freehand"), this);
	connect(Action_Freehand, &QAction::triggered, view_widget_, &ViewWidget::setFreehand);

	Action_Undo = new QAction(QIcon("D:\\USTC\\ComputerGraphing\\USTC_CG\\Homeworks\\1_MiniDraw\\project\\src\\App\\Image\\Undo.bmp"), tr("&Undo"), this);
	connect(Action_Undo, &QAction::triggered, view_widget_, &ViewWidget::setUndo);
}

void MiniDraw::Creat_ToolBar() {
	pToolBar = addToolBar(tr("&Main"));
	pToolBar->addAction(Action_About);
	pToolBar->addAction(Action_Line);
	pToolBar->addAction(Action_Rect);
	pToolBar->addAction(Action_Ellip);
	pToolBar->addAction(Action_Poly);
	pToolBar->addAction(Action_Freehand);
	pToolBar->addAction(Action_Undo);
}

void MiniDraw::Creat_Menu() {
	pMenu = menuBar()->addMenu(tr("&Figure Tool"));
	pMenu->addAction(Action_About);
	pMenu->addAction(Action_Line);
	pMenu->addAction(Action_Rect);
	pMenu->addAction(Action_Ellip);
	pMenu->addAction(Action_Poly);
	pMenu->addAction(Action_Freehand);
	pMenu->addAction(Action_Undo);
}

void MiniDraw::AboutBox() {
	QMessageBox::about(this, tr("About"), tr("MiniDraw: you can create line, rectangle, ellipse, polygan and freeline as you want"));
}

MiniDraw::~MiniDraw() {}
