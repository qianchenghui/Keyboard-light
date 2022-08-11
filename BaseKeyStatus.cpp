#include "BaseKeyStatus.h"

void BaseKeyStatus::setLabel(const bool flag) const
{
	_label->clear();
	_label->setText("");

	QString min_width = QString("min-width: %1px;").arg(12);              // ��С��ȣ�size
	QString min_height = QString("min-height: %1px;").arg(12);            // ��С�߶ȣ�size
	QString max_width = QString("max-width: %1px;").arg(12);              // ����ȣ�size
	QString max_height = QString("max-height: %1px;").arg(12);            // ���߶ȣ�size
	QString border_radius = QString("border-radius: %1px;").arg(12 / 2);  // �߿���Բ�ǣ��뾶Ϊsize/2
	QString border = QString("border:1px solid rgb(242, 242, 242);");     // �߿�Ϊ1px
	const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border;
	
	if (flag)
	{
		_label->setStyleSheet(SheetStyle + QString("background-color:rgb(101, 147, 71)"));
	}
	else
	{
		_label->setStyleSheet(SheetStyle + QString("background-color:rgb(126, 33, 18)"));
	}
}
