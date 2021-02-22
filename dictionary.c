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

;int main(int argc, char **argv){
    GtkBuilder *builder = NULL;
    mainP *widgets = g_slice_new(mainP);

    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new_from_file("dictionary.glade");
    
    widgets->window = GTK_WINDOW(gtk_builder_get_object(builder, "frmMain"));
    gtk_window_set_title(widgets->window, "Wörterbuch engl/deu");
    
    widgets->rbDeuEng = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rbDeuEng"));
    
    widgets->rbEngDeu = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rbEngDeu"));
    
    widgets->textViewOutput = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textViewOutput"));
    widgets->textViewBuffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(widgets->textViewOutput, widgets->textViewBuffer);   
    gtk_text_buffer_insert_at_cursor(widgets->textViewBuffer, "Leer", -1); // das funktioniert
    
    widgets->cmdSearch = GTK_BUTTON(gtk_builder_get_object(builder, "cmdSearch"));
    
    widgets->cmdAdd = GTK_BUTTON(gtk_builder_get_object(builder, "cmdAdd"));
    
    widgets->cmdRemove = GTK_BUTTON(gtk_builder_get_object(builder, "cmdRemove"));
    
    gtk_builder_connect_signals(builder, widgets);
    
    g_object_unref(builder);
    gtk_widget_show(widgets->window);
    
    gtk_main();
    
    g_slice_free(mainP, widgets);
    
    return EXIT_SUCCESS;
}

void on_frmMain_destroy(void){
    gtk_main_quit();
}

void cmdAddWord_clicked(GtkButton *button, frmAddP *widgets){
    Translation *trans = malloc(sizeof(Translation));
    
    strcpy(trans->German, gtk_entry_get_text(widgets->txtGerWord));
    strcpy(trans->English, gtk_entry_get_text(widgets->txtEngWord));
    
    free(trans);
}

void on_cmdAdd_clicked(GtkButton *button, mainP* mainWidgets){
    GtkBuilder *builder = NULL;
    frmAddP *widgets = g_slice_new(frmAddP);
    
    gtk_text_buffer_set_text(mainWidgets->textViewBuffer, "Neuer Text", -1); // das funktioniert nicht, Fehler: assertion GTK_IS_TEXT_BUFFER failed
    
    builder = gtk_builder_new_from_file("dictionary.glade");
    
    widgets->window = GTK_WINDOW(gtk_builder_get_object(builder, "frmAddItem"));
    
    widgets->txtGerWord = GTK_ENTRY(gtk_builder_get_object(builder, "txtGermanWord"));
    widgets->txtEngWord = GTK_ENTRY(gtk_builder_get_object(builder, "txtEnglishWord"));
    
    widgets->cmdAdd = GTK_BUTTON(gtk_builder_get_object(builder, "cmdAddWord"));
    widgets->cmdCancel = GTK_BUTTON(gtk_builder_get_object(builder, "cmdCancel"));
    
    
    gtk_builder_connect_signals(builder, NULL);
    
    
    
    g_object_unref(builder);
    gtk_widget_show(widgets->window);
    
    gtk_main();
    
    g_slice_free(frmAddP, widgets);
}

void on_frmAddItem_destroy(void){
    gtk_main_quit();
}

/*
void CreateNewDictionaryEntry(Translation *trans)
{
    FILE *file;
    file = fopen("words.txt", "w");
    fprintf(file, "%s|%s", trans->German, trans->English);
    fclose(file);
}*/

