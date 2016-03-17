#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include "scws/xtree.h"
#include "scws/xdb.h"
#include "scws/xdict.h"
#include "scws/charset.h"

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
			fprintf(stderr, "mk_dict: %s\n", msg);
		fprintf(stderr, "Try `%s -h' for more information.\n", program_name);
		exit(code);
	}

	printf("%s\n", program_name);
	printf("Merge the plain text dictionary.\n");
	printf("Usage: %s [options] [input file]\n", program_name);
	printf("  -i        Specified the plain text dictionary(default: dict.txt).\n");
	printf("  -p        Specified the PRIME num for xdb\n");
	printf("  -v        Show the version.\n");
	printf("  -h        Show this page.\n");
	exit(0);
}

/* usage: mk_dict -i dict.txt -o dict.xdb */
int main(int argc, char *argv[])
{
	int c,t;
	char *input, *delim = " \t\r\n";
	FILE *fp;
	char buf[256], *str, *ptr;
	word_st word, *w;
	xtree_t xt;

	input = NULL;
	if ((program_name = strrchr(argv[0], '/')) != NULL)
		program_name++;
	else
		program_name = argv[0];	

	/* parse the arguments */
	t = 0;
	while ((c = getopt(argc, argv, "i:p:vh")) != -1)
	{
		switch (c)
		{
			case 'i' :
				input = optarg;
				break;
			case 'p' :
				t = atoi(optarg);
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

	/* setup the xtree */
	if (t == 0)
		t = SCWS_XDICT_PRIME;	
	if ((xt = xtree_new(0, t)) == NULL)
	{
		perror("Failed to create the xtree");
		goto mk_end;
	}
	
	/* load the data */
	printf("Reading the input file: %s\n", input);
	fflush(stdout);

	t = 0;
	word.attr[2] = '\0';
	while (fgets(buf, sizeof(buf)-1, fp) != NULL)
	{
		// <word>\t<tf>\t<idf>\t<attr>\n
		if (buf[0] == ';' || buf[0] == '#')
			continue;

		str = strtok(buf, delim);
		if (str == NULL) continue;
		c = strlen(str);
		
		// init the word
		word.tf = word.idf = 1.0;
		word.flag = SCWS_WORD_FULL;
		word.attr[0] = '@';
		word.attr[1] = '\0';

		if (!(ptr = strtok(NULL, delim))) break;
		word.tf = (float) atof(ptr);

		if (!(ptr = strtok(NULL, delim))) break;
		word.idf = (float) atof(ptr);

		if (ptr = strtok(NULL, delim))
		{
			word.attr[0] = ptr[0];
			if (ptr[1]) word.attr[1] = ptr[1];
		}

		/* save the word */
		//printf("word: %s (len=%d)\n", str, c);
		if ((w = xtree_nget(xt, str, c, NULL)) == NULL)
		{
			w = (word_st *) pmalloc(xt->p, sizeof(word_st));
			memcpy(w, &word, sizeof(word));
			xtree_nput(xt, w, sizeof(word), str, c);
			t++;
		}
		else
		{
			if (w->flag == SCWS_WORD_FULL)
			{
				printf("dup word: %s (len=%d)\n", str, c);
			}
			w->tf = word.tf;
			w->idf = word.idf;
			w->flag |= SCWS_WORD_FULL;
			strcpy(w->attr, word.attr);
		}
	}

	/* save to xdb & free the xtree */
	printf("Total nodes=%d\n", t);
	fflush(stdout);
	
	xtree_free(xt);
	printf("OK, all been done!\n");
	fflush(stdout);

mk_end:
	fclose(fp);
	return 0;	
}
