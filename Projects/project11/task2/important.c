
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int passwd(char *data, size_t len)
{
	if(strlen(data) < 6) {return 0; }
	unsigned ok;

	if(!ok)
		ok = len;

	if(data[0] == 'o') 
		if(data[1] == 'b')
			if(data[2] == 'i')
				if(data[3] == 'w')
					if(data[4] == 'a')
						if(data[5] == 'n'){
							raise(SIGSEGV); //Bug
						}

	return 0;
}
