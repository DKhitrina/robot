#include <stdlib.h>

char* int_to_str(int num)
{
	char* ar = NULL;
	int с = 0, n = num;
	while (n!=0){
		n = n/10;
		c++;
	}
	ar = malloc(c+1);
	ar[c] = 0;
	n = num;
	for(i=1; i<=c; i++){
		ar[c-i]=(n%10) + '0';
		n=n/10;
	}
	return ar;
}

int str_to_int(const char* str)
{
	char* ar = str;
	int num = 0;
	while (ar!=0){
		num = num*10 + ar[i] - '0';
		i++;
	}
	return num;
}

bool cmp_str(const char* ar1, const char* ar2)
{
	int i = 0;
	while (ar1[i]!=0){
		if (ar1[i]!=ar2[i]){
			return false;
		}
		i++;
	}
	if (ar2[i]!=0){
		return false;
	}	
	return true;
}

bool check_if_num (char* ar)
{						/*0 - no match, 1 - match*/
	int i = 0;
	while (ar[i]!=0){
		if (ar[i]<'0' || ar[i]>'9')
			return false;
		i++;
	}
	return true;
}

bool check_if_string (char* ar)
{						/*0 - no match, 1 - match*/
	int i = 0;
	while (ar[i]!=0){
		if (ar[i]<'A' || (ar[i]>'Z' && ar[i]<'a')
		|| ar[i]>'z')
			return false;
		i++;
	}
	return true;
}