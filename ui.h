#ifndef POINTER_HANDLER_H
#define POINTER_HANDLER_H

#include <gtk/gtk.h>

typedef struct FrmMainPointer{
    GtkWidget *window;
    
    GtkLabel *lblHeadline;
    
    GtkToggleButton *rbDeuEng;
    GtkToggleButton *rbEngDeu;
    
    GtkTextView *textViewOutput;
    GtkTextBuffer *textViewBuffer;
    
    GtkButton *cmdSearch;
    GtkButton *cmdAdd;
    GtkButton *cmdRemove;
} mainP;

typedef struct FrmAddPointer{
    
}

#endif
