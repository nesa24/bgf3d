/**
	define the actions of system here.
 */

#ifndef ACTION_TYPES_H
#define ACTION_TYPES_H

#include <string>
using std::string;
//--------------------------------------------------
// Action Base, used to store action in queue.
class ActionBase
{

public:
	virtual ~ActionBase( void );
	
	virtual bool Do( void );
	void SetPhaseName( const char* name );
	string GetPhaseName( void );
protected:
	ActionBase( void );
	string m_strPhaseName;
};

//--------------------------------------------------
// Action UI
class ActionUI : public ActionBase
{
public:
	virtual ~ActionUI( void );

	virtual bool Do( void );
protected:
	ActionUI( void );
};

//--------------------------------------------------
// Action Logic
class ActionLogic : public ActionBase
{
public:
	virtual ~ActionLogic( void );

	virtual bool Do( void );
protected:
	ActionLogic( void );
};

//--------------------------------------------------
// Action change phase, change phase from old to new.
class ActChangePhase : public ActionUI
{
public:
	ActChangePhase( const char* strTargetPhase );
	virtual ~ActChangePhase( void );

	bool Do( void );
	
private:
	ActChangePhase( void );
	string m_strTargetPhase;
};

//--------------------------------------------------
// Action Exit
class ActExit : public ActionUI
{
public:
	ActExit( void );
	virtual ~ActExit( void );

	bool Do( void );

private:
};

//--------------------------------------------------
// Action change attribute
class ActChangeAttr : public ActionUI
{
public:
	ActChangeAttr( void );
	ActChangeAttr( const char* strObjName, const char* strAttrName,
					int iParam1, int iParam2 );
	~ActChangeAttr( void );

	bool Do( void );

private:
	string	m_strObjName;
	string	m_strAttrName;
	int		m_iParam1;
	int		m_iParam2;
};

//--------------------------------------------------
// Action left mouse button click
class ActLClick : public ActionUI
{
public:
	ActLClick( const POINT& posMouse );
	~ActLClick( void );

	bool Do( void );
private:
	ActLClick( void );
	POINT m_posMouse;
};

//--------------------------------------------------
// Action mouse move
class ActMouseMove : public ActionUI
{
public:
	ActMouseMove( const POINT& posMouse );
	~ActMouseMove( void );

	bool Do( void );
private:
	ActMouseMove( void );
	POINT m_posMouse;
};
//--------------------------------------------------
// Action Key down
class ActKeyDown : public ActionUI
{
public:
	ActKeyDown( const WPARAM Key );
	~ActKeyDown( void );

	bool Do( void );
private:
	ActKeyDown( void );
	WPARAM m_wKey;
};
//--------------------------------------------------
// Action Char Input
class ActCharInput : public ActionUI
{
public:
	ActCharInput( const WPARAM Key );
	~ActCharInput( void );

	bool Do( void );
private:
	ActCharInput( void );
	WPARAM m_wKey;
};

#endif
