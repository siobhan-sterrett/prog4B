#include "../src/isFloat.h"

#include <vector>

#include <iostream>
using namespace std;

int main()
{
	std::vector< const char* > strings {
		"0",
		"105",
		"09",
		"9.3",
		"09.3",
		"9.03",
		"9.30",
		"-5",
		"+5",
		"-5.7",
		"+5.7",
		"-0.3",
		"0.3",
		"+0.3",
		"-09.5",
		"-6e7",
		"-6e-7",
		"- 6 e - 7"
	};

	for( const char* str : strings )
		cout << str << " : " << isFloat( str ) << endl;

	return 0;
}
