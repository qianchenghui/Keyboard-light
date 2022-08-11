#pragma once
#include "BaseKeyStatus.h"

class NUMLOCK:public BaseKeyStatus
{
public:
	NUMLOCK() = default;
	NUMLOCK(QLabel* label) :n_label(label) {}
	~NUMLOCK() = default;

	void setLabel(const bool flag) const override;
private:
	QLabel* n_label;
};

