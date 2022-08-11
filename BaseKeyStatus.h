#pragma once
#include <QGraphicsDropShadowEffect>
#include <QLabel>
class BaseKeyStatus
{
public:
	BaseKeyStatus() = default;
	BaseKeyStatus(QLabel* label) :_label(label) {}
	virtual ~BaseKeyStatus() = default;

	virtual void setLabel(const bool flag) const;

private:
	QLabel* _label;
};

