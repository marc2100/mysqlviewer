#ifndef OWN_MYSQL_H
#define OWN_MYSQL_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <mysql/mysql.h>
#include "treeviewer.h"
#include "keyfile.h"


struct DB_STRUCT{
gint num_fields;				///die Anzahl der Spalten
gulong *element_size;		///die größe in Bytes für alle Spalten
GPtrArray *ptr_array;		///speichert die Spalteneinträge
};

void get_mysql_version (void);
GPtrArray *read_mysql_bd_row (void);

//ließt die Zeile mit der übergebenen ID aus
struct DB_STRUCT *read_row_mysql (guint ID);


//gibt das Bild
struct BILD_STRUCT *picture_mysql (gchar *name,MYSQL_RES* result);

#endif // OWN_MYSQL_H
