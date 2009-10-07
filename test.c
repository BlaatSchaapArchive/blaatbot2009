#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "xmlParser.h"

int main()
{
    void *lib;
    char *s;
    int FromPos, ToPos;
    void (*Blaat)(void);

    lib = dlopen("./libxmlParser.so", RTLD_LAZY);
    if (lib) {
      createXMLString = dlsym(lib, "createXMLString"); 
      if (Blaat) {
        Blaat();
      } else printf("Cannot Blaat\n%s\n",dlerror());
    dlclose(lib);    
    } else printf("Cannot lib\n%s\n",dlerror());
    
    return 0;
} 
