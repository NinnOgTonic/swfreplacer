// swfvartool.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "SWFReader.h"
#include "Tag.h"
#include "Rect.h"
#include "SWFFile.h"


///-----------------------------------------------------------
///
///
///-----------------------------------------------------------

int TranslateCommand(SWFFile *swf, char* szCmdline) {
    // Parsed instuction string.
    // tokens[0] -> command
    // tokens[1] -> Argument 1
    // tokens[2] -> Argument 2
    char tokens[3][256];
    int iTokenIndex = 0;


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Parse the string........
    //
    char szTemp[256] = {0,};
    char separators[] = " \t";
    char quote = '\"';
    int iStrLen = strlen(szCmdline);
    bool bSeparator = false;
    bool bQuote = false;
    int iBuf = 0;
    for (int i = 0; i < iStrLen; i++) {
        // Separator check
        bSeparator = false;
        for (int j = 0; j<sizeof (separators); j++) {
            if (szCmdline[i] == separators[j]) {
                bSeparator = true;
                break;
            }
        }

        // quote check
        // We are already insiede the Quoted phrase...
        if (bQuote) {
            // If we find quote mark again, it means the
            // end of quoted phrase.
            if (quote == szCmdline[i]) {
                // push the accumulated string
                bQuote = false;
                strcpy(tokens[iTokenIndex++], szTemp);
                memset(szTemp, 0, sizeof (szTemp));
                iBuf = 0;
            } else {
                // Accumulate the characters to the temporary buffer
                szTemp[iBuf++] = szCmdline[i];
            }
        }            // We aren't inside of the quote
        else {
            // If we meet quote mark, it means this is the start of the
            // quoted phrase.
            if (quote == szCmdline[i]) {
                bQuote = true;
            }                // This is not related with quotes, so we just do
                // check separators.
            else {
                if (!bSeparator) {
                    szTemp[iBuf++] = szCmdline[i];
                } else {
                    if (iBuf > 0) {
                        strcpy(tokens[iTokenIndex++], szTemp);
                        memset(szTemp, 0, sizeof (szTemp));
                        iBuf = 0;
                    }
                }
            }
        }
    }
    // If there is a string buffer not pushed into the command line buffer,
    // then push it.
    if (iBuf > 0) {
        strcpy(tokens[iTokenIndex++], szTemp);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - -


    // "ReplaceImage"
    // "ReplaceText"
    // "ReplaceSprite"
    if (0 == strcmp(tokens[0], "txt")) {
        printf("Changing text variable...\n");
        swf->ChangeEditValue(tokens[1], tokens[2]);
    } else if (0 == strcmp(tokens[0], "img")) {
        printf("Replacing Image data...\n");
        swf->ChangeJpgImg(tokens[1], tokens[2]);
    } else if (0 == strcmp(tokens[0], "sprite")) {
        // Still experimental.
        swf->ChangeSprite(tokens[1], tokens[2]);
    } else if (0 == strcmp(tokens[0], "start")) {
        return 0;
    } else if (0 == strcmp(tokens[0], "help") || 0 == strcmp(tokens[0], "?")) {
        printf("txt \"VariableName\" \"Text you want to put in\" \n");
        printf("img \"ExportName\" \"Path of Image File to replace\" \n");
        printf("sprite \"ExportName\" \"Path of SWF File to replace\" \n");
        printf("start\n");
    } else {
        printf("Unknown command\n");
    }

    return 1;
}




///-----------------------------------------------------------
///
/// Main function
///
///-----------------------------------------------------------

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("\nUsage: swfvartool.exe filename_source filename_target ");
        return 0;
    }




    // Read in the SWF file.
    // This will show the brief information of it.
    printf("------------------------------------------------\n");
    printf("Reading '%s'...\n", (char*) argv[1]);
    printf("------------------------------------------------\n");
    SWFFile *swf = new SWFFile((char*) argv[1]); // deletion is done within this function.
    printf("------------------------------------------------\n");



    //
    // Get commands from the console.
    //
    char szCmdline[256];
    char *sz = 0;
    do {
        printf("> ");
        sz = gets(szCmdline);
        if (0 != sz) {
            if( 0==TranslateCommand(swf, szCmdline) ){
                break;
            }
        }
    } while (0 != sz);



    printf("------------------------------------------------\n");
    printf("Now saving to '%s'...\n", (char*) argv[2]);
    printf("------------------------------------------------\n");

    // Now save it..
    swf->SaveTo((char*) argv[2]);


    printf("Press any key to finish...");
    getchar();

    delete swf;
}

