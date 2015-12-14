#include <stdio.h>
#include "AppMgr/App.h"
#include "Util/OmnNew.h"
#include "Util/JimoEncodingTester/JEUIATorturer_batch.h"


int 
main(int argc, char **argv)
{
	int index = 1;
	int tries = 100*1000*1000;
	while (index < argc)
	{
		if (strcmp(argv[index], "-tries") == 0)
		{
            tries = atoi(argv[index+1]);
			break;
		}
		index++;
	};
	OmnApp theApp(argc, argv);
	srand(time(NULL));
	AosJEUIATorturer_batch *tt = OmnNew AosJEUIATorturer_batch();
    tt->start(tries);

	return 0;

}