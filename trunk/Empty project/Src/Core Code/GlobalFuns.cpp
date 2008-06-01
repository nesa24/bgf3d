/*-----------------------------------------+      
|   @@@@@@@@@        @@@@@    @@@@@  @@@@@ |      
|   @@@@@@@@@@     @@@@@@@@   @@@@@  @@@@@ |      
|    @@     @@    @@@    @@@   @@    @@@   |      
|    @@     @@   @@@      @@   @@  @@@     |      
|    @@    @@    @@       @@   @@ @@@      |      
|    @@@@@@@    @@        @@   @@@@@@      |      
|   @@@@@@@@@   @@        @@  @@@@@@@@     |      
|   @@     @@@  @@       @@   @@@  @@@     |      
|   @@      @@  @@      @@@   @@    @@@    |      
|   @@      @@  @@@    @@@    @@     @@    |      
| @@@@@@@@@@@    @@@@@@@@   @@@@@@   @@@@  |      
| @@@@@@@@@@      @@@@@     @@@@@@    @@@  |      
+-----------------------------------------*/

#include "stdafx.h"
#include "ObjectFactory.h"
#include "PhaseFactory.h"
#include "GlobalFuns.h"
#include <luabind/lua_include.hpp> 
#include <luabind/luabind.hpp> 
#include <luabind/object.hpp> 

void RegisterToFactory( void )
{
	ObjectFactory &OF = singObjectFactory::instance();
	OF.Register( "Object", Object::CreateObject );
	OF.Register( "Panel", Panel::CreateObject );
	OF.Register( "StaticImage", Image::CreateObject );
	OF.Register( "StaticText", StaticText::CreateObject );
	OF.Register( "EditBox", EditBox::CreateObject );	
	OF.Register( "Button", ObjButton::CreateObject );

	OF.Register( "Line2D", Line2D::CreateObject );
	OF.Register( "Line3D", Line3D::CreateObject );
	OF.Register( "Point2D", Point2D::CreateObject );
	OF.Register( "TriangleStrip2D", TriangleStrip2D::CreateObject );
	OF.Register( "TriangleStrip3D", TriangleStrip3D::CreateObject );


	PhaseFactory &PF = singPhaseFactory::instance();
	PF.Register( "Phase", Phase::CreatePhase );
	PF.Register( "TestPhase", TestPhase::CreatePhase );
}

bool GameInit()
{
    //Rand seed Set
	srand( GetTickCount() );

	//Init LUA

	//Init DirectX stuff
	g_pCanvas = new Canvas;
	g_pAudio = new Audio;

	// create all things from lua
	int ret = lua_dofile( g_L, "Res/Script/loader.lua" );
	g_pCanvas->CreateCanvas();
	g_pCanvas->InitCanvas();

	g_pAudio->CreateAudio();
	g_pAudio->InitAudio();

	//Create Action Queue

	//Init Factories and Managers

	//Create all Phases
	//binded in LUA
	
	//Create basic objects
	//binded in LUA

	//enter the first phase
	singPhaseManager::instance().GetCurrentPhase()->Enter();

	
	return true;
}

//load global value
void LoadGlobal()
{
	using namespace luabind;

	g_Data = lua_open(); 

	luabind::open( g_Data ); 

	lua_dofile( g_Data, "Res/Script/global.lua" ); 

	object gl = globals( g_Data ); 

	g_iWindow_Width = object_cast<int>( gl[ "window_width" ] ); 
	g_iWindow_Height = object_cast<int>( gl[ "window_height" ] );
}


//------------------------------------------------------------
