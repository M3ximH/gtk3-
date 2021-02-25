#ifndef VW_FUNCTIONS_H
#define VW_FUNCTIONS_H

void on_cmdAdd_clicked(GtkButton *button, mainP* mainWidgets);
void cmdAddWord_clicked(GtkButton *button, frmAddP *widgets);
void on_cmdRemove_clicked(GtkButton *button, mainP *widgets);

char *trimWhitespace(char * s);
void RefreshWordList();
void deleteLine(FILE *srcFile, FILE *tempFile, const int line);
int isWhitespace(const char *s);

void on_frmMain_destroy(void);
void on_frmAddItem_destroy(void);

#endif
