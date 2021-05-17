#include <stdio.h>

int main()
{
   char stringa[20];
   FILE *stream1, *stream2;
	
   stream1 = fopen("prova.txt","wt");
   for(int i=0; i<5; i++){
   	printf("dammi una parola: ");
   	gets(stringa);
   	fwrite(stringa, sizeof(stringa), 1, stream1);
   }		
   fclose(stream1);

   stream2 = fopen("prova.txt","r");
   for(int i=0; i<5; i++){		
   	fread(&stringa, sizeof(stringa), 1, stream2);
   	printf("parola numero %d: %s\n", i, stringa);
   }
}

