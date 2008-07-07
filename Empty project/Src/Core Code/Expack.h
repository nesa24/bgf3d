#pragma once

#include <windows.h>
#include <string>

using std::string;

class Expack
{
public:
	Expack(void);
	virtual ~Expack(void);

	//virtual funs
	virtual string GetPackName()
	{
		return "Expack";
	};


	//Base only funs
	void AddPack(Expack* pPack);
	Expack* FindPack( string strPackName );
private:
	Expack* m_pNextPack;
};

class BasePack : 
	public Expack
{
public:
	BasePack(void);
	virtual ~BasePack(void);

	//pack create method
	static void* CreatePack(void)
	{
		return (void*)new BasePack;
	};

	string GetPackName()
	{
		return "BasePack";
	};

private:
};
