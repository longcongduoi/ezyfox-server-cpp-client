#include "EzyReleasePool.h"

EZY_NAMESPACE_START
namespace gc {
    
EzyReleasePool::EzyReleasePool() {
    
}
    
EzyReleasePool::~EzyReleasePool() {
    this->releaseAll();
}
    
void EzyReleasePool::addObject(base::EzyRef* object) {
    mObjects.push_back(object);
    object->retain();
}
    
void EzyReleasePool::releaseAll(){
    for (int i = 0; i < mObjects.size(); i++) {
        mObjects[i]->release();
    }
    mObjects.clear();
}
    
}
EZY_NAMESPACE_END
