#include "dev.h"

#define RECOGNIZE_PARENTH_TYPE(x)( ((x) == '{' || (x) == '[' || (x) == '(')? OPENING_PARENTH :                \
                                   ((x) == '}' || (x) == ']' || (x) == ')')? CLOSING_PARENTH : ANYTHING_ELSE  )
#define MAX_LINE_SIZE 3000

int readAndVerifyExpressions(FILE *fpExpressions)
{


    return OK;
}

int complementDetect(char bracket)
{


    return  OK;
}

int expressionsFileProcessing(const char *path)
{
    FILE *fpExpressions = fopen(path, "rt");
    tCola expressions;
    /// unsigned short cant = 0;
    char res,
         line[MAX_LINE_SIZE];

    if(!fpExpressions)
        return ERR_OPENING_FILE;

    crearCola(&expressions);

    while(fgets(line, MAX_LINE_SIZE, fpExpressions))
    {
        while((res = readAndVerifyExpressions(fpExpressions)))
        {
            //if(res == )
        }
    }

    vaciarCola(&expressions);

    fclose(fpExpressions);
    return END_PROCESS;
}
