#pragma once

#include <QtWidgets/QDialog>
#include <QTimer>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "ui_StatusShow.h"
#include <windows.h>
#include "NUMLOCK.h"
#include "CAPLOCK.h"
#include "SCRLOCK.h"

class StatusShow : public QDialog
{
    Q_OBJECT

public:
    StatusShow(QWidget *parent = Q_NULLPTR);

private:
    Ui::StatusShowClass ui;

private:
	QTimer*						m_timer;
	std::shared_ptr<NUMLOCK>	num;
	std::shared_ptr<CAPLOCK>	cap;
	std::shared_ptr<SCRLOCK>	scr;

	template<typename T>
	void setLabel(const bool flag, const T ptr);

	//��ʾԲ��
	//https://blog.csdn.net/me_you_/article/details/64123919
	void resizeEvent(QResizeEvent* e);

	//����϶�
	//https://blog.csdn.net/liboxiu/article/details/83578570
	QPoint	m_mousePoint;
	bool	m_isMousePressed;

	//ϵͳ����
	QSystemTrayIcon*	m_systemTray;
	QMenu*				m_menu;
	QAction*			m_action;

protected:
	virtual void mousePressEvent(QMouseEvent* event);  //��갴���¼�
	virtual void mouseMoveEvent(QMouseEvent* event);   //�����϶��¼�
	virtual void mouseReleaseEvent(QMouseEvent* event);//����ͷ��¼�
	virtual void mouseDoubleClickEvent(QMouseEvent* event);

private slots:
	void on_timeout();
};

template<typename T>
void StatusShow::setLabel(const bool flag, const T ptr)
{
	if (flag)
	{
		ptr->setLabel(true);
	}
	else
	{
		ptr->setLabel(false);
	}
}
