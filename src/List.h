#pragma once

#include <memory>

template < typename T >
class List
{
public:
	List< T >()
	{}

	List< T >( const List< T >& other ) :
		_prev( other._prev ),
		_next( other._next ),
		_val ( other._val  )
	{}

	List< T >( const List< T >&& other ) :
		_prev( other._prev ),
		_next( other._next ),
		_val ( other._val  )
	{
		other._prev = nullptr;
		other._next = nullptr;
		other._val  = nullptr;
	}

	List< T >( const T& val ) :
		_val( std::make_shared< T >( val ) )
	{}

private:
	std::shared_ptr< T > _val = nullptr;
	std::shared_ptr< List< T > > _prev = nullptr, _next = nullptr;
};

template < typename T >
List< T > insert_after( const List& );

template < typename T >
List< T > remove( const List& );

template < typename T >
const List< T >& prev( const List& );

template < typename T >
const List< T >& next( const List& );


