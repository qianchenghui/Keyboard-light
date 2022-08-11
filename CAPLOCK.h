#pragma once
#include "BaseKeyStatus.h"
class CAPLOCK :public BaseKeyStatus
{
public:	
	CAPLOCK() = default;
	CAPLOCK(QLabel* label) :c_label(label) {}
	~CAPLOCK() = default;

	void setLabel(const bool flag)const override;
private:
	QLabel* c_label;
};

