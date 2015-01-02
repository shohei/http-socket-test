#include "openurl.h"

int main(int argc, char** argv){
    openurl("output1.html","www.google.co.jp","/",80);
    openurl("output2.html","www.ie.u-ryukyu.ac.jp","/~e085739/c.makefile.tuts.html",80);
    openurl("output3.html","www.isl.ne.jp","/pcsp/python/python18.html",80);

    return 0;
}
