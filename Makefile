casovac: main.c
	gcc main.c -o casovac -I./raylib-5.5_linux_amd64/include -L./raylib-5.5_linux_amd64/lib -l:libraylib.a -lm
