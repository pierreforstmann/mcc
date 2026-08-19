/*
** tl.c
** test loop equivalence
*/
#include <stdio.h>
#include <stdint.h>

void code1() {
    char *key = "1234567890ABCDEF";
    uint32_t keybuf[2];
    uint8_t *q;

    int i = 0;
    printf("code1:\n");

    q = (uint8_t *)keybuf;

    while (q - (uint8_t *) keybuf - 8)
    {
        printf("i=%d\n", i);
        i++;
        *q++ = *key << 1;
        if (*key != '\0')
            key++;
    }
   
    printf("\n");

    i = 0;
    while (*key)
    {
            /*
             * And XOR with the next 8 characters of the key.
             */
            q = (uint8_t *) keybuf;
            while (q - (uint8_t *) keybuf - 8 && *key) {
                printf("i=%d\n", i);
                i++;
                *q++ ^= *key++ << 1;
            }
   }

}

void code2() {
    uint32_t keybuf[2];
    size_t              bytenum;

    printf("code2:\n");

    for (bytenum = 0; bytenum < sizeof(keybuf); bytenum++)
    {
        printf("bytenum=%ld\n", bytenum);
    }

    printf("\n");

    char *key = "12345678";
    uint8_t *q;
    q = (uint8_t *)keybuf;

    while (*key)
    {
            /*
             * And XOR with the next 8 characters of the key.
             */
            q = (uint8_t *) keybuf;
            for (bytenum = 0;
		 bytenum < sizeof(keybuf) && *key;
           	 bytenum++) {
                    printf("bytenum=%ld\n", bytenum);
                    *q++ ^= *key++ << 1;
            }
   }


}

int main(int argc, char **argv)
{
    code1();
    code2();


}
