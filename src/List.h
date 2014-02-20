#pragma once

#include <memory>
#include <algorithm>
#include <stdexcept>

template < typename T >
class List
{
public:
	List< T >() = default;
	List< T >( const List< T >& ) = default;
	
	List< T >( List< T >&& other )
	{
		std::swap( _next,  other._next  );
		std::swap( _value, other._value );
	}

	List< T >( const T& value ) :
		_value( std::make_shared< const T >( value ) )
	{}
	/*
	template < typename... Args >
	List< T > ( const T& value, Args... args ) :
		_next( std::make_shared< const List< T > >( args... ) ),
		_value( std::make_shared< const T >( value ) )
	{}
	*/
	List< T >& operator = ( const List< T >& ) = default;
	
	List< T >& operator = ( List< T >&& other )
	{
		std::swap( _next,  other._next  );
		std::swap( _value, other._value );
		return *this;
	}
	
	List< T > insert_after( const T& value ) const
	{
		List< T > newList( *this );
		List< T > newElement( value );
		
		newElement._next = _next;
		newList._next = std::make_shared< const List< T > >( newElement );
		
		return newList;
	}
	
	List< T > remove() const
	{
		return *this;
	}
	
	List< T > next() const
	{
		if( _next )
			return *_next;
		else
			throw std::out_of_range( "" );
	}
	
	const T& get_value() const
	{
		return *_value;
	}

private:
	std::shared_ptr< const List< T > > _next;
	std::shared_ptr< const T > _value;
};
