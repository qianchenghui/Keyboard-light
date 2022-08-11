#pragma once
#include "BaseKeyStatus.h"
class SCRLOCK :public BaseKeyStatus
{
public:
	SCRLOCK() = default;
	SCRLOCK(QLabel* label) :s_label(label) {}
	~SCRLOCK() = default;

	void setLabel(const bool flag) const override;

private:
	QLabel* s_label;
};

