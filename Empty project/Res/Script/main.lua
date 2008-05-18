-- we have bind follow classes and(or) functions to lua
--[[ 
	+-------------------------------------------------------
	|
	+-- Phase
	|	|
	|	+--	AddPanel
	|	|
	|	+--	GetPanel
	|	|
	|	+-- SetName
	|
	+-- Panel
	|	|
	|	+--	AddObject
	|	|
	|	+-- SetName
	|
	+-- ObjButton
	|	|
	|	+-- SetFun
	|	|
	|	+-- PushStrParam
	|	|
	|	+-- PushIntParam
	|
	+-- OFinstance
	|
	+-- PFinstance
	|
	+-- PMinstance
	|
	+-- ObjectFactory
	|	|
	|	+-- Create
	|
	+--	PhaseFactory
	|	|
	|	+-- Create
	|
	+-- PhaseManager
	|	|
	|	+--	GetPhase
	|	|
	|	+-- AddPhase
	|
	+-- strVector
	|	|
	|	+-- push_back
	|
	+-- intVector
	|	|
	|	+-- push_back
	|
	+-- ActionModule
	|	|
	|	+-- btnExit
	|
	+-------------------------------------------------------
]]
-------------------------------------------------------------
-- functon for init factory and manager. (singleton)
function Init()
	OFins = OFinstance();
	PMins = PMinstance();
	PFins = PFinstance();
end

-------------------------------------------------------------
-- function to create button, and bind all attributes.
function newButton( attr )
	local obj = OFins:Create( 'Button' );
	local button = ParseButton( obj );
	button:SetFun( attr.strFun );
	-- add codes for push string and int param
	local phase = PMins:GetPhase( attr.strPhase );
	local panel = phase:GetPanel( attr.strPanel );
	panel:AddObject( button );
end
-------------------------------------------------------------
-- function to create phase
function newPhase( attr )
	local phase = PFins:Create( 'phEntrance' );
	phase:SetName( attr.strName );
	PMins:AddPhase( phase );
end
-------------------------------------------------------------
-- function to crate panel
function newPanel( attr )
	local phase = PMins:GetPhase( attr.strPhase );
	local obj = OFins:Create( 'Panel' );
	local panel = ParsePanel( obj );
	panel:SetName( attr.strName );
	phase:AddPanel( panel );
end
-------------------------------------------------------------

-- call init
Init();

-- test for system
newPhase
{
	strName = 'phLogin',
};

newPanel
{
	strName = 'panelDefault',
	strPhase = 'phLogin',
};

newButton
{
	strFun = 'btnExit',
	strPhase = 'phLogin',
	strPanel = 'panelDefault',
};
