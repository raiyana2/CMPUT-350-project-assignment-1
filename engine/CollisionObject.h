#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <memory>

#include "GraphicsObject.h"
#include "MathUtil.h"

namespace CMPUT350 {

class CollisionObject : public GraphicsObject {
public:
    /** Notifies this object that it overlaps another collision object.
     * The engine calls this on both objects in a colliding pair.
     * @param obj The other object in the pair.
     * @return No value.
     */
    virtual void CollisionEnter(const std::shared_ptr<CollisionObject> &obj) = 0;

    /** Gets the current axis-aligned bounds used for collision checks.
     * @return Reference to this object's bounds; the referenced rectangle must remain valid.
     */
    virtual const Rect &GetBounds() = 0;
};

}  // namespace CMPUT350

#endif
