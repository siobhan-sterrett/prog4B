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
	
	List< T > insert_after( const T& val ) const
	{
		List< T > list_copy( *this );
		List< T > new_element( val );
		new_element._next = list_copy._next;
		new_element._prev = std::make_shared< list_copy >;
		list_copy._next = std::make_shared< new_element >;
		
		return list_copy;
	}
	
	List< T > remove() const
	{
		if( _prev != nullptr and next != nullptr ) {
			List< T > list_copy( *_prev );
			list_copy._next = _next;
			_next->_prev = _prev;
			return list_copy;
		} else if( _prev == nullptr and next != nullptr ) {
			List< T > list_copy( *_next );
			list_copy._prev = nullptr;
			return list_copy;
		} else if( _prev != nullptr and next == nullptr ) {
			List< T > list_copy( *_prev );
			list_copy._next = nullptr;
			return list_copy;
		} else {
			return nullptr;
		}
	}
	
	const List< T >& prev() const
	{
		return *_prev;
	}
	
	const List< T >& next() const
	{
		return *_next;
	}

private:
	std::shared_ptr< T > _val = nullptr;
	std::shared_ptr< List< T > > _prev = nullptr, _next = nullptr;
};
