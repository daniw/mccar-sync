#ifndef DOATSCOPEEXIT_H
#define DOATSCOPEEXIT_H

#include <functional>

class DoAtScopeExit
{
public:
	explicit DoAtScopeExit(std::function<void()> fn);
	~DoAtScopeExit();

private:
	std::function<void()> m_fn;
};

#endif // DOATSCOPEEXIT_H
