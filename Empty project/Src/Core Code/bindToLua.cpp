#include "StdAfx.h"
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class.hpp>

// A global lua state
lua_State* g_L;

// get canvas
Canvas* getCanvas( void )
{
	return g_pCanvas;
}

// get audio
Audio* getAudio( void )
{
	return g_pAudio;
}

// function go register functions and classes to lua
void bind2lua( void )
{
	using namespace luabind;
	using namespace std;
	// open lua state
	g_L = lua_open();
	luabind::open( g_L );

	lua_baselibopen(g_L);
	lua_iolibopen(g_L);
	lua_strlibopen(g_L);
	lua_mathlibopen(g_L);

	// bind Phase, PhaseManager, PhaseFactory, Panel
	// Object, ObjectFacroty to lua
	module( g_L )
	[
		class_< POINT >( "Point" )
		.def( constructor<>() )
		.def_readwrite( "x", &POINT::x )
		.def_readwrite( "y", &POINT::y ),

		class_<PicLocation>( "PicLocation" )
		.def( constructor<>() )
		.def_readwrite( "m_iPicID", &PicLocation::m_iPicID )
		.def_readwrite( "m_iTop", &PicLocation::m_iTop )
		.def_readwrite( "m_iLeft", &PicLocation::m_iLeft )
		.def_readwrite( "m_iBottom", &PicLocation::m_iBottom )
		.def_readwrite( "m_iRight", &PicLocation::m_iRight ),

		class_< Phase >( "Phase" )
		.def( "AddPanel", &Phase::AddPanel )
		.def( "GetPanel", &Phase::GetPanel )
		.def( "SetName", &Phase::SetName ),

		class_< Object >( "Object" )
		.def( "SetLayer", &Object::SetLayer)
		.def( "SetSize", &Object::SetSize )
		.def( "SetEnable", &Object::SetEnable )
		.def( "SetVisible", &Object::SetVisible )
		.def( "GetVisible", &Object::GetVisible )
		.def( "SetPosCenter", &Object::SetPosCenter )
		.def( "SetPosLT", &Object::SetPosLT )
		.def( "SetPosCompare", &Object::SetPosCompare )
		.def( "AddPicLocation", &Object::AddPicLocation )
		.def( "SetPicIndex", &Object::SetPicIndex )
		.def( "SetDataGroupByIndex", &Object::SetDataGroupByIndex )
		.def( "SetBoolGroupByIndex", &Object::SetBoolGroupByIndex )
		.def( "GetLayer", &Object::GetLayer )
		.def( "SetPicIndex", &Object::SetPicIndex )
		.def( "SetColorRGB", &Object::SetColorRGB )
		.def( "SetFocusFunc", &Object::SetFocusFunc)
		.def( "SetLoseFocusFunc", &Object::SetLoseFocusFunc),

		def( "ParseButton", &Object::Parse< ObjButton > ),
		def( "ParseStaticText", &Object::Parse< StaticText > ),
		def( "ParseEditBox", &Object::Parse< EditBox > ),
		def( "ParsePanel", &Object::Parse< Panel > ),

		class_<Panel, Object>("Panel")
		.def( "AddObject", &Panel::AddObject )
		.def( "SetName", &Panel::SetName ),
		
		class_< ObjUI, Object >( "ObjUI" ),

		class_< ObjButton, ObjUI >( "ObjButton" )
		.def( "SetFun", &ObjButton::SetFun )
		.def( "PushStrParam", &ObjButton::PushStrParam )
		.def( "PushIntParam", &ObjButton::PushIntParam ),

		class_< StaticText, ObjUI >( "StaticText" )
		.def( "SetContentStr", &StaticText::SetContentStr )
		.def( "SetTextID", &StaticText::SetTextID )
		.def( "SetName", &StaticText::SetName )
		.def( "SetLine", &StaticText::SetLine )
		.def( "GetLine", &StaticText::GetLine )
		.def( "SetCharLength", &StaticText::SetCharLength ),
		
		class_< EditBox, ObjUI >( "EditBox" )
		.def( "InitFinish", &EditBox::InitFinish )
		.def( "SetLock", &EditBox::SetLock )
		.def( "SetPassWord", &EditBox::SetPassWord )
		.def( "SetMaxLength", &EditBox::SetMaxLength ),
		
		def( "OFinstance", &singObjectFactory::instance ),
		def( "PFinstance", &singPhaseFactory::instance ),
		def( "PMinstance", &singPhaseManager::instance ),
		def( "getCanvas", &getCanvas ),
		def( "getAudio", &getAudio ),
		
		class_< ObjectFactory >( "ObjectFactory" ),
		class_< PhaseFactory >( "PhaseFactory" ),
		class_< PhaseManager >( "PhaseManager" ),
		class_< ActionModule >( "ActionModule" ),

		class_<Canvas>( "Canvas" )
		.def( "AddPicRes", &Canvas::AddPicRes )
		.def( "AddFont", &Canvas::AddFont ),

		class_<Audio>( "Audio" )
		.def( "AddSoundRes", &Audio::AddSoundRes )
		.def( "PlayMusic", &Audio::PlayMusic )		
		.def( "StopMusic", &Audio::StopMusic )		
		.def( "AddMusicRes", &Audio::AddMusicRes )
		.def( "SetSoundVolume", &Audio::SetSoundVolume)
		.def( "SoundOn", &Audio::SoundOn )
		.def( "SoundOff", &Audio::SoundOff )
		.def( "PlayGameSound", &Audio::PlayGameSound ),

		class_<singObjectFactory, ObjectFactory>( "ObjectFactory" )
		.def( "Create", &singObjectFactory::Create ),

		class_<singPhaseFactory, PhaseFactory>( "PhaseFactory" )
		.def( "Create", &singPhaseFactory::Create ),

		class_<singPhaseManager, PhaseManager >("PhaseManager")
		.def( "GetPhase", &singPhaseManager::GetThePhase )
		.def( "AddPhase", &singPhaseManager::AddPhase )
		.def( "ChangeToPhase", &singPhaseManager::ChangeToPhase),

		class_< vector<string> >( "strVector" )
		.def( "push_back", &vector<string>::push_back ),

		class_< vector<int> >( "intVector" )
		.def( "push_back", &vector<int>::push_back ),

		// bind your own button-action function
		class_< singActionModule, ActionModule >( "ActionModule" ),
		def( "btnExit", &singActionModule::btnExit ),

		def( "xtrace", &Out )
	];
}
