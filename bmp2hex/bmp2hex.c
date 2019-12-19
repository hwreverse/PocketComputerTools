/**************************************************************************
 * bmp.c                                                                  *
 * cooked together by HWR0                                                *
 * ===============                                                        *
 * evilhardware@mail.ru                                                   *
 **************************************************************************/

// will work only on little-Endian

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
    word planes;
    word bitDepth;     //I'l kick you if it is different from 24
    dword compression; // just fucking ignored
    dword imageSize;   //the RAM's the limit
    dword xPixelsPerMeter;
    dword yPixelsPerMeter;
} BMPHeader;

typedef struct rgbPIXEL /* the structure for a 24bit pixel. */
{
    byte r;
    byte g;
    byte b;
} RGB;

int *ptr, **bmp;

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

void load_bmp(char *file, BMPHeader *b, int order)
{
    FILE *fp;
    int bmpPosition = 0x36; //standard, but we check anyway

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
    /* check to see if it is a valid bitmap file for conversion to 8Bit GPRINT (height multiple of 8)*/
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

    // for loop to point rows pointer to appropriate location in 2D array
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
                bmp[x][y] = ((int)(currPixel.r) == 0); // I, lazy ass programmer,  test only if the red component is black
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
                bmp[x][y] = ((int)(currPixel.r) == 0); // I, lazy ass programmer,  test only if the red component is black
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
    printf("\n+---------------------------------------------------------------+\n");
    printf("| HWR0's BMP2HEX Converter for Casio / Sharp Pocket Calculators |\n");
    printf("+---------------------------------------------------------------+\n");
}

/**************************************************************************
 *  printHelp                                                             *
 *    prints the commandline options on stdout                            *
 **************************************************************************/
void printHelp()
{
    printBanner();
    printf("\n");
    printf("Usage: bmp2hex [OPTION...] BMPFile\n\n");

    printf("    -c,     Clean output, without banner\n");
    printf("    -H,     Shows essential data from BMP header\n");
    printf("    -t,     Show table      (0 1 )\n");
    printf("    -g,     Show graphics   (  %c%c)\n", 219, 219);
    printf("    -i,     Invert graphics (%c%c  )\n", 219, 219);
    printf("    -r,     Reverse Y order\n");
    printf("    -s,     Insert space between hex values\n");
    printf("    -d,     Show hex values as \"db 0x34, ...\" assembler line\n");
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
    printf("+---------------------------------------------------------------+\n");
    printf("| BMP File Header\n");
    printf("+---------------------------------------------------------------+\n");
    printf("| File size: %d Bytes\n", b->fileSize);
    printf("| Pixel Array Offset: 0x%02X\n", b->fileOffset);
    printf("| DIB Header size: %d Bytes\n", b->DIBHeaderSize);
    printf("| Image dimensions: %dpx Width x %dpx Height\n", b->width, b->height);
    printf("| Planes: %d\n", b->planes);
    printf("| Compression: %d\n", b->compression);
    printf("| Image size: %d Bytes\n", b->imageSize);
    printf("| X Pixels/meter: %d\n", b->xPixelsPerMeter);
    printf("| Y Pixels/meter: %d\n", b->yPixelsPerMeter);
    printf("+---------------------------------------------------------------+\n");
    printf("| 8-Bit Rows: %d\n", ((b->height) / 8));
    printf("+---------------------------------------------------------------+\n\n");
}

/**************************************************************************
 *  main                                                                  *
 *    main                                                                *
 **************************************************************************/
int main(int argc, char *argv[])
{
    BMPHeader fbmp;
    int rows = 0;
    int cols = 0;
    int rp = 0;
    int hv = 0; // hex value
    char *fileName = "";
    int showHeader = 0;
    //int validateClean = 1;
    int cleanOutput = 0;
    int space = 0;
    int db = 0;
    int reverseOrder = 0; // (former Bottoms-up)
    int inverseGraphics = 0;
    int showGraphics = 0;
    int showTable = 0;
    int paramsExist = 0;
    int index = 0, c = 0;

    if (argc < 2)
    {
        printAskforFuckingHelp();
        exit(1);
    }

    // let's getopt() !----------------------------------------------------------------------

    while ((c = getopt(argc, argv, "hHcsigrtd")) != -1)
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
        case 's': //insert space
            space = 1;
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
        case 'd': //hex output in db 0xe4, 0x12, ... format
            db = 1;
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
        space = 0;
        db = 0;
        reverseOrder = 0;
        inverseGraphics = 0;
        showGraphics = 1;
        showTable = 1;
    }

    if (!cleanOutput)
    {
        printBanner();
    }

    load_bmp(argv[argc - 1], &fbmp, reverseOrder);

    rows = fbmp.height / 8;
    cols = fbmp.width;

    if (showHeader)
        showBMPHeader(&fbmp);

    //Show Table
    if (showTable)
    {
        for (int y = 0; y < (fbmp.height); y++)
        {
            for (int x = 0; x < (fbmp.width); x++)
            {
                printf(" %d", bmp[x][y]);
            }
            printf("\n");
        }
        printf("\n");
    }
    //Show Graphics
    if (showGraphics)
    {
        for (int y = 0; y < (fbmp.height); y++)
        {
            for (int x = 0; x < (fbmp.width); x++)
            {
                if ((bmp[x][y]) == inverseGraphics)
                {
                    printf("%c%c", 219, 219);
                }
                else
                {
                    printf("  ");
                }
            }
            printf("\n");
        }

        printf("\n");
    }

    //now the hexconvert
    printf("\n");
    for (int rr = 0; rr < rows; rr++)
    {
        if (db)
            printf("db ");

        for (int cc = 0; cc < cols; cc++)
        {
            if (db)
                printf("0x");

            rp = rr * 8; // real position for y
            hv = bmp[cc][rp] * 128 + bmp[cc][rp + 1] * 64 + bmp[cc][rp + 2] * 32 + bmp[cc][rp + 3] * 16 + bmp[cc][rp + 4] * 8 + bmp[cc][rp + 5] * 4 + bmp[cc][rp + 6] * 2 + bmp[cc][rp + 7];
            printf("%02X", hv);

            if (db && (cc != (cols - 1)))
                printf(",");

            if (space)
                printf(" ");
        }
        printf("\n");
    }
    printf("\n\n");

    return 0;
    printf("\n");

    return 0;
}
