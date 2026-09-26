#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/syscall.h>

void createFile(){
  char name[100];

  printf("Enter the filename to be created: "); fflush(stdout);
  
  scanf("%s", name);
  
  
  int fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
  if(fd > 0){
    write(1, "File created successfull\n", 25);
  }else{
    write(1, "File creation failed\n", 21);
  }
}

void deleteFile(){
  char name[100];
  printf("Enter the filename to be deleted: "); fflush(stdout);
  
  scanf("%s", name);
  // printf("%s\n", name);

  int res = unlink(name);
  if(res == 0){
    write(1, "File deleted\n", 13);
  }else{
    write(1, "Failed to delete\n", 17);
  }
}

void readFile(){
  char name[100];
  write(1, "Enter the filename to be read: ", 30);
  scanf("%s", name);

  int src = open(name, O_RDONLY);

  char buffer[4096];
  int dest = 1, bytes; //stdout 

  while((bytes = read(src, buffer, sizeof(buffer))) > 0){
    write(dest, buffer, bytes);
  }
  close(src);
}

void copyFile(){
  printf("Ente the source and destination filename\n" );
  char from[100], to[100];
  scanf("%s %s", from, to);
  
  int src = open(from, O_RDONLY);
  int dest = open(to, O_WRONLY | O_CREAT, 0666);

  int bytes = 0;
  char buffer[4096];
  while((bytes = read(src, buffer, sizeof(buffer))) > 0){
    write(dest, buffer, sizeof(buffer));
  }
  close(src);
  close(dest);

}

void renameFile(){
  printf("Enter the current filename and the new filename: ");
  char cur[100], new_name[100];
  scanf("%s %s", cur, new_name);

  int res = syscall(SYS_rename, cur, new_name);
  if(res == 0){
    printf("successful\n");
  }else{
    printf("Failed\n");
  }
}

int main(){
  while(1){
    printf("Please enter: \n");
    printf("1 For create a file.\n");
    printf("2 For delete a file.\n");
    printf("3 For read a file.\n");
    printf("4 For write a file.\n");
    printf("5 For copy a file.\n");
    printf("6 For rename a file.\n");
    printf("\n");
    fflush(stdout);

    int n = 0;
    scanf("%d", &n);

    if(n == 1){
      createFile();
    }else if(n == 2){
      deleteFile();
    }else if(n == 3){
      readFile();
    }else if(n == 4){

    }else if(n == 5){
      copyFile();
    }else if(n == 6){
      renameFile();
    }
  }
  
}