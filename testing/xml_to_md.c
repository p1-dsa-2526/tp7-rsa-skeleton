//
// Created by flasque on 25/02/2026.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>

void generate_markdown_report(const char *xml_path, const char *md_path) {
    FILE *xml_file = fopen(xml_path, "r");
    FILE *md_file = fopen(md_path, "w");

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
    fprintf(md_file, "# Test Report - ");

    while (fgets(line, sizeof(line), xml_file)) {
        // Handle <testsuite> tag
        if (strstr(line, "<testsuite ")) {
            sscanf(line, "<testsuite name=\"%255[^\"]\" tests=\"%255[^\"]\"", suite_name, suite_tests);
            fprintf(md_file, "%s\n", suite_name);
            fprintf(md_file, "### Total Tests : %s\n\n", suite_tests);
        }

        // Handle <testcase> tag
        if (strstr(line, "<testcase")) {
            char test_name[256] = {0};
            char *failure = strstr(line, "Failure");

            sscanf(line, "<testcase name=\"%255[^\"]\"", test_name);

            if (failure) {
                fprintf(md_file, "- **%s**: ❌ Failed\n", test_name);
                // read next lines up to </testcase> to get failure message
                while (fgets(line, sizeof(line), xml_file) && !strstr(line, "</testcase>")) {

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
    char *base_name = argv[1];
    char *xml_path = (char *)malloc(100*sizeof(char));
    strcpy(xml_path, base_name);
    char *md_path;
    // replace .xml with .md
    if (strstr(xml_path, ".xml")) {
        md_path = strstr(xml_path, ".xml");
        *md_path = '\0'; // terminate the string at .xml
        md_path = strcat(xml_path, ".md"); // add .md extension
    } else {
        fprintf(stderr, "Input file must have .xml extension\n");
        return 1;
    }

    printf("Generating Markdown report from XML: %s\n", xml_path);

    generate_markdown_report(base_name, md_path);

    printf("Markdown report generated: %s\n", md_path);
    free(xml_path);
    return 0;
}