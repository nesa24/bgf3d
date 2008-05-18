function NullFunc()
end

-------------------------------------------------------------
-- functon for init factory and manager. (singleton)
function Init()
	OFins = OFinstance();
	PMins = PMinstance();
	PFins = PFinstance();
	pAudio = getAudio();
	pCanvas = getCanvas();
end
-------------------------------------------------------------
-- function to create object, the default function for creating
function newObject( attr )
	local obj = OFins:Create( attr.strType );
	local phase = PMins:GetPhase( attr.strPhase );
	local panel = phase:GetPanel( attr.strPanel );
	local panelLayer = panel:GetLayer();
	if attr.strFocusFunc == nil then
		attr.strFocusFunc = 'NullFunc';
		attr.FocusFunc = NullFunc;
	end
	if attr.strLoseFocusFunc == nil then
		attr.strLoseFocusFunc = 'NullFunc';
		attr.LoseFocusFunc = NullFunc;
	end
	-- begin set
	obj:SetFocusFunc( attr.strFocusFunc );
	obj:SetLoseFocusFunc( attr.strLoseFocusFunc );
	obj:SetLayer( panelLayer + attr.intLayer );
	obj:SetVisible( attr.bVisible );
	local Pos = Point();
	Pos.x = attr.iPosX;
	Pos.y = attr.iPosY;
	local Size = Point();
	Size.x = attr.iSizeX;
	Size.y = attr.iSizeY;
	obj:SetPosLT( Pos );
	obj:SetSize( Size );
	for __, value in pairs( attr.ListPL ) do
		local PL = PicLocation();
		PL.m_iPicID = value.PicID;
		PL.m_iTop = value.Top;
		PL.m_iLeft = value.Left;
		PL.m_iBottom = value.Bottom;
		PL.m_iRight = value.Right;
		obj:AddPicLocation( PL );
	end
	panel:AddObject( obj );
	return obj, attr.FocusFunc, attr.LoseFocusFunc;
end
-------------------------------------------------------------
-- function to create button, and bind all attributes.
function newButton( attr )
	local obj = newObject( attr );
	local button = ParseButton( obj );
	button:SetFun( attr.strFun );
	return attr.Func, attr.FocusFunc, attr.LoseFocusFunc;
end

-------------------------------------------------------------
-- function to create static text
function newStaticText( attr )
	local obj = newObject( attr );
	obj:SetColorRGB( attr.iRed, attr.iGreen, attr.iBlue );
	local text = ParseStaticText( obj );
	text:SetContentStr( attr.strContent );
	text:SetTextID( attr.iTextID );
	text:SetCharLength( attr.iCharLength );
	text:SetName( attr.strName );
	return text;
end

-------------------------------------------------------------
-- function to create edit box
function newEditBox( attr )
	local obj = newObject( attr );
	local edit = ParseEditBox( obj );
	edit:SetMaxLength( attr.iMaxLength );
	edit:InitFinish( attr.iTextID, attr.iCharLength, attr.iRed, attr.iGreen, attr.iBlue );
	edit:SetPassWord( attr.bPassWord );
	return edit;
end
-------------------------------------------------------------
-- function to create phase
function newPhase( attr )
	local phase = PFins:Create( attr.strType );
	phase:SetName( attr.strName );
	PMins:AddPhase( phase );
end
-------------------------------------------------------------
-- function to crate panel
function newPanel( attr )
	local phase = PMins:GetPhase( attr.strPhase );
	local obj = OFins:Create( 'Panel' );
	obj:SetLayer( attr.intLayer * 100 );
	local panel = ParsePanel( obj );
	panel:SetName( attr.strName );
	phase:AddPanel( panel );
	local Pos = Point();
	Pos.x = attr.iPosX;
	Pos.y = attr.iPosY;
	local Size = Point();
	Size.x = attr.iSizeX;
	Size.y = attr.iSizeY;
	obj:SetPosLT( Pos );
	obj:SetSize( Size );
	obj:SetVisible( attr.bVisible );
	xtrace( attr.strName .. ' ' .. tostring( attr.bVisible ) .. '\n' );
end
-------------------------------------------------------------
-- function to get the picture source
function getPicRes( picTable )
	for __, value in pairs( picTable ) do
		pCanvas:AddPicRes( value );
	end
end

-------------------------------------------------------------
-- function to get the picture source
function getFontRes( fontTable )
	for __, value in pairs( fontTable ) do
		pCanvas:AddFont( value.iSize, value.strFont, value.bThick, value.bTrend );
	end
end

-------------------------------------------------------------
-- function to get the text source
function getTextRes( textTable )
	for __, value in pairs( textTable ) do
		pCanvas:AddDisplayText( value.strName, value.strContent );
	end
end
-------------------------------------------------------------
-- function to get the sound source
function getWavRes( wavTable )
	for __, value in pairs( wavTable ) do
		xtrace( 'get...' );
		pAudio:AddSoundRes( value.strName, value.iType );
	end
end

function getMusicRes( muTable )
	for __, value in pairs( muTable ) do
		pAudio:AddMusicRes( value );
	end
end


-- call init
Init();
