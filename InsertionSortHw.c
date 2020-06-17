#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int CompLen(const char *leftStr,const char *rightStr)
{
    int stringLen1;
    int stringLen2;
    stringLen1=strlen(leftStr);
    stringLen2=strlen(rightStr);
    if(stringLen1>stringLen2)
    {
        return 1;
    }
    else if(stringLen1==stringLen2)
    {
        return 0;
    }
    else
    {
        return -1;
    }


}



int greater(const char *leftStr, const char *rightStr )	{
	return -strcmp(leftStr, rightStr);
}


int Lexigraph(const char *leftStr,const char *rightStr)
{
    int stringLen1;
    int stringLen2;
    stringLen1=strlen(leftStr);
    stringLen2=strlen(rightStr);
    if(stringLen1>stringLen2)
    {
        return 1;
    }
    else if(stringLen1==stringLen2)
    {
        return strcmp(leftStr,rightStr);
    }
    else
    {
        return -1;
    }
}





char** InsertionSort(char** Array,int rows,int given_func(const char*,const char*))
{
    int i,j;
    char *key;
    for(i=1;i<rows;i++)
    {
        key=Array[i];
        j=i-1;

        while(j>=0 && (given_func(Array[j],key))>0 )
            {
                Array[j+1]=Array[j];
                j=j-1;
            }
        Array[j+1]=key;


    }


}










int main()
{
    int i,n;
    int len;
    int dataAllocated=0;
    int count=1;
    int count2=1;
    FILE *file;
    char filename[100];

    int totalStrings;
    char one;
    char StringBuf[101];
    char **table;



    printf("Enter the name of file: ");
    scanf("%s",&filename);
    file=fopen(filename,"r");
    if(file==NULL)
        {
            printf("No file found");
            exit(1);
        }
    else
        {
          for (one = getc(file); one != EOF; one = getc(file))
            {
                count2=count2+1;
                  if (one == '\n')
                    {
                       count = count + 1;
                    }
            }
           totalStrings=count;
           rewind(file);
           //printf("%d\n",totalStrings);
           //StringArr[totalStrings];
           //table[totalStrings];
           table=(char**)malloc(totalStrings*sizeof(char*));

           for(i=0;i<totalStrings;i++)
           {
               fgets(StringBuf,101,file);
               for(n=0;n<strlen(StringBuf);n++)
               {
                   if(isspace(StringBuf[n]))
                   {
                       StringBuf[n]='\0';
                   }

               }
               len=strlen(StringBuf);
               //printf("%d\n",len);
               table[i]=(char*)malloc((len+1)*sizeof(char));
               strcpy(table[i],StringBuf);
               table[i][strlen(StringBuf)]='\0';

           }
          count2=count2-29;
          dataAllocated=(totalStrings*sizeof(void*))+count2;


          printf("\n Data is loaded");
          printf("\n Allocated space for storing the data: %7d B ( %d char and %d pointers)",dataAllocated,count2,totalStrings);
          printf("\n Pointer Size: %d Bytes\n",sizeof(void*));

          printf("\nOriginal data: \n");
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }


          printf("\n--------  compare by LENGTH only --------------\n");
          InsertionSort(table, totalStrings, CompLen);
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }


          printf("\n--------  compare by strcmp --------------\n");
          InsertionSort(table, totalStrings, strcmp);
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }
          fclose(file);


          printf("\n--------  compare by GREATER --------------\n");
          InsertionSort(table, totalStrings, greater);
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }


          printf("\n--------  compare by LENGTH and lexicografic --------------\n");
          InsertionSort(table, totalStrings, Lexigraph);
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }







        }


  for(i=0;i<totalStrings;i++)
  {
      free(table[i]);

  }
free(table);
}
