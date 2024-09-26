#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

const int N = 10;
int *xs = 0;

void print_xs(){
    for(int i=0; i<N; i++){
        printf("%d ", xs[i]);
    }
}

int main(int argc, char *argv[]) {
  printf("hello world\n");

  xs = mmap(NULL,N*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS , 0, 0);
  assert(xs!=MAP_FAILED);

  for(int i=0; i<N; i++){
      xs[i]=i+1;
  }

  pid_t child_pid = fork();
  assert(child_pid!=-1);

  if(child_pid==0){
      //child

      for(int i=0; i<N/2; i++){
          int j = N-1-i;
          int t = xs[i];
          xs[i]=xs[j];
          xs[j]=t;
      }

      printf("Child:\t");
      print_xs();
  }
  else{
      //parent
      waitpid(child_pid, NULL, 0);
      printf("Parent:\t");
      print_xs();
  }

  return 0;
}
