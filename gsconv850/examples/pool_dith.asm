10 ORG 100H
20 JP MAIN
30GPF EQU 0BFD0H
40MAIN: LD HL,L0
50 LD B,144
60 LD DE,0
70 CALL GPF
80 LD HL,L1
90 LD B,144
100 LD DE,0100H
110 CALL GPF
120 LD HL,L2
130 LD B,144
140 LD DE,0200H
150 CALL GPF
160 LD HL,L3
170 LD B,144
180 LD DE,0300H
190 CALL GPF
200 LD HL,L4
210 LD B,144
220 LD DE,0400H
230 CALL GPF
240 LD HL,L5
250 LD B,144
260 LD DE,0500H
270 CALL GPF
280 CALL WAIT
290 LD HL,L6
300 LD B,144
310 LD DE,0000H
320 CALL GPF
330 LD HL,L7
340 LD B,144
350 LD DE,0100H
360 CALL GPF
370 LD HL,L8
380 LD B,144
390 LD DE,0200H
400 CALL GPF
410 LD HL,L9
420 LD B,144
430 LD DE,0300H
440 CALL GPF
450 LD HL,L10
460 LD B,144
470 LD DE,0400H
480 CALL GPF
490 LD HL,L11
500 LD B,144
510 LD DE,0500H
520 CALL GPF
530 CALL WAIT
540 IN A,(1FH)
550 RLCA
560 RET C
570 JP MAIN
580 RET
590WAIT: LD BC,500
600WLOOP: DEC BC
610 LD A,B
620 OR C
630 JR NZ,WLOOP
640 RET
650L0: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
660 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 7FH
670 DB 3FH, 3FH, 1FH, 1FH, 0FH, 0FH, 0FH, 8FH, 87H, 47H, 0A7H, 0C7H
680 DB 27H, 0C7H, 2FH, 8FH, 0AFH, 4FH, 9FH, 1FH, 0BFH, 3FH, 7FH, 7FH
690 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
700 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
710 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
720 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
730 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
740 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
750 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
760 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

770L1: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
780 DB 0FFH, 0FFH, 0FFH, 0FFH, 7FH, 1FH, 0FH, 03H, 81H, 20H, 80H, 0D0H
790 DB 0E0H, 0E8H, 0F0H, 0F4H, 0F8H, 0F8H, 0FFH, 0FBH, 0FEH, 0FFH, 0FBH, 0FEH
800 DB 0FBH, 0EEH, 0F5H, 0DEH, 74H, 0CBH, 0CH, 02H, 06H, 00H, 05H, 00H
810 DB 14H, 21H, 43H, 8FH, 1FH, 7FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
820 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 7FH
830 DB 3FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
840 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
850 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
860 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
870 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
880 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

890L2: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
900 DB 0FFH, 0FFH, 0FFH, 43H, 0BAH, 0ECH, 0F8H, 0FAH, 0FEH, 0FFH, 0FFH, 0FFH
910 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
920 DB 0FFH, 0FFH, 0FEH, 0FFH, 0EFH, 0FDH, 0BBH, 0EEH, 58H, 0C0H, 40H, 0C0H
930 DB 40H, 40H, 0A0H, 4AH, 24H, 50H, 03H, 0BFH, 0FFH, 0FFH, 0FFH, 0FFH
940 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FDH, 0FFH, 0FEH, 0FFH, 0FFH, 80H
950 DB 7FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
960 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
970 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
980 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
990 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1000 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1010L3: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1020 DB 0FFH, 0FFH, 0FFH, 0FAH, 0EDH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1030 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1040 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FDH, 0FFH, 0F5H, 0DFH, 0B5H, 0EAH
1050 DB 0DDH, 63H, 5CH, 0A5H, 55H, 0AAH, 0E1H, 0FEH, 0FFH, 0FFH, 0FFH, 0FFH
1060 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1070 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1080 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1090 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1100 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1110 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1120 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1130L4: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1140 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1150 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1160 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FEH
1170 DB 0F5H, 0FFH, 0F5H, 0FEH, 0FDH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1180 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1190 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1200 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1210 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1220 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1230 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1240 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1250L5: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1260 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1270 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1280 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1290 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1300 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1310 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1320 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1330 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1340 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1350 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1360 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1370L6: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1380 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 7FH, 3FH
1390 DB 3FH, 1FH, 1FH, 0FH, 0FH, 07H, 07H, 07H, 07H, 07H, 07H, 07H
1400 DB 07H, 07H, 07H, 07H, 07H, 0FH, 0FH, 0FH, 1FH, 1FH, 3FH, 7FH
1410 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 7FH, 0FFH, 0FFH, 0FFH
1420 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1430 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1440 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1450 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1460 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1470 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1480 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1490L7: DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1500 DB 0FFH, 0FFH, 0FFH, 0FFH, 3FH, 0FH, 07H, 03H, 01H, 00H, 00H, 00H
1510 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1520 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1530 DB 00H, 00H, 03H, 03H, 01H, 00H, 40H, 0C0H, 0FCH, 0FFH, 0FFH, 0FFH
1540 DB 0FFH, 0FFH, 0DFH, 8FH, 07H, 03H, 03H, 0FH, 1FH, 7FH, 0FFH, 3FH
1550 DB 3FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1560 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1570 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1580 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1590 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH
1600 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH

1610L8: DB 0FFH, 0FFH, 0FFH, 0FFH, 7FH, 0FFH, 0FFH, 7FH, 0FFH, 0FFH, 7FH, 0FFH
1620 DB 0FFH, 0FFH, 0FH, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 80H, 40H
1630 DB 10H, 0A0H, 48H, 40H, 14H, 0A0H, 48H, 80H, 50H, 00H, 00H, 00H
1640 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1650 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 03H, 0FBH, 0FDH, 0F3H, 0FFH
1660 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FEH, 0FCH, 0FCH, 0FCH, 0FCH, 0FCH, 0EBH, 00H
1670 DB 00H, 0A5H, 0FFH, 7FH, 0FFH, 7FH, 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 0FFH
1680 DB 0BFH, 7FH, 0BFH, 0FFH, 0BFH, 7FH, 0BFH, 0FFH, 0BFH, 7FH, 0BFH, 0FFH
1690 DB 0BFH, 7FH, 0BFH, 0FFH, 0BFH, 7FH, 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 7FH
1700 DB 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 0FFH, 0BFH, 0FFH
1710 DB 7FH, 0BFH, 0FFH, 7FH, 0BFH, 0FFH, 7FH, 0BFH, 0FFH, 7FH, 0BFH, 0FFH
1720 DB 7FH, 0BFH, 0FFH, 7FH, 0FFH, 7FH, 0FFH, 7FH, 0FFH, 7FH, 0FFH, 0FFH

1730L9: DB 2BH, 00H, 03H, 00H, 05H, 01H, 02H, 09H, 01H, 02H, 05H, 01H
1740 DB 02H, 27H, 00H, 00H, 00H, 00H, 00H, 40H, 10H, 0A2H, 54H, 0AAH
1750 DB 0B5H, 6AH, 0DDH, 75H, 0DBH, 74H, 0ADH, 52H, 0ACH, 51H, 0AAH, 44H
1760 DB 20H, 00H, 80H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1770 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 0F0H, 0FFH, 0FFH, 0FFH, 0FFH
1780 DB 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0BFH, 0FFH, 1FH, 0AFH, 0C7H
1790 DB 13H, 0C5H, 12H, 0C1H, 2AH, 81H, 4AH, 82H, 54H, 02H, 0A2H, 48H
1800 DB 82H, 29H, 42H, 08H, 0A2H, 09H, 42H, 08H, 22H, 09H, 42H, 08H
1810 DB 42H, 09H, 42H, 08H, 42H, 09H, 02H, 48H, 02H, 12H, 84H, 01H
1820 DB 12H, 08H, 02H, 24H, 02H, 08H, 02H, 22H, 08H, 02H, 04H, 11H
1830 DB 02H, 01H, 0AH, 01H, 02H, 09H, 02H, 01H, 0AH, 01H, 02H, 09H
1840 DB 01H, 02H, 05H, 01H, 0AH, 01H, 0AH, 01H, 05H, 01H, 02H, 4DH

1850L10: DB 91H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 80H, 00H
1860 DB 00H, 80H, 00H, 00H, 40H, 00H, 00H, 90H, 05H, 2AH, 95H, 5AH
1870 DB 0B5H, 0EFH, 55H, 0FFH, 55H, 0FFH, 55H, 0BBH, 0EEH, 55H, 0BAH, 0D5H
1880 DB 0E9H, 56H, 0A8H, 52H, 0A8H, 40H, 0A0H, 40H, 00H, 80H, 00H, 00H
1890 DB 80H, 00H, 80H, 10H, 40H, 0AH, 03H, 8BH, 03H, 23H, 87H, 03H
1900 DB 27H, 03H, 87H, 03H, 23H, 05H, 83H, 11H, 06H, 81H, 03H, 24H
1910 DB 03H, 02H, 09H, 82H, 05H, 02H, 81H, 0AH, 01H, 02H, 08H, 02H
1920 DB 04H, 00H, 05H, 00H, 02H, 00H, 01H, 04H, 00H, 09H, 00H, 00H
1930 DB 02H, 00H, 00H, 00H, 02H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1940 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1950 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
1960 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 44H

1970L11: DB 0BAH, 88H, 44H, 11H, 0A2H, 54H, 01H, 52H, 28H, 82H, 28H, 92H
1980 DB 28H, 82H, 54H, 29H, 82H, 58H, 22H, 98H, 64H, 99H, 62H, 9CH
1990 DB 75H, 0BAH, 6DH, 0BFH, 0FBH, 7FH, 0FFH, 7FH, 0FDH, 7FH, 0FFH, 7EH
2000 DB 0FDH, 7FH, 0FDH, 7FH, 0BEH, 0FFH, 5EH, 7DH, 0AEH, 7EH, 0ABH, 0D6H
2010 DB 7AH, 0AEH, 0D4H, 5BH, 0B4H, 6BH, 0AAH, 5AH, 0ACH, 55H, 0B2H, 0CCH
2020 DB 35H, 0D2H, 2CH, 0D2H, 29H, 0CCH, 52H, 28H, 95H, 0A8H, 44H, 29H
2030 DB 44H, 91H, 24H, 90H, 22H, 88H, 20H, 8AH, 40H, 11H, 88H, 22H
2040 DB 40H, 08H, 41H, 08H, 40H, 12H, 80H, 24H, 00H, 10H, 84H, 00H
2050 DB 40H, 04H, 40H, 08H, 80H, 00H, 10H, 80H, 00H, 20H, 00H, 00H
2060 DB 20H, 00H, 00H, 40H, 00H, 80H, 00H, 00H, 00H, 00H, 00H, 00H
2070 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
2080 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H, 44H

