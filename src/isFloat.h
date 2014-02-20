#pragma once

#include <map>
#include <functional>

bool isFloat( const char* str )
{
	std::map< const char*, std::function< bool( const char* ) > > states {
		{ "q_0", [&states] ( const char* str ) -> bool {
			return 
				*str == 0 ? false :
				*str == '+' ?
					states["q_1"]( str + 1 ) :
				*str == '-' ?
					states["q_1"]( str + 1 ) :
				*str == ' ' ?
					states["q_1"]( str + 1 ) :
				'1' <= *str and *str <= '9' ?
					states["q_2"]( str + 1 ) :
				*str == '0' ?
					states["q_3"]( str + 1 ) :
				*str == '.' ?
					states["q_5"]( str + 1 ) :
				false;
		} },
		{ "q_1", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				*str == ' ' ?
					states["q_1"]( str + 1 ) :
				*str == '0' ?
					states["q_3"]( str + 1 ) :
				'1' <= *str and *str <= '9' ?
					states["q_2"]( str + 1 ) :	
				*str == '.' ?
					states["q_5"]( str + 1 ) :
				false;
		} },
		{ "q_2", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				'0' <= *str and *str <= '9' ?
					states["q_2"]( str + 1 ) :
				*str == '.' ?
					states["q_4"]( str + 1 ) :
				*str == 'e' ?
					states["q_8"]( str + 1 ) :
				*str == 'E' ?
					states["q_8"]( str + 1 ) :
				*str == ' ' ?
					states["q_7"]( str + 1 ) :
				false;
		} },
		{ "q_3", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				*str == '.' ?
					states["q_4"]( str + 1 ) :
				*str == ' ' ?
					states["q_7"]( str + 1 ) :
				*str == 'e' ?
					states["q_8"]( str + 1 ) :
				*str == 'E' ?
					states["q_8"]( str + 1 ) :
				false;
		} },
		{ "q_4", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				'0' <= *str and *str <= '9' ?
					states["q_6"]( str + 1 ) :	
				*str == ' ' ?
					states["q_7"]( str + 1 ) :
				*str == 'e' ?
					states["q_8"]( str + 1 ) :
				*str == 'E' ?
					states["q_8"]( str + 1 ) :
				false;
		} },
		{ "q_5", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				'0' <= *str and *str <= '9' ?
					states["q_6"]( str + 1 ) :
				false;
		} },
		{ "q_6", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				'0' <= *str and *str <= '9' ?
					states["q_6"]( str + 1 ) :
				*str == ' ' ?
					states["q_7"]( str + 1 ) :
				*str == 'e' ?
					states["q_8"]( str + 1 ) :
				*str == 'E' ?
					states["q_8"]( str + 1 ) :
				false;
		} },
		{ "q_7", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				*str == ' ' ?
					states["q_7"]( str + 1 ) :
				*str == 'e' ?
					states["q_8"]( str + 1 ) :
				*str == 'E' ?
					states["q_8"]( str + 1 ) :
				false;
		} },
		{ "q_8", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				*str == '0' ?
					states["q_12"]( str + 1 ) :
				'1' <= *str and *str <= '9' ?
					states["q_11"]( str + 1 ) :
				*str == ' ' ?
					states["q_9"]( str + 1 ) :
				*str == '+' ?
					states["q_10"]( str + 1 ) :
				*str == '-' ?
					states["q_10"]( str + 1 ) :
				false;
		} },
		{ "q_9", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				*str == '+' ?
					states["q_10"]( str + 1 ) :
				*str == '-' ?
					states["q_10"]( str + 1 ) :
				*str == ' ' ?
					states["q_9"]( str + 1 ) :
				false;
		} },
		{ "q_10", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? false :
				*str == '0' ?
					states["q_12"]( str + 1 ) :
				'1' <= *str and *str <= '9' ?
					states["q_11"]( str + 1 ) :
				*str == ' ' ?
					states["q_10"]( str + 1 ) :
				false;
		} },
		{ "q_11", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				'0' <= *str and *str <= '9' ?
					states["q_11"]( str + 1 ) :
				*str == ' ' ?
					states["q_13"]( str + 1 ) :
				false;
		} },
		{ "q_12", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				*str == ' ' ?
					states["q_13"]( str + 1 ) :
				false;
		} },
		{ "q_13", [&states] ( const char* str ) -> bool {
			return
				*str == 0 ? true :
				*str == ' ' ?
					states["q_13"]( str + 1 ) :
				false;
		} }
	};

	return states[ "q_0" ]( str );
}
