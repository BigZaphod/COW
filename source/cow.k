\d M
moo: "];"							/ 0: end loop
mOo: "p-:1;"						/ 1: dec mem ptr
moO: "p+:1;"						/ 2: inc mem ptr
mOO: ". M@(!M)@m p"				/ 3: eval
Moo: ".:[m p; M.OOM; M.oom];"	/ 4: read-write
MOo: "m[p]-:1;"					/ 5: dec mem
MoO: "m[p]+:1;"					/ 6: inc mem
MOO: "while[m p;"					/ 7: begin loop
OOO: "m[p]:0;"					/ 8: zero
MMM: ":[r~_n; r:m p; (r:_n;m[p]:r)];"	/ 9: save-load
OOM: "`0:,$m p;"					/ 10: write
oom: "m[p]:0$0:`;"				/ 11: read
\d ^
m:&10000; p:0; r:_n				/ set the stage
.,/M c@&(c:`$1_'(&c=*c)_ c:,/" ",/:0:_i 0)_lin!M / read, xlate, eval
\\


