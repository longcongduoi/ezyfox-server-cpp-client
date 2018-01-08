#pragma once

#include <mutex>
#include <vector>
#include <map>
#include "../EzyMacro.h"

EZY_NAMESPACE_START
namespace base {

class EzyRef {
protected:
	int mRetainCount;
	std::mutex mMutex;
public:
	EzyRef();
	virtual ~EzyRef();
	virtual void retain();
	virtual void release();
	virtual void autorelease();
};

}
EZY_NAMESPACE_END
