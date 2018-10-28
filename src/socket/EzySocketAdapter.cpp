#include <thread>
#include <chrono>
#include "EzySocketAdapter.h"
#include "../logger/EzyLogger.h"
#include "../entity/EzyValue.h"
#include "../entity/EzyJson.h"
#include "../entity/EzyObject.h"
#include "../gc/EzyAutoReleasePool.h"

EZY_NAMESPACE_START_WITH(socket)

EzySocketAdapter::EzySocketAdapter() {
	mActive = false;
    mHasError = false;
	mSocketPool = 0;
}

EzySocketAdapter::~EzySocketAdapter() {
    mActive = false;
    EZY_SAFE_DELETE(mSocketPool)
}

void EzySocketAdapter::run() {
	this->update();
    gc::EzyAutoReleasePool::getInstance()->removePool();
}

bool EzySocketAdapter::isActive() {
	std::unique_lock<std::mutex> lk(mMutex);
	return mActive;
}

bool EzySocketAdapter::hasError() {
    return mHasError;
}

void EzySocketAdapter::setActive(bool active) {
	std::unique_lock<std::mutex> lk(mMutex);
	mActive = active;
}

void EzySocketAdapter::start() {
	if (!isActive()) {
		setActive(true);
		std::thread newThread(&EzySocketAdapter::run, this);
		newThread.detach();
	}
}

void EzySocketAdapter::stop() {
	setActive(false);
	mSocketPool->clear();
}

void EzySocketAdapter::update() {
}

void EzySocketAdapter::pushMessage(EzySocketData* data) {
	mSocketPool->push(data);
}

EzySocketData* EzySocketAdapter::popMessage() {
	return mSocketPool->pop();
}

void EzySocketAdapter::popMessages(std::vector<EzySocketData*>& buffer) {
    mSocketPool->popAll(buffer);
}

EZY_NAMESPACE_END_WITH
