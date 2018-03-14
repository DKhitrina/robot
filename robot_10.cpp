#include <stdio.h>
#include <stdlib.h>

#define CREATEMODE 0
#define JOINMODE 1

int cmp_str(const char* ar1, const char* ar2)
{						/*0 - no match 1 - match*/
	int i = 0;
	while (ar1[i]!=0){
		if (ar1[i]!=ar2[i])
			return 0;
		i++;
	}
	if (ar2[i]!=0)
		return 0;
	return 1;
}

int check_if_num (char* ar)
{						/*0 - no match, 1 - match*/
	int i = 0;
	while (ar[i]!=0){
		if (ar[i]<'0' || ar[i]>'9')
			return 0;
		i++;
	}
	return 1;
}

int check_if_string (char* ar)
{						/*0 - no match, 1 - match*/
	int i = 0;
	while (ar[i]!=0){
		if (ar[i]<'A' || (ar[i]>'Z' && ar[i]<'a')
		|| ar[i]>'z')
			return 0;
		i++;
	}
	return 1;
}

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
	int ch = check_arguments(argc, argv);
	/*ch==CREATEMODE//JOINMODE*/
	if (ch==CREATEMODE)
		printf ("Create mode\n");
	if (ch==JOINMODE)
		printf ("Join mode\n");
	return 0;
}
