#ifndef SINGLETON_H
#define SINGLETON_H

template< typename T >
class Singleton : public T
{
public:
	static Singleton< T >& instance( void );
	~Singleton( void );
protected:
	Singleton( void );
	Singleton( const Singleton& );
	Singleton& operator=( const Singleton& );
};

template< typename T >
Singleton< T >& Singleton< T >::instance( void )
{
	static Singleton< T > _instance;
	return _instance;
}

template< typename T >
Singleton< T >::Singleton( void )
{
}

template< typename T >
Singleton< T >::~Singleton( void )
{
}

#endif
