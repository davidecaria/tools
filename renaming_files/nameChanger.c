#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


#define PATH "/Users/davide/Desktop/prove"
#define SIZE 100+1 

typedef struct element {
    char *name;
    int numOccurrences;
    char **variants;
} ELEMENT;

char **loadDir(int *);
DIR *openDir();

int main(){

    int i;
    char **names = loadDir(&i);    

    for(int j=0;j<i;j++){
        printf("%s\n",names[j]);
    }

    



    return 0;
}

DIR *openDir(){

    DIR *openDirectory = (DIR *)malloc(sizeof(DIR));
    openDirectory = opendir(PATH);
    if (openDirectory == NULL) {
        fprintf(stderr,"Can't open the directory|\n");
        exit(EXIT_FAILURE);
    }

    return openDirectory;

}

char **loadDir(int *i){

    DIR *openDirectory;
    struct dirent *dirReader;
    
    char **names;
    char *dirName;
    int numberFiles;

    //Scan to get the right number of elements
    openDirectory = openDir();
    numberFiles=0;
    while((dirReader=readdir(openDirectory))!=NULL){
        if(dirReader->d_type == DT_REG && strstr(dirReader->d_name,"Lezione")!=NULL){
            numberFiles++;
        }
    }
    closedir(openDirectory);

    printf("Ci sono %d file utili\n",numberFiles);

    names = (char **)malloc(numberFiles*sizeof(char *));
    if(names == NULL){
        fprintf(stderr,"Error in memory allocation\n");
        exit(EXIT_FAILURE);
    }
    for(int k=0;k<numberFiles;k++){
        names[k] = (char *)malloc((SIZE)*sizeof(char));
        if(names[k]==NULL){
            fprintf(stderr,"Error in memory allocation\n");
            exit(EXIT_FAILURE);
        }
    }

    //Getting the names
    openDirectory = openDir();
    int k=0;
    while((dirReader=readdir(openDirectory))!=NULL){
        if(dirReader->d_type == DT_REG && strstr(dirReader->d_name,"Lezione")!=NULL){
            strcpy(names[k],dirReader->d_name);
            k++;
        }
    }

    *i=numberFiles;

    return names;
}