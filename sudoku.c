/************/
/* Atah     */
/************/

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BLANK '.'
#define ERROR 1
#define SIZE 81
#define OK 0
#define FOUNDEOF -1

int found = 0;

int valid(char grid[],int index,char c){
  int i,row,col,blockRow,blockCol;

  row = index/9;
  col = index%9;
  blockRow = row/3 * 3;
  blockCol = col/3 * 3;

  for(i = 0;i<9;++i){
    if(grid[9*row+i] == c || grid[9*i +col] == c || grid[9*(blockRow+i/3) + (blockCol+i%3)] == c){
      return 0;
    }
  }
  return 1;
}

int validate(char grid[]){
  char c;
  int i,good;

  for(i = 0;i<SIZE;++i){
    c = grid[i];
    if(c != BLANK){
      if(c < '1' || c > '9') return 0;
      grid[i] = BLANK;
      good = valid(grid,i,c);
      grid[i] = c;
      if(!good) return 0;
    }
  }
  return 1;
}

int solve(char grid[],int i){
  char c;
  if(i >= 81)return 1;
  else if(grid[i] != BLANK)return solve(grid,i+1);
  else{
    for(c = '1';c <= '9'; ++c){
      if(valid(grid,i,c)){
	grid[i] = c;
	if(!solve(grid,i+1)){
	  grid[i] = BLANK;
	}
      }
    }
    return grid[i] != BLANK;
  }
}

void print(char grid[]){
  int i,j;

  for(i = 0;i<9;++i){
    for(j = 0;j<9;++j){
      printf("%c",grid[9+i+j]);
    }
    printf("\n");
  }
}

int EOOL(char c){
  if(c = EOF){
    found = 1;
    return;
  }
  if(c != '\n')printf("%c",c);
  while(c != '\n'){
    c = getchar();
    if(c == EOF){
      found = 1;
      return ERROR;
    }
  }
   if(found)return FOUNDEOF;
   return OK;
}

int main(){
  int res;
  char grid[SIZE+1];
  grid[SIZE] = '\0';

  while(!found){
    res = EOOL(grid[0]);
    if(res == OK) res = validate(grid) ? OK : ERROR;

    if(res == OK)
      {
	if(solve(grid,0))
	  {
	    printf("\n%s\n\n",grid);
	  }
	else printf("\nNo Solution\n\n");
      }
    else if(!found && res == ERROR) printf("\nERROR\n\n");
  }
  return 0;
}
