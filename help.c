#include "help.h"

char *help_minimal = ""
	"""usage: base-convert [options] initial_base base... number"
	"\n       base-convert [options] initial_base base... -a number..."
	"\n       base-convert {-h|--help}"
"\n";

/*
	For Vim, use :se cursorcolumn
	                               : --------------------------------------------------
*/

char *help_full = ""
	"""Usage"
	"\n    base-convert [options] initial_base base... number"
	"\n    base-convert [options] initial_base base... -a number..."
	"\n    base-convert {-h|--help}"
	"\n"
	"\nDescription"
	"\n    Convert numbers from one base representation to another."
	"\n"
	"\nArguments"
	"\n    number                  : A number to be converted to the other bases."
	"\n    number...               : Multiple numbers to be converted to the other"
	"\n                              bases."
	"\n    initial_base            : The base that numbers' value are initially"
	"\n                              represented with."
	"\n                              Note: All arguments for number must be written in"
	"\n                              this base."
	"\n    base...                 : Bases that numbers will converts into."
	"\n                              Note: At least one base must be provided."
	"\n"
	"\nOptions"
	"\n    -a, --array             : Provide multiple numbers for conversion."
	"\n    -b, --group-base        : Show results grouped together with the same"
	"\n                              base. (default)"
	"\n    -n, --group-number      : Show results grouped together with the same"
	"\n                              initial number."
	"\n    -r, --display-row       : Show results in rows. (default)"
	"\n    -c, --display-column    : Show results in columns."
	"\n    -i, --include-head      : Include the initial number in result."
	"\n    -h, --help              : Show this help file."
	"\n"
	"\nExamples"
	"\n        base-convert 2 10 -a 110100100 1000101"
	"\n    Changes the representation of the numbers '110100100' and '1000101' from"
	"\n    base2 into base10."
"\n";
