# bmp2hex

Program designed to take a 24bit BMP file (with only black and white pixels) 
and to convert it 8 rows, by 8 rows into the "GPRINT" 8bit Hex sequence 
for Sharp PC-1600, PC-E500, PC-G850* 
also for "DEFCHR$" used by Casio PB-1000 , AI-1000 and PB-2000C

For __**Sharp PC-1600**__, the corresponding IOCS Function would be **PRTGPTN @ 0x0154** or **LOADLCD @ 0x0160**

For __**Sharp PC-E500**__, the corresponding function is when you write on **STDO:SCRN:**, Command **Display 8-bit pattern @ 0x4a**

For __**Sharp PC-G850 / G850V / G850VS**__, the corresponding IOCS Function would be **Print 8-Bit Pattern @ 0xbfd0**

*(Data taken from the respective Tech or Usermanuals)*


Program will work on little-Endian Architectures.
Compilation tested on gcc (latest 8.*) under Linux and under MINGW64 under Windows

---

<pre>
<code>
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

</code>
</pre>

---

**Example:**

```
O:\bitmap2hex>bmp2hex.exe -c -H -t -g -i -d f.bmp
+---------------------------------------------------------------+
| BMP File Header
+---------------------------------------------------------------+
| File size: 216 Bytes
| Pixel Array Offset: 0x36
| DIB Header size: 40 Bytes
| Image dimensions: 6px Width x 8px Height
| Planes: 1
| Compression: 0
| Image size: 162 Bytes
| X Pixels/meter: 2834
| Y Pixels/meter: 2834
+---------------------------------------------------------------+
| 8-Bit Rows: 1
+---------------------------------------------------------------+

 1 1 1 1 1 0
 1 0 0 0 0 0
 1 0 0 1 0 0
 1 1 1 1 0 0
 1 0 0 1 0 0
 1 0 0 0 0 0
 1 0 0 0 0 0
 0 0 0 0 0 0

██████████
██
██    ██
████████
██    ██
██
██


db 0xFE,0x90,0x90,0xB8,0x80,0x00

```

****

```bash
proklarush@teonas:~# ./bmp2hex -c bf.bmp

03070F0F0F1F1F1F1F1F3F3F7F7FFFFFFFFFFFFF7F7F3F0F83A02C6D0D0D0100
80E0F0F0F0F0F0E0E0C0C08080808080C0E0F0F8FCFCFCF8F00008DCDEDEDE1E

```
****
![Right Foot of Bigfoot](img/bfoot_screen.jpg)

Left foot is next :)
