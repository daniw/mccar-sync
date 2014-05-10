#ifndef INVOKEINEVENTLOOP_H
#define INVOKEINEVENTLOOP_H

#include <functional>

class QObject;

void callFnDeferredAsync(QObject* pTargetThread, const std::function<void()>& fn);
void callFnDeferredSync(QObject* pTargetThread, const std::function<void()>& fn);

template <typename Fn>
auto _callFnDeferred(QObject* pTargetThread, Fn fn, /*isVoid = */ std::true_type) -> decltype(fn())
{
	callFnDeferredSync(pTargetThread, fn);
}

template <typename Fn>
auto _callFnDeferred(QObject* pTargetThread, Fn fn, /*isVoid = */ std::false_type) -> decltype(fn())
{
	decltype(fn()) ret;
	callFnDeferredSync(pTargetThread, [&]
	{
		ret = fn();
	});

	return ret;
}

template <typename Fn>
auto callFnDeferred(QObject* pTargetThread, Fn fn) -> decltype(fn())
{
	return _callFnDeferred(pTargetThread, fn, std::is_same<decltype(fn()), void>());
}

#endif // INVOKEINEVENTLOOP_H
