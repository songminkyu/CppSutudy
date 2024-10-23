module M;

int a = use_f<int>();// ok
int b = use_g<int>();// error
int c = use_h<int>();// ok