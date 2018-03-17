#include <stdio.h>
#include <stdlib.h>
#include <Server.hpp>
#include <Containers.hpp>
#include <Utils.hpp>

#define CREATEMODE 0
#define JOINMODE 1

int check_arguments(int argc, char** argv)
{
	if (argc!=6){
		printf("You need 5 arguments: IP, port, name, mode,"
		" mode specificator\n");
		exit(1);
	}
	if (!check_if_num (argv[2])){
		printf("Port number must be even\n");	/* check port */
		exit(1);
	}
	if (cmp_str(argv[4], "join"))
		return JOINMODE;
	if (cmp_str(argv[4], "create")){
		if (!check_if_num(argv[5])){
			printf("Number of connections should be even\n");
			exit(1);
		}
		return CREATEMODE;
	}
	printf ("You must point join of create mode\n");
	exit (1);
}

int main (int argc, char** argv)
{
//	int ch = check_arguments(argc, argv);

	Server srv = new Server("Test", "localhost", "4774");
	read();
	delete srv;
	return 0;
}
