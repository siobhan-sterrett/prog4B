#include "util.h"
#include "FA.h"

#include <cerrno>

int main()
{
	uint8_t str[256];
	uint8_t filename[256];
	uint8_t number[256];
	char c_str[256];
	int c;
	FILE* fileptr, * tempfileptr;
	uint8_t nEntries;
	bool good;

	FA is_float, is_uint8_t;

	// Set up finite automata! Got this idea from Andrew, after he showed
	//	me some Haskell code to simulate an FA.
	is_float( 0, '-' ) = 1;
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
	is_float( 9, '0' ) = 12;
	is_float( 9, '1' ) = 11;
	is_float( 9, '2' ) = 11;
	is_float( 9, '3' ) = 11;
	is_float( 9, '4' ) = 11;
	is_float( 9, '5' ) = 11;
	is_float( 9, '6' ) = 11;
	is_float( 9, '7' ) = 11;
	is_float( 9, '8' ) = 11;
	is_float( 9, '9' ) = 11;
	
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
				pstr_set( number, "" );
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
			c_str[0] = 'P';
			c_str[1] = 'l';
			c_str[2] = 'e';
			c_str[3] = 'a';
			c_str[4] = 's';
			c_str[5] = 'e';
			c_str[6] = ' ';
			c_str[7] = 'e';
			c_str[8] = 'n';
			c_str[9] = 't';
			c_str[10] = 'e';
			c_str[11] = 'r';
			c_str[12] = ' ';
			c_str[13] = 'f';
			c_str[14] = 'i';
			c_str[15] = 'l';
			c_str[16] = 'e';
			c_str[17] = 'n';
			c_str[18] = 'a';
			c_str[19] = 'm';
			c_str[20] = 'e';
			c_str[21] = '.';
			c_str[22] = '\n';
			c_str[23] = '>';
			c_str[24] = '>';
			c_str[25] = ' ';
			c_str[26] = 0;
			
			good = false;
			
			if( c_str[0] == 0 ) {
				str[0] = 0;
				good = true;
			} else str[1] = c_str[0];
			if( good == false ) {
				if( c_str[1] == 0 ) {
					str[0] = 1;
					good = true;
				} else str[2] = c_str[1];
			}
			if( good == false ) {
				if( c_str[2] == 0 ) {
					str[0] = 2;
					good = true;
				} else str[3] = c_str[2];
			}
			if( good == false ) {
				if( c_str[3] == 0 ) {
					str[0] = 3;
					good = true;
				} else str[4] = c_str[3];
			}
			if( good == false ) {
				if( c_str[4] == 0 ) {
					str[0] = 4;
					good = true;
				} else str[5] = c_str[4];
			}
			if( good == false ) {
				if( c_str[5] == 0 ) {
					str[0] = 5;
					good = true;
				} else str[6] = c_str[5];
			}
			if( good == false ) {
				if( c_str[6] == 0 ) {
					str[0] = 6;
					good = true;
				} else str[7] = c_str[6];
			}
			if( good == false ) {
				if( c_str[7] == 0 ) {
					str[0] = 7;
					good = true;
				} else str[8] = c_str[7];
			}
			if( good == false ) {
				if( c_str[8] == 0 ) {
					str[0] = 8;
					good = true;
				} else str[9] = c_str[8];
			}
			if( good == false ) {
				if( c_str[9] == 0 ) {
					str[0] = 9;
					good = true;
				} else str[10] = c_str[9];
			}
			if( good == false ) {
				if( c_str[10] == 0 ) {
					str[0] = 10;
					good = true;
				} else str[11] = c_str[10];
			}
			if( good == false ) {
				if( c_str[11] == 0 ) {
					str[0] = 11;
					good = true;
				} else str[12] = c_str[11];
			}
			if( good == false ) {
				if( c_str[12] == 0 ) {
					str[0] = 12;
					good = true;
				} else str[13] = c_str[12];
			}
			if( good == false ) {
				if( c_str[13] == 0 ) {
					str[0] = 13;
					good = true;
				} else str[14] = c_str[13];
			}
			if( good == false ) {
				if( c_str[14] == 0 ) {
					str[0] = 14;
					good = true;
				} else str[15] = c_str[14];
			}
			if( good == false ) {
				if( c_str[15] == 0 ) {
					str[0] = 15;
					good = true;
				} else str[16] = c_str[15];
			}
			if( good == false ) {
				if( c_str[16] == 0 ) {
					str[0] = 16;
					good = true;
				} else str[17] = c_str[16];
			}
			if( good == false ) {
				if( c_str[17] == 0 ) {
					str[0] = 17;
					good = true;
				} else str[18] = c_str[17];
			}
			if( good == false ) {
				if( c_str[18] == 0 ) {
					str[0] = 18;
					good = true;
				} else str[19] = c_str[18];
			}
			if( good == false ) {
				if( c_str[19] == 0 ) {
					str[0] = 19;
					good = true;
				} else str[20] = c_str[19];
			}
			if( good == false ) {
				if( c_str[20] == 0 ) {
					str[0] = 20;
					good = true;
				} else str[21] = c_str[20];
			}
			if( good == false ) {
				if( c_str[21] == 0 ) {
					str[0] = 21;
					good = true;
				} else str[22] = c_str[21];
			}
			if( good == false ) {
				if( c_str[22] == 0 ) {
					str[0] = 22;
					good = true;
				} else str[23] = c_str[22];
			}
			if( good == false ) {
				if( c_str[23] == 0 ) {
					str[0] = 23;
					good = true;
				} else str[24] = c_str[23];
			}
			if( good == false ) {
				if( c_str[24] == 0 ) {
					str[0] = 24;
					good = true;
				} else str[25] = c_str[24];
			}
			if( good == false ) {
				if( c_str[25] == 0 ) {
					str[0] = 25;
					good = true;
				} else str[26] = c_str[25];
			}
			if( good == false ) {
				if( c_str[26] == 0 ) {
					str[0] = 26;
					good = true;
				} else str[27] = c_str[26];
			}
			if( good == false ) {
				if( c_str[27] == 0 ) {
					str[0] = 27;
					good = true;
				} else str[28] = c_str[27];
			}
			if( good == false ) {
				if( c_str[28] == 0 ) {
					str[0] = 28;
					good = true;
				} else str[29] = c_str[28];
			}
			if( good == false ) {
				if( c_str[29] == 0 ) {
					str[0] = 29;
					good = true;
				} else str[30] = c_str[29];
			}
			if( good == false ) {
				if( c_str[30] == 0 ) {
					str[0] = 30;
					good = true;
				} else str[31] = c_str[30];
			}
			if( good == false ) {
				if( c_str[31] == 0 ) {
					str[0] = 31;
					good = true;
				} else str[32] = c_str[31];
			}
			if( good == false ) {
				if( c_str[32] == 0 ) {
					str[0] = 32;
					good = true;
				} else str[33] = c_str[32];
			}
			if( good == false ) {
				if( c_str[33] == 0 ) {
					str[0] = 33;
					good = true;
				} else str[34] = c_str[33];
			}
			if( good == false ) {
				if( c_str[34] == 0 ) {
					str[0] = 34;
					good = true;
				} else str[35] = c_str[34];
			}
			if( good == false ) {
				if( c_str[35] == 0 ) {
					str[0] = 35;
					good = true;
				} else str[36] = c_str[35];
			}
			if( good == false ) {
				if( c_str[36] == 0 ) {
					str[0] = 36;
					good = true;
				} else str[37] = c_str[36];
			}
			if( good == false ) {
				if( c_str[37] == 0 ) {
					str[0] = 37;
					good = true;
				} else str[38] = c_str[37];
			}
			if( good == false ) {
				if( c_str[38] == 0 ) {
					str[0] = 38;
					good = true;
				} else str[39] = c_str[38];
			}
			if( good == false ) {
				if( c_str[39] == 0 ) {
					str[0] = 39;
					good = true;
				} else str[40] = c_str[39];
			}
			if( good == false ) {
				if( c_str[40] == 0 ) {
					str[0] = 40;
					good = true;
				} else str[41] = c_str[40];
			}
			if( good == false ) {
				if( c_str[41] == 0 ) {
					str[0] = 41;
					good = true;
				} else str[42] = c_str[41];
			}
			if( good == false ) {
				if( c_str[42] == 0 ) {
					str[0] = 42;
					good = true;
				} else str[43] = c_str[42];
			}
			if( good == false ) {
				if( c_str[43] == 0 ) {
					str[0] = 43;
					good = true;
				} else str[44] = c_str[43];
			}
			if( good == false ) {
				if( c_str[44] == 0 ) {
					str[0] = 44;
					good = true;
				} else str[45] = c_str[44];
			}
			if( good == false ) {
				if( c_str[45] == 0 ) {
					str[0] = 45;
					good = true;
				} else str[46] = c_str[45];
			}
			if( good == false ) {
				if( c_str[46] == 0 ) {
					str[0] = 46;
					good = true;
				} else str[47] = c_str[46];
			}
			if( good == false ) {
				if( c_str[47] == 0 ) {
					str[0] = 47;
					good = true;
				} else str[48] = c_str[47];
			}
			if( good == false ) {
				if( c_str[48] == 0 ) {
					str[0] = 48;
					good = true;
				} else str[49] = c_str[48];
			}
			if( good == false ) {
				if( c_str[49] == 0 ) {
					str[0] = 49;
					good = true;
				} else str[50] = c_str[49];
			}
			if( good == false ) {
				if( c_str[50] == 0 ) {
					str[0] = 50;
					good = true;
				} else str[51] = c_str[50];
			}
			if( good == false ) {
				if( c_str[51] == 0 ) {
					str[0] = 51;
					good = true;
				} else str[52] = c_str[51];
			}
			if( good == false ) {
				if( c_str[52] == 0 ) {
					str[0] = 52;
					good = true;
				} else str[53] = c_str[52];
			}
			if( good == false ) {
				if( c_str[53] == 0 ) {
					str[0] = 53;
					good = true;
				} else str[54] = c_str[53];
			}
			if( good == false ) {
				if( c_str[54] == 0 ) {
					str[0] = 54;
					good = true;
				} else str[55] = c_str[54];
			}
			if( good == false ) {
				if( c_str[55] == 0 ) {
					str[0] = 55;
					good = true;
				} else str[56] = c_str[55];
			}
			if( good == false ) {
				if( c_str[56] == 0 ) {
					str[0] = 56;
					good = true;
				} else str[57] = c_str[56];
			}
			if( good == false ) {
				if( c_str[57] == 0 ) {
					str[0] = 57;
					good = true;
				} else str[58] = c_str[57];
			}
			if( good == false ) {
				if( c_str[58] == 0 ) {
					str[0] = 58;
					good = true;
				} else str[59] = c_str[58];
			}
			if( good == false ) {
				if( c_str[59] == 0 ) {
					str[0] = 59;
					good = true;
				} else str[60] = c_str[59];
			}
			if( good == false ) {
				if( c_str[60] == 0 ) {
					str[0] = 60;
					good = true;
				} else str[61] = c_str[60];
			}
			if( good == false ) {
				if( c_str[61] == 0 ) {
					str[0] = 61;
					good = true;
				} else str[62] = c_str[61];
			}
			if( good == false ) {
				if( c_str[62] == 0 ) {
					str[0] = 62;
					good = true;
				} else str[63] = c_str[62];
			}
			if( good == false ) {
				if( c_str[63] == 0 ) {
					str[0] = 63;
					good = true;
				} else str[64] = c_str[63];
			}
			if( good == false ) {
				if( c_str[64] == 0 ) {
					str[0] = 64;
					good = true;
				} else str[65] = c_str[64];
			}
			if( good == false ) {
				if( c_str[65] == 0 ) {
					str[0] = 65;
					good = true;
				} else str[66] = c_str[65];
			}
			if( good == false ) {
				if( c_str[66] == 0 ) {
					str[0] = 66;
					good = true;
				} else str[67] = c_str[66];
			}
			if( good == false ) {
				if( c_str[67] == 0 ) {
					str[0] = 67;
					good = true;
				} else str[68] = c_str[67];
			}
			if( good == false ) {
				if( c_str[68] == 0 ) {
					str[0] = 68;
					good = true;
				} else str[69] = c_str[68];
			}
			if( good == false ) {
				if( c_str[69] == 0 ) {
					str[0] = 69;
					good = true;
				} else str[70] = c_str[69];
			}
			if( good == false ) {
				if( c_str[70] == 0 ) {
					str[0] = 70;
					good = true;
				} else str[71] = c_str[70];
			}
			if( good == false ) {
				if( c_str[71] == 0 ) {
					str[0] = 71;
					good = true;
				} else str[72] = c_str[71];
			}
			if( good == false ) {
				if( c_str[72] == 0 ) {
					str[0] = 72;
					good = true;
				} else str[73] = c_str[72];
			}
			if( good == false ) {
				if( c_str[73] == 0 ) {
					str[0] = 73;
					good = true;
				} else str[74] = c_str[73];
			}
			if( good == false ) {
				if( c_str[74] == 0 ) {
					str[0] = 74;
					good = true;
				} else str[75] = c_str[74];
			}
			if( good == false ) {
				if( c_str[75] == 0 ) {
					str[0] = 75;
					good = true;
				} else str[76] = c_str[75];
			}
			if( good == false ) {
				if( c_str[76] == 0 ) {
					str[0] = 76;
					good = true;
				} else str[77] = c_str[76];
			}
			if( good == false ) {
				if( c_str[77] == 0 ) {
					str[0] = 77;
					good = true;
				} else str[78] = c_str[77];
			}
			if( good == false ) {
				if( c_str[78] == 0 ) {
					str[0] = 78;
					good = true;
				} else str[79] = c_str[78];
			}
			if( good == false ) {
				if( c_str[79] == 0 ) {
					str[0] = 79;
					good = true;
				} else str[80] = c_str[79];
			}
			if( good == false ) {
				if( c_str[80] == 0 ) {
					str[0] = 80;
					good = true;
				} else str[81] = c_str[80];
			}
			if( good == false ) {
				if( c_str[81] == 0 ) {
					str[0] = 81;
					good = true;
				} else str[82] = c_str[81];
			}
			if( good == false ) {
				if( c_str[82] == 0 ) {
					str[0] = 82;
					good = true;
				} else str[83] = c_str[82];
			}
			if( good == false ) {
				if( c_str[83] == 0 ) {
					str[0] = 83;
					good = true;
				} else str[84] = c_str[83];
			}
			if( good == false ) {
				if( c_str[84] == 0 ) {
					str[0] = 84;
					good = true;
				} else str[85] = c_str[84];
			}
			if( good == false ) {
				if( c_str[85] == 0 ) {
					str[0] = 85;
					good = true;
				} else str[86] = c_str[85];
			}
			if( good == false ) {
				if( c_str[86] == 0 ) {
					str[0] = 86;
					good = true;
				} else str[87] = c_str[86];
			}
			if( good == false ) {
				if( c_str[87] == 0 ) {
					str[0] = 87;
					good = true;
				} else str[88] = c_str[87];
			}
			if( good == false ) {
				if( c_str[88] == 0 ) {
					str[0] = 88;
					good = true;
				} else str[89] = c_str[88];
			}
			if( good == false ) {
				if( c_str[89] == 0 ) {
					str[0] = 89;
					good = true;
				} else str[90] = c_str[89];
			}
			if( good == false ) {
				if( c_str[90] == 0 ) {
					str[0] = 90;
					good = true;
				} else str[91] = c_str[90];
			}
			if( good == false ) {
				if( c_str[91] == 0 ) {
					str[0] = 91;
					good = true;
				} else str[92] = c_str[91];
			}
			if( good == false ) {
				if( c_str[92] == 0 ) {
					str[0] = 92;
					good = true;
				} else str[93] = c_str[92];
			}
			if( good == false ) {
				if( c_str[93] == 0 ) {
					str[0] = 93;
					good = true;
				} else str[94] = c_str[93];
			}
			if( good == false ) {
				if( c_str[94] == 0 ) {
					str[0] = 94;
					good = true;
				} else str[95] = c_str[94];
			}
			if( good == false ) {
				if( c_str[95] == 0 ) {
					str[0] = 95;
					good = true;
				} else str[96] = c_str[95];
			}
			if( good == false ) {
				if( c_str[96] == 0 ) {
					str[0] = 96;
					good = true;
				} else str[97] = c_str[96];
			}
			if( good == false ) {
				if( c_str[97] == 0 ) {
					str[0] = 97;
					good = true;
				} else str[98] = c_str[97];
			}
			if( good == false ) {
				if( c_str[98] == 0 ) {
					str[0] = 98;
					good = true;
				} else str[99] = c_str[98];
			}
			if( good == false ) {
				if( c_str[99] == 0 ) {
					str[0] = 99;
					good = true;
				} else str[100] = c_str[99];
			}
			if( good == false ) {
				if( c_str[100] == 0 ) {
					str[0] = 100;
					good = true;
				} else str[101] = c_str[100];
			}
			if( good == false ) {
				if( c_str[101] == 0 ) {
					str[0] = 101;
					good = true;
				} else str[102] = c_str[101];
			}
			if( good == false ) {
				if( c_str[102] == 0 ) {
					str[0] = 102;
					good = true;
				} else str[103] = c_str[102];
			}
			if( good == false ) {
				if( c_str[103] == 0 ) {
					str[0] = 103;
					good = true;
				} else str[104] = c_str[103];
			}
			if( good == false ) {
				if( c_str[104] == 0 ) {
					str[0] = 104;
					good = true;
				} else str[105] = c_str[104];
			}
			if( good == false ) {
				if( c_str[105] == 0 ) {
					str[0] = 105;
					good = true;
				} else str[106] = c_str[105];
			}
			if( good == false ) {
				if( c_str[106] == 0 ) {
					str[0] = 106;
					good = true;
				} else str[107] = c_str[106];
			}
			if( good == false ) {
				if( c_str[107] == 0 ) {
					str[0] = 107;
					good = true;
				} else str[108] = c_str[107];
			}
			if( good == false ) {
				if( c_str[108] == 0 ) {
					str[0] = 108;
					good = true;
				} else str[109] = c_str[108];
			}
			if( good == false ) {
				if( c_str[109] == 0 ) {
					str[0] = 109;
					good = true;
				} else str[110] = c_str[109];
			}
			if( good == false ) {
				if( c_str[110] == 0 ) {
					str[0] = 110;
					good = true;
				} else str[111] = c_str[110];
			}
			if( good == false ) {
				if( c_str[111] == 0 ) {
					str[0] = 111;
					good = true;
				} else str[112] = c_str[111];
			}
			if( good == false ) {
				if( c_str[112] == 0 ) {
					str[0] = 112;
					good = true;
				} else str[113] = c_str[112];
			}
			if( good == false ) {
				if( c_str[113] == 0 ) {
					str[0] = 113;
					good = true;
				} else str[114] = c_str[113];
			}
			if( good == false ) {
				if( c_str[114] == 0 ) {
					str[0] = 114;
					good = true;
				} else str[115] = c_str[114];
			}
			if( good == false ) {
				if( c_str[115] == 0 ) {
					str[0] = 115;
					good = true;
				} else str[116] = c_str[115];
			}
			if( good == false ) {
				if( c_str[116] == 0 ) {
					str[0] = 116;
					good = true;
				} else str[117] = c_str[116];
			}
			if( good == false ) {
				if( c_str[117] == 0 ) {
					str[0] = 117;
					good = true;
				} else str[118] = c_str[117];
			}
			if( good == false ) {
				if( c_str[118] == 0 ) {
					str[0] = 118;
					good = true;
				} else str[119] = c_str[118];
			}
			if( good == false ) {
				if( c_str[119] == 0 ) {
					str[0] = 119;
					good = true;
				} else str[120] = c_str[119];
			}
			if( good == false ) {
				if( c_str[120] == 0 ) {
					str[0] = 120;
					good = true;
				} else str[121] = c_str[120];
			}
			if( good == false ) {
				if( c_str[121] == 0 ) {
					str[0] = 121;
					good = true;
				} else str[122] = c_str[121];
			}
			if( good == false ) {
				if( c_str[122] == 0 ) {
					str[0] = 122;
					good = true;
				} else str[123] = c_str[122];
			}
			if( good == false ) {
				if( c_str[123] == 0 ) {
					str[0] = 123;
					good = true;
				} else str[124] = c_str[123];
			}
			if( good == false ) {
				if( c_str[124] == 0 ) {
					str[0] = 124;
					good = true;
				} else str[125] = c_str[124];
			}
			if( good == false ) {
				if( c_str[125] == 0 ) {
					str[0] = 125;
					good = true;
				} else str[126] = c_str[125];
			}
			if( good == false ) {
				if( c_str[126] == 0 ) {
					str[0] = 126;
					good = true;
				} else str[127] = c_str[126];
			}
			if( good == false ) {
				if( c_str[127] == 0 ) {
					str[0] = 127;
					good = true;
				} else str[128] = c_str[127];
			}
			if( good == false ) {
				if( c_str[128] == 0 ) {
					str[0] = 128;
					good = true;
				} else str[129] = c_str[128];
			}
			if( good == false ) {
				if( c_str[129] == 0 ) {
					str[0] = 129;
					good = true;
				} else str[130] = c_str[129];
			}
			if( good == false ) {
				if( c_str[130] == 0 ) {
					str[0] = 130;
					good = true;
				} else str[131] = c_str[130];
			}
			if( good == false ) {
				if( c_str[131] == 0 ) {
					str[0] = 131;
					good = true;
				} else str[132] = c_str[131];
			}
			if( good == false ) {
				if( c_str[132] == 0 ) {
					str[0] = 132;
					good = true;
				} else str[133] = c_str[132];
			}
			if( good == false ) {
				if( c_str[133] == 0 ) {
					str[0] = 133;
					good = true;
				} else str[134] = c_str[133];
			}
			if( good == false ) {
				if( c_str[134] == 0 ) {
					str[0] = 134;
					good = true;
				} else str[135] = c_str[134];
			}
			if( good == false ) {
				if( c_str[135] == 0 ) {
					str[0] = 135;
					good = true;
				} else str[136] = c_str[135];
			}
			if( good == false ) {
				if( c_str[136] == 0 ) {
					str[0] = 136;
					good = true;
				} else str[137] = c_str[136];
			}
			if( good == false ) {
				if( c_str[137] == 0 ) {
					str[0] = 137;
					good = true;
				} else str[138] = c_str[137];
			}
			if( good == false ) {
				if( c_str[138] == 0 ) {
					str[0] = 138;
					good = true;
				} else str[139] = c_str[138];
			}
			if( good == false ) {
				if( c_str[139] == 0 ) {
					str[0] = 139;
					good = true;
				} else str[140] = c_str[139];
			}
			if( good == false ) {
				if( c_str[140] == 0 ) {
					str[0] = 140;
					good = true;
				} else str[141] = c_str[140];
			}
			if( good == false ) {
				if( c_str[141] == 0 ) {
					str[0] = 141;
					good = true;
				} else str[142] = c_str[141];
			}
			if( good == false ) {
				if( c_str[142] == 0 ) {
					str[0] = 142;
					good = true;
				} else str[143] = c_str[142];
			}
			if( good == false ) {
				if( c_str[143] == 0 ) {
					str[0] = 143;
					good = true;
				} else str[144] = c_str[143];
			}
			if( good == false ) {
				if( c_str[144] == 0 ) {
					str[0] = 144;
					good = true;
				} else str[145] = c_str[144];
			}
			if( good == false ) {
				if( c_str[145] == 0 ) {
					str[0] = 145;
					good = true;
				} else str[146] = c_str[145];
			}
			if( good == false ) {
				if( c_str[146] == 0 ) {
					str[0] = 146;
					good = true;
				} else str[147] = c_str[146];
			}
			if( good == false ) {
				if( c_str[147] == 0 ) {
					str[0] = 147;
					good = true;
				} else str[148] = c_str[147];
			}
			if( good == false ) {
				if( c_str[148] == 0 ) {
					str[0] = 148;
					good = true;
				} else str[149] = c_str[148];
			}
			if( good == false ) {
				if( c_str[149] == 0 ) {
					str[0] = 149;
					good = true;
				} else str[150] = c_str[149];
			}
			if( good == false ) {
				if( c_str[150] == 0 ) {
					str[0] = 150;
					good = true;
				} else str[151] = c_str[150];
			}
			if( good == false ) {
				if( c_str[151] == 0 ) {
					str[0] = 151;
					good = true;
				} else str[152] = c_str[151];
			}
			if( good == false ) {
				if( c_str[152] == 0 ) {
					str[0] = 152;
					good = true;
				} else str[153] = c_str[152];
			}
			if( good == false ) {
				if( c_str[153] == 0 ) {
					str[0] = 153;
					good = true;
				} else str[154] = c_str[153];
			}
			if( good == false ) {
				if( c_str[154] == 0 ) {
					str[0] = 154;
					good = true;
				} else str[155] = c_str[154];
			}
			if( good == false ) {
				if( c_str[155] == 0 ) {
					str[0] = 155;
					good = true;
				} else str[156] = c_str[155];
			}
			if( good == false ) {
				if( c_str[156] == 0 ) {
					str[0] = 156;
					good = true;
				} else str[157] = c_str[156];
			}
			if( good == false ) {
				if( c_str[157] == 0 ) {
					str[0] = 157;
					good = true;
				} else str[158] = c_str[157];
			}
			if( good == false ) {
				if( c_str[158] == 0 ) {
					str[0] = 158;
					good = true;
				} else str[159] = c_str[158];
			}
			if( good == false ) {
				if( c_str[159] == 0 ) {
					str[0] = 159;
					good = true;
				} else str[160] = c_str[159];
			}
			if( good == false ) {
				if( c_str[160] == 0 ) {
					str[0] = 160;
					good = true;
				} else str[161] = c_str[160];
			}
			if( good == false ) {
				if( c_str[161] == 0 ) {
					str[0] = 161;
					good = true;
				} else str[162] = c_str[161];
			}
			if( good == false ) {
				if( c_str[162] == 0 ) {
					str[0] = 162;
					good = true;
				} else str[163] = c_str[162];
			}
			if( good == false ) {
				if( c_str[163] == 0 ) {
					str[0] = 163;
					good = true;
				} else str[164] = c_str[163];
			}
			if( good == false ) {
				if( c_str[164] == 0 ) {
					str[0] = 164;
					good = true;
				} else str[165] = c_str[164];
			}
			if( good == false ) {
				if( c_str[165] == 0 ) {
					str[0] = 165;
					good = true;
				} else str[166] = c_str[165];
			}
			if( good == false ) {
				if( c_str[166] == 0 ) {
					str[0] = 166;
					good = true;
				} else str[167] = c_str[166];
			}
			if( good == false ) {
				if( c_str[167] == 0 ) {
					str[0] = 167;
					good = true;
				} else str[168] = c_str[167];
			}
			if( good == false ) {
				if( c_str[168] == 0 ) {
					str[0] = 168;
					good = true;
				} else str[169] = c_str[168];
			}
			if( good == false ) {
				if( c_str[169] == 0 ) {
					str[0] = 169;
					good = true;
				} else str[170] = c_str[169];
			}
			if( good == false ) {
				if( c_str[170] == 0 ) {
					str[0] = 170;
					good = true;
				} else str[171] = c_str[170];
			}
			if( good == false ) {
				if( c_str[171] == 0 ) {
					str[0] = 171;
					good = true;
				} else str[172] = c_str[171];
			}
			if( good == false ) {
				if( c_str[172] == 0 ) {
					str[0] = 172;
					good = true;
				} else str[173] = c_str[172];
			}
			if( good == false ) {
				if( c_str[173] == 0 ) {
					str[0] = 173;
					good = true;
				} else str[174] = c_str[173];
			}
			if( good == false ) {
				if( c_str[174] == 0 ) {
					str[0] = 174;
					good = true;
				} else str[175] = c_str[174];
			}
			if( good == false ) {
				if( c_str[175] == 0 ) {
					str[0] = 175;
					good = true;
				} else str[176] = c_str[175];
			}
			if( good == false ) {
				if( c_str[176] == 0 ) {
					str[0] = 176;
					good = true;
				} else str[177] = c_str[176];
			}
			if( good == false ) {
				if( c_str[177] == 0 ) {
					str[0] = 177;
					good = true;
				} else str[178] = c_str[177];
			}
			if( good == false ) {
				if( c_str[178] == 0 ) {
					str[0] = 178;
					good = true;
				} else str[179] = c_str[178];
			}
			if( good == false ) {
				if( c_str[179] == 0 ) {
					str[0] = 179;
					good = true;
				} else str[180] = c_str[179];
			}
			if( good == false ) {
				if( c_str[180] == 0 ) {
					str[0] = 180;
					good = true;
				} else str[181] = c_str[180];
			}
			if( good == false ) {
				if( c_str[181] == 0 ) {
					str[0] = 181;
					good = true;
				} else str[182] = c_str[181];
			}
			if( good == false ) {
				if( c_str[182] == 0 ) {
					str[0] = 182;
					good = true;
				} else str[183] = c_str[182];
			}
			if( good == false ) {
				if( c_str[183] == 0 ) {
					str[0] = 183;
					good = true;
				} else str[184] = c_str[183];
			}
			if( good == false ) {
				if( c_str[184] == 0 ) {
					str[0] = 184;
					good = true;
				} else str[185] = c_str[184];
			}
			if( good == false ) {
				if( c_str[185] == 0 ) {
					str[0] = 185;
					good = true;
				} else str[186] = c_str[185];
			}
			if( good == false ) {
				if( c_str[186] == 0 ) {
					str[0] = 186;
					good = true;
				} else str[187] = c_str[186];
			}
			if( good == false ) {
				if( c_str[187] == 0 ) {
					str[0] = 187;
					good = true;
				} else str[188] = c_str[187];
			}
			if( good == false ) {
				if( c_str[188] == 0 ) {
					str[0] = 188;
					good = true;
				} else str[189] = c_str[188];
			}
			if( good == false ) {
				if( c_str[189] == 0 ) {
					str[0] = 189;
					good = true;
				} else str[190] = c_str[189];
			}
			if( good == false ) {
				if( c_str[190] == 0 ) {
					str[0] = 190;
					good = true;
				} else str[191] = c_str[190];
			}
			if( good == false ) {
				if( c_str[191] == 0 ) {
					str[0] = 191;
					good = true;
				} else str[192] = c_str[191];
			}
			if( good == false ) {
				if( c_str[192] == 0 ) {
					str[0] = 192;
					good = true;
				} else str[193] = c_str[192];
			}
			if( good == false ) {
				if( c_str[193] == 0 ) {
					str[0] = 193;
					good = true;
				} else str[194] = c_str[193];
			}
			if( good == false ) {
				if( c_str[194] == 0 ) {
					str[0] = 194;
					good = true;
				} else str[195] = c_str[194];
			}
			if( good == false ) {
				if( c_str[195] == 0 ) {
					str[0] = 195;
					good = true;
				} else str[196] = c_str[195];
			}
			if( good == false ) {
				if( c_str[196] == 0 ) {
					str[0] = 196;
					good = true;
				} else str[197] = c_str[196];
			}
			if( good == false ) {
				if( c_str[197] == 0 ) {
					str[0] = 197;
					good = true;
				} else str[198] = c_str[197];
			}
			if( good == false ) {
				if( c_str[198] == 0 ) {
					str[0] = 198;
					good = true;
				} else str[199] = c_str[198];
			}
			if( good == false ) {
				if( c_str[199] == 0 ) {
					str[0] = 199;
					good = true;
				} else str[200] = c_str[199];
			}
			if( good == false ) {
				if( c_str[200] == 0 ) {
					str[0] = 200;
					good = true;
				} else str[201] = c_str[200];
			}
			if( good == false ) {
				if( c_str[201] == 0 ) {
					str[0] = 201;
					good = true;
				} else str[202] = c_str[201];
			}
			if( good == false ) {
				if( c_str[202] == 0 ) {
					str[0] = 202;
					good = true;
				} else str[203] = c_str[202];
			}
			if( good == false ) {
				if( c_str[203] == 0 ) {
					str[0] = 203;
					good = true;
				} else str[204] = c_str[203];
			}
			if( good == false ) {
				if( c_str[204] == 0 ) {
					str[0] = 204;
					good = true;
				} else str[205] = c_str[204];
			}
			if( good == false ) {
				if( c_str[205] == 0 ) {
					str[0] = 205;
					good = true;
				} else str[206] = c_str[205];
			}
			if( good == false ) {
				if( c_str[206] == 0 ) {
					str[0] = 206;
					good = true;
				} else str[207] = c_str[206];
			}
			if( good == false ) {
				if( c_str[207] == 0 ) {
					str[0] = 207;
					good = true;
				} else str[208] = c_str[207];
			}
			if( good == false ) {
				if( c_str[208] == 0 ) {
					str[0] = 208;
					good = true;
				} else str[209] = c_str[208];
			}
			if( good == false ) {
				if( c_str[209] == 0 ) {
					str[0] = 209;
					good = true;
				} else str[210] = c_str[209];
			}
			if( good == false ) {
				if( c_str[210] == 0 ) {
					str[0] = 210;
					good = true;
				} else str[211] = c_str[210];
			}
			if( good == false ) {
				if( c_str[211] == 0 ) {
					str[0] = 211;
					good = true;
				} else str[212] = c_str[211];
			}
			if( good == false ) {
				if( c_str[212] == 0 ) {
					str[0] = 212;
					good = true;
				} else str[213] = c_str[212];
			}
			if( good == false ) {
				if( c_str[213] == 0 ) {
					str[0] = 213;
					good = true;
				} else str[214] = c_str[213];
			}
			if( good == false ) {
				if( c_str[214] == 0 ) {
					str[0] = 214;
					good = true;
				} else str[215] = c_str[214];
			}
			if( good == false ) {
				if( c_str[215] == 0 ) {
					str[0] = 215;
					good = true;
				} else str[216] = c_str[215];
			}
			if( good == false ) {
				if( c_str[216] == 0 ) {
					str[0] = 216;
					good = true;
				} else str[217] = c_str[216];
			}
			if( good == false ) {
				if( c_str[217] == 0 ) {
					str[0] = 217;
					good = true;
				} else str[218] = c_str[217];
			}
			if( good == false ) {
				if( c_str[218] == 0 ) {
					str[0] = 218;
					good = true;
				} else str[219] = c_str[218];
			}
			if( good == false ) {
				if( c_str[219] == 0 ) {
					str[0] = 219;
					good = true;
				} else str[220] = c_str[219];
			}
			if( good == false ) {
				if( c_str[220] == 0 ) {
					str[0] = 220;
					good = true;
				} else str[221] = c_str[220];
			}
			if( good == false ) {
				if( c_str[221] == 0 ) {
					str[0] = 221;
					good = true;
				} else str[222] = c_str[221];
			}
			if( good == false ) {
				if( c_str[222] == 0 ) {
					str[0] = 222;
					good = true;
				} else str[223] = c_str[222];
			}
			if( good == false ) {
				if( c_str[223] == 0 ) {
					str[0] = 223;
					good = true;
				} else str[224] = c_str[223];
			}
			if( good == false ) {
				if( c_str[224] == 0 ) {
					str[0] = 224;
					good = true;
				} else str[225] = c_str[224];
			}
			if( good == false ) {
				if( c_str[225] == 0 ) {
					str[0] = 225;
					good = true;
				} else str[226] = c_str[225];
			}
			if( good == false ) {
				if( c_str[226] == 0 ) {
					str[0] = 226;
					good = true;
				} else str[227] = c_str[226];
			}
			if( good == false ) {
				if( c_str[227] == 0 ) {
					str[0] = 227;
					good = true;
				} else str[228] = c_str[227];
			}
			if( good == false ) {
				if( c_str[228] == 0 ) {
					str[0] = 228;
					good = true;
				} else str[229] = c_str[228];
			}
			if( good == false ) {
				if( c_str[229] == 0 ) {
					str[0] = 229;
					good = true;
				} else str[230] = c_str[229];
			}
			if( good == false ) {
				if( c_str[230] == 0 ) {
					str[0] = 230;
					good = true;
				} else str[231] = c_str[230];
			}
			if( good == false ) {
				if( c_str[231] == 0 ) {
					str[0] = 231;
					good = true;
				} else str[232] = c_str[231];
			}
			if( good == false ) {
				if( c_str[232] == 0 ) {
					str[0] = 232;
					good = true;
				} else str[233] = c_str[232];
			}
			if( good == false ) {
				if( c_str[233] == 0 ) {
					str[0] = 233;
					good = true;
				} else str[234] = c_str[233];
			}
			if( good == false ) {
				if( c_str[234] == 0 ) {
					str[0] = 234;
					good = true;
				} else str[235] = c_str[234];
			}
			if( good == false ) {
				if( c_str[235] == 0 ) {
					str[0] = 235;
					good = true;
				} else str[236] = c_str[235];
			}
			if( good == false ) {
				if( c_str[236] == 0 ) {
					str[0] = 236;
					good = true;
				} else str[237] = c_str[236];
			}
			if( good == false ) {
				if( c_str[237] == 0 ) {
					str[0] = 237;
					good = true;
				} else str[238] = c_str[237];
			}
			if( good == false ) {
				if( c_str[238] == 0 ) {
					str[0] = 238;
					good = true;
				} else str[239] = c_str[238];
			}
			if( good == false ) {
				if( c_str[239] == 0 ) {
					str[0] = 239;
					good = true;
				} else str[240] = c_str[239];
			}
			if( good == false ) {
				if( c_str[240] == 0 ) {
					str[0] = 240;
					good = true;
				} else str[241] = c_str[240];
			}
			if( good == false ) {
				if( c_str[241] == 0 ) {
					str[0] = 241;
					good = true;
				} else str[242] = c_str[241];
			}
			if( good == false ) {
				if( c_str[242] == 0 ) {
					str[0] = 242;
					good = true;
				} else str[243] = c_str[242];
			}
			if( good == false ) {
				if( c_str[243] == 0 ) {
					str[0] = 243;
					good = true;
				} else str[244] = c_str[243];
			}
			if( good == false ) {
				if( c_str[244] == 0 ) {
					str[0] = 244;
					good = true;
				} else str[245] = c_str[244];
			}
			if( good == false ) {
				if( c_str[245] == 0 ) {
					str[0] = 245;
					good = true;
				} else str[246] = c_str[245];
			}
			if( good == false ) {
				if( c_str[246] == 0 ) {
					str[0] = 246;
					good = true;
				} else str[247] = c_str[246];
			}
			if( good == false ) {
				if( c_str[247] == 0 ) {
					str[0] = 247;
					good = true;
				} else str[248] = c_str[247];
			}
			if( good == false ) {
				if( c_str[248] == 0 ) {
					str[0] = 248;
					good = true;
				} else str[249] = c_str[248];
			}
			if( good == false ) {
				if( c_str[249] == 0 ) {
					str[0] = 249;
					good = true;
				} else str[250] = c_str[249];
			}
			if( good == false ) {
				if( c_str[250] == 0 ) {
					str[0] = 250;
					good = true;
				} else str[251] = c_str[250];
			}
			if( good == false ) {
				if( c_str[251] == 0 ) {
					str[0] = 251;
					good = true;
				} else str[252] = c_str[251];
			}
			if( good == false ) {
				if( c_str[252] == 0 ) {
					str[0] = 252;
					good = true;
				} else str[253] = c_str[252];
			}
			if( good == false ) {
				if( c_str[253] == 0 ) {
					str[0] = 253;
					good = true;
				} else str[254] = c_str[253];
			}
			if( good == false ) {
				if( c_str[254] == 0 ) {
					str[0] = 254;
					good = true;
				} else str[255] = c_str[254];
			}
			if( good == false ) {
				if( c_str[255] == 0 ) {
					str[0] = 255;
					good = true;
				} else str[256] = c_str[255];
			}

			if( 1 <= *str ) putc( str[1], stdout );
			if( 2 <= *str ) putc( str[2], stdout );
			if( 3 <= *str ) putc( str[3], stdout );
			if( 4 <= *str ) putc( str[4], stdout );
			if( 5 <= *str ) putc( str[5], stdout );
			if( 6 <= *str ) putc( str[6], stdout );
			if( 7 <= *str ) putc( str[7], stdout );
			if( 8 <= *str ) putc( str[8], stdout );
			if( 9 <= *str ) putc( str[9], stdout );
			if( 10 <= *str ) putc( str[10], stdout );
			if( 11 <= *str ) putc( str[11], stdout );
			if( 12 <= *str ) putc( str[12], stdout );
			if( 13 <= *str ) putc( str[13], stdout );
			if( 14 <= *str ) putc( str[14], stdout );
			if( 15 <= *str ) putc( str[15], stdout );
			if( 16 <= *str ) putc( str[16], stdout );
			if( 17 <= *str ) putc( str[17], stdout );
			if( 18 <= *str ) putc( str[18], stdout );
			if( 19 <= *str ) putc( str[19], stdout );
			if( 20 <= *str ) putc( str[20], stdout );
			if( 21 <= *str ) putc( str[21], stdout );
			if( 22 <= *str ) putc( str[22], stdout );
			if( 23 <= *str ) putc( str[23], stdout );
			if( 24 <= *str ) putc( str[24], stdout );
			if( 25 <= *str ) putc( str[25], stdout );
			if( 26 <= *str ) putc( str[26], stdout );
			if( 27 <= *str ) putc( str[27], stdout );
			if( 28 <= *str ) putc( str[28], stdout );
			if( 29 <= *str ) putc( str[29], stdout );
			if( 30 <= *str ) putc( str[30], stdout );
			if( 31 <= *str ) putc( str[31], stdout );
			if( 32 <= *str ) putc( str[32], stdout );
			if( 33 <= *str ) putc( str[33], stdout );
			if( 34 <= *str ) putc( str[34], stdout );
			if( 35 <= *str ) putc( str[35], stdout );
			if( 36 <= *str ) putc( str[36], stdout );
			if( 37 <= *str ) putc( str[37], stdout );
			if( 38 <= *str ) putc( str[38], stdout );
			if( 39 <= *str ) putc( str[39], stdout );
			if( 40 <= *str ) putc( str[40], stdout );
			if( 41 <= *str ) putc( str[41], stdout );
			if( 42 <= *str ) putc( str[42], stdout );
			if( 43 <= *str ) putc( str[43], stdout );
			if( 44 <= *str ) putc( str[44], stdout );
			if( 45 <= *str ) putc( str[45], stdout );
			if( 46 <= *str ) putc( str[46], stdout );
			if( 47 <= *str ) putc( str[47], stdout );
			if( 48 <= *str ) putc( str[48], stdout );
			if( 49 <= *str ) putc( str[49], stdout );
			if( 50 <= *str ) putc( str[50], stdout );
			if( 51 <= *str ) putc( str[51], stdout );
			if( 52 <= *str ) putc( str[52], stdout );
			if( 53 <= *str ) putc( str[53], stdout );
			if( 54 <= *str ) putc( str[54], stdout );
			if( 55 <= *str ) putc( str[55], stdout );
			if( 56 <= *str ) putc( str[56], stdout );
			if( 57 <= *str ) putc( str[57], stdout );
			if( 58 <= *str ) putc( str[58], stdout );
			if( 59 <= *str ) putc( str[59], stdout );
			if( 60 <= *str ) putc( str[60], stdout );
			if( 61 <= *str ) putc( str[61], stdout );
			if( 62 <= *str ) putc( str[62], stdout );
			if( 63 <= *str ) putc( str[63], stdout );
			if( 64 <= *str ) putc( str[64], stdout );
			if( 65 <= *str ) putc( str[65], stdout );
			if( 66 <= *str ) putc( str[66], stdout );
			if( 67 <= *str ) putc( str[67], stdout );
			if( 68 <= *str ) putc( str[68], stdout );
			if( 69 <= *str ) putc( str[69], stdout );
			if( 70 <= *str ) putc( str[70], stdout );
			if( 71 <= *str ) putc( str[71], stdout );
			if( 72 <= *str ) putc( str[72], stdout );
			if( 73 <= *str ) putc( str[73], stdout );
			if( 74 <= *str ) putc( str[74], stdout );
			if( 75 <= *str ) putc( str[75], stdout );
			if( 76 <= *str ) putc( str[76], stdout );
			if( 77 <= *str ) putc( str[77], stdout );
			if( 78 <= *str ) putc( str[78], stdout );
			if( 79 <= *str ) putc( str[79], stdout );
			if( 80 <= *str ) putc( str[80], stdout );
			if( 81 <= *str ) putc( str[81], stdout );
			if( 82 <= *str ) putc( str[82], stdout );
			if( 83 <= *str ) putc( str[83], stdout );
			if( 84 <= *str ) putc( str[84], stdout );
			if( 85 <= *str ) putc( str[85], stdout );
			if( 86 <= *str ) putc( str[86], stdout );
			if( 87 <= *str ) putc( str[87], stdout );
			if( 88 <= *str ) putc( str[88], stdout );
			if( 89 <= *str ) putc( str[89], stdout );
			if( 90 <= *str ) putc( str[90], stdout );
			if( 91 <= *str ) putc( str[91], stdout );
			if( 92 <= *str ) putc( str[92], stdout );
			if( 93 <= *str ) putc( str[93], stdout );
			if( 94 <= *str ) putc( str[94], stdout );
			if( 95 <= *str ) putc( str[95], stdout );
			if( 96 <= *str ) putc( str[96], stdout );
			if( 97 <= *str ) putc( str[97], stdout );
			if( 98 <= *str ) putc( str[98], stdout );
			if( 99 <= *str ) putc( str[99], stdout );
			if( 100 <= *str ) putc( str[100], stdout );
			if( 101 <= *str ) putc( str[101], stdout );
			if( 102 <= *str ) putc( str[102], stdout );
			if( 103 <= *str ) putc( str[103], stdout );
			if( 104 <= *str ) putc( str[104], stdout );
			if( 105 <= *str ) putc( str[105], stdout );
			if( 106 <= *str ) putc( str[106], stdout );
			if( 107 <= *str ) putc( str[107], stdout );
			if( 108 <= *str ) putc( str[108], stdout );
			if( 109 <= *str ) putc( str[109], stdout );
			if( 110 <= *str ) putc( str[110], stdout );
			if( 111 <= *str ) putc( str[111], stdout );
			if( 112 <= *str ) putc( str[112], stdout );
			if( 113 <= *str ) putc( str[113], stdout );
			if( 114 <= *str ) putc( str[114], stdout );
			if( 115 <= *str ) putc( str[115], stdout );
			if( 116 <= *str ) putc( str[116], stdout );
			if( 117 <= *str ) putc( str[117], stdout );
			if( 118 <= *str ) putc( str[118], stdout );
			if( 119 <= *str ) putc( str[119], stdout );
			if( 120 <= *str ) putc( str[120], stdout );
			if( 121 <= *str ) putc( str[121], stdout );
			if( 122 <= *str ) putc( str[122], stdout );
			if( 123 <= *str ) putc( str[123], stdout );
			if( 124 <= *str ) putc( str[124], stdout );
			if( 125 <= *str ) putc( str[125], stdout );
			if( 126 <= *str ) putc( str[126], stdout );
			if( 127 <= *str ) putc( str[127], stdout );
			if( 128 <= *str ) putc( str[128], stdout );
			if( 129 <= *str ) putc( str[129], stdout );
			if( 130 <= *str ) putc( str[130], stdout );
			if( 131 <= *str ) putc( str[131], stdout );
			if( 132 <= *str ) putc( str[132], stdout );
			if( 133 <= *str ) putc( str[133], stdout );
			if( 134 <= *str ) putc( str[134], stdout );
			if( 135 <= *str ) putc( str[135], stdout );
			if( 136 <= *str ) putc( str[136], stdout );
			if( 137 <= *str ) putc( str[137], stdout );
			if( 138 <= *str ) putc( str[138], stdout );
			if( 139 <= *str ) putc( str[139], stdout );
			if( 140 <= *str ) putc( str[140], stdout );
			if( 141 <= *str ) putc( str[141], stdout );
			if( 142 <= *str ) putc( str[142], stdout );
			if( 143 <= *str ) putc( str[143], stdout );
			if( 144 <= *str ) putc( str[144], stdout );
			if( 145 <= *str ) putc( str[145], stdout );
			if( 146 <= *str ) putc( str[146], stdout );
			if( 147 <= *str ) putc( str[147], stdout );
			if( 148 <= *str ) putc( str[148], stdout );
			if( 149 <= *str ) putc( str[149], stdout );
			if( 150 <= *str ) putc( str[150], stdout );
			if( 151 <= *str ) putc( str[151], stdout );
			if( 152 <= *str ) putc( str[152], stdout );
			if( 153 <= *str ) putc( str[153], stdout );
			if( 154 <= *str ) putc( str[154], stdout );
			if( 155 <= *str ) putc( str[155], stdout );
			if( 156 <= *str ) putc( str[156], stdout );
			if( 157 <= *str ) putc( str[157], stdout );
			if( 158 <= *str ) putc( str[158], stdout );
			if( 159 <= *str ) putc( str[159], stdout );
			if( 160 <= *str ) putc( str[160], stdout );
			if( 161 <= *str ) putc( str[161], stdout );
			if( 162 <= *str ) putc( str[162], stdout );
			if( 163 <= *str ) putc( str[163], stdout );
			if( 164 <= *str ) putc( str[164], stdout );
			if( 165 <= *str ) putc( str[165], stdout );
			if( 166 <= *str ) putc( str[166], stdout );
			if( 167 <= *str ) putc( str[167], stdout );
			if( 168 <= *str ) putc( str[168], stdout );
			if( 169 <= *str ) putc( str[169], stdout );
			if( 170 <= *str ) putc( str[170], stdout );
			if( 171 <= *str ) putc( str[171], stdout );
			if( 172 <= *str ) putc( str[172], stdout );
			if( 173 <= *str ) putc( str[173], stdout );
			if( 174 <= *str ) putc( str[174], stdout );
			if( 175 <= *str ) putc( str[175], stdout );
			if( 176 <= *str ) putc( str[176], stdout );
			if( 177 <= *str ) putc( str[177], stdout );
			if( 178 <= *str ) putc( str[178], stdout );
			if( 179 <= *str ) putc( str[179], stdout );
			if( 180 <= *str ) putc( str[180], stdout );
			if( 181 <= *str ) putc( str[181], stdout );
			if( 182 <= *str ) putc( str[182], stdout );
			if( 183 <= *str ) putc( str[183], stdout );
			if( 184 <= *str ) putc( str[184], stdout );
			if( 185 <= *str ) putc( str[185], stdout );
			if( 186 <= *str ) putc( str[186], stdout );
			if( 187 <= *str ) putc( str[187], stdout );
			if( 188 <= *str ) putc( str[188], stdout );
			if( 189 <= *str ) putc( str[189], stdout );
			if( 190 <= *str ) putc( str[190], stdout );
			if( 191 <= *str ) putc( str[191], stdout );
			if( 192 <= *str ) putc( str[192], stdout );
			if( 193 <= *str ) putc( str[193], stdout );
			if( 194 <= *str ) putc( str[194], stdout );
			if( 195 <= *str ) putc( str[195], stdout );
			if( 196 <= *str ) putc( str[196], stdout );
			if( 197 <= *str ) putc( str[197], stdout );
			if( 198 <= *str ) putc( str[198], stdout );
			if( 199 <= *str ) putc( str[199], stdout );
			if( 200 <= *str ) putc( str[200], stdout );
			if( 201 <= *str ) putc( str[201], stdout );
			if( 202 <= *str ) putc( str[202], stdout );
			if( 203 <= *str ) putc( str[203], stdout );
			if( 204 <= *str ) putc( str[204], stdout );
			if( 205 <= *str ) putc( str[205], stdout );
			if( 206 <= *str ) putc( str[206], stdout );
			if( 207 <= *str ) putc( str[207], stdout );
			if( 208 <= *str ) putc( str[208], stdout );
			if( 209 <= *str ) putc( str[209], stdout );
			if( 210 <= *str ) putc( str[210], stdout );
			if( 211 <= *str ) putc( str[211], stdout );
			if( 212 <= *str ) putc( str[212], stdout );
			if( 213 <= *str ) putc( str[213], stdout );
			if( 214 <= *str ) putc( str[214], stdout );
			if( 215 <= *str ) putc( str[215], stdout );
			if( 216 <= *str ) putc( str[216], stdout );
			if( 217 <= *str ) putc( str[217], stdout );
			if( 218 <= *str ) putc( str[218], stdout );
			if( 219 <= *str ) putc( str[219], stdout );
			if( 220 <= *str ) putc( str[220], stdout );
			if( 221 <= *str ) putc( str[221], stdout );
			if( 222 <= *str ) putc( str[222], stdout );
			if( 223 <= *str ) putc( str[223], stdout );
			if( 224 <= *str ) putc( str[224], stdout );
			if( 225 <= *str ) putc( str[225], stdout );
			if( 226 <= *str ) putc( str[226], stdout );
			if( 227 <= *str ) putc( str[227], stdout );
			if( 228 <= *str ) putc( str[228], stdout );
			if( 229 <= *str ) putc( str[229], stdout );
			if( 230 <= *str ) putc( str[230], stdout );
			if( 231 <= *str ) putc( str[231], stdout );
			if( 232 <= *str ) putc( str[232], stdout );
			if( 233 <= *str ) putc( str[233], stdout );
			if( 234 <= *str ) putc( str[234], stdout );
			if( 235 <= *str ) putc( str[235], stdout );
			if( 236 <= *str ) putc( str[236], stdout );
			if( 237 <= *str ) putc( str[237], stdout );
			if( 238 <= *str ) putc( str[238], stdout );
			if( 239 <= *str ) putc( str[239], stdout );
			if( 240 <= *str ) putc( str[240], stdout );
			if( 241 <= *str ) putc( str[241], stdout );
			if( 242 <= *str ) putc( str[242], stdout );
			if( 243 <= *str ) putc( str[243], stdout );
			if( 244 <= *str ) putc( str[244], stdout );
			if( 245 <= *str ) putc( str[245], stdout );
			if( 246 <= *str ) putc( str[246], stdout );
			if( 247 <= *str ) putc( str[247], stdout );
			if( 248 <= *str ) putc( str[248], stdout );
			if( 249 <= *str ) putc( str[249], stdout );
			if( 250 <= *str ) putc( str[250], stdout );
			if( 251 <= *str ) putc( str[251], stdout );
			if( 252 <= *str ) putc( str[252], stdout );
			if( 253 <= *str ) putc( str[253], stdout );
			if( 254 <= *str ) putc( str[254], stdout );
			if( 255 <= *str ) putc( str[255], stdout );
			
			c = 0;
			*filename = 0;
			
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			if( c != '\n' and c != EOF )
				c = getc( stdin );
			if( c != '\n' and c != EOF ) {
				++*filename;
				filename[*filename] = static_cast< uint8_t >( c );
			}
			// Fallthrough
			
		case 'S' :
		case 's' :
			if( 1 <= *number ) putc( number[1], tempfileptr );
			if( 2 <= *number ) putc( number[2], tempfileptr );
			if( 3 <= *number ) putc( number[3], tempfileptr );
			if( 4 <= *number ) putc( number[4], tempfileptr );
			if( 5 <= *number ) putc( number[5], tempfileptr );
			if( 6 <= *number ) putc( number[6], tempfileptr );
			if( 7 <= *number ) putc( number[7], tempfileptr );
			if( 8 <= *number ) putc( number[8], tempfileptr );
			if( 9 <= *number ) putc( number[9], tempfileptr );
			if( 10 <= *number ) putc( number[10], tempfileptr );
			if( 11 <= *number ) putc( number[11], tempfileptr );
			if( 12 <= *number ) putc( number[12], tempfileptr );
			if( 13 <= *number ) putc( number[13], tempfileptr );
			if( 14 <= *number ) putc( number[14], tempfileptr );
			if( 15 <= *number ) putc( number[15], tempfileptr );
			if( 16 <= *number ) putc( number[16], tempfileptr );
			if( 17 <= *number ) putc( number[17], tempfileptr );
			if( 18 <= *number ) putc( number[18], tempfileptr );
			if( 19 <= *number ) putc( number[19], tempfileptr );
			if( 20 <= *number ) putc( number[20], tempfileptr );
			if( 21 <= *number ) putc( number[21], tempfileptr );
			if( 22 <= *number ) putc( number[22], tempfileptr );
			if( 23 <= *number ) putc( number[23], tempfileptr );
			if( 24 <= *number ) putc( number[24], tempfileptr );
			if( 25 <= *number ) putc( number[25], tempfileptr );
			if( 26 <= *number ) putc( number[26], tempfileptr );
			if( 27 <= *number ) putc( number[27], tempfileptr );
			if( 28 <= *number ) putc( number[28], tempfileptr );
			if( 29 <= *number ) putc( number[29], tempfileptr );
			if( 30 <= *number ) putc( number[30], tempfileptr );
			if( 31 <= *number ) putc( number[31], tempfileptr );
			if( 32 <= *number ) putc( number[32], tempfileptr );
			if( 33 <= *number ) putc( number[33], tempfileptr );
			if( 34 <= *number ) putc( number[34], tempfileptr );
			if( 35 <= *number ) putc( number[35], tempfileptr );
			if( 36 <= *number ) putc( number[36], tempfileptr );
			if( 37 <= *number ) putc( number[37], tempfileptr );
			if( 38 <= *number ) putc( number[38], tempfileptr );
			if( 39 <= *number ) putc( number[39], tempfileptr );
			if( 40 <= *number ) putc( number[40], tempfileptr );
			if( 41 <= *number ) putc( number[41], tempfileptr );
			if( 42 <= *number ) putc( number[42], tempfileptr );
			if( 43 <= *number ) putc( number[43], tempfileptr );
			if( 44 <= *number ) putc( number[44], tempfileptr );
			if( 45 <= *number ) putc( number[45], tempfileptr );
			if( 46 <= *number ) putc( number[46], tempfileptr );
			if( 47 <= *number ) putc( number[47], tempfileptr );
			if( 48 <= *number ) putc( number[48], tempfileptr );
			if( 49 <= *number ) putc( number[49], tempfileptr );
			if( 50 <= *number ) putc( number[50], tempfileptr );
			if( 51 <= *number ) putc( number[51], tempfileptr );
			if( 52 <= *number ) putc( number[52], tempfileptr );
			if( 53 <= *number ) putc( number[53], tempfileptr );
			if( 54 <= *number ) putc( number[54], tempfileptr );
			if( 55 <= *number ) putc( number[55], tempfileptr );
			if( 56 <= *number ) putc( number[56], tempfileptr );
			if( 57 <= *number ) putc( number[57], tempfileptr );
			if( 58 <= *number ) putc( number[58], tempfileptr );
			if( 59 <= *number ) putc( number[59], tempfileptr );
			if( 60 <= *number ) putc( number[60], tempfileptr );
			if( 61 <= *number ) putc( number[61], tempfileptr );
			if( 62 <= *number ) putc( number[62], tempfileptr );
			if( 63 <= *number ) putc( number[63], tempfileptr );
			if( 64 <= *number ) putc( number[64], tempfileptr );
			if( 65 <= *number ) putc( number[65], tempfileptr );
			if( 66 <= *number ) putc( number[66], tempfileptr );
			if( 67 <= *number ) putc( number[67], tempfileptr );
			if( 68 <= *number ) putc( number[68], tempfileptr );
			if( 69 <= *number ) putc( number[69], tempfileptr );
			if( 70 <= *number ) putc( number[70], tempfileptr );
			if( 71 <= *number ) putc( number[71], tempfileptr );
			if( 72 <= *number ) putc( number[72], tempfileptr );
			if( 73 <= *number ) putc( number[73], tempfileptr );
			if( 74 <= *number ) putc( number[74], tempfileptr );
			if( 75 <= *number ) putc( number[75], tempfileptr );
			if( 76 <= *number ) putc( number[76], tempfileptr );
			if( 77 <= *number ) putc( number[77], tempfileptr );
			if( 78 <= *number ) putc( number[78], tempfileptr );
			if( 79 <= *number ) putc( number[79], tempfileptr );
			if( 80 <= *number ) putc( number[80], tempfileptr );
			if( 81 <= *number ) putc( number[81], tempfileptr );
			if( 82 <= *number ) putc( number[82], tempfileptr );
			if( 83 <= *number ) putc( number[83], tempfileptr );
			if( 84 <= *number ) putc( number[84], tempfileptr );
			if( 85 <= *number ) putc( number[85], tempfileptr );
			if( 86 <= *number ) putc( number[86], tempfileptr );
			if( 87 <= *number ) putc( number[87], tempfileptr );
			if( 88 <= *number ) putc( number[88], tempfileptr );
			if( 89 <= *number ) putc( number[89], tempfileptr );
			if( 90 <= *number ) putc( number[90], tempfileptr );
			if( 91 <= *number ) putc( number[91], tempfileptr );
			if( 92 <= *number ) putc( number[92], tempfileptr );
			if( 93 <= *number ) putc( number[93], tempfileptr );
			if( 94 <= *number ) putc( number[94], tempfileptr );
			if( 95 <= *number ) putc( number[95], tempfileptr );
			if( 96 <= *number ) putc( number[96], tempfileptr );
			if( 97 <= *number ) putc( number[97], tempfileptr );
			if( 98 <= *number ) putc( number[98], tempfileptr );
			if( 99 <= *number ) putc( number[99], tempfileptr );
			if( 100 <= *number ) putc( number[100], tempfileptr );
			if( 101 <= *number ) putc( number[101], tempfileptr );
			if( 102 <= *number ) putc( number[102], tempfileptr );
			if( 103 <= *number ) putc( number[103], tempfileptr );
			if( 104 <= *number ) putc( number[104], tempfileptr );
			if( 105 <= *number ) putc( number[105], tempfileptr );
			if( 106 <= *number ) putc( number[106], tempfileptr );
			if( 107 <= *number ) putc( number[107], tempfileptr );
			if( 108 <= *number ) putc( number[108], tempfileptr );
			if( 109 <= *number ) putc( number[109], tempfileptr );
			if( 110 <= *number ) putc( number[110], tempfileptr );
			if( 111 <= *number ) putc( number[111], tempfileptr );
			if( 112 <= *number ) putc( number[112], tempfileptr );
			if( 113 <= *number ) putc( number[113], tempfileptr );
			if( 114 <= *number ) putc( number[114], tempfileptr );
			if( 115 <= *number ) putc( number[115], tempfileptr );
			if( 116 <= *number ) putc( number[116], tempfileptr );
			if( 117 <= *number ) putc( number[117], tempfileptr );
			if( 118 <= *number ) putc( number[118], tempfileptr );
			if( 119 <= *number ) putc( number[119], tempfileptr );
			if( 120 <= *number ) putc( number[120], tempfileptr );
			if( 121 <= *number ) putc( number[121], tempfileptr );
			if( 122 <= *number ) putc( number[122], tempfileptr );
			if( 123 <= *number ) putc( number[123], tempfileptr );
			if( 124 <= *number ) putc( number[124], tempfileptr );
			if( 125 <= *number ) putc( number[125], tempfileptr );
			if( 126 <= *number ) putc( number[126], tempfileptr );
			if( 127 <= *number ) putc( number[127], tempfileptr );
			if( 128 <= *number ) putc( number[128], tempfileptr );
			if( 129 <= *number ) putc( number[129], tempfileptr );
			if( 130 <= *number ) putc( number[130], tempfileptr );
			if( 131 <= *number ) putc( number[131], tempfileptr );
			if( 132 <= *number ) putc( number[132], tempfileptr );
			if( 133 <= *number ) putc( number[133], tempfileptr );
			if( 134 <= *number ) putc( number[134], tempfileptr );
			if( 135 <= *number ) putc( number[135], tempfileptr );
			if( 136 <= *number ) putc( number[136], tempfileptr );
			if( 137 <= *number ) putc( number[137], tempfileptr );
			if( 138 <= *number ) putc( number[138], tempfileptr );
			if( 139 <= *number ) putc( number[139], tempfileptr );
			if( 140 <= *number ) putc( number[140], tempfileptr );
			if( 141 <= *number ) putc( number[141], tempfileptr );
			if( 142 <= *number ) putc( number[142], tempfileptr );
			if( 143 <= *number ) putc( number[143], tempfileptr );
			if( 144 <= *number ) putc( number[144], tempfileptr );
			if( 145 <= *number ) putc( number[145], tempfileptr );
			if( 146 <= *number ) putc( number[146], tempfileptr );
			if( 147 <= *number ) putc( number[147], tempfileptr );
			if( 148 <= *number ) putc( number[148], tempfileptr );
			if( 149 <= *number ) putc( number[149], tempfileptr );
			if( 150 <= *number ) putc( number[150], tempfileptr );
			if( 151 <= *number ) putc( number[151], tempfileptr );
			if( 152 <= *number ) putc( number[152], tempfileptr );
			if( 153 <= *number ) putc( number[153], tempfileptr );
			if( 154 <= *number ) putc( number[154], tempfileptr );
			if( 155 <= *number ) putc( number[155], tempfileptr );
			if( 156 <= *number ) putc( number[156], tempfileptr );
			if( 157 <= *number ) putc( number[157], tempfileptr );
			if( 158 <= *number ) putc( number[158], tempfileptr );
			if( 159 <= *number ) putc( number[159], tempfileptr );
			if( 160 <= *number ) putc( number[160], tempfileptr );
			if( 161 <= *number ) putc( number[161], tempfileptr );
			if( 162 <= *number ) putc( number[162], tempfileptr );
			if( 163 <= *number ) putc( number[163], tempfileptr );
			if( 164 <= *number ) putc( number[164], tempfileptr );
			if( 165 <= *number ) putc( number[165], tempfileptr );
			if( 166 <= *number ) putc( number[166], tempfileptr );
			if( 167 <= *number ) putc( number[167], tempfileptr );
			if( 168 <= *number ) putc( number[168], tempfileptr );
			if( 169 <= *number ) putc( number[169], tempfileptr );
			if( 170 <= *number ) putc( number[170], tempfileptr );
			if( 171 <= *number ) putc( number[171], tempfileptr );
			if( 172 <= *number ) putc( number[172], tempfileptr );
			if( 173 <= *number ) putc( number[173], tempfileptr );
			if( 174 <= *number ) putc( number[174], tempfileptr );
			if( 175 <= *number ) putc( number[175], tempfileptr );
			if( 176 <= *number ) putc( number[176], tempfileptr );
			if( 177 <= *number ) putc( number[177], tempfileptr );
			if( 178 <= *number ) putc( number[178], tempfileptr );
			if( 179 <= *number ) putc( number[179], tempfileptr );
			if( 180 <= *number ) putc( number[180], tempfileptr );
			if( 181 <= *number ) putc( number[181], tempfileptr );
			if( 182 <= *number ) putc( number[182], tempfileptr );
			if( 183 <= *number ) putc( number[183], tempfileptr );
			if( 184 <= *number ) putc( number[184], tempfileptr );
			if( 185 <= *number ) putc( number[185], tempfileptr );
			if( 186 <= *number ) putc( number[186], tempfileptr );
			if( 187 <= *number ) putc( number[187], tempfileptr );
			if( 188 <= *number ) putc( number[188], tempfileptr );
			if( 189 <= *number ) putc( number[189], tempfileptr );
			if( 190 <= *number ) putc( number[190], tempfileptr );
			if( 191 <= *number ) putc( number[191], tempfileptr );
			if( 192 <= *number ) putc( number[192], tempfileptr );
			if( 193 <= *number ) putc( number[193], tempfileptr );
			if( 194 <= *number ) putc( number[194], tempfileptr );
			if( 195 <= *number ) putc( number[195], tempfileptr );
			if( 196 <= *number ) putc( number[196], tempfileptr );
			if( 197 <= *number ) putc( number[197], tempfileptr );
			if( 198 <= *number ) putc( number[198], tempfileptr );
			if( 199 <= *number ) putc( number[199], tempfileptr );
			if( 200 <= *number ) putc( number[200], tempfileptr );
			if( 201 <= *number ) putc( number[201], tempfileptr );
			if( 202 <= *number ) putc( number[202], tempfileptr );
			if( 203 <= *number ) putc( number[203], tempfileptr );
			if( 204 <= *number ) putc( number[204], tempfileptr );
			if( 205 <= *number ) putc( number[205], tempfileptr );
			if( 206 <= *number ) putc( number[206], tempfileptr );
			if( 207 <= *number ) putc( number[207], tempfileptr );
			if( 208 <= *number ) putc( number[208], tempfileptr );
			if( 209 <= *number ) putc( number[209], tempfileptr );
			if( 210 <= *number ) putc( number[210], tempfileptr );
			if( 211 <= *number ) putc( number[211], tempfileptr );
			if( 212 <= *number ) putc( number[212], tempfileptr );
			if( 213 <= *number ) putc( number[213], tempfileptr );
			if( 214 <= *number ) putc( number[214], tempfileptr );
			if( 215 <= *number ) putc( number[215], tempfileptr );
			if( 216 <= *number ) putc( number[216], tempfileptr );
			if( 217 <= *number ) putc( number[217], tempfileptr );
			if( 218 <= *number ) putc( number[218], tempfileptr );
			if( 219 <= *number ) putc( number[219], tempfileptr );
			if( 220 <= *number ) putc( number[220], tempfileptr );
			if( 221 <= *number ) putc( number[221], tempfileptr );
			if( 222 <= *number ) putc( number[222], tempfileptr );
			if( 223 <= *number ) putc( number[223], tempfileptr );
			if( 224 <= *number ) putc( number[224], tempfileptr );
			if( 225 <= *number ) putc( number[225], tempfileptr );
			if( 226 <= *number ) putc( number[226], tempfileptr );
			if( 227 <= *number ) putc( number[227], tempfileptr );
			if( 228 <= *number ) putc( number[228], tempfileptr );
			if( 229 <= *number ) putc( number[229], tempfileptr );
			if( 230 <= *number ) putc( number[230], tempfileptr );
			if( 231 <= *number ) putc( number[231], tempfileptr );
			if( 232 <= *number ) putc( number[232], tempfileptr );
			if( 233 <= *number ) putc( number[233], tempfileptr );
			if( 234 <= *number ) putc( number[234], tempfileptr );
			if( 235 <= *number ) putc( number[235], tempfileptr );
			if( 236 <= *number ) putc( number[236], tempfileptr );
			if( 237 <= *number ) putc( number[237], tempfileptr );
			if( 238 <= *number ) putc( number[238], tempfileptr );
			if( 239 <= *number ) putc( number[239], tempfileptr );
			if( 240 <= *number ) putc( number[240], tempfileptr );
			if( 241 <= *number ) putc( number[241], tempfileptr );
			if( 242 <= *number ) putc( number[242], tempfileptr );
			if( 243 <= *number ) putc( number[243], tempfileptr );
			if( 244 <= *number ) putc( number[244], tempfileptr );
			if( 245 <= *number ) putc( number[245], tempfileptr );
			if( 246 <= *number ) putc( number[246], tempfileptr );
			if( 247 <= *number ) putc( number[247], tempfileptr );
			if( 248 <= *number ) putc( number[248], tempfileptr );
			if( 249 <= *number ) putc( number[249], tempfileptr );
			if( 250 <= *number ) putc( number[250], tempfileptr );
			if( 251 <= *number ) putc( number[251], tempfileptr );
			if( 252 <= *number ) putc( number[252], tempfileptr );
			if( 253 <= *number ) putc( number[253], tempfileptr );
			if( 254 <= *number ) putc( number[254], tempfileptr );
			if( 255 <= *number ) putc( number[255], tempfileptr );
			
			c = getc( fileptr );
			while( c != EOF ) {
				putc( c, tempfileptr );
				c = getc( fileptr );
			}
			fclose( fileptr );
			fclose( tempfileptr );
				
			if( 1 <= *filename )
				c_str[0] = filename[1];
			else
				c_str[0] = 0;
			if( 2 <= *filename )
				c_str[1] = filename[2];
			else
				c_str[1] = 0;
			if( 3 <= *filename )
				c_str[2] = filename[3];
			else
				c_str[2] = 0;
			if( 4 <= *filename )
				c_str[3] = filename[4];
			else
				c_str[3] = 0;
			if( 5 <= *filename )
				c_str[4] = filename[5];
			else
				c_str[4] = 0;
			if( 6 <= *filename )
				c_str[5] = filename[6];
			else
				c_str[5] = 0;
			if( 7 <= *filename )
				c_str[6] = filename[7];
			else
				c_str[6] = 0;
			if( 8 <= *filename )
				c_str[7] = filename[8];
			else
				c_str[7] = 0;
			if( 9 <= *filename )
				c_str[8] = filename[9];
			else
				c_str[8] = 0;
			if( 10 <= *filename )
				c_str[9] = filename[10];
			else
				c_str[9] = 0;
			if( 11 <= *filename )
				c_str[10] = filename[11];
			else
				c_str[10] = 0;
			if( 12 <= *filename )
				c_str[11] = filename[12];
			else
				c_str[11] = 0;
			if( 13 <= *filename )
				c_str[12] = filename[13];
			else
				c_str[12] = 0;
			if( 14 <= *filename )
				c_str[13] = filename[14];
			else
				c_str[13] = 0;
			if( 15 <= *filename )
				c_str[14] = filename[15];
			else
				c_str[14] = 0;
			if( 16 <= *filename )
				c_str[15] = filename[16];
			else
				c_str[15] = 0;
			if( 17 <= *filename )
				c_str[16] = filename[17];
			else
				c_str[16] = 0;
			if( 18 <= *filename )
				c_str[17] = filename[18];
			else
				c_str[17] = 0;
			if( 19 <= *filename )
				c_str[18] = filename[19];
			else
				c_str[18] = 0;
			if( 20 <= *filename )
				c_str[19] = filename[20];
			else
				c_str[19] = 0;
			if( 21 <= *filename )
				c_str[20] = filename[21];
			else
				c_str[20] = 0;
			if( 22 <= *filename )
				c_str[21] = filename[22];
			else
				c_str[21] = 0;
			if( 23 <= *filename )
				c_str[22] = filename[23];
			else
				c_str[22] = 0;
			if( 24 <= *filename )
				c_str[23] = filename[24];
			else
				c_str[23] = 0;
			if( 25 <= *filename )
				c_str[24] = filename[25];
			else
				c_str[24] = 0;
			if( 26 <= *filename )
				c_str[25] = filename[26];
			else
				c_str[25] = 0;
			if( 27 <= *filename )
				c_str[26] = filename[27];
			else
				c_str[26] = 0;
			if( 28 <= *filename )
				c_str[27] = filename[28];
			else
				c_str[27] = 0;
			if( 29 <= *filename )
				c_str[28] = filename[29];
			else
				c_str[28] = 0;
			if( 30 <= *filename )
				c_str[29] = filename[30];
			else
				c_str[29] = 0;
			if( 31 <= *filename )
				c_str[30] = filename[31];
			else
				c_str[30] = 0;
			if( 32 <= *filename )
				c_str[31] = filename[32];
			else
				c_str[31] = 0;
			if( 33 <= *filename )
				c_str[32] = filename[33];
			else
				c_str[32] = 0;
			if( 34 <= *filename )
				c_str[33] = filename[34];
			else
				c_str[33] = 0;
			if( 35 <= *filename )
				c_str[34] = filename[35];
			else
				c_str[34] = 0;
			if( 36 <= *filename )
				c_str[35] = filename[36];
			else
				c_str[35] = 0;
			if( 37 <= *filename )
				c_str[36] = filename[37];
			else
				c_str[36] = 0;
			if( 38 <= *filename )
				c_str[37] = filename[38];
			else
				c_str[37] = 0;
			if( 39 <= *filename )
				c_str[38] = filename[39];
			else
				c_str[38] = 0;
			if( 40 <= *filename )
				c_str[39] = filename[40];
			else
				c_str[39] = 0;
			if( 41 <= *filename )
				c_str[40] = filename[41];
			else
				c_str[40] = 0;
			if( 42 <= *filename )
				c_str[41] = filename[42];
			else
				c_str[41] = 0;
			if( 43 <= *filename )
				c_str[42] = filename[43];
			else
				c_str[42] = 0;
			if( 44 <= *filename )
				c_str[43] = filename[44];
			else
				c_str[43] = 0;
			if( 45 <= *filename )
				c_str[44] = filename[45];
			else
				c_str[44] = 0;
			if( 46 <= *filename )
				c_str[45] = filename[46];
			else
				c_str[45] = 0;
			if( 47 <= *filename )
				c_str[46] = filename[47];
			else
				c_str[46] = 0;
			if( 48 <= *filename )
				c_str[47] = filename[48];
			else
				c_str[47] = 0;
			if( 49 <= *filename )
				c_str[48] = filename[49];
			else
				c_str[48] = 0;
			if( 50 <= *filename )
				c_str[49] = filename[50];
			else
				c_str[49] = 0;
			if( 51 <= *filename )
				c_str[50] = filename[51];
			else
				c_str[50] = 0;
			if( 52 <= *filename )
				c_str[51] = filename[52];
			else
				c_str[51] = 0;
			if( 53 <= *filename )
				c_str[52] = filename[53];
			else
				c_str[52] = 0;
			if( 54 <= *filename )
				c_str[53] = filename[54];
			else
				c_str[53] = 0;
			if( 55 <= *filename )
				c_str[54] = filename[55];
			else
				c_str[54] = 0;
			if( 56 <= *filename )
				c_str[55] = filename[56];
			else
				c_str[55] = 0;
			if( 57 <= *filename )
				c_str[56] = filename[57];
			else
				c_str[56] = 0;
			if( 58 <= *filename )
				c_str[57] = filename[58];
			else
				c_str[57] = 0;
			if( 59 <= *filename )
				c_str[58] = filename[59];
			else
				c_str[58] = 0;
			if( 60 <= *filename )
				c_str[59] = filename[60];
			else
				c_str[59] = 0;
			if( 61 <= *filename )
				c_str[60] = filename[61];
			else
				c_str[60] = 0;
			if( 62 <= *filename )
				c_str[61] = filename[62];
			else
				c_str[61] = 0;
			if( 63 <= *filename )
				c_str[62] = filename[63];
			else
				c_str[62] = 0;
			if( 64 <= *filename )
				c_str[63] = filename[64];
			else
				c_str[63] = 0;
			if( 65 <= *filename )
				c_str[64] = filename[65];
			else
				c_str[64] = 0;
			if( 66 <= *filename )
				c_str[65] = filename[66];
			else
				c_str[65] = 0;
			if( 67 <= *filename )
				c_str[66] = filename[67];
			else
				c_str[66] = 0;
			if( 68 <= *filename )
				c_str[67] = filename[68];
			else
				c_str[67] = 0;
			if( 69 <= *filename )
				c_str[68] = filename[69];
			else
				c_str[68] = 0;
			if( 70 <= *filename )
				c_str[69] = filename[70];
			else
				c_str[69] = 0;
			if( 71 <= *filename )
				c_str[70] = filename[71];
			else
				c_str[70] = 0;
			if( 72 <= *filename )
				c_str[71] = filename[72];
			else
				c_str[71] = 0;
			if( 73 <= *filename )
				c_str[72] = filename[73];
			else
				c_str[72] = 0;
			if( 74 <= *filename )
				c_str[73] = filename[74];
			else
				c_str[73] = 0;
			if( 75 <= *filename )
				c_str[74] = filename[75];
			else
				c_str[74] = 0;
			if( 76 <= *filename )
				c_str[75] = filename[76];
			else
				c_str[75] = 0;
			if( 77 <= *filename )
				c_str[76] = filename[77];
			else
				c_str[76] = 0;
			if( 78 <= *filename )
				c_str[77] = filename[78];
			else
				c_str[77] = 0;
			if( 79 <= *filename )
				c_str[78] = filename[79];
			else
				c_str[78] = 0;
			if( 80 <= *filename )
				c_str[79] = filename[80];
			else
				c_str[79] = 0;
			if( 81 <= *filename )
				c_str[80] = filename[81];
			else
				c_str[80] = 0;
			if( 82 <= *filename )
				c_str[81] = filename[82];
			else
				c_str[81] = 0;
			if( 83 <= *filename )
				c_str[82] = filename[83];
			else
				c_str[82] = 0;
			if( 84 <= *filename )
				c_str[83] = filename[84];
			else
				c_str[83] = 0;
			if( 85 <= *filename )
				c_str[84] = filename[85];
			else
				c_str[84] = 0;
			if( 86 <= *filename )
				c_str[85] = filename[86];
			else
				c_str[85] = 0;
			if( 87 <= *filename )
				c_str[86] = filename[87];
			else
				c_str[86] = 0;
			if( 88 <= *filename )
				c_str[87] = filename[88];
			else
				c_str[87] = 0;
			if( 89 <= *filename )
				c_str[88] = filename[89];
			else
				c_str[88] = 0;
			if( 90 <= *filename )
				c_str[89] = filename[90];
			else
				c_str[89] = 0;
			if( 91 <= *filename )
				c_str[90] = filename[91];
			else
				c_str[90] = 0;
			if( 92 <= *filename )
				c_str[91] = filename[92];
			else
				c_str[91] = 0;
			if( 93 <= *filename )
				c_str[92] = filename[93];
			else
				c_str[92] = 0;
			if( 94 <= *filename )
				c_str[93] = filename[94];
			else
				c_str[93] = 0;
			if( 95 <= *filename )
				c_str[94] = filename[95];
			else
				c_str[94] = 0;
			if( 96 <= *filename )
				c_str[95] = filename[96];
			else
				c_str[95] = 0;
			if( 97 <= *filename )
				c_str[96] = filename[97];
			else
				c_str[96] = 0;
			if( 98 <= *filename )
				c_str[97] = filename[98];
			else
				c_str[97] = 0;
			if( 99 <= *filename )
				c_str[98] = filename[99];
			else
				c_str[98] = 0;
			if( 100 <= *filename )
				c_str[99] = filename[100];
			else
				c_str[99] = 0;
			if( 101 <= *filename )
				c_str[100] = filename[101];
			else
				c_str[100] = 0;
			if( 102 <= *filename )
				c_str[101] = filename[102];
			else
				c_str[101] = 0;
			if( 103 <= *filename )
				c_str[102] = filename[103];
			else
				c_str[102] = 0;
			if( 104 <= *filename )
				c_str[103] = filename[104];
			else
				c_str[103] = 0;
			if( 105 <= *filename )
				c_str[104] = filename[105];
			else
				c_str[104] = 0;
			if( 106 <= *filename )
				c_str[105] = filename[106];
			else
				c_str[105] = 0;
			if( 107 <= *filename )
				c_str[106] = filename[107];
			else
				c_str[106] = 0;
			if( 108 <= *filename )
				c_str[107] = filename[108];
			else
				c_str[107] = 0;
			if( 109 <= *filename )
				c_str[108] = filename[109];
			else
				c_str[108] = 0;
			if( 110 <= *filename )
				c_str[109] = filename[110];
			else
				c_str[109] = 0;
			if( 111 <= *filename )
				c_str[110] = filename[111];
			else
				c_str[110] = 0;
			if( 112 <= *filename )
				c_str[111] = filename[112];
			else
				c_str[111] = 0;
			if( 113 <= *filename )
				c_str[112] = filename[113];
			else
				c_str[112] = 0;
			if( 114 <= *filename )
				c_str[113] = filename[114];
			else
				c_str[113] = 0;
			if( 115 <= *filename )
				c_str[114] = filename[115];
			else
				c_str[114] = 0;
			if( 116 <= *filename )
				c_str[115] = filename[116];
			else
				c_str[115] = 0;
			if( 117 <= *filename )
				c_str[116] = filename[117];
			else
				c_str[116] = 0;
			if( 118 <= *filename )
				c_str[117] = filename[118];
			else
				c_str[117] = 0;
			if( 119 <= *filename )
				c_str[118] = filename[119];
			else
				c_str[118] = 0;
			if( 120 <= *filename )
				c_str[119] = filename[120];
			else
				c_str[119] = 0;
			if( 121 <= *filename )
				c_str[120] = filename[121];
			else
				c_str[120] = 0;
			if( 122 <= *filename )
				c_str[121] = filename[122];
			else
				c_str[121] = 0;
			if( 123 <= *filename )
				c_str[122] = filename[123];
			else
				c_str[122] = 0;
			if( 124 <= *filename )
				c_str[123] = filename[124];
			else
				c_str[123] = 0;
			if( 125 <= *filename )
				c_str[124] = filename[125];
			else
				c_str[124] = 0;
			if( 126 <= *filename )
				c_str[125] = filename[126];
			else
				c_str[125] = 0;
			if( 127 <= *filename )
				c_str[126] = filename[127];
			else
				c_str[126] = 0;
			if( 128 <= *filename )
				c_str[127] = filename[128];
			else
				c_str[127] = 0;
			if( 129 <= *filename )
				c_str[128] = filename[129];
			else
				c_str[128] = 0;
			if( 130 <= *filename )
				c_str[129] = filename[130];
			else
				c_str[129] = 0;
			if( 131 <= *filename )
				c_str[130] = filename[131];
			else
				c_str[130] = 0;
			if( 132 <= *filename )
				c_str[131] = filename[132];
			else
				c_str[131] = 0;
			if( 133 <= *filename )
				c_str[132] = filename[133];
			else
				c_str[132] = 0;
			if( 134 <= *filename )
				c_str[133] = filename[134];
			else
				c_str[133] = 0;
			if( 135 <= *filename )
				c_str[134] = filename[135];
			else
				c_str[134] = 0;
			if( 136 <= *filename )
				c_str[135] = filename[136];
			else
				c_str[135] = 0;
			if( 137 <= *filename )
				c_str[136] = filename[137];
			else
				c_str[136] = 0;
			if( 138 <= *filename )
				c_str[137] = filename[138];
			else
				c_str[137] = 0;
			if( 139 <= *filename )
				c_str[138] = filename[139];
			else
				c_str[138] = 0;
			if( 140 <= *filename )
				c_str[139] = filename[140];
			else
				c_str[139] = 0;
			if( 141 <= *filename )
				c_str[140] = filename[141];
			else
				c_str[140] = 0;
			if( 142 <= *filename )
				c_str[141] = filename[142];
			else
				c_str[141] = 0;
			if( 143 <= *filename )
				c_str[142] = filename[143];
			else
				c_str[142] = 0;
			if( 144 <= *filename )
				c_str[143] = filename[144];
			else
				c_str[143] = 0;
			if( 145 <= *filename )
				c_str[144] = filename[145];
			else
				c_str[144] = 0;
			if( 146 <= *filename )
				c_str[145] = filename[146];
			else
				c_str[145] = 0;
			if( 147 <= *filename )
				c_str[146] = filename[147];
			else
				c_str[146] = 0;
			if( 148 <= *filename )
				c_str[147] = filename[148];
			else
				c_str[147] = 0;
			if( 149 <= *filename )
				c_str[148] = filename[149];
			else
				c_str[148] = 0;
			if( 150 <= *filename )
				c_str[149] = filename[150];
			else
				c_str[149] = 0;
			if( 151 <= *filename )
				c_str[150] = filename[151];
			else
				c_str[150] = 0;
			if( 152 <= *filename )
				c_str[151] = filename[152];
			else
				c_str[151] = 0;
			if( 153 <= *filename )
				c_str[152] = filename[153];
			else
				c_str[152] = 0;
			if( 154 <= *filename )
				c_str[153] = filename[154];
			else
				c_str[153] = 0;
			if( 155 <= *filename )
				c_str[154] = filename[155];
			else
				c_str[154] = 0;
			if( 156 <= *filename )
				c_str[155] = filename[156];
			else
				c_str[155] = 0;
			if( 157 <= *filename )
				c_str[156] = filename[157];
			else
				c_str[156] = 0;
			if( 158 <= *filename )
				c_str[157] = filename[158];
			else
				c_str[157] = 0;
			if( 159 <= *filename )
				c_str[158] = filename[159];
			else
				c_str[158] = 0;
			if( 160 <= *filename )
				c_str[159] = filename[160];
			else
				c_str[159] = 0;
			if( 161 <= *filename )
				c_str[160] = filename[161];
			else
				c_str[160] = 0;
			if( 162 <= *filename )
				c_str[161] = filename[162];
			else
				c_str[161] = 0;
			if( 163 <= *filename )
				c_str[162] = filename[163];
			else
				c_str[162] = 0;
			if( 164 <= *filename )
				c_str[163] = filename[164];
			else
				c_str[163] = 0;
			if( 165 <= *filename )
				c_str[164] = filename[165];
			else
				c_str[164] = 0;
			if( 166 <= *filename )
				c_str[165] = filename[166];
			else
				c_str[165] = 0;
			if( 167 <= *filename )
				c_str[166] = filename[167];
			else
				c_str[166] = 0;
			if( 168 <= *filename )
				c_str[167] = filename[168];
			else
				c_str[167] = 0;
			if( 169 <= *filename )
				c_str[168] = filename[169];
			else
				c_str[168] = 0;
			if( 170 <= *filename )
				c_str[169] = filename[170];
			else
				c_str[169] = 0;
			if( 171 <= *filename )
				c_str[170] = filename[171];
			else
				c_str[170] = 0;
			if( 172 <= *filename )
				c_str[171] = filename[172];
			else
				c_str[171] = 0;
			if( 173 <= *filename )
				c_str[172] = filename[173];
			else
				c_str[172] = 0;
			if( 174 <= *filename )
				c_str[173] = filename[174];
			else
				c_str[173] = 0;
			if( 175 <= *filename )
				c_str[174] = filename[175];
			else
				c_str[174] = 0;
			if( 176 <= *filename )
				c_str[175] = filename[176];
			else
				c_str[175] = 0;
			if( 177 <= *filename )
				c_str[176] = filename[177];
			else
				c_str[176] = 0;
			if( 178 <= *filename )
				c_str[177] = filename[178];
			else
				c_str[177] = 0;
			if( 179 <= *filename )
				c_str[178] = filename[179];
			else
				c_str[178] = 0;
			if( 180 <= *filename )
				c_str[179] = filename[180];
			else
				c_str[179] = 0;
			if( 181 <= *filename )
				c_str[180] = filename[181];
			else
				c_str[180] = 0;
			if( 182 <= *filename )
				c_str[181] = filename[182];
			else
				c_str[181] = 0;
			if( 183 <= *filename )
				c_str[182] = filename[183];
			else
				c_str[182] = 0;
			if( 184 <= *filename )
				c_str[183] = filename[184];
			else
				c_str[183] = 0;
			if( 185 <= *filename )
				c_str[184] = filename[185];
			else
				c_str[184] = 0;
			if( 186 <= *filename )
				c_str[185] = filename[186];
			else
				c_str[185] = 0;
			if( 187 <= *filename )
				c_str[186] = filename[187];
			else
				c_str[186] = 0;
			if( 188 <= *filename )
				c_str[187] = filename[188];
			else
				c_str[187] = 0;
			if( 189 <= *filename )
				c_str[188] = filename[189];
			else
				c_str[188] = 0;
			if( 190 <= *filename )
				c_str[189] = filename[190];
			else
				c_str[189] = 0;
			if( 191 <= *filename )
				c_str[190] = filename[191];
			else
				c_str[190] = 0;
			if( 192 <= *filename )
				c_str[191] = filename[192];
			else
				c_str[191] = 0;
			if( 193 <= *filename )
				c_str[192] = filename[193];
			else
				c_str[192] = 0;
			if( 194 <= *filename )
				c_str[193] = filename[194];
			else
				c_str[193] = 0;
			if( 195 <= *filename )
				c_str[194] = filename[195];
			else
				c_str[194] = 0;
			if( 196 <= *filename )
				c_str[195] = filename[196];
			else
				c_str[195] = 0;
			if( 197 <= *filename )
				c_str[196] = filename[197];
			else
				c_str[196] = 0;
			if( 198 <= *filename )
				c_str[197] = filename[198];
			else
				c_str[197] = 0;
			if( 199 <= *filename )
				c_str[198] = filename[199];
			else
				c_str[198] = 0;
			if( 200 <= *filename )
				c_str[199] = filename[200];
			else
				c_str[199] = 0;
			if( 201 <= *filename )
				c_str[200] = filename[201];
			else
				c_str[200] = 0;
			if( 202 <= *filename )
				c_str[201] = filename[202];
			else
				c_str[201] = 0;
			if( 203 <= *filename )
				c_str[202] = filename[203];
			else
				c_str[202] = 0;
			if( 204 <= *filename )
				c_str[203] = filename[204];
			else
				c_str[203] = 0;
			if( 205 <= *filename )
				c_str[204] = filename[205];
			else
				c_str[204] = 0;
			if( 206 <= *filename )
				c_str[205] = filename[206];
			else
				c_str[205] = 0;
			if( 207 <= *filename )
				c_str[206] = filename[207];
			else
				c_str[206] = 0;
			if( 208 <= *filename )
				c_str[207] = filename[208];
			else
				c_str[207] = 0;
			if( 209 <= *filename )
				c_str[208] = filename[209];
			else
				c_str[208] = 0;
			if( 210 <= *filename )
				c_str[209] = filename[210];
			else
				c_str[209] = 0;
			if( 211 <= *filename )
				c_str[210] = filename[211];
			else
				c_str[210] = 0;
			if( 212 <= *filename )
				c_str[211] = filename[212];
			else
				c_str[211] = 0;
			if( 213 <= *filename )
				c_str[212] = filename[213];
			else
				c_str[212] = 0;
			if( 214 <= *filename )
				c_str[213] = filename[214];
			else
				c_str[213] = 0;
			if( 215 <= *filename )
				c_str[214] = filename[215];
			else
				c_str[214] = 0;
			if( 216 <= *filename )
				c_str[215] = filename[216];
			else
				c_str[215] = 0;
			if( 217 <= *filename )
				c_str[216] = filename[217];
			else
				c_str[216] = 0;
			if( 218 <= *filename )
				c_str[217] = filename[218];
			else
				c_str[217] = 0;
			if( 219 <= *filename )
				c_str[218] = filename[219];
			else
				c_str[218] = 0;
			if( 220 <= *filename )
				c_str[219] = filename[220];
			else
				c_str[219] = 0;
			if( 221 <= *filename )
				c_str[220] = filename[221];
			else
				c_str[220] = 0;
			if( 222 <= *filename )
				c_str[221] = filename[222];
			else
				c_str[221] = 0;
			if( 223 <= *filename )
				c_str[222] = filename[223];
			else
				c_str[222] = 0;
			if( 224 <= *filename )
				c_str[223] = filename[224];
			else
				c_str[223] = 0;
			if( 225 <= *filename )
				c_str[224] = filename[225];
			else
				c_str[224] = 0;
			if( 226 <= *filename )
				c_str[225] = filename[226];
			else
				c_str[225] = 0;
			if( 227 <= *filename )
				c_str[226] = filename[227];
			else
				c_str[226] = 0;
			if( 228 <= *filename )
				c_str[227] = filename[228];
			else
				c_str[227] = 0;
			if( 229 <= *filename )
				c_str[228] = filename[229];
			else
				c_str[228] = 0;
			if( 230 <= *filename )
				c_str[229] = filename[230];
			else
				c_str[229] = 0;
			if( 231 <= *filename )
				c_str[230] = filename[231];
			else
				c_str[230] = 0;
			if( 232 <= *filename )
				c_str[231] = filename[232];
			else
				c_str[231] = 0;
			if( 233 <= *filename )
				c_str[232] = filename[233];
			else
				c_str[232] = 0;
			if( 234 <= *filename )
				c_str[233] = filename[234];
			else
				c_str[233] = 0;
			if( 235 <= *filename )
				c_str[234] = filename[235];
			else
				c_str[234] = 0;
			if( 236 <= *filename )
				c_str[235] = filename[236];
			else
				c_str[235] = 0;
			if( 237 <= *filename )
				c_str[236] = filename[237];
			else
				c_str[236] = 0;
			if( 238 <= *filename )
				c_str[237] = filename[238];
			else
				c_str[237] = 0;
			if( 239 <= *filename )
				c_str[238] = filename[239];
			else
				c_str[238] = 0;
			if( 240 <= *filename )
				c_str[239] = filename[240];
			else
				c_str[239] = 0;
			if( 241 <= *filename )
				c_str[240] = filename[241];
			else
				c_str[240] = 0;
			if( 242 <= *filename )
				c_str[241] = filename[242];
			else
				c_str[241] = 0;
			if( 243 <= *filename )
				c_str[242] = filename[243];
			else
				c_str[242] = 0;
			if( 244 <= *filename )
				c_str[243] = filename[244];
			else
				c_str[243] = 0;
			if( 245 <= *filename )
				c_str[244] = filename[245];
			else
				c_str[244] = 0;
			if( 246 <= *filename )
				c_str[245] = filename[246];
			else
				c_str[245] = 0;
			if( 247 <= *filename )
				c_str[246] = filename[247];
			else
				c_str[246] = 0;
			if( 248 <= *filename )
				c_str[247] = filename[248];
			else
				c_str[247] = 0;
			if( 249 <= *filename )
				c_str[248] = filename[249];
			else
				c_str[248] = 0;
			if( 250 <= *filename )
				c_str[249] = filename[250];
			else
				c_str[249] = 0;
			if( 251 <= *filename )
				c_str[250] = filename[251];
			else
				c_str[250] = 0;
			if( 252 <= *filename )
				c_str[251] = filename[252];
			else
				c_str[251] = 0;
			if( 253 <= *filename )
				c_str[252] = filename[253];
			else
				c_str[252] = 0;
			if( 254 <= *filename )
				c_str[253] = filename[254];
			else
				c_str[253] = 0;
			if( 255 <= *filename )
				c_str[254] = filename[255];
			else
				c_str[254] = 0;
			c_str[255] = 0;
			
			fileptr = fopen( c_str, "w" );
			
			c_str[0] = '.';
			c_str[1] = 't';
			c_str[2] = 'e';
			c_str[3] = 'm';
			c_str[4] = 'p';
			c_str[5] = 'a';
			c_str[6] = 'n';
			c_str[7] = 'u';
			c_str[8] = 'g';
			c_str[9] = 'i';
			c_str[10] = 'r';
			c_str[11] = 'q';
			c_str[12] = 'g';
			c_str[13] = 'h';
			c_str[14] = 0;

			good = false;

			if( c_str[0] == 0 ) {
				str[0] = 0;
				good = true;
			} else str[1] = c_str[0];
			if( good == false ) {
				if( c_str[1] == 0 ) {
					str[0] = 1;
					good = true;
				} else str[2] = c_str[1];
			}
			if( good == false ) {
				if( c_str[2] == 0 ) {
					str[0] = 2;
					good = true;
				} else str[3] = c_str[2];
			}
			if( good == false ) {
				if( c_str[3] == 0 ) {
					str[0] = 3;
					good = true;
				} else str[4] = c_str[3];
			}
			if( good == false ) {
				if( c_str[4] == 0 ) {
					str[0] = 4;
					good = true;
				} else str[5] = c_str[4];
			}
			if( good == false ) {
				if( c_str[5] == 0 ) {
					str[0] = 5;
					good = true;
				} else str[6] = c_str[5];
			}
			if( good == false ) {
				if( c_str[6] == 0 ) {
					str[0] = 6;
					good = true;
				} else str[7] = c_str[6];
			}
			if( good == false ) {
				if( c_str[7] == 0 ) {
					str[0] = 7;
					good = true;
				} else str[8] = c_str[7];
			}
			if( good == false ) {
				if( c_str[8] == 0 ) {
					str[0] = 8;
					good = true;
				} else str[9] = c_str[8];
			}
			if( good == false ) {
				if( c_str[9] == 0 ) {
					str[0] = 9;
					good = true;
				} else str[10] = c_str[9];
			}
			if( good == false ) {
				if( c_str[10] == 0 ) {
					str[0] = 10;
					good = true;
				} else str[11] = c_str[10];
			}
			if( good == false ) {
				if( c_str[11] == 0 ) {
					str[0] = 11;
					good = true;
				} else str[12] = c_str[11];
			}
			if( good == false ) {
				if( c_str[12] == 0 ) {
					str[0] = 12;
					good = true;
				} else str[13] = c_str[12];
			}
			if( good == false ) {
				if( c_str[13] == 0 ) {
					str[0] = 13;
					good = true;
				} else str[14] = c_str[13];
			}
			if( good == false ) {
				if( c_str[14] == 0 ) {
					str[0] = 14;
					good = true;
				} else str[15] = c_str[14];
			}
			if( good == false ) {
				if( c_str[15] == 0 ) {
					str[0] = 15;
					good = true;
				} else str[16] = c_str[15];
			}
			if( good == false ) {
				if( c_str[16] == 0 ) {
					str[0] = 16;
					good = true;
				} else str[17] = c_str[16];
			}
			if( good == false ) {
				if( c_str[17] == 0 ) {
					str[0] = 17;
					good = true;
				} else str[18] = c_str[17];
			}
			if( good == false ) {
				if( c_str[18] == 0 ) {
					str[0] = 18;
					good = true;
				} else str[19] = c_str[18];
			}
			if( good == false ) {
				if( c_str[19] == 0 ) {
					str[0] = 19;
					good = true;
				} else str[20] = c_str[19];
			}
			if( good == false ) {
				if( c_str[20] == 0 ) {
					str[0] = 20;
					good = true;
				} else str[21] = c_str[20];
			}
			if( good == false ) {
				if( c_str[21] == 0 ) {
					str[0] = 21;
					good = true;
				} else str[22] = c_str[21];
			}
			if( good == false ) {
				if( c_str[22] == 0 ) {
					str[0] = 22;
					good = true;
				} else str[23] = c_str[22];
			}
			if( good == false ) {
				if( c_str[23] == 0 ) {
					str[0] = 23;
					good = true;
				} else str[24] = c_str[23];
			}
			if( good == false ) {
				if( c_str[24] == 0 ) {
					str[0] = 24;
					good = true;
				} else str[25] = c_str[24];
			}
			if( good == false ) {
				if( c_str[25] == 0 ) {
					str[0] = 25;
					good = true;
				} else str[26] = c_str[25];
			}
			if( good == false ) {
				if( c_str[26] == 0 ) {
					str[0] = 26;
					good = true;
				} else str[27] = c_str[26];
			}
			if( good == false ) {
				if( c_str[27] == 0 ) {
					str[0] = 27;
					good = true;
				} else str[28] = c_str[27];
			}
			if( good == false ) {
				if( c_str[28] == 0 ) {
					str[0] = 28;
					good = true;
				} else str[29] = c_str[28];
			}
			if( good == false ) {
				if( c_str[29] == 0 ) {
					str[0] = 29;
					good = true;
				} else str[30] = c_str[29];
			}
			if( good == false ) {
				if( c_str[30] == 0 ) {
					str[0] = 30;
					good = true;
				} else str[31] = c_str[30];
			}
			if( good == false ) {
				if( c_str[31] == 0 ) {
					str[0] = 31;
					good = true;
				} else str[32] = c_str[31];
			}
			if( good == false ) {
				if( c_str[32] == 0 ) {
					str[0] = 32;
					good = true;
				} else str[33] = c_str[32];
			}
			if( good == false ) {
				if( c_str[33] == 0 ) {
					str[0] = 33;
					good = true;
				} else str[34] = c_str[33];
			}
			if( good == false ) {
				if( c_str[34] == 0 ) {
					str[0] = 34;
					good = true;
				} else str[35] = c_str[34];
			}
			if( good == false ) {
				if( c_str[35] == 0 ) {
					str[0] = 35;
					good = true;
				} else str[36] = c_str[35];
			}
			if( good == false ) {
				if( c_str[36] == 0 ) {
					str[0] = 36;
					good = true;
				} else str[37] = c_str[36];
			}
			if( good == false ) {
				if( c_str[37] == 0 ) {
					str[0] = 37;
					good = true;
				} else str[38] = c_str[37];
			}
			if( good == false ) {
				if( c_str[38] == 0 ) {
					str[0] = 38;
					good = true;
				} else str[39] = c_str[38];
			}
			if( good == false ) {
				if( c_str[39] == 0 ) {
					str[0] = 39;
					good = true;
				} else str[40] = c_str[39];
			}
			if( good == false ) {
				if( c_str[40] == 0 ) {
					str[0] = 40;
					good = true;
				} else str[41] = c_str[40];
			}
			if( good == false ) {
				if( c_str[41] == 0 ) {
					str[0] = 41;
					good = true;
				} else str[42] = c_str[41];
			}
			if( good == false ) {
				if( c_str[42] == 0 ) {
					str[0] = 42;
					good = true;
				} else str[43] = c_str[42];
			}
			if( good == false ) {
				if( c_str[43] == 0 ) {
					str[0] = 43;
					good = true;
				} else str[44] = c_str[43];
			}
			if( good == false ) {
				if( c_str[44] == 0 ) {
					str[0] = 44;
					good = true;
				} else str[45] = c_str[44];
			}
			if( good == false ) {
				if( c_str[45] == 0 ) {
					str[0] = 45;
					good = true;
				} else str[46] = c_str[45];
			}
			if( good == false ) {
				if( c_str[46] == 0 ) {
					str[0] = 46;
					good = true;
				} else str[47] = c_str[46];
			}
			if( good == false ) {
				if( c_str[47] == 0 ) {
					str[0] = 47;
					good = true;
				} else str[48] = c_str[47];
			}
			if( good == false ) {
				if( c_str[48] == 0 ) {
					str[0] = 48;
					good = true;
				} else str[49] = c_str[48];
			}
			if( good == false ) {
				if( c_str[49] == 0 ) {
					str[0] = 49;
					good = true;
				} else str[50] = c_str[49];
			}
			if( good == false ) {
				if( c_str[50] == 0 ) {
					str[0] = 50;
					good = true;
				} else str[51] = c_str[50];
			}
			if( good == false ) {
				if( c_str[51] == 0 ) {
					str[0] = 51;
					good = true;
				} else str[52] = c_str[51];
			}
			if( good == false ) {
				if( c_str[52] == 0 ) {
					str[0] = 52;
					good = true;
				} else str[53] = c_str[52];
			}
			if( good == false ) {
				if( c_str[53] == 0 ) {
					str[0] = 53;
					good = true;
				} else str[54] = c_str[53];
			}
			if( good == false ) {
				if( c_str[54] == 0 ) {
					str[0] = 54;
					good = true;
				} else str[55] = c_str[54];
			}
			if( good == false ) {
				if( c_str[55] == 0 ) {
					str[0] = 55;
					good = true;
				} else str[56] = c_str[55];
			}
			if( good == false ) {
				if( c_str[56] == 0 ) {
					str[0] = 56;
					good = true;
				} else str[57] = c_str[56];
			}
			if( good == false ) {
				if( c_str[57] == 0 ) {
					str[0] = 57;
					good = true;
				} else str[58] = c_str[57];
			}
			if( good == false ) {
				if( c_str[58] == 0 ) {
					str[0] = 58;
					good = true;
				} else str[59] = c_str[58];
			}
			if( good == false ) {
				if( c_str[59] == 0 ) {
					str[0] = 59;
					good = true;
				} else str[60] = c_str[59];
			}
			if( good == false ) {
				if( c_str[60] == 0 ) {
					str[0] = 60;
					good = true;
				} else str[61] = c_str[60];
			}
			if( good == false ) {
				if( c_str[61] == 0 ) {
					str[0] = 61;
					good = true;
				} else str[62] = c_str[61];
			}
			if( good == false ) {
				if( c_str[62] == 0 ) {
					str[0] = 62;
					good = true;
				} else str[63] = c_str[62];
			}
			if( good == false ) {
				if( c_str[63] == 0 ) {
					str[0] = 63;
					good = true;
				} else str[64] = c_str[63];
			}
			if( good == false ) {
				if( c_str[64] == 0 ) {
					str[0] = 64;
					good = true;
				} else str[65] = c_str[64];
			}
			if( good == false ) {
				if( c_str[65] == 0 ) {
					str[0] = 65;
					good = true;
				} else str[66] = c_str[65];
			}
			if( good == false ) {
				if( c_str[66] == 0 ) {
					str[0] = 66;
					good = true;
				} else str[67] = c_str[66];
			}
			if( good == false ) {
				if( c_str[67] == 0 ) {
					str[0] = 67;
					good = true;
				} else str[68] = c_str[67];
			}
			if( good == false ) {
				if( c_str[68] == 0 ) {
					str[0] = 68;
					good = true;
				} else str[69] = c_str[68];
			}
			if( good == false ) {
				if( c_str[69] == 0 ) {
					str[0] = 69;
					good = true;
				} else str[70] = c_str[69];
			}
			if( good == false ) {
				if( c_str[70] == 0 ) {
					str[0] = 70;
					good = true;
				} else str[71] = c_str[70];
			}
			if( good == false ) {
				if( c_str[71] == 0 ) {
					str[0] = 71;
					good = true;
				} else str[72] = c_str[71];
			}
			if( good == false ) {
				if( c_str[72] == 0 ) {
					str[0] = 72;
					good = true;
				} else str[73] = c_str[72];
			}
			if( good == false ) {
				if( c_str[73] == 0 ) {
					str[0] = 73;
					good = true;
				} else str[74] = c_str[73];
			}
			if( good == false ) {
				if( c_str[74] == 0 ) {
					str[0] = 74;
					good = true;
				} else str[75] = c_str[74];
			}
			if( good == false ) {
				if( c_str[75] == 0 ) {
					str[0] = 75;
					good = true;
				} else str[76] = c_str[75];
			}
			if( good == false ) {
				if( c_str[76] == 0 ) {
					str[0] = 76;
					good = true;
				} else str[77] = c_str[76];
			}
			if( good == false ) {
				if( c_str[77] == 0 ) {
					str[0] = 77;
					good = true;
				} else str[78] = c_str[77];
			}
			if( good == false ) {
				if( c_str[78] == 0 ) {
					str[0] = 78;
					good = true;
				} else str[79] = c_str[78];
			}
			if( good == false ) {
				if( c_str[79] == 0 ) {
					str[0] = 79;
					good = true;
				} else str[80] = c_str[79];
			}
			if( good == false ) {
				if( c_str[80] == 0 ) {
					str[0] = 80;
					good = true;
				} else str[81] = c_str[80];
			}
			if( good == false ) {
				if( c_str[81] == 0 ) {
					str[0] = 81;
					good = true;
				} else str[82] = c_str[81];
			}
			if( good == false ) {
				if( c_str[82] == 0 ) {
					str[0] = 82;
					good = true;
				} else str[83] = c_str[82];
			}
			if( good == false ) {
				if( c_str[83] == 0 ) {
					str[0] = 83;
					good = true;
				} else str[84] = c_str[83];
			}
			if( good == false ) {
				if( c_str[84] == 0 ) {
					str[0] = 84;
					good = true;
				} else str[85] = c_str[84];
			}
			if( good == false ) {
				if( c_str[85] == 0 ) {
					str[0] = 85;
					good = true;
				} else str[86] = c_str[85];
			}
			if( good == false ) {
				if( c_str[86] == 0 ) {
					str[0] = 86;
					good = true;
				} else str[87] = c_str[86];
			}
			if( good == false ) {
				if( c_str[87] == 0 ) {
					str[0] = 87;
					good = true;
				} else str[88] = c_str[87];
			}
			if( good == false ) {
				if( c_str[88] == 0 ) {
					str[0] = 88;
					good = true;
				} else str[89] = c_str[88];
			}
			if( good == false ) {
				if( c_str[89] == 0 ) {
					str[0] = 89;
					good = true;
				} else str[90] = c_str[89];
			}
			if( good == false ) {
				if( c_str[90] == 0 ) {
					str[0] = 90;
					good = true;
				} else str[91] = c_str[90];
			}
			if( good == false ) {
				if( c_str[91] == 0 ) {
					str[0] = 91;
					good = true;
				} else str[92] = c_str[91];
			}
			if( good == false ) {
				if( c_str[92] == 0 ) {
					str[0] = 92;
					good = true;
				} else str[93] = c_str[92];
			}
			if( good == false ) {
				if( c_str[93] == 0 ) {
					str[0] = 93;
					good = true;
				} else str[94] = c_str[93];
			}
			if( good == false ) {
				if( c_str[94] == 0 ) {
					str[0] = 94;
					good = true;
				} else str[95] = c_str[94];
			}
			if( good == false ) {
				if( c_str[95] == 0 ) {
					str[0] = 95;
					good = true;
				} else str[96] = c_str[95];
			}
			if( good == false ) {
				if( c_str[96] == 0 ) {
					str[0] = 96;
					good = true;
				} else str[97] = c_str[96];
			}
			if( good == false ) {
				if( c_str[97] == 0 ) {
					str[0] = 97;
					good = true;
				} else str[98] = c_str[97];
			}
			if( good == false ) {
				if( c_str[98] == 0 ) {
					str[0] = 98;
					good = true;
				} else str[99] = c_str[98];
			}
			if( good == false ) {
				if( c_str[99] == 0 ) {
					str[0] = 99;
					good = true;
				} else str[100] = c_str[99];
			}
			if( good == false ) {
				if( c_str[100] == 0 ) {
					str[0] = 100;
					good = true;
				} else str[101] = c_str[100];
			}
			if( good == false ) {
				if( c_str[101] == 0 ) {
					str[0] = 101;
					good = true;
				} else str[102] = c_str[101];
			}
			if( good == false ) {
				if( c_str[102] == 0 ) {
					str[0] = 102;
					good = true;
				} else str[103] = c_str[102];
			}
			if( good == false ) {
				if( c_str[103] == 0 ) {
					str[0] = 103;
					good = true;
				} else str[104] = c_str[103];
			}
			if( good == false ) {
				if( c_str[104] == 0 ) {
					str[0] = 104;
					good = true;
				} else str[105] = c_str[104];
			}
			if( good == false ) {
				if( c_str[105] == 0 ) {
					str[0] = 105;
					good = true;
				} else str[106] = c_str[105];
			}
			if( good == false ) {
				if( c_str[106] == 0 ) {
					str[0] = 106;
					good = true;
				} else str[107] = c_str[106];
			}
			if( good == false ) {
				if( c_str[107] == 0 ) {
					str[0] = 107;
					good = true;
				} else str[108] = c_str[107];
			}
			if( good == false ) {
				if( c_str[108] == 0 ) {
					str[0] = 108;
					good = true;
				} else str[109] = c_str[108];
			}
			if( good == false ) {
				if( c_str[109] == 0 ) {
					str[0] = 109;
					good = true;
				} else str[110] = c_str[109];
			}
			if( good == false ) {
				if( c_str[110] == 0 ) {
					str[0] = 110;
					good = true;
				} else str[111] = c_str[110];
			}
			if( good == false ) {
				if( c_str[111] == 0 ) {
					str[0] = 111;
					good = true;
				} else str[112] = c_str[111];
			}
			if( good == false ) {
				if( c_str[112] == 0 ) {
					str[0] = 112;
					good = true;
				} else str[113] = c_str[112];
			}
			if( good == false ) {
				if( c_str[113] == 0 ) {
					str[0] = 113;
					good = true;
				} else str[114] = c_str[113];
			}
			if( good == false ) {
				if( c_str[114] == 0 ) {
					str[0] = 114;
					good = true;
				} else str[115] = c_str[114];
			}
			if( good == false ) {
				if( c_str[115] == 0 ) {
					str[0] = 115;
					good = true;
				} else str[116] = c_str[115];
			}
			if( good == false ) {
				if( c_str[116] == 0 ) {
					str[0] = 116;
					good = true;
				} else str[117] = c_str[116];
			}
			if( good == false ) {
				if( c_str[117] == 0 ) {
					str[0] = 117;
					good = true;
				} else str[118] = c_str[117];
			}
			if( good == false ) {
				if( c_str[118] == 0 ) {
					str[0] = 118;
					good = true;
				} else str[119] = c_str[118];
			}
			if( good == false ) {
				if( c_str[119] == 0 ) {
					str[0] = 119;
					good = true;
				} else str[120] = c_str[119];
			}
			if( good == false ) {
				if( c_str[120] == 0 ) {
					str[0] = 120;
					good = true;
				} else str[121] = c_str[120];
			}
			if( good == false ) {
				if( c_str[121] == 0 ) {
					str[0] = 121;
					good = true;
				} else str[122] = c_str[121];
			}
			if( good == false ) {
				if( c_str[122] == 0 ) {
					str[0] = 122;
					good = true;
				} else str[123] = c_str[122];
			}
			if( good == false ) {
				if( c_str[123] == 0 ) {
					str[0] = 123;
					good = true;
				} else str[124] = c_str[123];
			}
			if( good == false ) {
				if( c_str[124] == 0 ) {
					str[0] = 124;
					good = true;
				} else str[125] = c_str[124];
			}
			if( good == false ) {
				if( c_str[125] == 0 ) {
					str[0] = 125;
					good = true;
				} else str[126] = c_str[125];
			}
			if( good == false ) {
				if( c_str[126] == 0 ) {
					str[0] = 126;
					good = true;
				} else str[127] = c_str[126];
			}
			if( good == false ) {
				if( c_str[127] == 0 ) {
					str[0] = 127;
					good = true;
				} else str[128] = c_str[127];
			}
			if( good == false ) {
				if( c_str[128] == 0 ) {
					str[0] = 128;
					good = true;
				} else str[129] = c_str[128];
			}
			if( good == false ) {
				if( c_str[129] == 0 ) {
					str[0] = 129;
					good = true;
				} else str[130] = c_str[129];
			}
			if( good == false ) {
				if( c_str[130] == 0 ) {
					str[0] = 130;
					good = true;
				} else str[131] = c_str[130];
			}
			if( good == false ) {
				if( c_str[131] == 0 ) {
					str[0] = 131;
					good = true;
				} else str[132] = c_str[131];
			}
			if( good == false ) {
				if( c_str[132] == 0 ) {
					str[0] = 132;
					good = true;
				} else str[133] = c_str[132];
			}
			if( good == false ) {
				if( c_str[133] == 0 ) {
					str[0] = 133;
					good = true;
				} else str[134] = c_str[133];
			}
			if( good == false ) {
				if( c_str[134] == 0 ) {
					str[0] = 134;
					good = true;
				} else str[135] = c_str[134];
			}
			if( good == false ) {
				if( c_str[135] == 0 ) {
					str[0] = 135;
					good = true;
				} else str[136] = c_str[135];
			}
			if( good == false ) {
				if( c_str[136] == 0 ) {
					str[0] = 136;
					good = true;
				} else str[137] = c_str[136];
			}
			if( good == false ) {
				if( c_str[137] == 0 ) {
					str[0] = 137;
					good = true;
				} else str[138] = c_str[137];
			}
			if( good == false ) {
				if( c_str[138] == 0 ) {
					str[0] = 138;
					good = true;
				} else str[139] = c_str[138];
			}
			if( good == false ) {
				if( c_str[139] == 0 ) {
					str[0] = 139;
					good = true;
				} else str[140] = c_str[139];
			}
			if( good == false ) {
				if( c_str[140] == 0 ) {
					str[0] = 140;
					good = true;
				} else str[141] = c_str[140];
			}
			if( good == false ) {
				if( c_str[141] == 0 ) {
					str[0] = 141;
					good = true;
				} else str[142] = c_str[141];
			}
			if( good == false ) {
				if( c_str[142] == 0 ) {
					str[0] = 142;
					good = true;
				} else str[143] = c_str[142];
			}
			if( good == false ) {
				if( c_str[143] == 0 ) {
					str[0] = 143;
					good = true;
				} else str[144] = c_str[143];
			}
			if( good == false ) {
				if( c_str[144] == 0 ) {
					str[0] = 144;
					good = true;
				} else str[145] = c_str[144];
			}
			if( good == false ) {
				if( c_str[145] == 0 ) {
					str[0] = 145;
					good = true;
				} else str[146] = c_str[145];
			}
			if( good == false ) {
				if( c_str[146] == 0 ) {
					str[0] = 146;
					good = true;
				} else str[147] = c_str[146];
			}
			if( good == false ) {
				if( c_str[147] == 0 ) {
					str[0] = 147;
					good = true;
				} else str[148] = c_str[147];
			}
			if( good == false ) {
				if( c_str[148] == 0 ) {
					str[0] = 148;
					good = true;
				} else str[149] = c_str[148];
			}
			if( good == false ) {
				if( c_str[149] == 0 ) {
					str[0] = 149;
					good = true;
				} else str[150] = c_str[149];
			}
			if( good == false ) {
				if( c_str[150] == 0 ) {
					str[0] = 150;
					good = true;
				} else str[151] = c_str[150];
			}
			if( good == false ) {
				if( c_str[151] == 0 ) {
					str[0] = 151;
					good = true;
				} else str[152] = c_str[151];
			}
			if( good == false ) {
				if( c_str[152] == 0 ) {
					str[0] = 152;
					good = true;
				} else str[153] = c_str[152];
			}
			if( good == false ) {
				if( c_str[153] == 0 ) {
					str[0] = 153;
					good = true;
				} else str[154] = c_str[153];
			}
			if( good == false ) {
				if( c_str[154] == 0 ) {
					str[0] = 154;
					good = true;
				} else str[155] = c_str[154];
			}
			if( good == false ) {
				if( c_str[155] == 0 ) {
					str[0] = 155;
					good = true;
				} else str[156] = c_str[155];
			}
			if( good == false ) {
				if( c_str[156] == 0 ) {
					str[0] = 156;
					good = true;
				} else str[157] = c_str[156];
			}
			if( good == false ) {
				if( c_str[157] == 0 ) {
					str[0] = 157;
					good = true;
				} else str[158] = c_str[157];
			}
			if( good == false ) {
				if( c_str[158] == 0 ) {
					str[0] = 158;
					good = true;
				} else str[159] = c_str[158];
			}
			if( good == false ) {
				if( c_str[159] == 0 ) {
					str[0] = 159;
					good = true;
				} else str[160] = c_str[159];
			}
			if( good == false ) {
				if( c_str[160] == 0 ) {
					str[0] = 160;
					good = true;
				} else str[161] = c_str[160];
			}
			if( good == false ) {
				if( c_str[161] == 0 ) {
					str[0] = 161;
					good = true;
				} else str[162] = c_str[161];
			}
			if( good == false ) {
				if( c_str[162] == 0 ) {
					str[0] = 162;
					good = true;
				} else str[163] = c_str[162];
			}
			if( good == false ) {
				if( c_str[163] == 0 ) {
					str[0] = 163;
					good = true;
				} else str[164] = c_str[163];
			}
			if( good == false ) {
				if( c_str[164] == 0 ) {
					str[0] = 164;
					good = true;
				} else str[165] = c_str[164];
			}
			if( good == false ) {
				if( c_str[165] == 0 ) {
					str[0] = 165;
					good = true;
				} else str[166] = c_str[165];
			}
			if( good == false ) {
				if( c_str[166] == 0 ) {
					str[0] = 166;
					good = true;
				} else str[167] = c_str[166];
			}
			if( good == false ) {
				if( c_str[167] == 0 ) {
					str[0] = 167;
					good = true;
				} else str[168] = c_str[167];
			}
			if( good == false ) {
				if( c_str[168] == 0 ) {
					str[0] = 168;
					good = true;
				} else str[169] = c_str[168];
			}
			if( good == false ) {
				if( c_str[169] == 0 ) {
					str[0] = 169;
					good = true;
				} else str[170] = c_str[169];
			}
			if( good == false ) {
				if( c_str[170] == 0 ) {
					str[0] = 170;
					good = true;
				} else str[171] = c_str[170];
			}
			if( good == false ) {
				if( c_str[171] == 0 ) {
					str[0] = 171;
					good = true;
				} else str[172] = c_str[171];
			}
			if( good == false ) {
				if( c_str[172] == 0 ) {
					str[0] = 172;
					good = true;
				} else str[173] = c_str[172];
			}
			if( good == false ) {
				if( c_str[173] == 0 ) {
					str[0] = 173;
					good = true;
				} else str[174] = c_str[173];
			}
			if( good == false ) {
				if( c_str[174] == 0 ) {
					str[0] = 174;
					good = true;
				} else str[175] = c_str[174];
			}
			if( good == false ) {
				if( c_str[175] == 0 ) {
					str[0] = 175;
					good = true;
				} else str[176] = c_str[175];
			}
			if( good == false ) {
				if( c_str[176] == 0 ) {
					str[0] = 176;
					good = true;
				} else str[177] = c_str[176];
			}
			if( good == false ) {
				if( c_str[177] == 0 ) {
					str[0] = 177;
					good = true;
				} else str[178] = c_str[177];
			}
			if( good == false ) {
				if( c_str[178] == 0 ) {
					str[0] = 178;
					good = true;
				} else str[179] = c_str[178];
			}
			if( good == false ) {
				if( c_str[179] == 0 ) {
					str[0] = 179;
					good = true;
				} else str[180] = c_str[179];
			}
			if( good == false ) {
				if( c_str[180] == 0 ) {
					str[0] = 180;
					good = true;
				} else str[181] = c_str[180];
			}
			if( good == false ) {
				if( c_str[181] == 0 ) {
					str[0] = 181;
					good = true;
				} else str[182] = c_str[181];
			}
			if( good == false ) {
				if( c_str[182] == 0 ) {
					str[0] = 182;
					good = true;
				} else str[183] = c_str[182];
			}
			if( good == false ) {
				if( c_str[183] == 0 ) {
					str[0] = 183;
					good = true;
				} else str[184] = c_str[183];
			}
			if( good == false ) {
				if( c_str[184] == 0 ) {
					str[0] = 184;
					good = true;
				} else str[185] = c_str[184];
			}
			if( good == false ) {
				if( c_str[185] == 0 ) {
					str[0] = 185;
					good = true;
				} else str[186] = c_str[185];
			}
			if( good == false ) {
				if( c_str[186] == 0 ) {
					str[0] = 186;
					good = true;
				} else str[187] = c_str[186];
			}
			if( good == false ) {
				if( c_str[187] == 0 ) {
					str[0] = 187;
					good = true;
				} else str[188] = c_str[187];
			}
			if( good == false ) {
				if( c_str[188] == 0 ) {
					str[0] = 188;
					good = true;
				} else str[189] = c_str[188];
			}
			if( good == false ) {
				if( c_str[189] == 0 ) {
					str[0] = 189;
					good = true;
				} else str[190] = c_str[189];
			}
			if( good == false ) {
				if( c_str[190] == 0 ) {
					str[0] = 190;
					good = true;
				} else str[191] = c_str[190];
			}
			if( good == false ) {
				if( c_str[191] == 0 ) {
					str[0] = 191;
					good = true;
				} else str[192] = c_str[191];
			}
			if( good == false ) {
				if( c_str[192] == 0 ) {
					str[0] = 192;
					good = true;
				} else str[193] = c_str[192];
			}
			if( good == false ) {
				if( c_str[193] == 0 ) {
					str[0] = 193;
					good = true;
				} else str[194] = c_str[193];
			}
			if( good == false ) {
				if( c_str[194] == 0 ) {
					str[0] = 194;
					good = true;
				} else str[195] = c_str[194];
			}
			if( good == false ) {
				if( c_str[195] == 0 ) {
					str[0] = 195;
					good = true;
				} else str[196] = c_str[195];
			}
			if( good == false ) {
				if( c_str[196] == 0 ) {
					str[0] = 196;
					good = true;
				} else str[197] = c_str[196];
			}
			if( good == false ) {
				if( c_str[197] == 0 ) {
					str[0] = 197;
					good = true;
				} else str[198] = c_str[197];
			}
			if( good == false ) {
				if( c_str[198] == 0 ) {
					str[0] = 198;
					good = true;
				} else str[199] = c_str[198];
			}
			if( good == false ) {
				if( c_str[199] == 0 ) {
					str[0] = 199;
					good = true;
				} else str[200] = c_str[199];
			}
			if( good == false ) {
				if( c_str[200] == 0 ) {
					str[0] = 200;
					good = true;
				} else str[201] = c_str[200];
			}
			if( good == false ) {
				if( c_str[201] == 0 ) {
					str[0] = 201;
					good = true;
				} else str[202] = c_str[201];
			}
			if( good == false ) {
				if( c_str[202] == 0 ) {
					str[0] = 202;
					good = true;
				} else str[203] = c_str[202];
			}
			if( good == false ) {
				if( c_str[203] == 0 ) {
					str[0] = 203;
					good = true;
				} else str[204] = c_str[203];
			}
			if( good == false ) {
				if( c_str[204] == 0 ) {
					str[0] = 204;
					good = true;
				} else str[205] = c_str[204];
			}
			if( good == false ) {
				if( c_str[205] == 0 ) {
					str[0] = 205;
					good = true;
				} else str[206] = c_str[205];
			}
			if( good == false ) {
				if( c_str[206] == 0 ) {
					str[0] = 206;
					good = true;
				} else str[207] = c_str[206];
			}
			if( good == false ) {
				if( c_str[207] == 0 ) {
					str[0] = 207;
					good = true;
				} else str[208] = c_str[207];
			}
			if( good == false ) {
				if( c_str[208] == 0 ) {
					str[0] = 208;
					good = true;
				} else str[209] = c_str[208];
			}
			if( good == false ) {
				if( c_str[209] == 0 ) {
					str[0] = 209;
					good = true;
				} else str[210] = c_str[209];
			}
			if( good == false ) {
				if( c_str[210] == 0 ) {
					str[0] = 210;
					good = true;
				} else str[211] = c_str[210];
			}
			if( good == false ) {
				if( c_str[211] == 0 ) {
					str[0] = 211;
					good = true;
				} else str[212] = c_str[211];
			}
			if( good == false ) {
				if( c_str[212] == 0 ) {
					str[0] = 212;
					good = true;
				} else str[213] = c_str[212];
			}
			if( good == false ) {
				if( c_str[213] == 0 ) {
					str[0] = 213;
					good = true;
				} else str[214] = c_str[213];
			}
			if( good == false ) {
				if( c_str[214] == 0 ) {
					str[0] = 214;
					good = true;
				} else str[215] = c_str[214];
			}
			if( good == false ) {
				if( c_str[215] == 0 ) {
					str[0] = 215;
					good = true;
				} else str[216] = c_str[215];
			}
			if( good == false ) {
				if( c_str[216] == 0 ) {
					str[0] = 216;
					good = true;
				} else str[217] = c_str[216];
			}
			if( good == false ) {
				if( c_str[217] == 0 ) {
					str[0] = 217;
					good = true;
				} else str[218] = c_str[217];
			}
			if( good == false ) {
				if( c_str[218] == 0 ) {
					str[0] = 218;
					good = true;
				} else str[219] = c_str[218];
			}
			if( good == false ) {
				if( c_str[219] == 0 ) {
					str[0] = 219;
					good = true;
				} else str[220] = c_str[219];
			}
			if( good == false ) {
				if( c_str[220] == 0 ) {
					str[0] = 220;
					good = true;
				} else str[221] = c_str[220];
			}
			if( good == false ) {
				if( c_str[221] == 0 ) {
					str[0] = 221;
					good = true;
				} else str[222] = c_str[221];
			}
			if( good == false ) {
				if( c_str[222] == 0 ) {
					str[0] = 222;
					good = true;
				} else str[223] = c_str[222];
			}
			if( good == false ) {
				if( c_str[223] == 0 ) {
					str[0] = 223;
					good = true;
				} else str[224] = c_str[223];
			}
			if( good == false ) {
				if( c_str[224] == 0 ) {
					str[0] = 224;
					good = true;
				} else str[225] = c_str[224];
			}
			if( good == false ) {
				if( c_str[225] == 0 ) {
					str[0] = 225;
					good = true;
				} else str[226] = c_str[225];
			}
			if( good == false ) {
				if( c_str[226] == 0 ) {
					str[0] = 226;
					good = true;
				} else str[227] = c_str[226];
			}
			if( good == false ) {
				if( c_str[227] == 0 ) {
					str[0] = 227;
					good = true;
				} else str[228] = c_str[227];
			}
			if( good == false ) {
				if( c_str[228] == 0 ) {
					str[0] = 228;
					good = true;
				} else str[229] = c_str[228];
			}
			if( good == false ) {
				if( c_str[229] == 0 ) {
					str[0] = 229;
					good = true;
				} else str[230] = c_str[229];
			}
			if( good == false ) {
				if( c_str[230] == 0 ) {
					str[0] = 230;
					good = true;
				} else str[231] = c_str[230];
			}
			if( good == false ) {
				if( c_str[231] == 0 ) {
					str[0] = 231;
					good = true;
				} else str[232] = c_str[231];
			}
			if( good == false ) {
				if( c_str[232] == 0 ) {
					str[0] = 232;
					good = true;
				} else str[233] = c_str[232];
			}
			if( good == false ) {
				if( c_str[233] == 0 ) {
					str[0] = 233;
					good = true;
				} else str[234] = c_str[233];
			}
			if( good == false ) {
				if( c_str[234] == 0 ) {
					str[0] = 234;
					good = true;
				} else str[235] = c_str[234];
			}
			if( good == false ) {
				if( c_str[235] == 0 ) {
					str[0] = 235;
					good = true;
				} else str[236] = c_str[235];
			}
			if( good == false ) {
				if( c_str[236] == 0 ) {
					str[0] = 236;
					good = true;
				} else str[237] = c_str[236];
			}
			if( good == false ) {
				if( c_str[237] == 0 ) {
					str[0] = 237;
					good = true;
				} else str[238] = c_str[237];
			}
			if( good == false ) {
				if( c_str[238] == 0 ) {
					str[0] = 238;
					good = true;
				} else str[239] = c_str[238];
			}
			if( good == false ) {
				if( c_str[239] == 0 ) {
					str[0] = 239;
					good = true;
				} else str[240] = c_str[239];
			}
			if( good == false ) {
				if( c_str[240] == 0 ) {
					str[0] = 240;
					good = true;
				} else str[241] = c_str[240];
			}
			if( good == false ) {
				if( c_str[241] == 0 ) {
					str[0] = 241;
					good = true;
				} else str[242] = c_str[241];
			}
			if( good == false ) {
				if( c_str[242] == 0 ) {
					str[0] = 242;
					good = true;
				} else str[243] = c_str[242];
			}
			if( good == false ) {
				if( c_str[243] == 0 ) {
					str[0] = 243;
					good = true;
				} else str[244] = c_str[243];
			}
			if( good == false ) {
				if( c_str[244] == 0 ) {
					str[0] = 244;
					good = true;
				} else str[245] = c_str[244];
			}
			if( good == false ) {
				if( c_str[245] == 0 ) {
					str[0] = 245;
					good = true;
				} else str[246] = c_str[245];
			}
			if( good == false ) {
				if( c_str[246] == 0 ) {
					str[0] = 246;
					good = true;
				} else str[247] = c_str[246];
			}
			if( good == false ) {
				if( c_str[247] == 0 ) {
					str[0] = 247;
					good = true;
				} else str[248] = c_str[247];
			}
			if( good == false ) {
				if( c_str[248] == 0 ) {
					str[0] = 248;
					good = true;
				} else str[249] = c_str[248];
			}
			if( good == false ) {
				if( c_str[249] == 0 ) {
					str[0] = 249;
					good = true;
				} else str[250] = c_str[249];
			}
			if( good == false ) {
				if( c_str[250] == 0 ) {
					str[0] = 250;
					good = true;
				} else str[251] = c_str[250];
			}
			if( good == false ) {
				if( c_str[251] == 0 ) {
					str[0] = 251;
					good = true;
				} else str[252] = c_str[251];
			}
			if( good == false ) {
				if( c_str[252] == 0 ) {
					str[0] = 252;
					good = true;
				} else str[253] = c_str[252];
			}
			if( good == false ) {
				if( c_str[253] == 0 ) {
					str[0] = 253;
					good = true;
				} else str[254] = c_str[253];
			}
			if( good == false ) {
				if( c_str[254] == 0 ) {
					str[0] = 254;
					good = true;
				} else str[255] = c_str[254];
			}
			if( good == false ) {
				if( c_str[255] == 0 ) {
					str[0] = 255;
					good = true;
				} else str[256] = c_str[255];
			}
			
			if( 1 <= *str )
				c_str[0] = str[1];
			else
				c_str[0] = 0;
			if( 2 <= *str )
				c_str[1] = str[2];
			else
				c_str[1] = 0;
			if( 3 <= *str )
				c_str[2] = str[3];
			else
				c_str[2] = 0;
			if( 4 <= *str )
				c_str[3] = str[4];
			else
				c_str[3] = 0;
			if( 5 <= *str )
				c_str[4] = str[5];
			else
				c_str[4] = 0;
			if( 6 <= *str )
				c_str[5] = str[6];
			else
				c_str[5] = 0;
			if( 7 <= *str )
				c_str[6] = str[7];
			else
				c_str[6] = 0;
			if( 8 <= *str )
				c_str[7] = str[8];
			else
				c_str[7] = 0;
			if( 9 <= *str )
				c_str[8] = str[9];
			else
				c_str[8] = 0;
			if( 10 <= *str )
				c_str[9] = str[10];
			else
				c_str[9] = 0;
			if( 11 <= *str )
				c_str[10] = str[11];
			else
				c_str[10] = 0;
			if( 12 <= *str )
				c_str[11] = str[12];
			else
				c_str[11] = 0;
			if( 13 <= *str )
				c_str[12] = str[13];
			else
				c_str[12] = 0;
			if( 14 <= *str )
				c_str[13] = str[14];
			else
				c_str[13] = 0;
			if( 15 <= *str )
				c_str[14] = str[15];
			else
				c_str[14] = 0;
			if( 16 <= *str )
				c_str[15] = str[16];
			else
				c_str[15] = 0;
			if( 17 <= *str )
				c_str[16] = str[17];
			else
				c_str[16] = 0;
			if( 18 <= *str )
				c_str[17] = str[18];
			else
				c_str[17] = 0;
			if( 19 <= *str )
				c_str[18] = str[19];
			else
				c_str[18] = 0;
			if( 20 <= *str )
				c_str[19] = str[20];
			else
				c_str[19] = 0;
			if( 21 <= *str )
				c_str[20] = str[21];
			else
				c_str[20] = 0;
			if( 22 <= *str )
				c_str[21] = str[22];
			else
				c_str[21] = 0;
			if( 23 <= *str )
				c_str[22] = str[23];
			else
				c_str[22] = 0;
			if( 24 <= *str )
				c_str[23] = str[24];
			else
				c_str[23] = 0;
			if( 25 <= *str )
				c_str[24] = str[25];
			else
				c_str[24] = 0;
			if( 26 <= *str )
				c_str[25] = str[26];
			else
				c_str[25] = 0;
			if( 27 <= *str )
				c_str[26] = str[27];
			else
				c_str[26] = 0;
			if( 28 <= *str )
				c_str[27] = str[28];
			else
				c_str[27] = 0;
			if( 29 <= *str )
				c_str[28] = str[29];
			else
				c_str[28] = 0;
			if( 30 <= *str )
				c_str[29] = str[30];
			else
				c_str[29] = 0;
			if( 31 <= *str )
				c_str[30] = str[31];
			else
				c_str[30] = 0;
			if( 32 <= *str )
				c_str[31] = str[32];
			else
				c_str[31] = 0;
			if( 33 <= *str )
				c_str[32] = str[33];
			else
				c_str[32] = 0;
			if( 34 <= *str )
				c_str[33] = str[34];
			else
				c_str[33] = 0;
			if( 35 <= *str )
				c_str[34] = str[35];
			else
				c_str[34] = 0;
			if( 36 <= *str )
				c_str[35] = str[36];
			else
				c_str[35] = 0;
			if( 37 <= *str )
				c_str[36] = str[37];
			else
				c_str[36] = 0;
			if( 38 <= *str )
				c_str[37] = str[38];
			else
				c_str[37] = 0;
			if( 39 <= *str )
				c_str[38] = str[39];
			else
				c_str[38] = 0;
			if( 40 <= *str )
				c_str[39] = str[40];
			else
				c_str[39] = 0;
			if( 41 <= *str )
				c_str[40] = str[41];
			else
				c_str[40] = 0;
			if( 42 <= *str )
				c_str[41] = str[42];
			else
				c_str[41] = 0;
			if( 43 <= *str )
				c_str[42] = str[43];
			else
				c_str[42] = 0;
			if( 44 <= *str )
				c_str[43] = str[44];
			else
				c_str[43] = 0;
			if( 45 <= *str )
				c_str[44] = str[45];
			else
				c_str[44] = 0;
			if( 46 <= *str )
				c_str[45] = str[46];
			else
				c_str[45] = 0;
			if( 47 <= *str )
				c_str[46] = str[47];
			else
				c_str[46] = 0;
			if( 48 <= *str )
				c_str[47] = str[48];
			else
				c_str[47] = 0;
			if( 49 <= *str )
				c_str[48] = str[49];
			else
				c_str[48] = 0;
			if( 50 <= *str )
				c_str[49] = str[50];
			else
				c_str[49] = 0;
			if( 51 <= *str )
				c_str[50] = str[51];
			else
				c_str[50] = 0;
			if( 52 <= *str )
				c_str[51] = str[52];
			else
				c_str[51] = 0;
			if( 53 <= *str )
				c_str[52] = str[53];
			else
				c_str[52] = 0;
			if( 54 <= *str )
				c_str[53] = str[54];
			else
				c_str[53] = 0;
			if( 55 <= *str )
				c_str[54] = str[55];
			else
				c_str[54] = 0;
			if( 56 <= *str )
				c_str[55] = str[56];
			else
				c_str[55] = 0;
			if( 57 <= *str )
				c_str[56] = str[57];
			else
				c_str[56] = 0;
			if( 58 <= *str )
				c_str[57] = str[58];
			else
				c_str[57] = 0;
			if( 59 <= *str )
				c_str[58] = str[59];
			else
				c_str[58] = 0;
			if( 60 <= *str )
				c_str[59] = str[60];
			else
				c_str[59] = 0;
			if( 61 <= *str )
				c_str[60] = str[61];
			else
				c_str[60] = 0;
			if( 62 <= *str )
				c_str[61] = str[62];
			else
				c_str[61] = 0;
			if( 63 <= *str )
				c_str[62] = str[63];
			else
				c_str[62] = 0;
			if( 64 <= *str )
				c_str[63] = str[64];
			else
				c_str[63] = 0;
			if( 65 <= *str )
				c_str[64] = str[65];
			else
				c_str[64] = 0;
			if( 66 <= *str )
				c_str[65] = str[66];
			else
				c_str[65] = 0;
			if( 67 <= *str )
				c_str[66] = str[67];
			else
				c_str[66] = 0;
			if( 68 <= *str )
				c_str[67] = str[68];
			else
				c_str[67] = 0;
			if( 69 <= *str )
				c_str[68] = str[69];
			else
				c_str[68] = 0;
			if( 70 <= *str )
				c_str[69] = str[70];
			else
				c_str[69] = 0;
			if( 71 <= *str )
				c_str[70] = str[71];
			else
				c_str[70] = 0;
			if( 72 <= *str )
				c_str[71] = str[72];
			else
				c_str[71] = 0;
			if( 73 <= *str )
				c_str[72] = str[73];
			else
				c_str[72] = 0;
			if( 74 <= *str )
				c_str[73] = str[74];
			else
				c_str[73] = 0;
			if( 75 <= *str )
				c_str[74] = str[75];
			else
				c_str[74] = 0;
			if( 76 <= *str )
				c_str[75] = str[76];
			else
				c_str[75] = 0;
			if( 77 <= *str )
				c_str[76] = str[77];
			else
				c_str[76] = 0;
			if( 78 <= *str )
				c_str[77] = str[78];
			else
				c_str[77] = 0;
			if( 79 <= *str )
				c_str[78] = str[79];
			else
				c_str[78] = 0;
			if( 80 <= *str )
				c_str[79] = str[80];
			else
				c_str[79] = 0;
			if( 81 <= *str )
				c_str[80] = str[81];
			else
				c_str[80] = 0;
			if( 82 <= *str )
				c_str[81] = str[82];
			else
				c_str[81] = 0;
			if( 83 <= *str )
				c_str[82] = str[83];
			else
				c_str[82] = 0;
			if( 84 <= *str )
				c_str[83] = str[84];
			else
				c_str[83] = 0;
			if( 85 <= *str )
				c_str[84] = str[85];
			else
				c_str[84] = 0;
			if( 86 <= *str )
				c_str[85] = str[86];
			else
				c_str[85] = 0;
			if( 87 <= *str )
				c_str[86] = str[87];
			else
				c_str[86] = 0;
			if( 88 <= *str )
				c_str[87] = str[88];
			else
				c_str[87] = 0;
			if( 89 <= *str )
				c_str[88] = str[89];
			else
				c_str[88] = 0;
			if( 90 <= *str )
				c_str[89] = str[90];
			else
				c_str[89] = 0;
			if( 91 <= *str )
				c_str[90] = str[91];
			else
				c_str[90] = 0;
			if( 92 <= *str )
				c_str[91] = str[92];
			else
				c_str[91] = 0;
			if( 93 <= *str )
				c_str[92] = str[93];
			else
				c_str[92] = 0;
			if( 94 <= *str )
				c_str[93] = str[94];
			else
				c_str[93] = 0;
			if( 95 <= *str )
				c_str[94] = str[95];
			else
				c_str[94] = 0;
			if( 96 <= *str )
				c_str[95] = str[96];
			else
				c_str[95] = 0;
			if( 97 <= *str )
				c_str[96] = str[97];
			else
				c_str[96] = 0;
			if( 98 <= *str )
				c_str[97] = str[98];
			else
				c_str[97] = 0;
			if( 99 <= *str )
				c_str[98] = str[99];
			else
				c_str[98] = 0;
			if( 100 <= *str )
				c_str[99] = str[100];
			else
				c_str[99] = 0;
			if( 101 <= *str )
				c_str[100] = str[101];
			else
				c_str[100] = 0;
			if( 102 <= *str )
				c_str[101] = str[102];
			else
				c_str[101] = 0;
			if( 103 <= *str )
				c_str[102] = str[103];
			else
				c_str[102] = 0;
			if( 104 <= *str )
				c_str[103] = str[104];
			else
				c_str[103] = 0;
			if( 105 <= *str )
				c_str[104] = str[105];
			else
				c_str[104] = 0;
			if( 106 <= *str )
				c_str[105] = str[106];
			else
				c_str[105] = 0;
			if( 107 <= *str )
				c_str[106] = str[107];
			else
				c_str[106] = 0;
			if( 108 <= *str )
				c_str[107] = str[108];
			else
				c_str[107] = 0;
			if( 109 <= *str )
				c_str[108] = str[109];
			else
				c_str[108] = 0;
			if( 110 <= *str )
				c_str[109] = str[110];
			else
				c_str[109] = 0;
			if( 111 <= *str )
				c_str[110] = str[111];
			else
				c_str[110] = 0;
			if( 112 <= *str )
				c_str[111] = str[112];
			else
				c_str[111] = 0;
			if( 113 <= *str )
				c_str[112] = str[113];
			else
				c_str[112] = 0;
			if( 114 <= *str )
				c_str[113] = str[114];
			else
				c_str[113] = 0;
			if( 115 <= *str )
				c_str[114] = str[115];
			else
				c_str[114] = 0;
			if( 116 <= *str )
				c_str[115] = str[116];
			else
				c_str[115] = 0;
			if( 117 <= *str )
				c_str[116] = str[117];
			else
				c_str[116] = 0;
			if( 118 <= *str )
				c_str[117] = str[118];
			else
				c_str[117] = 0;
			if( 119 <= *str )
				c_str[118] = str[119];
			else
				c_str[118] = 0;
			if( 120 <= *str )
				c_str[119] = str[120];
			else
				c_str[119] = 0;
			if( 121 <= *str )
				c_str[120] = str[121];
			else
				c_str[120] = 0;
			if( 122 <= *str )
				c_str[121] = str[122];
			else
				c_str[121] = 0;
			if( 123 <= *str )
				c_str[122] = str[123];
			else
				c_str[122] = 0;
			if( 124 <= *str )
				c_str[123] = str[124];
			else
				c_str[123] = 0;
			if( 125 <= *str )
				c_str[124] = str[125];
			else
				c_str[124] = 0;
			if( 126 <= *str )
				c_str[125] = str[126];
			else
				c_str[125] = 0;
			if( 127 <= *str )
				c_str[126] = str[127];
			else
				c_str[126] = 0;
			if( 128 <= *str )
				c_str[127] = str[128];
			else
				c_str[127] = 0;
			if( 129 <= *str )
				c_str[128] = str[129];
			else
				c_str[128] = 0;
			if( 130 <= *str )
				c_str[129] = str[130];
			else
				c_str[129] = 0;
			if( 131 <= *str )
				c_str[130] = str[131];
			else
				c_str[130] = 0;
			if( 132 <= *str )
				c_str[131] = str[132];
			else
				c_str[131] = 0;
			if( 133 <= *str )
				c_str[132] = str[133];
			else
				c_str[132] = 0;
			if( 134 <= *str )
				c_str[133] = str[134];
			else
				c_str[133] = 0;
			if( 135 <= *str )
				c_str[134] = str[135];
			else
				c_str[134] = 0;
			if( 136 <= *str )
				c_str[135] = str[136];
			else
				c_str[135] = 0;
			if( 137 <= *str )
				c_str[136] = str[137];
			else
				c_str[136] = 0;
			if( 138 <= *str )
				c_str[137] = str[138];
			else
				c_str[137] = 0;
			if( 139 <= *str )
				c_str[138] = str[139];
			else
				c_str[138] = 0;
			if( 140 <= *str )
				c_str[139] = str[140];
			else
				c_str[139] = 0;
			if( 141 <= *str )
				c_str[140] = str[141];
			else
				c_str[140] = 0;
			if( 142 <= *str )
				c_str[141] = str[142];
			else
				c_str[141] = 0;
			if( 143 <= *str )
				c_str[142] = str[143];
			else
				c_str[142] = 0;
			if( 144 <= *str )
				c_str[143] = str[144];
			else
				c_str[143] = 0;
			if( 145 <= *str )
				c_str[144] = str[145];
			else
				c_str[144] = 0;
			if( 146 <= *str )
				c_str[145] = str[146];
			else
				c_str[145] = 0;
			if( 147 <= *str )
				c_str[146] = str[147];
			else
				c_str[146] = 0;
			if( 148 <= *str )
				c_str[147] = str[148];
			else
				c_str[147] = 0;
			if( 149 <= *str )
				c_str[148] = str[149];
			else
				c_str[148] = 0;
			if( 150 <= *str )
				c_str[149] = str[150];
			else
				c_str[149] = 0;
			if( 151 <= *str )
				c_str[150] = str[151];
			else
				c_str[150] = 0;
			if( 152 <= *str )
				c_str[151] = str[152];
			else
				c_str[151] = 0;
			if( 153 <= *str )
				c_str[152] = str[153];
			else
				c_str[152] = 0;
			if( 154 <= *str )
				c_str[153] = str[154];
			else
				c_str[153] = 0;
			if( 155 <= *str )
				c_str[154] = str[155];
			else
				c_str[154] = 0;
			if( 156 <= *str )
				c_str[155] = str[156];
			else
				c_str[155] = 0;
			if( 157 <= *str )
				c_str[156] = str[157];
			else
				c_str[156] = 0;
			if( 158 <= *str )
				c_str[157] = str[158];
			else
				c_str[157] = 0;
			if( 159 <= *str )
				c_str[158] = str[159];
			else
				c_str[158] = 0;
			if( 160 <= *str )
				c_str[159] = str[160];
			else
				c_str[159] = 0;
			if( 161 <= *str )
				c_str[160] = str[161];
			else
				c_str[160] = 0;
			if( 162 <= *str )
				c_str[161] = str[162];
			else
				c_str[161] = 0;
			if( 163 <= *str )
				c_str[162] = str[163];
			else
				c_str[162] = 0;
			if( 164 <= *str )
				c_str[163] = str[164];
			else
				c_str[163] = 0;
			if( 165 <= *str )
				c_str[164] = str[165];
			else
				c_str[164] = 0;
			if( 166 <= *str )
				c_str[165] = str[166];
			else
				c_str[165] = 0;
			if( 167 <= *str )
				c_str[166] = str[167];
			else
				c_str[166] = 0;
			if( 168 <= *str )
				c_str[167] = str[168];
			else
				c_str[167] = 0;
			if( 169 <= *str )
				c_str[168] = str[169];
			else
				c_str[168] = 0;
			if( 170 <= *str )
				c_str[169] = str[170];
			else
				c_str[169] = 0;
			if( 171 <= *str )
				c_str[170] = str[171];
			else
				c_str[170] = 0;
			if( 172 <= *str )
				c_str[171] = str[172];
			else
				c_str[171] = 0;
			if( 173 <= *str )
				c_str[172] = str[173];
			else
				c_str[172] = 0;
			if( 174 <= *str )
				c_str[173] = str[174];
			else
				c_str[173] = 0;
			if( 175 <= *str )
				c_str[174] = str[175];
			else
				c_str[174] = 0;
			if( 176 <= *str )
				c_str[175] = str[176];
			else
				c_str[175] = 0;
			if( 177 <= *str )
				c_str[176] = str[177];
			else
				c_str[176] = 0;
			if( 178 <= *str )
				c_str[177] = str[178];
			else
				c_str[177] = 0;
			if( 179 <= *str )
				c_str[178] = str[179];
			else
				c_str[178] = 0;
			if( 180 <= *str )
				c_str[179] = str[180];
			else
				c_str[179] = 0;
			if( 181 <= *str )
				c_str[180] = str[181];
			else
				c_str[180] = 0;
			if( 182 <= *str )
				c_str[181] = str[182];
			else
				c_str[181] = 0;
			if( 183 <= *str )
				c_str[182] = str[183];
			else
				c_str[182] = 0;
			if( 184 <= *str )
				c_str[183] = str[184];
			else
				c_str[183] = 0;
			if( 185 <= *str )
				c_str[184] = str[185];
			else
				c_str[184] = 0;
			if( 186 <= *str )
				c_str[185] = str[186];
			else
				c_str[185] = 0;
			if( 187 <= *str )
				c_str[186] = str[187];
			else
				c_str[186] = 0;
			if( 188 <= *str )
				c_str[187] = str[188];
			else
				c_str[187] = 0;
			if( 189 <= *str )
				c_str[188] = str[189];
			else
				c_str[188] = 0;
			if( 190 <= *str )
				c_str[189] = str[190];
			else
				c_str[189] = 0;
			if( 191 <= *str )
				c_str[190] = str[191];
			else
				c_str[190] = 0;
			if( 192 <= *str )
				c_str[191] = str[192];
			else
				c_str[191] = 0;
			if( 193 <= *str )
				c_str[192] = str[193];
			else
				c_str[192] = 0;
			if( 194 <= *str )
				c_str[193] = str[194];
			else
				c_str[193] = 0;
			if( 195 <= *str )
				c_str[194] = str[195];
			else
				c_str[194] = 0;
			if( 196 <= *str )
				c_str[195] = str[196];
			else
				c_str[195] = 0;
			if( 197 <= *str )
				c_str[196] = str[197];
			else
				c_str[196] = 0;
			if( 198 <= *str )
				c_str[197] = str[198];
			else
				c_str[197] = 0;
			if( 199 <= *str )
				c_str[198] = str[199];
			else
				c_str[198] = 0;
			if( 200 <= *str )
				c_str[199] = str[200];
			else
				c_str[199] = 0;
			if( 201 <= *str )
				c_str[200] = str[201];
			else
				c_str[200] = 0;
			if( 202 <= *str )
				c_str[201] = str[202];
			else
				c_str[201] = 0;
			if( 203 <= *str )
				c_str[202] = str[203];
			else
				c_str[202] = 0;
			if( 204 <= *str )
				c_str[203] = str[204];
			else
				c_str[203] = 0;
			if( 205 <= *str )
				c_str[204] = str[205];
			else
				c_str[204] = 0;
			if( 206 <= *str )
				c_str[205] = str[206];
			else
				c_str[205] = 0;
			if( 207 <= *str )
				c_str[206] = str[207];
			else
				c_str[206] = 0;
			if( 208 <= *str )
				c_str[207] = str[208];
			else
				c_str[207] = 0;
			if( 209 <= *str )
				c_str[208] = str[209];
			else
				c_str[208] = 0;
			if( 210 <= *str )
				c_str[209] = str[210];
			else
				c_str[209] = 0;
			if( 211 <= *str )
				c_str[210] = str[211];
			else
				c_str[210] = 0;
			if( 212 <= *str )
				c_str[211] = str[212];
			else
				c_str[211] = 0;
			if( 213 <= *str )
				c_str[212] = str[213];
			else
				c_str[212] = 0;
			if( 214 <= *str )
				c_str[213] = str[214];
			else
				c_str[213] = 0;
			if( 215 <= *str )
				c_str[214] = str[215];
			else
				c_str[214] = 0;
			if( 216 <= *str )
				c_str[215] = str[216];
			else
				c_str[215] = 0;
			if( 217 <= *str )
				c_str[216] = str[217];
			else
				c_str[216] = 0;
			if( 218 <= *str )
				c_str[217] = str[218];
			else
				c_str[217] = 0;
			if( 219 <= *str )
				c_str[218] = str[219];
			else
				c_str[218] = 0;
			if( 220 <= *str )
				c_str[219] = str[220];
			else
				c_str[219] = 0;
			if( 221 <= *str )
				c_str[220] = str[221];
			else
				c_str[220] = 0;
			if( 222 <= *str )
				c_str[221] = str[222];
			else
				c_str[221] = 0;
			if( 223 <= *str )
				c_str[222] = str[223];
			else
				c_str[222] = 0;
			if( 224 <= *str )
				c_str[223] = str[224];
			else
				c_str[223] = 0;
			if( 225 <= *str )
				c_str[224] = str[225];
			else
				c_str[224] = 0;
			if( 226 <= *str )
				c_str[225] = str[226];
			else
				c_str[225] = 0;
			if( 227 <= *str )
				c_str[226] = str[227];
			else
				c_str[226] = 0;
			if( 228 <= *str )
				c_str[227] = str[228];
			else
				c_str[227] = 0;
			if( 229 <= *str )
				c_str[228] = str[229];
			else
				c_str[228] = 0;
			if( 230 <= *str )
				c_str[229] = str[230];
			else
				c_str[229] = 0;
			if( 231 <= *str )
				c_str[230] = str[231];
			else
				c_str[230] = 0;
			if( 232 <= *str )
				c_str[231] = str[232];
			else
				c_str[231] = 0;
			if( 233 <= *str )
				c_str[232] = str[233];
			else
				c_str[232] = 0;
			if( 234 <= *str )
				c_str[233] = str[234];
			else
				c_str[233] = 0;
			if( 235 <= *str )
				c_str[234] = str[235];
			else
				c_str[234] = 0;
			if( 236 <= *str )
				c_str[235] = str[236];
			else
				c_str[235] = 0;
			if( 237 <= *str )
				c_str[236] = str[237];
			else
				c_str[236] = 0;
			if( 238 <= *str )
				c_str[237] = str[238];
			else
				c_str[237] = 0;
			if( 239 <= *str )
				c_str[238] = str[239];
			else
				c_str[238] = 0;
			if( 240 <= *str )
				c_str[239] = str[240];
			else
				c_str[239] = 0;
			if( 241 <= *str )
				c_str[240] = str[241];
			else
				c_str[240] = 0;
			if( 242 <= *str )
				c_str[241] = str[242];
			else
				c_str[241] = 0;
			if( 243 <= *str )
				c_str[242] = str[243];
			else
				c_str[242] = 0;
			if( 244 <= *str )
				c_str[243] = str[244];
			else
				c_str[243] = 0;
			if( 245 <= *str )
				c_str[244] = str[245];
			else
				c_str[244] = 0;
			if( 246 <= *str )
				c_str[245] = str[246];
			else
				c_str[245] = 0;
			if( 247 <= *str )
				c_str[246] = str[247];
			else
				c_str[246] = 0;
			if( 248 <= *str )
				c_str[247] = str[248];
			else
				c_str[247] = 0;
			if( 249 <= *str )
				c_str[248] = str[249];
			else
				c_str[248] = 0;
			if( 250 <= *str )
				c_str[249] = str[250];
			else
				c_str[249] = 0;
			if( 251 <= *str )
				c_str[250] = str[251];
			else
				c_str[250] = 0;
			if( 252 <= *str )
				c_str[251] = str[252];
			else
				c_str[251] = 0;
			if( 253 <= *str )
				c_str[252] = str[253];
			else
				c_str[252] = 0;
			if( 254 <= *str )
				c_str[253] = str[254];
			else
				c_str[253] = 0;
			if( 255 <= *str )
				c_str[254] = str[255];
			else
				c_str[254] = 0;
			c_str[255] = 0;
			
			tempfileptr = fopen( c_str, "r" );
			
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
