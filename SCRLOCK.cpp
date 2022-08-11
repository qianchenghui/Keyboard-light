#include "SCRLOCK.h"

void SCRLOCK::setLabel(const bool flag) const
{
	std::shared_ptr<BaseKeyStatus> base = std::make_shared<BaseKeyStatus>(s_label);
	base->setLabel(flag);
}