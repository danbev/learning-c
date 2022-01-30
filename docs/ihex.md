### Intel Hex files
Is a storage format in ascii of a binary file, like a binary file compiled with
gcc for example:
```console
$ cat ihex.c 
int main(int argc, char** argv) {
  return 0;
}
$ gcc -o ihex ihex.c

$ file ihex
ihex: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=5067a6cf200ea8e42c940102046560cab0407702, for GNU/Linux 3.2.0, not stripped

$ size ihex
   text	   data	    bss	    dec	    hex	filename
   1043	    460	      4	   1507	    5e3	ihex
$ 

$ du -h ihex
24K	ihex
```

So we can transform this binary into Intel Hex format using `objcopy`:
```console
$ objcopy -O ihex ihex ihex.hex

$ file ihex.hex 
ihex.hex: ASCII text, with CRLF line terminators

$ du -h ihex.hex
8.0K	ihex.hex
```

So lets take a look at some of the produced `ihex.hex` file:
```
:020000040040BA
:100318002F6C696236342F6C642D6C696E75782D7C
:0C0328007838362D36342E736F2E3200DC
:10033800040000001000000005000000474E5500B2
:10034800028000C00400000001000000000000005E
:10035800040000001400000003000000474E550090
:100368005067A6CF200EA8E42C940102046560CA49
:04037800B040770218
...
:00000001FF 
```

### Format
```
:BBAAAATT[DDDDDD]CC
```
#### start of line
Each line in this format starts with a `:`.

#### Byte Count (BB)
The next to 2 hex digits specify the number of bytes in the data field.

#### Address (AAAA)
The address in bytes

#### Type (TT)
00 = data bytes
01 = end of file marker
02 = extended address 
04 = extended address 

#### Checksum (CC)


So thinking about the information in the .hex file provieds the addresses and
the contents of those memory locations, that could be instructions or data. This
data is placed in those memory locations when we flash a microcontroller. So
any information regarding sections that we would have seen in an .elf file
do not exist. 
