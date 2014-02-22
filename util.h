#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>

class PStrErr
{
public:
	const char* what() const throw()
	{
		return "String is too long.";
	}
};

uint8_t* pstr_set( uint8_t* pstr, const char* source )
{
	for( int i = 0; i < 256; ++i ) {
		if( source[i] == 0 ) {
			pstr[0] = i;
			return pstr;
		} else
			pstr[ i + 1 ] = source[i];
	}
	
	throw PStrErr();
}

void pstr_put( const uint8_t* pstr, FILE* in )
{
	for( uint8_t i = 1; i <= *pstr; ++i )
		putc( pstr[i], in );
}

uint8_t* pstr_copy( uint8_t* pstr1, const uint8_t* pstr2 )
{
	for( int i = 0; i < 256; ++i )
		pstr1[i] = pstr2[i];
		
	return pstr1;
}

uint8_t* pstr_getline( uint8_t* pstr, FILE* in )
{
	int c = 0;
	*pstr = 0;
	
	for( int i = 1; i < 256; ++i ) {
		if( c != '\n' and c != EOF )
			c = getc( in );
		if( c != '\n' and c != EOF ) {
			++*pstr;
			pstr[*pstr] = static_cast< uint8_t >( c );
		}
	}
	
	return pstr;
}

uint8_t* pstr_pushback( uint8_t* pstr, uint8_t c )
{
	if( *pstr == 255 ) {
		throw PStrErr();
	}
	
	++*pstr;
	pstr[*pstr] = c;
	
	return pstr;
}

FILE* pstr_fopen( const uint8_t* filename, const char* mode )
{
	char c_str[256];
	
	for( uint8_t i = 0; i < 255; ++i ) {
		if( i + 1 <= *filename )
			c_str[i] = filename[ i + 1 ];
		else
			c_str[i] = 0;
	}
	
	c_str[255] = 0;
	
	return fopen( c_str, mode );
}

uint8_t pstr_to_uint8_t( const uint8_t* pstr )
{
	uint8_t i = 0;
	uint8_t c;
	
	if( *pstr > 0 ) {
		c = pstr[1];
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
	}
	if( *pstr > 1 ) {
		i *= 10;
		c = pstr[2];
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
	}
	if( *pstr > 2 ) {
		i *= 10;
		c = pstr[3];
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
		if( c != '0' ) {
			--c;
			++i;
		}
	}
	
	return i;
}

uint8_t* pstr_insert( uint8_t* pstr, uint8_t pos, uint8_t c )
{
	if( pstr[0] == 255 )
		throw PStrErr();
	
	for( int i = 255; i > 1; --i )
		if( i > pos )
			pstr[i] = pstr[ i - 1 ];
	
	pstr[pos] = c;
	++pstr[0];
	
	return pstr;
}

uint8_t* pstr_remove( uint8_t* pstr, uint8_t pos )
{
	for( int i = 1; i < 255; ++i )
		if( i >= pos )
			pstr[i] = pstr[ i + 1 ];
			
	--pstr[0];
	
	return pstr;
}

uint8_t* canonicalize( uint8_t* pstr )
{
	// Remove spaces
	// Change 'E' to 'e'
	// Add .0 to integers
	// Add 0 to numbers with no integer part
	// pstr is assumed to already be a legal floating point number
	
	bool good = false;
	bool point = false;
	
	// remove spaces
	for( int i = 1; i < 256; ++i )
		if( pstr[0] >= i )
			if( pstr[i] == ' ' )
				pstr_remove( pstr, i );
	
	// change 'E' to 'e'
	for( int i = 1; i < 256; ++i )
		if( pstr[0] >= i )
			if( pstr[i] == 'E' )
				pstr[i] = 'e';
	
	// Add 0 to numbers with no integer part
	for( int i = 1; i < 256; ++i ) {
		if( pstr[0] >= i and good == false ) {
			if( '0' <= pstr[i] and pstr[i] <= '9' ) {
				good = true;
			} else if( pstr[i] == '.' ) {
				pstr_insert( pstr, i, '0' );
				good = true;
			}
		}
	}
	
	good = false;
	
	// Add .0 to integers
	for( int i = 0; i < 256; ++i ) {
		if( pstr[0] >= i and good == false ) {
			if( pstr[i] == '.' ) {
				good = true;
			} else if( pstr[i] == 'e' ) {
				pstr_insert( pstr, i, '.' );
				pstr_insert( pstr, i + 1, '0' );
				good = true;
			}
		} else if( i == pstr[0] + 1 and good == false ) {
			pstr_insert( pstr, i, '.' );
			pstr_insert( pstr, i + 1, '0' );
			good = true;
		}
	}
	
	good = false;
	
	// Add 0 to numbers with no decimal part
	for( int i = 1; i < 256; ++i ) {
		if( pstr[0] >= i and good == false ) {
			if( pstr[i] == '.' ) {
				point = true;
			} else if( '0' <= pstr[i] and pstr[i] <= '9' and point == true ) {
				good = true;
			} else if( pstr[i] == 'e' and point == true ) {
				pstr_insert( pstr, i, '0' );
				good = true;
			}
		} else if( i == pstr[0] + 1 and good == false ) {
			pstr_insert( pstr, i, '0' );
			good = true;
		}
	}
	
	return pstr;
}
