/* Beleg Programmierung 1
 * Aufgabe 3, Wörterbuch deu-engl/engl-deu
 * Datei: dictionary.c
 * Author: Maxim Hannes Haschke
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ui.h"
#include "functions.h"

int main(int argc, char **argv){
    printf("Hallo\n");
    
    GtkBuilder *builder = NULL;
    mainP *widgets = g_slice_new(mainP);

    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new_from_file("dictionary.glade");
    
    // Pointern Steuerelemente zuweisen
    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "frmMain"));
    
    // ComboBox
    widgets->cbSort = GTK_COMBO_BOX(gtk_builder_get_object(builder, "cbSort"));
    
    // TreeView
    widgets->treeStore = GTK_TREE_STORE(gtk_builder_get_object(builder, "treeStore"));
    widgets->treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeView"));
    widgets->cx0 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx0"));
    widgets->cx1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx1"));
    widgets->cx2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx2"));
    widgets->treeSelection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "treeSelection"));
    widgets->cr0 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr0"));
    widgets->cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr1"));
    widgets->cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr2"));
    
    // Buttons
    widgets->cmdSearch = GTK_BUTTON(gtk_builder_get_object(builder, "cmdSearch"));
    widgets->cmdAdd = GTK_BUTTON(gtk_builder_get_object(builder, "cmdAdd"));
    widgets->cmdRemove = GTK_BUTTON(gtk_builder_get_object(builder, "cmdRemove"));
    widgets->cmdRefresh = GTK_BUTTON(gtk_builder_get_object(builder, "cmdRefresh"));
    
    gtk_tree_view_column_add_attribute(widgets->cx0, widgets->cr0, "text", 0);
    gtk_tree_view_column_add_attribute(widgets->cx1, widgets->cr1, "text", 1);
    gtk_tree_view_column_add_attribute(widgets->cx2, widgets->cr2, "text", 2);
    
    gtk_builder_connect_signals(builder, widgets);
    
    g_object_unref(builder);
    gtk_widget_show(widgets->window);
    RefreshWordList(widgets);
    gtk_main();
    
    g_slice_free(mainP, widgets);
    
    return EXIT_SUCCESS;
}


void RefreshWordList(mainP *widgets){
    gtk_tree_store_clear(widgets->treeStore);
    
    FILE *file;
    file = fopen("words.txt", "r");
    if(file != NULL){
        const size_t line_size = 256;
        char *line = malloc(line_size);
        int linecount=0;
        while(fgets(line, line_size, file) != NULL){
            char *parts = strtok(line, "|");
            char *partarr[2];
            int i = 0;
            while(parts != NULL){
                partarr[i++] = parts;
                parts = strtok(NULL, "|");
            }
            
            char _index[5];
            sprintf(_index, "%d", linecount);
            GtkTreeIter iter;
            gtk_tree_store_append(widgets->treeStore, &iter, NULL);
            gtk_tree_store_set(widgets->treeStore, &iter, 0, _index, -1);
            gtk_tree_store_set(widgets->treeStore, &iter, 1, trimWhitespace(partarr[0]), -1);
            gtk_tree_store_set(widgets->treeStore, &iter, 2, trimWhitespace(partarr[1]), -1);
            
            linecount++;
        }
        free(line);
    }
}

char *trimWhitespace(char * s) {
    int l = strlen(s);

    while(isspace(s[l - 1])) --l;
    while(* s && isspace(* s)) ++s, --l;

    return strndup(s, l);
}

void on_cmdRemove_clicked(GtkButton *button, mainP *widgets){
    gchar *value;
	GtkTreeIter iter;
	GtkTreeModel *model;

	if (gtk_tree_selection_get_selected
		(widgets->treeSelection, &model, &iter) == FALSE)
			return;

	gtk_tree_model_get(model, &iter, 0, &value,  -1);
    
    int line_index = atoi(value);
    printf("%i\n", line_index);
    
    FILE *srcFile;
    FILE *tempFile;
    
    srcFile = fopen("words.txt", "r");
    tempFile = fopen("delete-line.tmp", "w");
    
    if(srcFile == NULL || tempFile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    rewind(srcFile); // Zeiger an Anfang der Datei setzen
    deleteLine(srcFile, tempFile, line_index); // alle Zeilen außer die zu löschende in neue Datei schreiben
    fclose(srcFile);
    fclose(tempFile);
    remove("words.txt"); // Datei mit Zeile die gelöscht werden soll wird gelöscht, um tempFile umzubenennen
    rename("delete-line.tmp", "words.txt"); // temp-file in original umbennen
    RefreshWordList(widgets);
}

void deleteLine(FILE *srcFile, FILE *tempFile, const int line)
{
    char buffer[256];
    int count = 0;
    
    while((fgets(buffer, 256, srcFile)) != NULL)
    {
        if(line != count) 
            fputs(buffer, tempFile);
        
        count++;
    }
}

void on_cmdRefresh_clicked(GtkButton *button, mainP *widgets){
    RefreshWordList(widgets);
}

void on_cbSort_changed(GtkComboBox *cb, mainP *widgets){
    gint selectedIndex = gtk_combo_box_get_active(widgets->cbSort);
    if(selectedIndex == (gint)0) // Deutsch, aufsteigend
        gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(widgets->treeStore), 1, GTK_SORT_ASCENDING);
    else if(selectedIndex == (gint)1) // Deutsch, absteigend
        gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(widgets->treeStore), 1, GTK_SORT_DESCENDING);
    else if(selectedIndex == (gint)2) // Englisch, aufsteigend
        gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(widgets->treeStore), 2, GTK_SORT_ASCENDING);
    else if(selectedIndex == (gint)3) // Englisch, absteigend
        gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(widgets->treeStore), 2, GTK_SORT_DESCENDING); 
}

void on_frmMain_destroy(void){
    gtk_main_quit();
}

void on_cmdAdd_clicked(GtkButton *button, mainP* mainWidgets){
    GtkBuilder *builder = NULL;
    frmAddP *widgets = g_slice_new(frmAddP);
    
    //gtk_text_buffer_set_text(mainWidgets->textViewBuffer, "Neuer Text", -1); 
    
    builder = gtk_builder_new_from_file("dictionary.glade");
    
    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "frmAddItem"));
    
    widgets->txtGerWord = GTK_ENTRY(gtk_builder_get_object(builder, "txtGermanWord"));
    widgets->txtEngWord = GTK_ENTRY(gtk_builder_get_object(builder, "txtEnglishWord"));
    
    widgets->cmdAdd = GTK_BUTTON(gtk_builder_get_object(builder, "cmdAddWord"));
    widgets->cmdCancel = GTK_BUTTON(gtk_builder_get_object(builder, "cmdCancel"));
    
    
    gtk_builder_connect_signals(builder, widgets);
    
    
    
    g_object_unref(builder);
    gtk_widget_show(widgets->window);
    
    gtk_main();
    g_slice_free(frmAddP, widgets);
}

void cmdAddWord_clicked(GtkButton *button, frmAddP* widgets){
    assert(widgets != NULL);
    Translation *trans = malloc(sizeof(Translation));
    trans->German = malloc(sizeof(gtk_entry_get_text(widgets->txtGerWord))); // Speicher reservieren
    trans->English = malloc(sizeof(gtk_entry_get_text(widgets->txtEngWord))); // Speicher reservieren
    trans->German = gtk_entry_get_text(widgets->txtGerWord); // Text aus Entry in struct speichern
    trans->English = gtk_entry_get_text(widgets->txtEngWord); // Text aus Entry in struct speichern
    
    if(trans->German[0] != '\0' || trans->English[0] != '\0'){ // Textfeld nicht leer?
        if(isWhitespace(trans->German) == 0 || isWhitespace(trans->English) == 0){ // Textfeld nicht nur Leerzeichen?
            FILE *file;
            file = fopen("words.txt", "at"); // Datei zum Anhängen öffnen
            char out[256]; // Text der in Datei geschrieben wird
            sprintf(out, "%s|%s\n", trans->German, trans->English); // Eingegebene Worte in Out, | als Trennzeichen
            free(trans); // Speicher wieder freigeben
            fputs(out, file); // In Datei schreiben
            fclose(file);
            gtk_widget_destroy(widgets->window); // Fenster schließen
        }else
            printf("Eingabe besteht aus Leerzeichen ist ungültig");
    }else
        printf("Leere Eingaben sind ungültig");
}

int isWhitespace(const char *s){
    while(*s != '\0'){
        if(!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

void on_frmAddItem_destroy(void){
    gtk_main_quit();
}





