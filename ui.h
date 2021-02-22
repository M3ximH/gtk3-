#ifndef POINTER_HANDLER_H
#define POINTER_HANDLER_H

#include <gtk/gtk.h>

typedef struct FrmMainPointer{
    GtkWindow *window;
    
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
    GtkWindow *window;
    
    GtkEntry *txtGerWord;
    GtkEntry *txtEngWord;
    
    GtkButton *cmdAdd;
    GtkButton *cmdCancel;
} frmAddP;

typedef struct GermanEnglishWordConnection{
    char German[80];
    char English[50];
} Translation;

#endif
