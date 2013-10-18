#include <iostream>
#include <statgrab.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

/*
Output format:
Date	RX	TX
*/

int main ( int argc, char* argv[] ) {
	/* Default interval is 60 seconds (one minute) */
	int interval = 60;

	/* Default interface is eth0 */
	string interface = "eth0";

	/* Default date format is HH:MM:SS */
	string format = "%T";

	/* Check if user specified alternate interface or interval */
	for ( int i = 1; i < argc; i++ ) {
		/* Arguments require values. */
		if ( i + 2 > argc) {
			cerr << "Invalid number of arguments." << endl;
			return 1;
		}

		if ( strcmp(argv[i], "-i") == 0 ) {
			interface = argv[++i];
		} else if ( strcmp(argv[i], "--interval") == 0 ) {
			interval = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-d") == 0 ) {
			format = argv[++i];
		}
	}

	const char* datefmt = format.c_str();

	time_t t = time(0);
	struct tm * d = localtime(&t);

	/* If interval is a minute or higher, align to 0 seconds */
	if ( d->tm_sec > 0 && interval >= 60 ) {
		cerr << "Waiting " << (60 - d->tm_sec + interval) << " seconds." << endl;
		sleep ( 60 - d->tm_sec );
	}

	int* entries = new int;
	sg_network_io_stats* ifstats = sg_get_network_io_stats(entries);

	int offset = -1;

	for ( int i = 0; i < *entries; i++ ) {
		if ( strcmp(ifstats[i].interface_name, interface.c_str()) == 0 ) {
			offset = i;
			break;
		}
	}

	if ( offset == -1 ) {
		cerr << interface << ": interface not found." << endl;
		return 2;
	}

	char datebuffer[256];

	while ( true ) {
		sleep ( interval );

		t = time(0);
		d = localtime(&t);

		ifstats = sg_get_network_io_stats_diff(entries);

		/* Output date */
		strftime(datebuffer, 256, datefmt, d);
		cout << datebuffer << "\t";

		/* Output average throughput for the interval (bytes/time) */
		cout
		<< (ifstats[offset].rx / interval) << "\t"
		<< (ifstats[offset].tx / interval) << endl;
	}
}
