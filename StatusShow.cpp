#include "StatusShow.h"

StatusShow::StatusShow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//定时
	m_timer = new QTimer(this);	//指定父对象，系统自动回收
	m_timer->setInterval(50);
	connect(m_timer, &QTimer::timeout, this, &StatusShow::on_timeout);
	m_timer->start();

	//数字锁定
	num = std::make_shared<NUMLOCK>(ui.Nums);
	setLabel(GetKeyState(VK_NUMLOCK), num);
	//大写锁定
	cap = std::make_shared<CAPLOCK>(ui.Caps);
	setLabel(GetKeyState(VK_CAPITAL), cap);
	//滚动锁定
	scr = std::make_shared<SCRLOCK>(ui.Scrs);
	setLabel(GetKeyState(VK_SCROLL), scr);

	//无边框 置顶显示
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::FramelessWindowHint);

	//托盘图标
	m_systemTray = new QSystemTrayIcon(this);
	m_systemTray->setIcon(QIcon("keyboard.png"));
	m_systemTray->setToolTip("Keyboard indicator");
	m_systemTray->show();

	m_menu = new QMenu(this);
	m_action = new QAction(this);
	m_action->setText("Exit");
	m_menu->addAction(m_action);
	connect(m_action, &QAction::triggered, this, &QCoreApplication::exit);
	m_systemTray->setContextMenu(m_menu);
}

void StatusShow::resizeEvent(QResizeEvent* e)
{
	QBitmap bmp(size());
	bmp.fill();
	QPainter p(&bmp);
	p.setRenderHint(QPainter::Antialiasing);
	//p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧 
	//只要上边角圆弧 
	int arcR = 10; //圆弧大小
	QRect rect = this->rect().adjusted(0, 0, 0, 0);
	QPainterPath path;
	//逆时针 
	path.moveTo(arcR, 0);
	//左上角
	path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
	path.lineTo(0, rect.height() - arcR);
	//左下角
	path.arcTo(0, rect.height() - arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
	path.lineTo(rect.width(), rect.height());
	//右下角
	path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2, arcR * 2, arcR * 2, 270.0f, 90.0f);
	path.lineTo(rect.width(), arcR);
	//右上角
	path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
	path.lineTo(arcR, 0);
	p.drawPath(path);
	//此行代码必须添加，不然无法达到正常的显示
	p.fillPath(path, QBrush(Qt::red));
	setMask(bmp);

	return QDialog::resizeEvent(e);
}

void StatusShow::mousePressEvent(QMouseEvent* event)
{
	m_mousePoint = event->pos();    //鼠标相对于窗体的位置
	m_isMousePressed = true;        //鼠标按下
	event->accept();
}

void StatusShow::mouseMoveEvent(QMouseEvent* event)
{
	//若鼠标左键被按下
	if (m_isMousePressed == true)
	{
		//鼠标相对于屏幕的位置
		QPoint curMousePoint = event->globalPos() - m_mousePoint;
		//移动主窗体位置
		move(curMousePoint);
	}
	event->accept();
}

void StatusShow::mouseReleaseEvent(QMouseEvent* event)
{
	//鼠标未按下
	m_isMousePressed = false;
	event->accept();
}

void StatusShow::mouseDoubleClickEvent(QMouseEvent* event)
{
	exit(0);
}

void StatusShow::on_timeout()
{
	setLabel(GetKeyState(VK_NUMLOCK), num);
	setLabel(GetKeyState(VK_CAPITAL), cap);
	setLabel(GetKeyState(VK_SCROLL), scr);
}