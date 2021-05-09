#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// for saving information of functions
// data types : short = 0, int = 1, long = 2, char : 3 unsigned short ~ char: 4 ~ 7 , float : 8, double : 9, char* : 10
typedef struct {
    char* name;
    int out;  // out type
    int par_size = 0;
    int* par; // parameter types
} fuc_proto;

//to save variable information
typedef struct {
    char* name;
    char type;  // variable type
} variables;


int typetoint(char* type);
/*
void stubdecision(char* target);
void makestub(fuc_proto proto, FILE* stub);
*/
void driverstart(FILE* driver);
void driverend(FILE* driver);

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        FILE* test_case = fopen(argv[2], "r");
        FILE* driver = fopen("driver.c", "w");
        char[1024] buf;
        driverstart(driver);
        //save target fuction prototype
        fuc_proto target;
        char* tok = strtok(fgets(buf, 1024, test_case), " (),");

        if((target.out = typetoint(tok)) == -1)
        {
            tok = strtok(NULL, " (),");
            target.out = typetoint(tok) + 4;
        }
        tok = strtok(NULL, " (),");

        if(!strcmp(tok, "*"))
            target.out = 10;

        target.name = malloc(sizeof(char) *  (strlen(tok)+1));
        strcpy(target.name,tok);
        tok = strtok(NULL, " (),");

        while(ptr != NULL)
        {
            target.par_size++;
            target.par = realloc(target.par, sizeof(int) * target.par_size);
            if((target.par[target.par_size-1] = typetoint(tok)) == -1)
            {
                tok = strtok(NULL, " (),");
                target.par[target.par_size-1] = typetoint(tok) + 4;
            }
            tok = strtok(NULL, " (),");

            if(!strcmp(tok, "*"))
                target.par[target.par_size-1] = 10;
        }

        //write driver main function 
        int test_num;
        while(!feof(test_case))
        {
            int i;
            char* temp[1024];
            fscanf(test_case, "%d", &test_num);
            fprintf(driver, "if(%s(", target.name);
            for(i = 0; i < par_size-1; i++)
            {
                fscanf(test_case, "%s" temp);
                switch(target.par[i])
                {
                    case 10:
                        fprintf(driver, "\"%s\", ", temp);
                        break;
                    default:
                        fprintf(driver, "%s, ", temp);
                }
            }

            fscanf(test_case, "%s" temp);
            switch(target.par[i])
            {
                case 10:
                    fprintf(driver, "\"%s\") == ", temp);
                    break;
                default:
                    fprintf(driver, "%s) == ", temp);
            }

            fscanf(test_case, "%s" temp);
            switch(target.out)
            {
                case 10:
                    fprintf(driver, "\"%s\")", temp);
                    break;
                default:
                    fprintf(driver, "%s)", temp);
            }

            fprintf(driver, "printf(\"test case %d : pass\\n\");\n", test_num);
            fprintf(driver, "else printf(\"test case 2 : Fail\\n\")\n", test_num);
        }

        driverend(driver);

        fclose(test_case);
        fclose(driver);

        //stubdecision(argv[1]);
    }
    else
    {
        printf("uasage: auto sut.c test_case.txt \n");
    }

    return 0;
}

int typetoint(char* type)
{
    if(!strcmp(type, "short"))
        return 0;
    else if(!strcmp(type, "int"))
        return 1;
    else if(!strcmp(type, "long"))
        return 2;
    else if(!strcmp(type, "char"))
        return 3;
    else if(!strcmp(type, "float"))
        return 8;
    else if(!strcmp(type, "double"))
        return 9;
    else if(!strcmp(type, "char *"))
        return 10;
    else if(!strcmp(type, "unsigned"))
        return -1;
}

/*
void stubdecision(char* target)
{
    FILE* sut = fopen(target, "r");
    FILE* stub = fopen("stub.c", "w");


    fclose(sut);
}

void makestub(fuc_proto proto, FILE* stub)
{

}
*/

void driverstart(FILE* driver)
{
    fprintf(driver, "#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n"); //#include
    fprintf(driver, "\n int main(void){\n");
}

void driverend(FILE* driver)
{
    fprintf(driver, "}\n");
}