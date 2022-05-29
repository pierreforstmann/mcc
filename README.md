# mcc

<h1> Explaining 1st International Obfuscated C Code Contest (1984) anonymous.c</h1>

In November 2015 Iggy Fernandez has published <a href=http://www.toadworld.com/platforms/oracle/b/weblog/archive/2015/11/29/the-best-job-interview-of-my-life>The Best Job Interview of My Life</a> about a job interview for C programming. In the same article he has published following C code <a href=https://groups.google.com/forum/#!topic/net.lang.c/KyEvAtrJRqE/discussion>anonymous.c</a> and has asked for a "good code explanation":
<pre>
$ cat >helloworld.c
int i;main(){for(;i["]&lti;++i){--i;}"];read('-'-'-',i+++"hello, world!\n",'/'/'/'));}read(j,i,p){write(j/p+p,i---j,i/i);}
$ cc -o helloworld helloworld.c
$ ./helloworld
hello, world!
</pre>
Here is my answer (for this blog post I have used Fabrice Bellard <a href=http://bellard.org/tcc/>TCC compiler</a> for Windows 64 bit on Windows 8.1).
<h2> Arrays and pointers in C</h2>
In C langage there is special relationship between arrays and pointers. 
If <code>a</code> is an array variable name and <code>i</code> an integer variable name used to index this array, the following expressions to access array entry designated by variable i are equivalent:
<br>
<br>
<code>a[ i ]</code> 
<br>
<code>*( a + i )</code>
<br>
<code>i[ a ]</code>
<br>
<code>*( i + a )</code>
<br>
<br>
See <a href=https://en.wikipedia.org/wiki/Pointer_%28computer_programming%29#C_and_C.2B.2B>C Pointer Arithmetic on Wikipedia</a>.
<br>
<br>
I have written 7 C programs and explained in each step what I have changed with respect to the previous one. The last one is the same as anonymous.c (ignoring spaces and line breaks).
<h2>test0.c</h2>
The following code displays the 13 characters of "hello, world!" string:
<pre>
>type test0.c
int i = 0;
char s[] = "hello, world!";
main()
{
for( ; *(s + i ); i++)
 {
	printf("i=%d ",i);
	printf("*(s+i)=%c\n",*(s+i));
 }
}
>tcc -o test0.exe test0.c

>test0
i=0 *(s+i)=h
i=1 *(s+i)=e
i=2 *(s+i)=l
i=3 *(s+i)=l
i=4 *(s+i)=o
i=5 *(s+i)=,
i=6 *(s+i)=
i=7 *(s+i)=w
i=8 *(s+i)=o
i=9 *(s+i)=r
i=10 *(s+i)=l
i=11 *(s+i)=d
i=12 *(s+i)=!

</pre>
Remember also that a C string is a array of characters that starts at index 0 (like any C array) and must end with binary 0. In above code this is used to end the loop: when i is set to 13, the character pointed by <code>*(s+i)</code> is the the binary 0 and this ends the loop because 0 evaluates to false in C.
<h2>test1.c</h2>
In the expression <code> *(s+i) </code> I can swap array name and index name:
<pre>
>type test1.c
int i = 0;
char s[] = "hello, world!";
main()
{
for( ; *( i + s ); i++)
 {
	printf("i=%d ", i);
	printf("*(i+s)=%c\n", *( i + s ));
 }
}
>tcc -o test1.exe test1.c

>test1
i=0 *(i+s)=h
i=1 *(i+s)=e
i=2 *(i+s)=l
i=3 *(i+s)=l
i=4 *(i+s)=o
i=5 *(i+s)=,
i=6 *(i+s)=
i=7 *(i+s)=w
i=8 *(i+s)=o
i=9 *(i+s)=r
i=10 *(i+s)=l
i=11 *(i+s)=d
i=12 *(i+s)=!
</pre>
<h2>test2.c</h2>
At this step I use array expression <code>i[s]</code> to replace <code>*( i + s )</code>:
<pre>
>type test2.c
int i = 0;
char s[] = "hello, world!";
main()
{
for( ; i[s]; i++)
 {
        printf("i=%d ", i);
        printf("i[s]=%c\n", i[s]);
 }
}
>tcc -o test2.exe test2.c

>test2
i=0 i[s]=h
i=1 i[s]=e
i=2 i[s]=l
i=3 i[s]=l
i=4 i[s]=o
i=5 i[s]=,
i=6 i[s]=
i=7 i[s]=w
i=8 i[s]=o
i=9 i[s]=r
i=10 i[s]=l
i=11 i[s]=d
i=12 i[s]=!

</pre>
<h2>test3.c</h2>
Now I decide to:
<li>
replace the s string with a different character string  of 15 characters (actually the one used in anonymous.c) because I will add "\n" to "hello world!" string
</li>
<li>
use a new pointer arithmetic expression to print "hello world!\n" characters one by one
</li>
<li>
use the write function instead of printf:
</li>
<pre>
>test3
hello, world!

>type test3.c
int i = 0;
char s[] = "]&lti;++i){--i;}";
main()
{
for( ; i[s]; i++ )
 {
        write(1, "hello, world!\n" + i , 1);
 }
}
>tcc -o test3.exe test3.c

>test3
hello, world!

</pre>
<h2>test4.c</h2>
Now I made following changes:
<li>
I remove the s string variable and to replace it by its litteral value in the for loop
</li>
<li>
I move the write function in the last part of the loop making the loop body empty
</li>
<li>
I add in the last part of the loop the i incrementation:
</li>
<pre>
>type test4.c
int i = 0;
main()
{
for( ; i["]&lti;++i){--i;}"]; write(1, "hello, world!\n" + i++ , 1) )
 {

 }
}
>tcc -o test4.exe test4.c

>test4
hello, world!


</pre>
<h2>test5.c</h2>
Now I modify the code to:
<li>
swap "hello world\n" and variable i
</li>
<li>
create a new function named read but that only calls write
</li>
<li>
replace write call by read call in for loop
</li>
<li>
delete empty loop body:
</li>
<pre>
>type test5.c
int i = 0;
main()
{
 for( ; i["]&lti;++i){--i;}"]; read(1, i++ +  "hello, world!\n" , 1) );
}
read(p1,p2,p3)
{
 write(p1,p2,p3);
}
>tcc -o test5.exe test5.c

>test5
hello, world!

</pre>
<h2>test6.c</h2>
Now I:
<li>
replace read first actual parameter from 1 to 0 
</li>
<li>
rename read function formal parameters from p1, p2, p3 to j, i p
</li>
</li>
<li>
modify write function actual parameters like in final code from p1, p2, p3 to j+p/p, i - - - - j and i/i
</li>
Because:
<br>
- p is always set to 1 and j always set to 0, j+p/p always evaluates to 1, 
<br>
- j is always set to 0, i - - - - j always evaluates to i
<br>
- parameter i contains the character to be displayed: it will not be 0 because string "hello world!\n" has only a binary 0 at string end: so i/i always evaluates to 1:
<pre>
>type test6.c
int i = 0;
main()
{
 for( ; i["]&lti;++i){--i;}"]; read(0, i++ +  "hello, world!\n" , 1) );
}
read(j , i , p)
{
 write(j + p/p , i - - - - j, i/i);
}
>tcc -o test6.exe test6.c

>test6
hello, world!

</pre>
<h2>test7.c = anonymous.c </h2>
Last step is to change read actual parameters by arithmetic expression where characters are converted to integers:
<li>
0 is replaced by '-' - '-'
</li>
<li>
1 is replaced by '/' / '/':
</li>
<pre>
>type test7.c
int i;
main()
{
 for( ; i["]&lti;++i){--i;}"]; read('-'-'-', i++ +  "hello, world!\n" , '/'/'/') );
}
read(j , i , p)
{
 write(j + p/p , i - - - - j, i/i);
}
>tcc -o test7.exe test7.c

>test7
hello, world!

</pre>
Except spaces and line breaks this is now the original C code.

