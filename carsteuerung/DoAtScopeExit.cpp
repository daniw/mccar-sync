#include "DoAtScopeExit.h"

DoAtScopeExit::DoAtScopeExit(std::function<void()> fn)
	: m_fn(std::move(fn))
{
}

DoAtScopeExit::~DoAtScopeExit()
{
	m_fn();
}
