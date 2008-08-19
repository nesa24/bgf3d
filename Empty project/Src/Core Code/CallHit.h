#ifndef CALL_HIT_H
#define CALL_HIT_H
#include "Object.h"
#include "Phase.h"
#include "Panel.h"

using namespace std;

template< typename T >
class CallHit
{
public:
	CallHit( const POINT& posMouse ) : m_hitedObject( NULL ), m_posMouse( &posMouse )
	{
	};
	~CallHit( void ){};
	void operator()( T* obj )
	{
		if (obj->IsHited( *m_posMouse ))
		{
			if (!m_hitedObject)
				m_hitedObject = obj;
			if (obj->GetLayer() <= m_hitedObject->GetLayer())
				m_hitedObject = obj;
		}
	}

	T* m_hitedObject;
	const POINT* m_posMouse;
};

#endif
