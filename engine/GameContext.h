#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "DrawContext.h"
#include "EngineView.h"
#include "GameObject.h"

namespace CMPUT350 {

class GameContext {
public:
    /** Engine interface used by game objects to add objects during callbacks. */
    EngineView *mEngineView;

    /** Drawing interface for the current render window. */
    DrawContext *ScreenContext;
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
