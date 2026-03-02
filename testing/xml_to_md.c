//
// Created by flasque on 25/02/2026.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MD_REPORT_FILE "../test_reports/all_tests.md"

typedef enum e_high
{
    HIGHLIGHT_BOLD = 0,
    HIGHLIGHT_ITALIC,
    HIGHLIGHT_TITLE1,
    HIGHLIGHT_TITLE2,
    HIGHLIGHT_TITLE3
} t_high;

static char str_highlight[5][10] = {
    "**", // bold
    "*",  // italic
    "# ", // title 1
    "## ", // title 2
    "### " // title 3
};


void md_highlight(char *str,char *part, t_high high)
{
    // modify str to add markdown highlight around part
    char *pos = strstr(str, part);
    if (pos) {
        char temp[1024];
        strncpy(temp, str, pos - str); // copy part before
        temp[pos - str] = '\0';
        strcat(temp, str_highlight[high]); // add highlight
        strcat(temp, part); // add part
        strcat(temp, str_highlight[high]); // add highlight
        strcat(temp, pos + strlen(part)); // add part after
        strcpy(str, temp); // copy back to original string
    }
}

void generate_markdown_report(const char *xml_path, const char *md_path, int partial)
{

    char mode[4] = "w";
    if (partial==1)
    {
        mode[0] = 'a';
        mode[1] = '\0';
    }

    FILE *xml_file = fopen(xml_path, "r");
    FILE *md_file = fopen(md_path, mode);

    if (!xml_file) {
        fprintf(stderr, "Failed to open XML file: %s\n", xml_path);
        return;
    }
    if (!md_file) {
        fprintf(stderr, "Failed to open Markdown file: %s\n", md_path);
        fclose(xml_file);
        return;
    }

    char line[1024];
    char suite_name[256] = {0};
    char suite_tests[256] = {0};

    // Write Markdown header
    if (!partial)
    {
        fprintf(md_file, "# Test Report - ");
    }

    while (fgets(line, sizeof(line), xml_file))
    {
        // Handle <testsuite> tag
        if (strstr(line, "<testsuite ")) {
            sscanf(line, "<testsuite name=\"%255[^\"]\" tests=\"%255[^\"]\"", suite_name, suite_tests);
            fprintf(md_file, "%s\n", suite_name);
            if (!partial) fprintf(md_file, "### Total Tests : %s\n\n", suite_tests);
        }

        // Handle <testcase> tag
        if (strstr(line, "<testcase")) {
            char test_name[256] = {0};
            char *failure = strstr(line, "Failure");

            sscanf(line, "<testcase name=\"%255[^\"]\"", test_name);

            if (failure) {
                fprintf(md_file, "- **%s**: ❌ Failed\n", test_name);
                // read next lines up to </testcase> to get failure message
                while (fgets(line, sizeof(line), xml_file) && !strstr(line, "</testcase>"))
                {
                    md_highlight(line, "Expected", HIGHLIGHT_ITALIC);
                    md_highlight(line, "Actual", HIGHLIGHT_ITALIC);
                    md_highlight(line, "Message", HIGHLIGHT_ITALIC);
                    md_highlight(line, "true", HIGHLIGHT_BOLD);
                    md_highlight(line, "false", HIGHLIGHT_BOLD);
                    fprintf(md_file, ">%s>\n", line);
                }
            } else {
                fprintf(md_file, "- **%s**: ✅ Passed\n", test_name);
            }
        }
    }

    // Clean up
    fclose(xml_file);
    fclose(md_file);
}

int main(int argc, char *argv[]) {
    int partial = 0;
    char *base_name = argv[1];

    if (argc==3)
    {
        if (strcmp(argv[2], "--partial") == 0)
        {
            partial = 1;
        }
    }

    char *xml_path = (char *)malloc(200*sizeof(char));
    strcpy(xml_path, base_name);
    char *md_path;
    // replace .xml with .md
    if (strstr(xml_path, ".xml"))
    {
        md_path = strstr(xml_path, ".xml");
        *md_path = '\0'; // terminate the string at .xml
        md_path = strcat(xml_path, ".md"); // add .md extension
        if (partial ==1)
        {
            strcpy(md_path, MD_REPORT_FILE);
        }
    } else {
        fprintf(stderr, "Input file must have .xml extension\n");
        return 1;
    }

    printf("Generating Markdown report from XML: %s\n", xml_path);

    generate_markdown_report(base_name, md_path, partial);

    printf("Markdown report generated: %s\n", md_path);
    free(xml_path);
    return 0;
}