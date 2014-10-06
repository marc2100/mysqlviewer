#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "own_mysql.h"
#include "treeviewer.h"

//G_CALLBACK-Funktionen
void button_refresh_clicked(GtkWidget *widget, gpointer data);
void button_exit_clicked(GtkWidget *widget, gpointer data);



#endif // BUTTONS_H
