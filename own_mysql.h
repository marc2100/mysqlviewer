/*
Copyright (c) 2014-2015 "Marcus Pries"

This file is part of mysqlviewer.

mysqlviewer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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


//gibt das Bild zurück
struct BILD_STRUCT *picture_mysql (gchar *name,MYSQL_RES* result);

#endif // OWN_MYSQL_H
