#pragma once

#include "util.h"

#include <cstdint>

class FA
{
public :
	FA()
	{
		for( int i = 0; i < 256; ++i )
		for( int j = 0; j < 256; ++j )
			delta[i][j] = -1;
		
		for( int i = 0; i < 256; ++i )
			F[i] = -1;
	}
	
	bool operator () ( const uint8_t* pstr ) const
	{
		int state = 0;
		
		for( int i = 1; i < 256; ++i ) {
			if( i <= *pstr ) {
				state = delta[ state ][ pstr[i] ];
				if( state == -1 )
					return false;
			}
		}
		
		for( int i = 0; i < 256; ++i )
			if( F[i] == state )
				return true;
		
		return false;
	}
	
	int& operator () ( const uint8_t& state, const uint8_t& c )
	{
		return delta[ state ][ c ];
	}
	
	void accept( const uint8_t& state )
	{
		for( int i = 0; i < 256; ++i )
			if( F[i] == -1 ) {
				F[i] = state;
				return;
			}
	}
	
	void unaccept( const uint8_t& state )
	{
		for( int i = 0; i < 256; ++i )
			if( F[i] == state )
				F[i] = -1;
	}

private :
	int delta[256][256];
	int F[256];
};
