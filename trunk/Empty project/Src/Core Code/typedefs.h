#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "Singleton.h"
#include "ActionModule.h"
#include "ObjectFactory.h"
#include "PhaseFactory.h"
#include "GeneralFactory.h"
#include "PhaseManager.h"

#include "DrawComponent.h"
#include "Camera.h"
#include "PhysicsModule.h"


/************************************************************************/
/* added general singleton                                                                     */
/************************************************************************/
typedef Singleton< ActionModule >		singActionModule;
typedef Singleton< ObjectFactory >		singObjectFactory;
typedef Singleton< PhaseFactory >		singPhaseFactory;
typedef Singleton< GeneralFactory >		singFactory;
typedef Singleton< PhaseManager >		singPhaseManager;
typedef Singleton< Camera >				singCamera;
typedef Singleton< PhysicsModule >		singPhysicsModule;

/************************************************************************/
/* added drawcomponent singleton                                                                     */
/************************************************************************/
typedef Singleton< DrawBasic >			singDrawBasic;
typedef Singleton< AnimationMoveX >		singAnimationMoveX;
typedef Singleton< AnimationMoveY >		singAnimationMoveY;		
typedef Singleton< AnimationAlpha >		singAnimationAlpha;
typedef Singleton< AnimationCircumrotate > singAnimationCircumrotate;
typedef Singleton< AnimationScale >		singAnimationScale;
typedef Singleton< AnimationFrame >     singAnimationFrame;

#endif
