/*
    Author: Elmer Rivera
    Date of Program completion: 09/28/2019
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Function takes two strings and determines which string
//is longer and which is shorter. Once computed the function
//returns 1 if the first name is greater than the second,
//returns 0 if the names are equal in length,
//and returns -1 otherwise.
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


//Function used to compare two names at a time and decide
//which is greater. The inverse of the result is returned
//because of the way the sorted name list is intended to be
//displayed.
int greater(const char *leftStr, const char *rightStr )	{
	return -strcmp(leftStr, rightStr);
}

//Function used to compare two names at a time and decide
//which string goes first alphabetically.
//Returns 1 if the first name is greater
//Returns the result strcmp() if the names are equal
//returns -1 otherwise.
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




//Function that takes an array of strings, number of rows in the array, a specified
//function that determines the method of order, and sorts the array of strings using the
//a modified version of the insertion sort algorithm.
//**only modification is given_func(Array[j],key) is written instead of just key in the
//while loop.
//Returns a douple pointer to the array of strings.
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

    //Variable declerations and initializations
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


    //File Input handling and names parsed into an array of strings
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

           //Calculation of the total number of names in the user given file 
           //and allocating memory necessary based on the result 
           totalStrings=count;
           rewind(file);
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
               table[i]=(char*)malloc((len+1)*sizeof(char));
               strcpy(table[i],StringBuf);
               table[i][strlen(StringBuf)]='\0';

           }
          count2=count2-29;
          dataAllocated=(totalStrings*sizeof(void*))+count2;

          //Output showing program progression and displaying stats such as how many pointers and bytes are used.
          printf("\n Data is loaded");
          printf("\n Allocated space for storing the data: %7d B ( %d char and %d pointers)",dataAllocated,count2,totalStrings);
          printf("\n Pointer Size: %d Bytes\n",sizeof(void*));
          
          //Prints the unsorted data as given in the user input file
          printf("\nOriginal data: \n");
          for(i=0;i<totalStrings;i++)
          {
              printf("%s\n",table[i]);
          }

          //All 4 sections of code below print the sorted list of names
          //based on 4 different orders: length,strcmp,greater, and lexicographic
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

//Deallocate the array of strings and all dynamic memory in order to not have memory leaks.
  for(i=0;i<totalStrings;i++)
  {
      free(table[i]);

  }
free(table);
}
