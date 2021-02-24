#ifndef POINTER_HANDLER_H
#define POINTER_HANDLER_H

#include <gtk/gtk.h>

typedef struct FrmMainPointer{
    GtkWidget *window;
    
    GtkLabel *lblHeadline;
    
    GtkToggleButton *rbDeuEng;
    GtkToggleButton *rbEngDeu;
    
    GtkTreeStore *treeStore;
    GtkTreeView *treeView;
    GtkTreeViewColumn *cx1;
    GtkTreeViewColumn *cx2;
    GtkTreeSelection *treeSelection;
    GtkCellRenderer *cr1;
    GtkCellRenderer *cr2;
    
    GtkButton *cmdSearch;
    GtkButton *cmdAdd;
    GtkButton *cmdRemove;
} mainP;

typedef struct FrmAddPointer{
    GtkWidget *window;
    
    GtkEntry *txtGerWord;
    GtkEntry *txtEngWord;
    
    GtkButton *cmdAdd;
    GtkButton *cmdCancel;
} frmAddP;

typedef struct GermanEnglishWordConnection{
    const char *German;
    const char *English;
} Translation;

#endif
