

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<iostream>



using namespace std;
int main ()
{
int i;
char str[80];
char al[50]="hola gatos";
char ho[50]=" del mundo";



strcat(al,ho);
printf("%s\n",al);
sprintf(str, "rostopic pub -l /hola std_msgs/String '%s'", al);
system(str);

   return(0);
}
