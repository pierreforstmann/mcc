/*
* tal.c : test array loop
* using example from 
* https://httpd.apache.org/docs/2.4/developer/modguide.html:
*
* static int example_handler(request_rec *r)
* {
*   
*    keyValuePair *formData;
*   
*    formData = readPost(r);
*    if (formData) {
*        int i;
*        for (i = 0; &formData[i]; i++) {
*            if (formData[i].key && formData[i].value) {
*                ap_rprintf(r, "%s = %s\n", formData[i].key, formData[i].value);
*            } else if (formData[i].key) {
*                ap_rprintf(r, "%s\n", formData[i].key);
*            } else if (formData[i].value) {
*                ap_rprintf(r, "= %s\n", formData[i].value);
*            } else {
*                break;
*            }
*        }
*    }
*    return OK;
* }
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        typedef struct {
         int c;
        } s;
        s *ps;
        int n = 3;
        int i;

        ps = (s *)malloc(sizeof(s) * (n + 1));
	memset((void *)ps, '\0', sizeof(s) * (n +1));
        ps[0].c = 0;
        ps[1].c = 1;
        ps[2].c = 2;

        for ( i = 0 ; &ps[i] ; i++)
                printf("&ps[%d]=%p ps[%d].c=%d \n", i, &ps[i], i, ps[i].c);

        exit(0);
}
