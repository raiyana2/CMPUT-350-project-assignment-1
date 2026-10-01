#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <memory>
#include <vector>

namespace CMPUT350 {

class GameObject;

class EngineView {
public:
    /** Queues a game object for activation by the engine.
     * @param gameObject Shared ownership of the object to add.
     * @return No value.
     */
    virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) = 0;
};

}  // namespace CMPUT350

#endif
