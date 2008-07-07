/** @file	Object.h
	@brief	This is the base class file of all UI and game spirit
	@author jMulrO BOK
	@date July 22, 2006

	This class has a lot of virtual methods that will be implement by child
	classes, and most of the methods implement here is about attribute.
 */

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

#ifndef OBJECT_H_BOK
#define OBJECT_H_BOK

//------------------------------------------------------------
//	Include
//------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <string>
#include <assert.h>
#include "Enumerate.h"
#include "Structure.h"
#include "Expack.h"

using std::string;

/************************************************************************/
/* 动画属性定义                                                                     */
/************************************************************************/
//总数
#define ANIMATION_PROPERTY_NER 16

//x目标
#define ANIMATION_PROPERTY_X_END		0
//x方向上速度
#define ANIMATION_PROPERTY_X_SPEED		1
//y目标
#define ANIMATION_PROPERTY_Y_END		2
//y方向上速度
#define ANIMATION_PROPERTY_Y_SPEED		3
//alpha修改速度
#define ANIMATION_PROPERTY_ALPHA		4
//color_red修改速度
#define ANIMATION_PROPERTY_RED			5
//color_green修改速度
#define ANIMATION_PROPERTY_GREEN		6
//color_blue修改速度
#define ANIMATION_PROPERTY_BLUE			7
//旋转速度
#define ANIMATION_PROPERTY_CIRCUM		8
//缩放速度
#define ANIMATION_PROPERTY_SCALE		9
//针播放时间
#define ANIMATION_PROPERTY_TIME			10
//针动画当前时间
#define ANIMATION_PROPERTY_CURTIME		11
//循环
#define ANIMATION_PROPERTY_FRAME_LOOP	12

/************************************************************************/
/* 动画类型定义                                                                     */
/************************************************************************/
#define ANIMATION_TYPE_NBR		16

//X方向移动动画
#define ANIMATION_TYPE_X_MOVE	0
//y
#define ANIMATION_TYPE_Y_MOVE	1
//颜色及ALPHA动画
#define ANIMATION_TYPE_ALPHA	2
//旋转
#define ANIMATION_TYPE_CIRCUMROTATE	3
//缩放
#define ANIMATION_TYPE_SCALE	4
//针动画
#define ANIMATION_TYPE_FRAME	5

#define COLOR_ARGB(a,r,g,b) ((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))

class Canvas;

//------------------------------------------------------------
//	Namespace
//------------------------------------------------------------
using std::vector;

//------------------------------------------------------------
//	Class definition
//------------------------------------------------------------

/** @brief Definition of class Object
	@warning none till now
	@bug none till now

	This class is the base class of all UI and game spirit. Most of the attributes of UI and 
	game spirit	are stored in this class, and it provide a lot of methods that you can access 
	these data member even modify them. Some of the methods is inline, because it's short and 
	will be	called frequently.
*/
class Object
{
public:
	//------------------------------------------------------------
	//	constructor & destructor
	//------------------------------------------------------------
	/** @brief constructor
	 */
	Object( void );

	/** @brief destructor
	 */
	virtual ~Object( void );

	//------------------------------------------------------------
	//	Methods for attributes
	//------------------------------------------------------------

	/** @brief Get object type
		@warning If you want to use multi-inherit, virtual method must be used.
		@return	the class type.

		this is a virtual method, that you MUST overload it.
	 */
	virtual ObjectType GetObjectType( void ) const
	{
		return ObjectBase;
	}

	/** @brief Get m_bEnable data member
	 */
	inline const bool & GetEnable( void ) const
	{
		return m_bEnable;
	}

	/** @brief Set m_bEnable data member
		@param	bEnable	true for enable and false for not enable
	 */
	void SetEnable( const bool bEnable );

	/** @brief Get m_bVisible data member
	 */
	inline const bool & GetVisible( void ) const
	{
		return m_bVisible;
	}

	/** @brief Set m_bVisible data member
		@param	bVisible	true for visible, else false

		this method is virtual. Because of that, for example, if the object is a panel, and if you want to
		set this panel invisible, it must set all its child object to invisible.
	 */
	virtual void SetVisible( const bool bVisible );

	/** @brief Get object draw layer
	 */
	inline const unsigned int & GetLayer( void ) const
	{
		return m_uiLayer;
	}
	
	/** @brief Set object draw layer
		@param uiLayer	the layer of object drawing
	 */
	void SetLayer( const unsigned int &uiLayer );

	/** @brief Get the zoom parameter of x axis
	 */
	inline const float & GetXScale( void ) const
	{
		return m_fXScale;
	}

	/** @brief Get the zoom parameter of y axis
	 */
	inline const float & GetYScale( void ) const
	{
		return m_fYScale;
	}

	/** @brief Set the zoom parameter of x axis
		@param fXScale	the parameter of zoom for X axis
	 */
	void SetXScale( const float &fXScale );

	/** @brief	Set the zoom parameter of y axis
		@param	fYScale	the parameter of zoom for Y axis
	 */
	void SetYScale( const float &fYScale );

	/** @brief Set the zoom parameter of both x and y axis
		@param fXScale	the parameter of zoom for X axis
		@param fYScale	the parameter of zoom for Y axis
	 */
	void SetScale( const float &fXScale, const float &fYScale );

	/** @brief	Get the center position of object
	 */
	inline const POINT & GetPosCenter( void ) const
	{
		return m_posCenter;
	}

	/************************************************************************/
	/* @bruef Set the color of object                                                                     */
	/************************************************************************/
	inline void SetColorARGB( int alpha, int red, int green, int blue )
	{
		
		m_dwColor = COLOR_ARGB( alpha, red, green, blue );
	}

	inline void SetColorDWORD( DWORD color )
	{
		m_dwColor = color;
	}

	inline void SetColorAlpha( int alpha )
	{
		m_dwColor = (((alpha)&0xff)<<24|((m_dwColor)&0xffffff));
	}

	inline void SetColorRGB( int red, int green, int blue )
	{
		m_dwColor = (((m_dwColor)&0xff000000|((COLOR_ARGB(0,red,green,blue))&0xffffff)));
	}
	/************************************************************************/
	/* @bruef Get the color                                                                     */
	/************************************************************************/
	inline DWORD GetColorDWORD()
	{
		return m_dwColor;
	}

	inline int GetColorAlpha()
	{
		return (((m_dwColor)>>24)&0xff);
	}

	inline int GetColorRed()
	{
		return (((m_dwColor)>>16)&0xff);
	}

	inline int GetColorGreen()
	{
		return (((m_dwColor)>>8)&0xff);
	}

	inline int GetColorBlue()
	{
		return ((m_dwColor)&0xff);
	}

	/************************************************************************/
	/* Angle                                                                      */
	/************************************************************************/

	inline void SetAngle( const int &iangle )
	{
		m_iAngle = iangle;
	}

	inline const int &GetAngle() const
	{
		return m_iAngle;
	}
	/** @brief Set the center position of object
		@param posCenter	the center point of object
	 */
	void SetPosCenter( const POINT &posCenter );

	/** @brief Get the left-top point
		@return the left-top position of this object
	 */
	inline const POINT &GetPosLT( void ) const
	{
		return m_posLT;
	}

	/** @brief Set the left-top point of object
		@param posLT	a point that holds left-top point	
	*/
	virtual void SetPosLT( const POINT &posLT );

	/** @brief Get the compared position
		@return the compared position
	 */
	inline const POINT & GetPosCompare( void ) const
	{
		return m_posCompare;
	}

	/** @brief Set the compared position
		@param posCompare
	 */
	void SetPosCompare( const POINT &posCompare );

	/** @brief Get the size of object picture
		@return	the size of current object picture
	 */
	inline const POINT & GetSize( void ) const
	{
		return m_Size;
	}

	/** @brief Set the size of object
		@param Size	the size of object	
	*/
	virtual void SetSize( const POINT &Size );

	/** @brief Add picture location for this object
		@param picLocation	a PicLocation that holds a picture for this object

		this method will add a picture to the picture list for this object
	 */
	void AddPicLocation( const PicLocation &picLocation );

	/** @brief Get the current picture information of this object
		@return the current picture information, as a PicLocation instance, will be returned.
	 */
	inline virtual const PicLocation & GetPicLocation( void ) const 
	{
		assert( m_vecPicLocation.size() );	// if the picture vector is empty, then error...
		return m_vecPicLocation[ m_indexCurrentPic ];
	}

	inline virtual const int & GetPicLocationSize( void ) const
	{
		return m_vecPicLocation.size();
	}

	inline virtual const int & GetPicLocationCurID( void ) const
	{
		return m_indexCurrentPic;
	}

	/** @brief Set the index of picture that will used for this object	 
	 */
	void SetPicIndex( unsigned int index );

	/** @brief Get a data group member by index
		@param	index	the index that you want to get from data group, notice that it started with 0.
		@return	just as m_BaseDataGroup[ index ]
		@warning Be sure that you passed a valid index.
	 */
	inline const int & GetDataGroupByIndex( const int index ) const
	{
		return m_BaseDataGroup[ index ];
	}

	/** @brief Set a data group member by index
		@param	index	the index of member that you want to modify, notice that it started with 0.
		@param	value	the value of that member you want to modify
		@warning Be sure that you passed a valid index
	 */
	void SetDataGroupByIndex( const int index, const int &value );

	/** @brief	Get a bool group member by index
		@param	index	the index that you want to get from bool group, notice that it started with 0.
		@return	just as m_BaseBoolGroup[ index ]
		@warning Be sure that you passed a valid index.
	 */
	inline const bool & GetBoolGroupByIndex( const int index ) const
	{
		return m_BaseBoolGroup[ index ];
	}

	/** @brief	Set a bool group member by index
		@param	index	the index of member that you want to modify, notice that it started with 0.
		@param	value	the value of that member you want to modify
		@warning Be sure that you passed a valid index
	*/
	void SetBoolGroupByIndex( const int index, const bool &value );

	//------------------------------------------------------------
	//	Methods for Object Factory
	//------------------------------------------------------------

	/** @brief	method used to create an instance of this class
		@return return a pointer to an instance of this class
	 */
	static Object *CreateObject( void );

	//------------------------------------------------------------
	//	Methods for others
	//------------------------------------------------------------

	/** @brief	method for mouse left click action
		@param	posMouse	the position of mouse click action
	 */
	virtual void MouseLClick( void );

	/** @brief	method for mouse double click action
	 */
	virtual void MouseDBClick( void );

	/** @brief	method for mouse right click action
	 */
	virtual void MouseRClick( void );

	/** @brief	method for Key down action
	 */
	virtual void KeyDown( const WPARAM &wKey );

	/** @brief method for mouse in action
		
		this method is for mouse in action. While the mouse is in the object range,
		it may be called.
	 */
	virtual void MouseIn( void );

	/** @brief method for get focus
		
		Always, after get focus, MouseIn will be called.
	 */
	virtual void GetFocus( void );

	/** @brief	method for lose focus
	 */
	virtual void LoseFocus( void );

	/** @brief	method for Hit Test
		@param	posMouse	the point of mouse
		@return	return true if hit successful, else false
	 */
	virtual bool IsHited( const POINT &posMouse );

	/** @brief method to parse Object* to other type	 
	 */
	template< typename T >
	static T* Parse( Object* src )
	{
		return static_cast< T* >( src );
	}

	virtual void SetFocusFunc( string strFunc );
	virtual void SetLoseFocusFunc( string strFunc );

	virtual void SetPicLocationID( int iid )
	{
		m_vecPicLocation[m_indexCurrentPic].m_iPicID = iid;
	}
	virtual void SetCurPicLocation( int iid )
	{
		m_indexCurrentPic = iid;
	}
	virtual void SetCurPicLocationData( const PicLocation &pic )
	{
		m_vecPicLocation[m_indexCurrentPic] = pic;
	}

protected:
	///	Object enable or not, may special for UI elements
	bool		m_bEnable;
	///	Object visible or not, for most of the objects
	bool		m_bVisible;
	///	the layer of object, for graphics engine
	unsigned int	m_uiLayer;
	/// an index that holds the current picture of object
	unsigned int	m_indexCurrentPic;
	///	the zoom parameter of x axis
	float		m_fXScale;
	///	the zoom parameter of y axis
	float		m_fYScale;
	///	the point of object center
	POINT		m_posCenter;
	///	the point of the left-top of object
	POINT		m_posLT;
	/// the compared position of object
	POINT		m_posCompare;
	///	the size of object
	POINT		m_Size;
	///	vector that holds a couple of picture locations belongs to object
	vector< PicLocation >	m_vecPicLocation;
	/// an array that holds some useful integer data
	int			m_BaseDataGroup[ 16 ];
	/// an array that holds some useful bool data
	bool		m_BaseBoolGroup[ 16 ];
	/// the color of object
	DWORD		m_dwColor;
	/// the angle of object
	int			m_iAngle;
	/// string holds function name for get focus
	string		m_strFocusFunc;
	/// string holds function name for lose focus
	string		m_strLoseFocusFunc;

	//the head of Expack series
	Expack* m_pFirstPack;
public:
	/** draw the object on the canvas
	*   kyo's Added
	*/
	virtual bool Draw(Canvas* pCanvas);
	virtual void LogicKeyDown();
public:
	/** Other methods
	*   ly's Added
	*/
	inline Expack* GetExPack(void)
	{
		return m_pFirstPack;
	};
};

#endif
