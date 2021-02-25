#ifndef POINTER_HANDLER_H
#define POINTER_HANDLER_H

#include <gtk/gtk.h>

typedef struct FrmMainPointer{
    GtkWidget *window;
    
    GtkLabel *lblHeadline;

    GtkComboBox *cbSort;
    GtkComboBoxText *cbtRemove;
    
    GtkTreeStore *treeStore;
    GtkTreeView *treeView;
    GtkTreeViewColumn *cx0;
    GtkTreeViewColumn *cx1;
    GtkTreeViewColumn *cx2;
    GtkTreeSelection *treeSelection;
    GtkCellRenderer *cr0;
    GtkCellRenderer *cr1;
    GtkCellRenderer *cr2;
    
    GtkButton *cmdSearch;
    GtkButton *cmdAdd;
    GtkButton *cmdRemove;
    GtkButton *cmdRefresh;
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
