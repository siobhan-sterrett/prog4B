#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>

uint8_t* pstr_set( uint8_t* pstr, const char* source )
{
	for( int i = 0; i < 256; ++i ) {
		if( source[i] == 0 ) {
			pstr[0] = i;
			return pstr;
		} else
			pstr[ i + 1 ] = source[i];
	}
	
	throw "String too long.";
}

void pstr_put( uint8_t* pstr, FILE* in )
{
	for( uint8_t i = 1; i <= *pstr; ++i )
		putc( pstr[i], in );
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
		throw "String too long.";
	}
	
	++*pstr;
	pstr[*pstr] = c;
	
	return pstr;
}

FILE* pstr_fopen( uint8_t* filename, const char* mode )
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
