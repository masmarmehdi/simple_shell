#include "main.h"
/**
 * prompt - int func
 *
 * Return: 0
 */
int prompt(void)
{
    char *prompt = "$ ";
    ssize_t writecount = 0;

    if (isatty(STDIN_FILENO) == 1)
    {
        writecount = write(STDOUT_FILENO, prompt, 2);
        if (writecount == -1)
            exit(0);
    }
    return (0);
}
/**
 * _read - char func
 *
 * Return: pointer
 */
char *_read(void)
{
    ssize_t readcount = 0;
    size_t n = 0;
    char *buffer = NULL;
    int i = 0;

    readcount = getline(&buffer, &n, stdin);
    if (readcount == -1)
    {
        free(buffer);
        if (isatty(STDIN_FILENO) != 0)
            write(STDOUT_FILENO, "\n", 1);
        exit(0);
    }
    if (buffer[readcount - 1] == '\n' || buffer[readcount - 1] == '\t')
        buffer[readcount - 1] = '\0';
    for (i = 0; buffer[i]; i++)
    {
        if (buffer[i] == '#' && buffer[i - 1] == ' ')
        {
            buffer[i] = '\0';
            break;
        }
    }
    return (buffer);
}
/**
 * _fullpathbuffer - char func
 * @av: param
 * @PATH: param
 * @copy: param
 *
 * Return: pointer
 */
char *_fullpathbuffer(char **av, char *PATH, char *copy)
{
    char *tok, *fullpathbuffer = NULL, *concatstr = NULL;
    static char tmp[256];
    int PATHcount = 0, fullpathflag = 0, /*len = 0,*/ z = 0, toklen = 0;
    struct stat h;

    copy = NULL;
    copy = _strdup(PATH);
    PATHcount = _splitPATH(copy);
    tok = strtok(copy, ": =");
    while (tok != NULL)
    {
        concatstr = _concat(tmp, av, tok);
        if (stat(concatstr, &h) == 0)
        {
            fullpathbuffer = concatstr;
            fullpathflag = 1;
            break;
        }
        if (z < PATHcount - 2)
        {
            toklen = _strlen(tok);
            if (tok[toklen + 1] == ':')
            {
                if (stat(av[0], &h) == 0)
                {
                    fullpathbuffer = av[0];
                    fullpathflag = 1;
                    break;
                }
            }
        }
        z++;
        tok = strtok(NULL, ":");
    }
    if (fullpathflag == 0)
        fullpathbuffer = av[0];
    free(copy);
    return (fullpathbuffer);
}
/**
 * checkbuiltins - int func
 * @av: param
 * @buffer: param
 * @exitstatus: param
 * Return: 1 or 0
 */
int checkbuiltins(char **av, char *buffer, int exitstatus)
{
    int i;

    if (_strcmp(av[0], "env") == 0)
    {
        _env();
        for (i = 0; av[i]; i++)
            free(av[i]);
        free(av);
        free(buffer);
        return (1);
    }
    else if (_strcmp(av[0], "exit") == 0)
    {
        for (i = 0; av[i]; i++)
            free(av[i]);
        free(av);
        free(buffer);
        exit(exitstatus);
    }
    else
        return (0);
}
/**
 * _forkprocess - int func
 * @av: param
 * @buffer: param
 * @fullpathbuffer: param
 *
 * Return: 0 on success
 */
int _forkprocess(char **av, char *buffer, char *fullpathbuffer)
{
    int i, status, result, exitstatus = 0;
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("Error");
        exit(1);
    }
    if (pid == 0)
    {
        result = execve(fullpathbuffer, av, environ);
        if (result == -1)
        {
            perror(av[0]);
            for (i = 0; av[i]; i++)
                free(av[i]);
            free(av);
            free(buffer);
            exit(127);
        }
    }
    wait(&status);
    if (WIFEXITED(status))
    {
        exitstatus = WEXITSTATUS(status);
    }
    for (i = 0; av[i]; i++)
        free(av[i]);
    free(av);
    free(buffer);
    return (exitstatus);
}
