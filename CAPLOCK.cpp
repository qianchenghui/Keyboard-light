#include "CAPLOCK.h"

void CAPLOCK::setLabel(const bool flag) const
{
	std::shared_ptr<BaseKeyStatus> base = std::make_shared<BaseKeyStatus>(c_label);
	base->setLabel(flag);
}
