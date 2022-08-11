#include "StatusShow.h"

StatusShow::StatusShow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//��ʱ
	m_timer = new QTimer(this);	//ָ��������ϵͳ�Զ�����
	m_timer->setInterval(50);
	connect(m_timer, &QTimer::timeout, this, &StatusShow::on_timeout);
	m_timer->start();

	//��������
	num = std::make_shared<NUMLOCK>(ui.Nums);
	setLabel(GetKeyState(VK_NUMLOCK), num);
	//��д����
	cap = std::make_shared<CAPLOCK>(ui.Caps);
	setLabel(GetKeyState(VK_CAPITAL), cap);
	//��������
	scr = std::make_shared<SCRLOCK>(ui.Scrs);
	setLabel(GetKeyState(VK_SCROLL), scr);

	//�ޱ߿� �ö���ʾ
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::FramelessWindowHint);

	//����ͼ��
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
	//p.drawRoundedRect(bmp.rect(), 20, 20); //�ĸ��Ƕ���Բ�� 
	//ֻҪ�ϱ߽�Բ�� 
	int arcR = 10; //Բ����С
	QRect rect = this->rect().adjusted(0, 0, 0, 0);
	QPainterPath path;
	//��ʱ�� 
	path.moveTo(arcR, 0);
	//���Ͻ�
	path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
	path.lineTo(0, rect.height() - arcR);
	//���½�
	path.arcTo(0, rect.height() - arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
	path.lineTo(rect.width(), rect.height());
	//���½�
	path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2, arcR * 2, arcR * 2, 270.0f, 90.0f);
	path.lineTo(rect.width(), arcR);
	//���Ͻ�
	path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
	path.lineTo(arcR, 0);
	p.drawPath(path);
	//���д��������ӣ���Ȼ�޷��ﵽ��������ʾ
	p.fillPath(path, QBrush(Qt::red));
	setMask(bmp);

	return QDialog::resizeEvent(e);
}

void StatusShow::mousePressEvent(QMouseEvent* event)
{
	m_mousePoint = event->pos();    //�������ڴ����λ��
	m_isMousePressed = true;        //��갴��
	event->accept();
}

void StatusShow::mouseMoveEvent(QMouseEvent* event)
{
	//��������������
	if (m_isMousePressed == true)
	{
		//����������Ļ��λ��
		QPoint curMousePoint = event->globalPos() - m_mousePoint;
		//�ƶ�������λ��
		move(curMousePoint);
	}
	event->accept();
}

void StatusShow::mouseReleaseEvent(QMouseEvent* event)
{
	//���δ����
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