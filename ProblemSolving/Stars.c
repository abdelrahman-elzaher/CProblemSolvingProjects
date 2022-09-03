#include <stdio.h>
#include <stdlib.h>
void set_Star(char arr[][30],int rows,int cols,int i_star,int j_star)
{

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(i==i_star &&j==j_star)
                arr[i][j]='*';
            else if(i==i_star && j<j_star)
                arr[i][j]='>';
            else if(i==i_star && j>j_star)
                arr[i][j]='<';
            else if(i<i_star &&j==j_star)
                arr[i][j]='v';
            else if(i>i_star &&j==j_star)
                arr[i][j]='^';
            else if(i<i_star && j<j_star)
                arr[i][j]='A';
            else if(i<i_star && j>j_star)
                arr[i][j]='B';
            else if(i>i_star && j<j_star)
                arr[i][j]='C';
            else if(i>i_star && j>j_star)
                arr[i][j]='D';
        }
    }
}

void Search_Star(char arr[][30],int rows,int cols,int *i_star,int *j_star)
{
    int low_rows=0;
    int high_rows=rows-1;
    int low_col=0;
    int high_col=cols-1;
    int mid_row;
    int mid_col;

    while((low_rows<=high_rows &&low_col<=high_col))
    {

        mid_row=(low_rows+high_rows)/2;
        mid_col=(low_col+high_col)/2;
        if(arr[mid_row][mid_col]=='*')
        {
            *i_star=mid_row;
            *j_star=mid_col;
            return 1;
        }
        else if(arr[mid_row][mid_col]=='v')
        {//so it is in the col so the mid_col will be the same and change the rows
         low_rows=mid_row+1;

        }
        else if(arr[mid_row][mid_col]=='^')
        {//so it is in the col so the mid_col will be the same and change the rows
         high_rows=mid_row-1;

        }
        else if(arr[mid_row][mid_col]=='>')
        {
            low_col=mid_col+1;
        }
        else if(arr[mid_row][mid_col]=='<')
        {
            high_col=mid_col-1;
        }
        else if(arr[mid_row][mid_col]=='A')
        {
            low_col=mid_col+1;
            low_rows=mid_row+1;

        }
        else if(arr[mid_row][mid_col]=='B')
        {

            high_col=mid_col-1;
            high_rows=mid_row+1;
        }
        else if(arr[mid_row][mid_col]=='C')
        {
            high_col=mid_col+1;
            high_rows=mid_row-1;
        }
        else if(arr[mid_row][mid_col]=='D')
        {
            high_col=mid_col-1;
            high_rows=mid_row-1;
        }

    }

return;

}
void MatrixPrint(char arr[][30],int i,int j)//arr is  pointer to an array of size 5
{
    for(int rows=0;rows<i;rows++)
    {
        for(int cols=0;cols<j;cols++)
        {
            printf("%c ",arr[rows][cols]);
        }
        printf("\n");
    }

}
int main()
{
    int x, y;
    int index_x,index_y;
    char arr[30][30]={0};

    scanf("%d %d",&x,&y);
    set_Star(arr,10,10,x,y);
    MatrixPrint(arr,10,10);
    Search_Star(arr,10,10,&index_x,&index_y);

    printf("* found in -->%d %d",index_x,index_y);
    printf("Hello world!\n");
    return 0;
}
