# bmp2hex

Program designed to take a 24bit BMP file (with only black and white pixels) 
and to convert it 8 rows, by 8 rows into the "GPRINT" 8bit Hex sequence 
for Sharp PC-1600, PC-E500, PC-G850* 
also for "DEFCHR$" used by Casio PB-1000 , AI-1000 and PB-2000C

<br>
<pre><code>
Usage: bmp2hex [OPTION...] BMPFile

    -c,     Clean output, without banner
    -H,     Shows essential data from BMP header
    -t,     Show table      (0 1 )
    -g,     Show graphics   (  ██)
    -i,     Invert graphics (██  )
    -r,     Reverse Y order
    -s,     Insert space between hex values
    -d,     Show hex values as "db 0x34, ..." assembler line
    -h,     Display this help message

</code></pre>