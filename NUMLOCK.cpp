#include "NUMLOCK.h"

void NUMLOCK::setLabel(const bool flag) const
{
	std::shared_ptr<BaseKeyStatus> base = std::make_shared<BaseKeyStatus>(n_label);
	base->setLabel(flag);
}
