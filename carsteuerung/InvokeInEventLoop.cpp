#include "InvokeInEventLoop.h"

#include "DoAtScopeExit.h"

#include <QObject>
#include <QEvent>
#include <QCoreApplication>
#include <QThread>

#include <queue>
#include <memory>

#include <boost/thread.hpp>

class FnCallDeferrer : public QObject
{
public:
	typedef std::function<void()> DeferredFn;
	typedef std::queue<DeferredFn>	QueueType;

	explicit FnCallDeferrer(QObject* /*parent*/ = 0)
	{
	}

	/**
	Calls all deferred calls
	*/
	void callDeferredFnCalls()
	{
		QueueType queue;
		//copy because:
		//- events can add new event while being processed.
		//- Ensures reentrancy and protects from endless loops
		//- A deferred fn can delete the CallDeferrer itself (Being used in case of the global callFnDeferred fn)
		std::swap(queue, m_deferredFnCalls);
		while (!queue.empty())
		{
			DeferredFn fn = queue.front();
            assert(fn);
			fn();
			queue.pop();
		}
	}

	void callFnDeferred(const DeferredFn& fn)
	{
        assert(fn);
		m_deferredFnCalls.push(fn);
		QCoreApplication::postEvent(this, new QEvent(QEvent::Type(QEvent::User + 100)));
	}

	size_t	getQueueSize()
	{
		return m_deferredFnCalls.size();
	}

	bool event(QEvent* pEvent) override
	{
		callDeferredFnCalls();
		pEvent->accept();
		return true;
	}

private:
	QueueType m_deferredFnCalls;
};

void callFnDeferredAsync(QObject* pTargetThread, const std::function<void()>& fn)
{
	FnCallDeferrer* pTmpDeferrer = new FnCallDeferrer();
	pTmpDeferrer->moveToThread(pTargetThread->thread());
	pTmpDeferrer->callFnDeferred([=]
	{
		DoAtScopeExit atExit([&]{ delete pTmpDeferrer; });
		fn();
	});
}

struct AsyncCallData
{
	boost::mutex mutex;
	boost::condition_variable condition;

	enum class State
	{
		Idle,
		Running,
		Finished
	};

	State state = State::Idle;
	bool requestAbort = false;
};

void callFnDeferredSync(QObject* pTargetThread, const std::function<void()>& fn)
{
	if (pTargetThread->thread() == QThread::currentThread())
	{
		fn();
	}
	else
	{
		auto ptrAsyncCallData = std::make_shared<AsyncCallData>();
		callFnDeferredAsync(pTargetThread, [=]
		{
			DoAtScopeExit atExit([&]
			{
				boost::mutex::scoped_lock lock(ptrAsyncCallData->mutex);
				ptrAsyncCallData->state = AsyncCallData::State::Finished;
				ptrAsyncCallData->condition.notify_all();
			});

			{
				boost::mutex::scoped_lock lock(ptrAsyncCallData->mutex);

				if (ptrAsyncCallData->requestAbort)
					return;

				ptrAsyncCallData->state = AsyncCallData::State::Running;
				ptrAsyncCallData->condition.notify_all();
			}

			fn();
		});

		try
		{
			boost::mutex::scoped_lock lock(ptrAsyncCallData->mutex);
			while (ptrAsyncCallData->state != AsyncCallData::State::Finished)
			{
				ptrAsyncCallData->condition.wait(lock);
			}
		}
		catch (boost::thread_interrupted&)
		{
			boost::mutex::scoped_lock lock(ptrAsyncCallData->mutex);

			ptrAsyncCallData->requestAbort = true;
			ptrAsyncCallData->condition.notify_all();

			while (ptrAsyncCallData->state == AsyncCallData::State::Running)
			{
				ptrAsyncCallData->condition.wait(lock);
			}
			throw;
		}
	}
}
