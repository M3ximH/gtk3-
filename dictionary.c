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
    
    // Radiobuttons
    widgets->rbDeuEng = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rbDeuEng"));
    widgets->rbEngDeu = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rbEngDeu"));
    
    // TreeView
    widgets->treeStore = GTK_TREE_STORE(gtk_builder_get_object(builder, "treeStore"));
    widgets->treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeView"));
    widgets->cx1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx1"));
    widgets->cx2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx2"));
    widgets->treeSelection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "treeSelection"));
    widgets->cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr1"));
    widgets->cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr2"));
    
    // Buttons
    widgets->cmdSearch = GTK_BUTTON(gtk_builder_get_object(builder, "cmdSearch"));
    widgets->cmdAdd = GTK_BUTTON(gtk_builder_get_object(builder, "cmdAdd"));
    widgets->cmdRemove = GTK_BUTTON(gtk_builder_get_object(builder, "cmdRemove"));
    
    gtk_tree_view_column_add_attribute(widgets->cx1, widgets->cr1, "text", 0);
    gtk_tree_view_column_add_attribute(widgets->cx2, widgets->cr2, "text", 1);
    
    GtkTreeIter iter;
    gtk_tree_store_append(widgets->treeStore, &iter, NULL);
    gtk_tree_store_set(widgets->treeStore, &iter, 0, "Hallo", -1);
    gtk_tree_store_set(widgets->treeStore, &iter, 1, "Hello", -1);
    
    gtk_builder_connect_signals(builder, widgets);
    
    g_object_unref(builder);
    gtk_widget_show(widgets->window);
    RefreshWordList(widgets->treeStore);
    gtk_main();
    
    g_slice_free(mainP, widgets);
    
    return EXIT_SUCCESS;
}


void RefreshWordList(GtkTreeStore *store){
    gtk_tree_store_clear(store);
    
    FILE *file;
    file = fopen("words.txt", "r");
    if(file != NULL){
        const size_t line_size = 256;
        char *line = malloc(line_size);
        while(fgets(line, line_size, file) != NULL){
            char *parts = strtok(line, "|");
            char *partarr[2];
            int i = 0;
            while(parts != NULL){
                partarr[i++] = parts;
                parts = strtok(NULL, "|");
            }
            GtkTreeIter iter;
            gtk_tree_store_append(store, &iter, NULL);
            gtk_tree_store_set(store, &iter, 0, partarr[0], -1);
            gtk_tree_store_set(store, &iter, 1, partarr[1], -1);
        }
        free(line);
    }
}

void on_cmdRemove_clicked(GtkButton *button, mainP *widgets){
    assert(widgets != NULL);
    gchar *value;
	GtkTreeIter iter;
	GtkTreeModel *model;

	if (gtk_tree_selection_get_selected
		(widgets->treeSelection, &model, &iter) == FALSE)
			return;

	gtk_tree_model_get(model, &iter, 0, &value,  -1);
	printf("col 0 = %s; ", value);
	gtk_tree_model_get(model, &iter, 1, &value,  -1);
	printf("col 1  = %s\n", value);
}

void on_treeSelect_changed(GtkWidget *c){
    gchar *value;
	GtkTreeIter iter;
	GtkTreeModel *model;

	if (gtk_tree_selection_get_selected
		(GTK_TREE_SELECTION(c), &model, &iter) == FALSE)
			return;

	gtk_tree_model_get(model, &iter, 0, &value,  -1);
	printf("col 0 = %s; ", value);
	gtk_tree_model_get(model, &iter, 1, &value,  -1);
	printf("col 1  = %s\n", value);
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
        FILE *file;
        file = fopen("words.txt", "at"); // Datei zum Anhängen öffnen
        char out[256]; // Text der in Datei geschrieben wird
        sprintf(out, "%s|%s\n", trans->German, trans->English); // Eingegebene Worte in Out, | als Trennzeichen
        free(trans); // Speicher wieder freigeben
        fputs(out, file); // In Datei schreiben
        fclose(file);
        gtk_widget_destroy(widgets->window); // Fenster schließen
    }else{
        printf("Leere Eingaben sind ungültig");
    }
}

void on_frmAddItem_destroy(void){
    gtk_main_quit();
}





