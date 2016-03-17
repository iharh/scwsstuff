#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *program_name;
static void show_usage(int code, const char *msg)
{
    if (code)
    {
        if (msg != NULL)
            fprintf(stderr, "norm_dict: %s\n", msg);
        fprintf(stderr, "Try `%s -h' for more information.\n", program_name);
        exit(code);
    }

    printf("%s\n", program_name);
    printf("Normalize the plain text dictionary.\n");
    printf("Usage: %s [options] [input file]\n", program_name);
    printf("  -i        Specified the plain text dictionary(default: dict.txt).\n");
    printf("  -v        Show the version.\n");
    printf("  -h        Show this page.\n");
    exit(0);
}

int
main(int argc, char *argv[])
{
    int c;
    char *input, *delim = " \t\r\n";
    FILE *fp;
    char buf[256], attr[256], *str, *ptr;
    float tf, idf;

    input = NULL;
    if ((program_name = strrchr(argv[0], '/')) != NULL)
        program_name++;
    else
        program_name = argv[0];	

    /* parse the arguments */
    while ((c = getopt(argc, argv, "i:vh")) != -1)
    {
        switch (c)
        {
            case 'i' :
                input = optarg;
                break;
            case 'v' :
                printf("%s: convert the plain text dictionary to xdb format\n",	program_name);
                exit(0);			
                break;
            case 'h' :
                show_usage(0, NULL);
                break;
            case '?' :
                default :
                exit(-1);
        }
    }

    /* other arguments */
    argc -= optind;
    if (argc > 0 && input == NULL)
    {
        input = argv[optind++];		
        argc--;
    }

    if (input == NULL)
        input = "dict.txt";

    /* check the input */
    if ((fp = fopen(input, "r")) == NULL)
    {
        perror("Cann't open the input file");
        return -1;
    }

    while (fgets(buf, sizeof(buf) - 1, fp) != NULL)
    {
        // <word>\t<tf>\t<idf>\t<attr>\n
        if (buf[0] == ';' || buf[0] == '#')
        {
            printf("%s", buf);
            continue;
        }

        str = strtok(buf, delim);
        if (str == NULL)
            continue;

        // init the word
        tf = idf = 1.0;

        if (!(ptr = strtok(NULL, delim)))
            break;
        tf = (float) atof(ptr);

        if (!(ptr = strtok(NULL, delim)))
            break;
        idf = (float) atof(ptr);

        ptr = strtok(NULL, delim);

	printf("%s\t%.2f\t%.2f\t%s\n", str, tf, idf, "11"); // ptr
    }

    fclose(fp);
    return 0;	
}
