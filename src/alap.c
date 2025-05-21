#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APP_VERSION "1.0.0"

#define TEMPLATE_C                                   \
"#include <stdio.h>\n"                               \
"int main()\n"                \
"{\n"                                               \
"\tprintf(\"Hello World!\\n\");\n"                  \
"\treturn 0;\n"                                     \
"}\n"

#define TEMPLATE_BASH                                \
"#!/bin/bash\n"                                      \
"echo \"Hello World\"\n"

#define TEMPLATE_PYTHON                              \
"message = \"Hello, Python!\"\n"                     \
"print(message)\n"

#define TEMPLATE_JS \
"console.log(\"Hello, JavaScript!\");\n"

#define TEMPLATE_JAVA                                \
"public class Main {\n"                              \
"\tpublic static void main(String[] args) {\n"       \
"\t\tSystem.out.println(\"Hello, Java!\");\n"        \
"\t}\n"                                              \
"}\n"

#define TEMPLATE_FASTAPI                             \
"from fastapi import FastAPI\n\n"                    \
"app = FastAPI()\n\n"                                \
"@app.get(\"/\")\n"                                  \
"def read_root():\n"                                 \
"\treturn {\"message\": \"Hello FastAPI\"}\n"


void print_usage();
void print_version();
void generate_template_file(const char *output_name, const char *language);
void print_template_to_stdout(const char *language);

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            print_usage();
        }
        else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
        {
            print_version();
        }
        else
        {
            const char *lang = argv[1];
            char output_filename[64];

            if (strcmp(lang, "c") == 0)
                strcpy(output_filename, "main.c");
            else if (strcmp(lang, "sh") == 0)
                strcpy(output_filename, "main.sh");
            else if (strcmp(lang, "py") == 0)
                strcpy(output_filename, "main.py");
            else if (strcmp(lang, "js") == 0)
                strcpy(output_filename, "main.js");
            else if (strcmp(lang, "java") == 0)
                strcpy(output_filename, "main.java");
            else if (strcmp(lang, "fastapi") == 0)
                strcpy(output_filename, "main.py");
            else
            {
                print_usage();
                return 1;
            }

            generate_template_file(output_filename, lang);
        }
    }
    else if (argc == 3 && strcmp(argv[2], "--stdout") == 0)
    {
        print_template_to_stdout(argv[1]);
    }
    else
    {
        print_usage();
    }

    return 0;
}

void print_usage()
{
    printf("alap v%s,\n\n", APP_VERSION);
    printf("Usage: alap <template_id> [option]\n\n");
    printf("Available options: \n\n");

    printf("-h, --help \t show this help\n");
    printf("-v, --version \t version info\n");
    printf("--stdout\t don't create source file, print result to stdout\n\n");

    printf("Available templates: \n\n");

    printf("* c\t\t - C source code [main.c]\n");
    printf("* sh\t\t - Bash source code [main.sh]\n");
    printf("* py\t\t - Python 3 source code [main.py]\n");
    printf("* js\t\t - Java source code [Main.java]\n");
    printf("* java\t\t - Java source code [Main.java]\n");
    printf("* fastapi\t - Python FastAPI project [main.py]\n");
}

void print_version()
{
    printf("alap v%s\n", APP_VERSION);
}

void generate_template_file(const char *output_name, const char *language)
{
    FILE *fp = fopen(output_name, "r");
    if (fp)
    {
        printf("Error: the file '%s' already exists\n", output_name);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fp = fopen(output_name, "w");
    if (!fp)
    {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    if (strcmp(language, "c") == 0)
        fputs(TEMPLATE_C, fp);
    else if (strcmp(language, "sh") == 0)
        fputs(TEMPLATE_BASH, fp);
    else if (strcmp(language, "py") == 0)
        fputs(TEMPLATE_PYTHON, fp);
    else if (strcmp(language, "js") == 0)
        fputs(TEMPLATE_JS, fp);
    else if (strcmp(language, "java") == 0)
        fputs(TEMPLATE_JAVA, fp);
    else if (strcmp(language, "fastapi") == 0)
        fputs(TEMPLATE_FASTAPI, fp);

    fclose(fp);
    printf("# '%s' was created\n", output_name);
}

void print_template_to_stdout(const char *language)
{
    if (strcmp(language, "c") == 0)
        printf("%s", TEMPLATE_C);
    else if (strcmp(language, "sh") == 0)
        printf("%s", TEMPLATE_BASH);
    else if (strcmp(language, "py") == 0)
        printf("%s", TEMPLATE_PYTHON);
    else if (strcmp(language, "js") == 0)
        printf("%s", TEMPLATE_JS);
    else if (strcmp(language, "java") == 0)
        printf("%s", TEMPLATE_JAVA);
    else if (strcmp(language, "fastapi") == 0)
        printf("%s", TEMPLATE_FASTAPI);
    else
        print_usage();
}