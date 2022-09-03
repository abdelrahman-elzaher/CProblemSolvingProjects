#include <stdio.h>
#include <stdlib.h>
int SearchCharInPointers(char **arr,int Size,char TargetChar,int *Rows,int *Cols)
{
    int Count=0;
    *Rows=-1;
    *Cols=-1;
    for(int i=0;i<Size;i++)
    {
        for(int j=0;arr[i][j];j++)
            {
                if(arr[i][j]==TargetChar)
                {
                    if(Count==0)
                    {*Rows=i;
                    *Cols=j;}
                    Count++;
                }
            }
    }
    return Count;
}

int SearchCharInPage(char page[][10],int line,char TargetChar,int *Rows,int *Cols)
{
    for(int i=0;i<line;i++)
    {
        for(int j=0;page[i][j];j++)
            {
                if(page[i][j]==TargetChar)
                {
                    *Rows=i;
                    *Cols=j;
                    return 1;
                }
            }
    }
    return 0;
}

int main()
{
    char page[][10]={"ahmed","khaled","sadek","mohamed"};
    int NumberOfRow,NumberOfChar;
    char ch='l';
    if(SearchCharInPage(page,4,ch,&NumberOfRow,&NumberOfChar))
    {
        printf("found char  %c in Line-->%d  and this char it is index -->%d",ch,NumberOfRow+1,NumberOfChar+1);
    }
    else
    {
        printf("Not Found char");
    }

        return 0;
}
