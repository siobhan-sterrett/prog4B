#include "util.h"
#include "FA.h"

#include <cerrno>

int main()
{
	uint8_t str[256];
	uint8_t filename[256];
	uint8_t number[256];
	int c;
	FILE* fileptr, * tempfileptr;
	uint8_t nEntries;
	
	FA is_float, is_uint8_t;

	is_float( 0, '-' ) = 1;
	is_float( 0, ' ' ) = 1;
	is_float( 0, '1' ) = 2;
	is_float( 0, '2' ) = 2;
	is_float( 0, '3' ) = 2;
	is_float( 0, '4' ) = 2;
	is_float( 0, '5' ) = 2;
	is_float( 0, '6' ) = 2;
	is_float( 0, '7' ) = 2;
	is_float( 0, '8' ) = 2;
	is_float( 0, '9' ) = 2;
	is_float( 0, '.' ) = 5;
	is_float( 0, '0' ) = 3;

	is_float( 1, ' ' ) = 1;
	is_float( 1, '0' ) = 3;
	is_float( 1, '1' ) = 2;
	is_float( 1, '2' ) = 2;
	is_float( 1, '3' ) = 2;
	is_float( 1, '4' ) = 2;
	is_float( 1, '5' ) = 2;
	is_float( 1, '6' ) = 2;
	is_float( 1, '7' ) = 2;
	is_float( 1, '8' ) = 2;
	is_float( 1, '9' ) = 2;
	is_float( 1, '.' ) = 5;

	is_float( 2, '0' ) = 2;
	is_float( 2, '1' ) = 2;
	is_float( 2, '2' ) = 2;
	is_float( 2, '3' ) = 2;
	is_float( 2, '4' ) = 2;
	is_float( 2, '5' ) = 2;
	is_float( 2, '6' ) = 2;
	is_float( 2, '7' ) = 2;
	is_float( 2, '8' ) = 2;
	is_float( 2, '9' ) = 2;
	is_float( 2, '.' ) = 4;
	is_float( 2, ' ' ) = 7;
	is_float( 2, 'e' ) = 8;
	is_float( 2, 'E' ) = 8;

	is_float( 3, '.' ) = 4;
	is_float( 3, ' ' ) = 7;
	is_float( 3, 'e' ) = 8;
	is_float( 3, 'E' ) = 8;

	is_float( 4, '0' ) = 6;
	is_float( 4, '1' ) = 6;
	is_float( 4, '2' ) = 6;
	is_float( 4, '3' ) = 6;
	is_float( 4, '4' ) = 6;
	is_float( 4, '5' ) = 6;
	is_float( 4, '6' ) = 6;
	is_float( 4, '7' ) = 6;
	is_float( 4, '8' ) = 6;
	is_float( 4, '9' ) = 6;
	is_float( 4, ' ' ) = 7;
	is_float( 4, 'e' ) = 8;
	is_float( 4, 'E' ) = 8;

	is_float( 5, '0' ) = 6;
	is_float( 5, '1' ) = 6;
	is_float( 5, '2' ) = 6;
	is_float( 5, '3' ) = 6;
	is_float( 5, '4' ) = 6;
	is_float( 5, '5' ) = 6;
	is_float( 5, '6' ) = 6;
	is_float( 5, '7' ) = 6;
	is_float( 5, '8' ) = 6;
	is_float( 5, '9' ) = 6;

	is_float( 6, '0' ) = 6;
	is_float( 6, '1' ) = 6;
	is_float( 6, '2' ) = 6;
	is_float( 6, '3' ) = 6;
	is_float( 6, '4' ) = 6;
	is_float( 6, '5' ) = 6;
	is_float( 6, '6' ) = 6;
	is_float( 6, '7' ) = 6;
	is_float( 6, '8' ) = 6;
	is_float( 6, '9' ) = 6;
	is_float( 6, ' ' ) = 7;
	is_float( 6, 'e' ) = 8;
	is_float( 6, 'E' ) = 8;

	is_float( 7, ' ' ) = 7;
	is_float( 7, 'e' ) = 8;
	is_float( 7, 'E' ) = 8;

	is_float( 8, ' ' ) = 9;
	is_float( 8, '-' ) = 10;
	is_float( 8, '1' ) = 11;
	is_float( 8, '2' ) = 11;
	is_float( 8, '3' ) = 11;
	is_float( 8, '4' ) = 11;
	is_float( 8, '5' ) = 11;
	is_float( 8, '6' ) = 11;
	is_float( 8, '7' ) = 11;
	is_float( 8, '8' ) = 11;
	is_float( 8, '9' ) = 11;
	is_float( 8, '0' ) = 12;

	is_float( 9, ' ' ) = 9;
	is_float( 9, '-' ) = 10;

	is_float( 10, '0' ) = 12;
	is_float( 10, '1' ) = 11;
	is_float( 10, '2' ) = 11;
	is_float( 10, '3' ) = 11;
	is_float( 10, '4' ) = 11;
	is_float( 10, '5' ) = 11;
	is_float( 10, '6' ) = 11;
	is_float( 10, '7' ) = 11;
	is_float( 10, '8' ) = 11;
	is_float( 10, '9' ) = 11;
	is_float( 10, ' ' ) = 10;

	is_float( 11, '0' ) = 11;
	is_float( 11, '1' ) = 11;
	is_float( 11, '2' ) = 11;
	is_float( 11, '3' ) = 11;
	is_float( 11, '4' ) = 11;
	is_float( 11, '5' ) = 11;
	is_float( 11, '6' ) = 11;
	is_float( 11, '7' ) = 11;
	is_float( 11, '8' ) = 11;
	is_float( 11, '9' ) = 11;
	
	is_float.accept( 2 );
	is_float.accept( 3 );
	is_float.accept( 4 );
	is_float.accept( 6 );
	is_float.accept( 11 );
	
	is_uint8_t( 0, '0' ) = 1;
	is_uint8_t( 0, '1' ) = 2;
	is_uint8_t( 0, '2' ) = 3;
	is_uint8_t( 0, '3' ) = 2;
	is_uint8_t( 0, '4' ) = 2;
	is_uint8_t( 0, '5' ) = 2;
	is_uint8_t( 0, '6' ) = 2;
	is_uint8_t( 0, '7' ) = 2;
	is_uint8_t( 0, '8' ) = 2;
	is_uint8_t( 0, '9' ) = 2;
	
	is_uint8_t( 2, '0' ) = 4;
	is_uint8_t( 2, '1' ) = 4;
	is_uint8_t( 2, '2' ) = 4;
	is_uint8_t( 2, '3' ) = 4;
	is_uint8_t( 2, '4' ) = 4;
	is_uint8_t( 2, '5' ) = 4;
	is_uint8_t( 2, '6' ) = 4;
	is_uint8_t( 2, '7' ) = 4;
	is_uint8_t( 2, '8' ) = 4;
	is_uint8_t( 2, '9' ) = 4;
	
	is_uint8_t( 3, '0' ) = 6;
	is_uint8_t( 3, '1' ) = 6;
	is_uint8_t( 3, '2' ) = 6;
	is_uint8_t( 3, '3' ) = 6;
	is_uint8_t( 3, '4' ) = 6;
	is_uint8_t( 3, '5' ) = 8;
	is_uint8_t( 3, '6' ) = 10;
	is_uint8_t( 3, '7' ) = 10;
	is_uint8_t( 3, '8' ) = 10;
	is_uint8_t( 3, '9' ) = 10;
	
	is_uint8_t( 4, '0' ) = 5;
	is_uint8_t( 4, '1' ) = 5;
	is_uint8_t( 4, '2' ) = 5;
	is_uint8_t( 4, '3' ) = 5;
	is_uint8_t( 4, '4' ) = 5;
	is_uint8_t( 4, '5' ) = 5;
	is_uint8_t( 4, '6' ) = 5;
	is_uint8_t( 4, '7' ) = 5;
	is_uint8_t( 4, '8' ) = 5;
	is_uint8_t( 4, '9' ) = 5;
	
	is_uint8_t( 6, '0' ) = 7;
	is_uint8_t( 6, '1' ) = 7;
	is_uint8_t( 6, '2' ) = 7;
	is_uint8_t( 6, '3' ) = 7;
	is_uint8_t( 6, '4' ) = 7;
	is_uint8_t( 6, '5' ) = 7;
	is_uint8_t( 6, '6' ) = 7;
	is_uint8_t( 6, '7' ) = 7;
	is_uint8_t( 6, '8' ) = 7;
	is_uint8_t( 6, '9' ) = 7;
	
	is_uint8_t( 8, '0' ) = 9;
	is_uint8_t( 8, '1' ) = 9;
	is_uint8_t( 8, '2' ) = 9;
	is_uint8_t( 8, '3' ) = 9;
	is_uint8_t( 8, '4' ) = 9;
	is_uint8_t( 8, '5' ) = 9;
	
	is_uint8_t.accept( 1 );
	is_uint8_t.accept( 2 );
	is_uint8_t.accept( 3 );
	is_uint8_t.accept( 4 );
	is_uint8_t.accept( 5 );
	is_uint8_t.accept( 6 );
	is_uint8_t.accept( 7 );
	is_uint8_t.accept( 8 );
	is_uint8_t.accept( 9 );
	is_uint8_t.accept( 10 );

begin :
	pstr_set( str, "Please enter filename.\n>> " );
	pstr_put( str, stdout );
	pstr_getline( filename, stdin );
	
	pstr_set( str, "[R]ead, [W]rite, [M]odify?\n>> " );
	pstr_put( str, stdout );
	c = getc( stdin );
	while( getc( stdin ) != '\n' );
	
	if( c == 'r' ) goto read;
	if( c == 'R' ) goto read;
	if( c == 'w' ) goto write;
	if( c == 'W' ) goto write;
	if( c == 'm' ) goto modify;
	if( c == 'M' ) goto modify;
	
	pstr_set( str, "Invalid entry.\n" );
	pstr_put( str, stdout );
	goto begin;
	
read :
	fileptr = pstr_fopen( filename, "r" );
	if( fileptr == nullptr )
		if( errno == 2 ) {
			pstr_set( str, "File does not exist.\n" );
			pstr_put( str, stdout );
			errno = 0;
			goto begin;
		}
	
	c = 0;
	for( int i = 0; i < 256; ++i ) {
		if( c != EOF )
			c = getc( fileptr );
		if( c != EOF ) {
			ungetc( c, fileptr );
			pstr_getline( str, fileptr );
			pstr_pushback( str, '\n' );
			pstr_put( str, stdout );
		}
	}
	
	fclose( fileptr );
	
	exit( 0 );

write :
	fileptr = pstr_fopen( filename, "r" );
	if( fileptr != nullptr ) {
		pstr_set( str, "File already exists.\n" );
		pstr_put( str, stdout );
		fclose( fileptr );
		goto begin;
	}
	
	fileptr = pstr_fopen( filename, "w" );
	
filesize :
	pstr_set( str, "How many entries?\n>> " );
	pstr_put( str, stdout );
	
	pstr_getline( str, stdin );
	
	if( ! is_uint8_t( str ) ) {
		pstr_set( str, "Please enter a positive integer.\n" );
		pstr_put( str, stdout );
		goto filesize;
	}
	
	nEntries = pstr_to_uint8_t( str );
	
	for( int i = 0; i < 256; ++i )
		if( i < nEntries ) {
write_number :
			pstr_set( str, "Enter number.\n>> " );
			pstr_put( str, stdout );
			pstr_getline( str, stdin );
			
			if( ! is_float( str ) ) {
				pstr_set( str, "Please enter a floating-point number.\n" );
				pstr_put( str, stdout );
				goto write_number;
			}
			
			// Canonicalize
			canonicalize( str );
			
			pstr_pushback( str, '\n' );
			pstr_put( str, fileptr );
		}
	
	return 0;

modify :
	fileptr = pstr_fopen( filename, "r" );
	if( fileptr == nullptr )
		if( errno == 2 ) {
			pstr_set( str, "File does not exist.\n" );
			pstr_put( str, stdout );
			errno = 0;
			goto begin;
		}
		
	pstr_set( str, ".tempanugirqgh" );
	tempfileptr = pstr_fopen( str, "w" );
	
	c = 0;
	if( c != EOF )
		c = getc( fileptr );
	if( c != EOF ) {
		ungetc( c, fileptr );
		pstr_getline( number, fileptr );
	}
	
	// Canonicalize
	canonicalize( number );
	
	pstr_pushback( number, '\n' );
	pstr_copy( str, number );
	pstr_pushback( str, '\n' );
	pstr_put( str, stdout );

	while( true ) {
		pstr_set( str, "[N]ext        [C]hange   [D]elete   [I]nsert\n"
					   "[S]ave   Save [A]s       [Q]uit\n>> " );
		pstr_put( str, stdout );
		
		c = getc( stdin );
		while( getc( stdin ) != '\n' );
		
		switch( c ) {
		case 'N' :
		case 'n' :
			pstr_put( number, tempfileptr );
			// Fallthrough
			
		case 'D' :
		case 'd' :
			c = 0;
			if( c != EOF )
				c = getc( fileptr );
			if( c != EOF ) {
				ungetc( c, fileptr );
				pstr_getline( number, fileptr );
				
				// Canonicalize
				canonicalize( number );
				
				pstr_pushback( number, '\n' );
				pstr_copy( str, number );
				pstr_pushback( str, '\n' );
				pstr_put( str, stdout );
			} else {
				pstr_set( str, "\n\n" );
				pstr_put( str, stdout );
			}
			
			break;
			
		case 'I' :
		case 'i' :
modify_insert :
			pstr_set( str, "Enter number.\n>> " );
			pstr_put( str, stdout );
			pstr_getline( str, stdin );
			
			if( ! is_float( str ) ) {
				pstr_set( str, "Please enter a floating-point number.\n" );
				pstr_put( str, stdout );
				goto modify_insert;
			}
			
			pstr_put( number, tempfileptr );
			
			pstr_copy( number, str );
			
			// Canonicalize
			canonicalize( number );
			
			pstr_pushback( number, '\n' );
			pstr_copy( str, number );
			pstr_pushback( str, '\n' );
			pstr_put( str, stdout );
			
			break;
		
		case 'C' :
		case 'c' :
modify_change :
			pstr_set( str, "Enter number.\n>> " );
			pstr_put( str, stdout );
			pstr_getline( str, stdin );
			
			if( ! is_float( str ) ) {
				pstr_set( str, "Please enter a floating-point number.\n" );
				pstr_put( str, stdout );
				goto modify_change;
			}
			
			pstr_copy( number, str );
			
			// Canonicalize
			canonicalize( number );
			
			pstr_pushback( number, '\n' );
			pstr_copy( str, number );
			pstr_pushback( str, '\n' );
			pstr_put( str, stdout );
			
			break;
			
		case 'A' :
		case 'a' :
			pstr_set( str, "Please enter filename.\n>> " );
			pstr_put( str, stdout );
			pstr_getline( filename, stdin );
			// Fallthrough
			
		case 'S' :
		case 's' :
			pstr_put( number, tempfileptr );
			c = getc( fileptr );
			while( c != EOF ) {
				putc( c, tempfileptr );
				c = getc( fileptr );
			}
			fclose( fileptr );
			fclose( tempfileptr );
			
			fileptr = pstr_fopen( filename, "w" );
			pstr_set( str, ".tempanugirqgh" );
			tempfileptr = pstr_fopen( str, "r" );
			
			c = getc( tempfileptr );
			while( c != EOF ) {
				putc( c, fileptr );
				c = getc( tempfileptr );
			}
			
			fclose( fileptr );
			fclose( tempfileptr );
			
			exit( 0 );
			break;
		
		case 'Q' :
		case 'q' :
			exit( 0 );
			break;
		}
	}
	
	return 0;
}
