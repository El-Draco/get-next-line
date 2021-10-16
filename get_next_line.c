#include "get_next_line.h"
#include "get_next_line_utils.c"
#define BUFFER_SIZE 1

char    *get_next_line(int fd)
{
    int i;
    char *line;
    char *buff;
    char *temp;
    static char *saved;
    int sz;
    i = 0;
    line = NULL;
    temp = NULL;
    if (BUFFER_SIZE == 0)
        return NULL;
    buff = malloc(BUFFER_SIZE + 1);
    sz = read(fd, buff, BUFFER_SIZE);
    if (sz == 0 && !saved)
        return line;

    while (sz  > 0)
    {
        if (sz == 0)
            return NULL;
        buff[sz] = 0;
        if (!saved)
            saved = ft_strdup(buff);
        else
            saved = ft_strjoin(saved, buff);
        //Case 1: IF theres a new line inside:
        //Look for a new line or end of file inside this read buffer:
        
        if(line)
            free(line);
        if (ft_strchr(buff,'\n') != NULL )
        {
            //If thers a new line inside the buffer array:
            //then we return everything in saved + the new buffer array
            //We also neeed to ensure that after we return the line - we also reset
            //the static array since we found a \n:
            

            //Code to trim and delete things before the newline goes here:
            //Also dont forget to save characters after the nwline here too:
            if(saved)
                temp = (ft_strdup(1 + (ft_strchr(saved,'\n'))));

            line = ft_substr(saved,0,ft_strlen(saved) - ft_strlen(temp));
            saved = ft_strdup(temp);
            if (temp)
                free(temp);
            // if(!saved)
            //     free(saved);
            break;
        }

        //Case 2: IF there is NO newline:
        // else
        // {
        //     //Then we append the buffer array to the saved and keep reading on and on:
        //     continue;
        // }

        sz = read(fd, buff, BUFFER_SIZE);      
    }
    //Case 3:
    //When we finished reading everything from the file but we still have data left
    //in our static array:
    //BAscially the leftovers:
    // if (!saved)
    // {
    //     free(buff);
    //     return (line);
    // }
    
    if (sz == 0 && (ft_strlen(saved) > 0))
    {
        //If theres a new line:
        while (ft_strchr(saved,'\n') != NULL)
        {
            if(saved)
                temp = (ft_strdup(1 + (ft_strchr(saved,'\n'))));

            //line = ft_substr(saved,0,ft_strlen(saved) - ft_strlen(temp));
            if(!line)
                line = ft_substr(saved,0,ft_strlen(saved) - ft_strlen(temp));
            else
                line = ft_strjoin(line,ft_substr(saved,0,ft_strlen(saved) - ft_strlen(temp)));
            saved = ft_strdup(temp);
            if(temp)
                free(temp);
            // if(!saved)
            //     free(saved);
            
            //return line;
        }
        //No new line:
        if ( ft_strchr(saved,'\n') == NULL && ft_strlen(saved) > 0)
        {
            line = ft_strdup(saved);
            if(saved)
                free(saved);
        }

        //If line is empty but theres
        
    }
    free(buff);
    // if(!line)
    //     line = NULL;
    return line;
}
int main(int argc, char **argv)
{
    char *s;
    int fd = open("test.txt",O_RDONLY);
    int i = 0;
    while(i < 20)
    {
        s = get_next_line(fd);
        printf("%s", s);
        i++;
    }   
}