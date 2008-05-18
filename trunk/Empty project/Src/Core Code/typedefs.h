#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "Singleton.h"
#include "ActionModule.h"
#include "ObjectFactory.h"
#include "PhaseFactory.h"
#include "PhaseManager.h"

/************************************************************************/
/* added drawcomponent                                                                     */
/************************************************************************/
#include "DrawComponent.h"


typedef Singleton< ActionModule >		singActionModule;
typedef Singleton< ObjectFactory >		singObjectFactory;
typedef Singleton< PhaseFactory >		singPhaseFactory;
typedef Singleton< PhaseManager >		singPhaseManager;

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
