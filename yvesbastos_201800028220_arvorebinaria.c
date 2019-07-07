#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct files{

    char name[51];
    char permission[3];
    int size;
    int position;
    struct files *right;
    struct files *left; 

}file;

void initFile(file **root, char name[51], char permission[3], int size, int position){

    file *aux = root[0];

    file *element = (file*)malloc(sizeof(file));
    element->left = NULL;
    element->right = NULL;
    strcpy(element->name, name);
    strcpy(element->permission, permission);
    element->size = size;
    element->position = position;

    if(root[0] == NULL){
        root[0] = element;
        return;
    }
    else{
        while(aux != NULL){
            if(strcmp(aux->name, name) == 0){
                if(strcmp(aux->permission, "rw") == 0){
                    strcpy(aux->permission, permission);
                    aux->size = size;
                    aux->position = position;
                    return;
                }
                else{
                    return;
                }
            }          
            else if(strcmp(aux->name, name) < 0){
                if(aux->right == NULL){
                    aux->right = element;
                    return;
                }     
                else{
                    aux = aux->right;
                }
            }  
            else{
                if(aux->left == NULL){
                    aux->left = element;
                    return;
                }
                else{
                    aux = aux->left;
                }
            }    
        }
    }
}

void EPD(file *root, FILE *output){
    
    if(root == NULL){
        return;
    }
    else{
        EPD(root->left, output);
        fprintf(output, "%d %s %s %d bytes\n", root->position, root->name, root->permission, root->size);
        EPD(root->right, output);
    }
}

void PED(file *root, FILE *output){

    if(root == NULL){
        return;
    }
    else{
        fprintf(output, "%d %s %s %d bytes\n", root->position, root->name, root->permission, root->size);
        PED(root->left, output);
        PED(root->right, output);
    }
}

void EDP(file *root, FILE *output){
    if(root == NULL){
        return;
    }
    else{
        EPD(root->left, output);
        EPD(root->right, output);
        fprintf(output, "%d %s %s %d bytes\n", root->position, root->name, root->permission, root->size);
    }
} 

int main(int argc, char const *argv[]){

    FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

    char name[51], permission[3];
    int size, numbFiles, position = 0;

    file **root = (file**)malloc(sizeof(file*));
    root[0] = NULL;

    fscanf(input, "%d", &numbFiles);
    while(fscanf(input, "%50s %s %d", name, permission, &size) != EOF){

        initFile(root, name, permission, size, position);
        position++;
    }
   
    fprintf(output, "EPD:\n");
    EPD(root[0], output);
    fprintf(output, "PED:\n");
    PED(root[0], output);
    fprintf(output, "EDP:\n");
    EDP(root[0], output);

    fclose(input);
	fclose(output);
    
    return 0;
}
