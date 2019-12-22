#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

typedef struct hdrBITMAP /* the structure for a bitmap header (just the essentials)*/
{
    dword fileSize;
    dword rsrv;
    dword fileOffset;
    dword DIBHeaderSize;
    dword width;
    dword height;
    word planes;           //boeing fucked up
    word bitDepth;         //I'l kick you if it is different from 24
    dword compression;     //just fucking ignored
    dword imageSize;       //your env and the RAM's the limit
    dword xPixelsPerMeter; //size doesn't matter, it's where you pipe it !
    dword yPixelsPerMeter;
} BMPHeader;

typedef struct rgbPIXEL /* the structure for a 24bit pixel. */
{
    byte r;
    byte g;
    byte b;
} RGB;

//*******************Global Vars********************************************
int *ptr, **bmp; // The 2D - Array for the bitmap file
BMPHeader fbmp;

/**************************************************************************
 *  fskip                                                                 *
 *     Skips bytes (8bits) in a file.                                     *
 **************************************************************************/

void fskip(FILE *fp, int num_bytes)
{
    int i;
    for (i = 0; i < num_bytes; i++)
        fgetc(fp);
}

/**************************************************************************
 *  load_bmp                                                              *
 *    Loads a bitmap file into memory.                                    *
 **************************************************************************/

void load_bmp(char *file, BMPHeader *b, int order, int avg, int lo, int hi, int verbose)
{
    FILE *fp;
    int bmpPosition = 0x36; //standard, but we check anyway
    int tempv = 0;
    long index;
    int x, y, i, j, len = 0, parity = 0; //hexvalue!

    RGB currPixel;

    /* open the file */
    if ((fp = fopen(file, "rb")) == NULL)
    {
        printf("Stars are against us - Error opening file %s.\n", file);
        exit(1);
    }

    /* check to see if it is a valid bitmap file */
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        printf("WTF? %s ain't a bitmap file!\n", file);
        exit(1);
    }

    /* read in the header, at least the relevant part*/
    fread(b, sizeof(BMPHeader), 1, fp);
    //printf(" %x", (int)(b->fileOffset));
    bmpPosition = (int)(b->fileOffset);
    fseek(fp, bmpPosition, SEEK_SET);
    //fsetpos(fp, &bmpPosition);  // deprecated because won't compile under linux ... but under MINGW64 !
    if (!((b->bitDepth) == 24)) // 24bits per pixel = 8bits per color in RGB
    {
        fclose(fp);
        printf("%s is not in 24bits per pixel format! Are you asking for a Seg Fault ?!\n\n", file);
        exit(1);
    }

    /* check to see if we have any rows to convert*/
    if ((b->height) / 8 == 0)
    {

        printf("%s's height smaller than 8 pixels! Put some meat on them bones!\n\n", file);
        exit(1);
    }
    /* check to see if we have too big a bitmap as argument*/
    if ((b->height) / 8 > 6)
    {

        printf("%s will take more than 6 rows of 8-bit to encode. Gojira no welcome here !\n\n", file);
        exit(1);
    }

    /* check to see if we need to truncate*/
    if (!((b->height) % 8 == 0))
    {

        printf("%s's height ain't divisible by 8, so I will truncate!\n\n", file);
    }

    len = sizeof(int *) * (int)(b->width) + sizeof(int) * (int)(b->height) * (int)(b->width);
    if ((bmp = (int **)malloc(len)) == NULL)
    {
        fclose(fp);
        printf("Your credit's no good here !. Error allocating memory for file %s.\n", file);
        exit(1);
    };

    // ptr is now pointing to the first element in of 2D array
    ptr = (int *)(bmp + (b->width));

    // for loop to point array rows pointer to appropriate location in 2D array
    for (i = 0; i < (b->width); i++)
        bmp[i] = (ptr + (b->height) * i);

    parity = (b->width) % 4;

    /* read the bitmap */
    if (order)
    {
        for (y = 0; y < (b->height); y++)
        {
            for (x = 0; x < (b->width); x++)
            {
                //   fgetpos(fp, &position);
                //   printf(" %x ", position);
                fread(&currPixel, sizeof(RGB), 1, fp);
                if (avg)
                {
                    tempv = ((int)(currPixel.r) + (int)(currPixel.g) + (int)(currPixel.b)) / 3;
                }
                else
                {
                    tempv = (int)(currPixel.r); // I, lazy ass programmer,  test only if the red component is black
                }
                if (tempv < lo)
                {
                    bmp[x][y] = 0;
                }
                else if (tempv < hi)
                {
                    bmp[x][y] = 1;
                }
                else
                {
                    bmp[x][y] = 2;
                }
            }
            /* mind the padding */
            fskip(fp, parity);
        }
    }
    else
    {
        for (y = (b->height) - 1; y >= 0; y--)
        {
            for (x = 0; x < (b->width); x++)
            {
                //   fgetpos(fp, &position);
                //   printf(" %x ", position);
                fread(&currPixel, sizeof(RGB), 1, fp);
                if (avg)
                {
                    tempv = ((int)(currPixel.r) + (int)(currPixel.g) + (int)(currPixel.b)) / 3;
                }
                else
                {
                    tempv = (int)(currPixel.r); // I, lazy ass programmer,  test only if the red component is black
                }
                if (tempv < lo)
                {
                    bmp[x][y] = 0;
                }
                else if (tempv < hi)
                {
                    bmp[x][y] = 1;
                }
                else
                {
                    bmp[x][y] = 2;
                }
            }
            /* mind the padding */
            fskip(fp, parity);
        }
    }

    fclose(fp);
}

/**************************************************************************
 *  printBanner                                                           *
 *    prints the 0wner's banner on stdout                                 *
 **************************************************************************/
void printBanner() //Hi Bruce, green mood today ?
{
    printf("\n+-----------------------------------------------------------------+\n");
    printf("| HWR0's GrayScale BMP Converter for Sharp G850* Pocket Computers |\n");
    printf("+-----------------------------------------------------------------+\n");
}

/**************************************************************************
 *  printHelp                                                             *
 *    prints the commandline options on stdout                            *
 **************************************************************************/
void printHelp()
{
    printBanner();
    printf("\n");
    printf("Usage: gsconv850 [OPTION...] BMPFile\n\n");

    printf("    -c,     Clean output, without banner\n");
    printf("    -H,     Shows essential data from BMP header\n");
    printf("    -t,     Show table      (0 1 2 ) - DEBUG\n");
    printf("    -g,     Show graphics   (  %c%c%c%c) - DEBUG\n", 177, 177, 219, 219);
    printf("    -i,     Invert graphics (%c%c%c%c  ) - DEBUG\n", 219, 219, 177, 177);
    printf("    -r,     Reverse Y order\n");
    printf("    -a,     Average RGB Pixel to gray, otherwise just the red channel taken\n");
    printf("    -s,     Remove space between hex values\n");
    printf("    -8,     G850 Text editor specifics\n");
    printf("    -v,     Verbose File Load - DEBUG\n");
    printf("    -h,     Display this help message\n\n");
};

/**************************************************************************
 *  printAskforFuckingHelp                                                *
 *    prints the option to set if you want help on stdout                 *
 **************************************************************************/
void printAskforFuckingHelp()
{
    printBanner();
    printf("\nUse -h or to display command-line options\n\n");
    exit(1);
}

/**************************************************************************
 *  showBMPHeader                                                         *
 *    prints detailed Header Info we get on stdout                        *
 **************************************************************************/
void showBMPHeader(BMPHeader *b)
{
    printf("+-----------------------------------------------------------------+\n");
    printf("| BMP File Header\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("| File size: %d Bytes\n", b->fileSize);
    printf("| Pixel Array Offset: 0x%02X\n", b->fileOffset);
    printf("| DIB Header size: %d Bytes\n", b->DIBHeaderSize);
    printf("| Image dimensions: %dpx Width x %dpx Height\n", b->width, b->height);
    printf("| Planes: %d\n", b->planes);
    printf("| Compression: %d\n", b->compression);
    printf("| Image size: %d Bytes\n", b->imageSize);
    printf("| X Pixels/meter: %d\n", b->xPixelsPerMeter);
    printf("| Y Pixels/meter: %d\n", b->yPixelsPerMeter);
    printf("+-----------------------------------------------------------------+\n");
    printf("| 8-Bit Rows: %d\n", ((b->height) / 8));
    printf("+-----------------------------------------------------------------+\n\n");
}

/**************************************************************************
 *  showBMPTable                                                          *
 *    shows the grayscale data (0,1,2) in table form on stdout            *
 **************************************************************************/
void showBMPTable()
{
    for (int y = 0; y < (fbmp.height); y++)
    {
        for (int x = 0; x < (fbmp.width); x++)
        {
            printf(" %d", bmp[x][y]);
        }
        printf("\n");
    }
}

/**************************************************************************
 *  showBMPGraphics                                                       *
 *    shows the grayscale data (0,1,2) in gfx form (ASCIIART) on stdout   *
 **************************************************************************/
void showBMPGraphics(int invColors /*colors inverted?*/)
{
    int tmpv = 0;
    int gray = 177;
    int white = 219; //white = if white is foreground in terminal !

    for (int y = 0; y < (fbmp.height); y++)
    {
        for (int x = 0; x < (fbmp.width); x++)
        {
            tmpv = bmp[x][y];
            if (invColors)
                tmpv = 2 - tmpv;

            if (tmpv == 0)
            {
                printf("  ");
            }
            else if (tmpv == 1)
            {
                printf("%c%c", gray, gray);
            }
            else
            {
                printf("%c%c", white, white);
            }
        }
        printf("\n");
    }
}

/**************************************************************************
 *  l                                                                     *
 *    prints lineNumber w/o space if selected on stdout                   *
 **************************************************************************/
void l(int ifnb /*line numbers?*/, int lineNumber)
{
    if (ifnb)
        printf("%d", lineNumber);
}

/**************************************************************************
 *  ls                                                                    *
 *    prints lineNumber + space if selected on stdout                     *
 **************************************************************************/
void ls(int ifnb /*line numbers?*/, int lineNumber)
{
    if (ifnb)
        printf("%d ", lineNumber);
}

/**************************************************************************
 *  ls                                                                    *
 *    prints lineNumber + space if selected on stdout                     *
 **************************************************************************/
int hexValue(int c /*column*/, int r /*row*/, int sbi /*subimage*/)
{
    int temp = 0;
    int rp = 0; //real position for y

    rp = r * 8;
    if (sbi)
    {
        temp = (bmp[c][rp] == 2) * 128 + (bmp[c][rp + 1] == 2) * 64 + (bmp[c][rp + 2] == 2) * 32 + (bmp[c][rp + 3] == 2) * 16 + (bmp[c][rp + 4] == 2) * 8 + (bmp[c][rp + 5] == 2) * 4 + (bmp[c][rp + 6] == 2) * 2 + (bmp[c][rp + 7] == 2);
    }
    else
    {
        temp = ((bmp[c][rp] == 1) || (bmp[c][rp] == 2)) * 128 + ((bmp[c][rp + 1] == 1) || (bmp[c][rp + 1] == 2)) * 64 + ((bmp[c][rp + 2] == 1) || (bmp[c][rp + 2] == 2)) * 32 + ((bmp[c][rp + 3] == 1) || (bmp[c][rp + 3] == 2)) * 16 + ((bmp[c][rp + 4] == 1) || (bmp[c][rp + 4] == 2)) * 8 + ((bmp[c][rp + 5] == 1) || (bmp[c][rp + 5] == 2)) * 4 + ((bmp[c][rp + 6] == 1) || (bmp[c][rp + 6] == 2)) * 2 + ((bmp[c][rp + 7] == 1) || (bmp[c][rp + 7] == 2));
    }
    return temp;
}

/**************************************************************************
 *  showBMPGraphics                                                       *
 *    shows the grayscale data (0,1,2) in gfx form (ASCIIART) on stdout   *
 **************************************************************************/
void generateASMCode(int g850 /*G850 Text editor Syntax*/, int spc /*Insert Space*/, int rsio /*Reverse Sub-Image Order*/)
{

    int lnumbers = 0; //future params
    int lzero = 0;    //future params
    int xsyntax = 1;  //future params

    int line = 10;
    int waitCycles = 500;
    int endChar = 0x26; // not in use right now
    int cols = 0;
    int rows = 0;
    int hexV = 0;
    int dbr = 0; //number of DB hexvalue1, hexvalue2,... rows as we limit the number of values per line to 12
    int rem = 0; //remainder line
    /*-------------------------------------------------------------------------------------*/
    lnumbers = g850;   //Line Numbers
    lzero = g850;      //Leading Zero for Hexvalues > 0x9F (Sharp G850 Texteditor specifics)
    xsyntax = !(g850); //0x0. syntax instead of 0..H for hex values
    cols = (int)fbmp.width;
    rows = (int)fbmp.height / 8;
    /*-------------------------------------------------------------------------------------*/

    ls(lnumbers, line);
    printf("ORG ");
    if (xsyntax)
    {
        printf("0x0100\n");
    }
    else
    {
        printf("100H\n");
    }
    line += 10;
    ls(lnumbers, line);
    printf("JP MAIN\n");

    /*--GPRINTF SYSCALL--*/

    line += 10;
    l(lnumbers, line);
    printf("GPF: EQU ");
    if (xsyntax)
    {
        printf("0xbfd0\n");
    }
    else
    {
        printf("0BFD0H\n");
    }

    /*--Main Subroutine - Display rows of Subimage 0--*/

    line += 10;
    l(lnumbers, line);
    printf("MAIN: LD HL,L0\n");
    line += 10;
    ls(lnumbers, line);
    printf("LD B,%d\n", cols);
    line += 10;
    ls(lnumbers, line);
    printf("LD DE,0\n");
    line += 10;
    ls(lnumbers, line);
    printf("CALL GPF\n");
    for (int i = 1; i < rows; i++)
    {
        line += 10;
        ls(lnumbers, line);
        printf("LD HL,L%d\n", i);
        line += 10;
        ls(lnumbers, line);
        printf("LD B,%d\n", cols);
        line += 10;
        ls(lnumbers, line);
        printf("LD DE,");
        if (xsyntax)
        {
            printf(" 0x%02x00\n", i);
        }
        else
        {
            printf("%02X00H\n", i);
        }
        line += 10;
        ls(lnumbers, line);
        printf("CALL GPF\n");
    }
    line += 10;
    ls(lnumbers, line);
    printf("CALL WAIT\n");

    /*--Main Subroutine - Display rows of Subimage 1--*/

    for (int i = 0; i < rows; i++)
    {
        line += 10;
        ls(lnumbers, line);
        printf("LD HL,L%d\n", (i + rows));
        line += 10;
        ls(lnumbers, line);
        printf("LD B,%d\n", cols);
        line += 10;
        ls(lnumbers, line);
        printf("LD DE,");
        if (xsyntax)
        {
            printf(" 0x%02x00\n", i);
        }
        else
        {
            printf("%02X00H\n", i);
        }
        line += 10;
        ls(lnumbers, line);
        printf("CALL GPF\n");
    }
    line += 10;
    ls(lnumbers, line);
    printf("CALL WAIT\n");

    /*--Check for Break--*/

    line += 10;
    ls(lnumbers, line);
    printf("IN A,(");
    if (xsyntax)
    {
        printf("0x1f)\n");
    }
    else
    {
        printf("1FH)\n");
    }
    line += 10;
    ls(lnumbers, line);
    printf("RLCA\n");
    line += 10;
    ls(lnumbers, line);
    printf("RET C\n");
    line += 10;
    ls(lnumbers, line);
    printf("JP MAIN\n");
    line += 10;
    ls(lnumbers, line);
    printf("RET\n");

    /*--WAIT Subroutine--*/

    line += 10;
    l(lnumbers, line);
    printf("WAIT: LD BC,%d\n", waitCycles);
    line += 10;
    l(lnumbers, line);
    printf("WLOOP: DEC BC\n");
    line += 10;
    ls(lnumbers, line);
    printf("LD A,B\n");
    line += 10;
    ls(lnumbers, line);
    printf("OR C\n");
    line += 10;
    ls(lnumbers, line);
    printf("JR NZ,WLOOP\n");
    line += 10;
    ls(lnumbers, line);
    printf("RET\n");

    /*--Subimage 1--*/

    for (int i = 0; i < rows; i++)
    {
        line += 10;
        l(lnumbers, line);
        printf("L%d: DB ", i);
        for (int j = 0; j < (cols / 12); j++)
        {
            if (j > 0)
            {
                line += 10;
                ls(lnumbers, line);
                printf("DB ");
            }
            for (int k = 0; k < 12; k++)
            {
                hexV = hexValue((j * 12) + k, i, 0);
                if (xsyntax)
                {
                    printf("0x%02x", hexV);
                }
                else
                {
                    if (hexV > 0x9f) //if 2 dig. hexnumber starts with a letter, then we must for the G850 Texteditor's sake add a leading zero !
                        printf("0");
                    printf("%02XH", hexV);
                }
                if (k < 11)
                {
                    printf(",");
                    if (spc)
                        printf(" ");
                }
            }
            printf("\n");
        }
        dbr = (cols / 12) - 1;
        rem = cols % 12;
        if (rem > 0)
        {
            line += 10;
            ls(lnumbers, line);
            printf("DB ");
        }
        for (int k = 0; k < rem; k++)
        {

            hexV = hexValue((dbr * 12) + k, i, 0);
            if (xsyntax)
            {
                printf("0x%02x", hexV);
            }
            else
            {
                if (hexV > 0x9f) //if 2 dig. hexnumber starts with a letter, then we must for the G850 Texteditor's sake add a leading zero !
                    printf("0");
                printf("%02XH", hexV);
            }
            if (k < (rem - 1))
            {
                printf(",");
                if (spc)
                    printf(" ");
            }
        }
        printf("\n");
    }

    /*--Subimage 2--*/

    for (int i = 0; i < rows; i++)
    {
        line += 10;
        l(lnumbers, line);
        printf("L%d: DB ", i + rows);
        for (int j = 0; j < (cols / 12); j++)
        {
            if (j > 0)
            {
                line += 10;
                ls(lnumbers, line);
                printf("DB ");
            }
            for (int k = 0; k < 12; k++)
            {
                hexV = hexValue((j * 12) + k, i, 1);
                if (xsyntax)
                {
                    printf("0x%02x", hexV);
                }
                else
                {
                    if (hexV > 0x9f) //if 2 dig. hexnumber starts with a letter, then we must for the G850 Texteditor's sake add a leading zero !
                        printf("0");
                    printf("%02XH", hexV);
                }
                if (k < 11)
                {
                    printf(",");
                    if (spc)
                        printf(" ");
                }
            }
            printf("\n");
        }
        dbr = (cols / 12) - 1;
        rem = cols % 12;
        if (rem > 0)
        {
            line += 10;
            ls(lnumbers, line);
            printf("DB ");
        }
        for (int k = 0; k < rem; k++)
        {

            hexV = hexValue((dbr * 12) + k, i, 1);
            if (xsyntax)
            {
                printf("0x%02x", hexV);
            }
            else
            {
                if (hexV > 0x9f) //if 2 dig. hexnumber starts with a letter, then we must for the G850 Texteditor's sake add a leading zero !
                    printf("0");
                printf("%02XH", hexV);
            }
            if (k < (rem - 1))
            {
                printf(",");
                if (spc)
                    printf(" ");
            }
        }
        printf("\n");
    }
}

/**************************************************************************
 *  main                                                                  *
 *    main                                                                *
 **************************************************************************/

int main(int argc, char *argv[])
{
    int rows = 0;
    int cols = 0;
    int rp = 0;
    int hv = 0; // hex value
    char *fileName = "";
    int showHeader = 0;
    int cleanOutput = 0;
    int space = 1;
    int spec850 = 0;
    int reverseOrder = 0; // (former Bottoms-up)
    int inverseGraphics = 0;
    int showGraphics = 0;
    int showTable = 0;
    int paramsExist = 0;
    int index = 0, c = 0;
    int vrbose = 0;
    int low = 85;   //lower limit for gray zone, under it is black
    int high = 171; //higher limit for gray zone, above is white
    int average = 0;

    if (argc < 2)
    {
        printAskforFuckingHelp();
        exit(1);
    }

    // let's getopt() !----------------------------------------------------------------------

    while ((c = getopt(argc, argv, "hHcsigrt8va")) != -1)
        switch (c)
        {
        case 'h': //help
            printHelp();
            exit(1);
        case 'H': //Header
            showHeader = 1;
            paramsExist = 1;
            break;
        case 'c': //clean
            cleanOutput = 1;
            paramsExist = 1;
            break;
        case 's': //remove space
            space = 0;
            paramsExist = 1;
            break;
        case 'i': //invert Graphics
            inverseGraphics = 1;
            paramsExist = 1;
            break;
        case 'g': //show Graphics
            showGraphics = 1;
            paramsExist = 1;
            break;
        case 'r': //reverse order for y coordinates
            reverseOrder = 1;
            paramsExist = 1;
            break;
        case 't': //show Table
            showTable = 1;
            paramsExist = 1;
            break;
        case '8': //850 editor specifics
            spec850 = 1;
            paramsExist = 1;
            break;
        case 'v': //verbose file load
            vrbose = 1;
            paramsExist = 1;
            break;
        case 'a': //average RGB pixel
            average = 1;
            paramsExist = 1;
            break;

        default:
            printAskforFuckingHelp();
            abort();
        }

    for (index = optind; index < argc; index++)
    {
        if (index != (argc - 1))
        {
            printf("Non-option argument %s\n", argv[index]);
            printAskforFuckingHelp();
            exit(1);
        }
    }

    // getopts finished !----------------------------------------------------------------------

    if (!paramsExist)
    {
        showHeader = 1;
        cleanOutput = 0;
        space = 1;
        vrbose = 0;
        reverseOrder = 0;
        inverseGraphics = 0;
        showGraphics = 0;
        showTable = 0;
        spec850 = 0;
        average = 0;
    }

    if (!cleanOutput)
    {
        printBanner();
    }
    //Load File ----------------------------------------------------------------------------
    load_bmp(argv[argc - 1], &fbmp, reverseOrder, average, low, high, vrbose);

    rows = fbmp.height / 8;
    cols = fbmp.width;

    //Show BMP Header Info -----------------------------------------------------------------
    if (showHeader)
        showBMPHeader(&fbmp);

    //Show Table ---------------------------------------------------------------------------
    if (showTable)
    {
        showBMPTable();
        printf("\n");
    }
    //Show Graphics ------------------------------------------------------------------------
    if (showGraphics)
    {
        showBMPGraphics(inverseGraphics);
        printf("\n");
    }
    //Print Z80 ASM code -------------------------------------------------------------------

    generateASMCode(spec850, space, 0);

    return 0;
}