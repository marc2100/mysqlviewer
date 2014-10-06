#ifndef KEYFILE_H
#define KEYFILE_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "own_mysql.h"
#include "treeviewer.h"

#define keyfile_file "mysql-viewer"

///läd die Keyfile *filename oder bie NULL die default keyfile_file
///@return true bei erfolg, bei fehlern false
gboolean keyfile_init (const gchar *filename);


///gibt einen String mit dem User für die Datenbank zurück
///@warning muss mit g_free freigegeben werden
///@return gchar *db_username
gchar *keyfile_get_db_user (void);

///gibt einen String mit dem Passwort für die Datenbank zurück
///@warning muss mit g_free freigegeben werden
///@return gchar *db_password
gchar *keyfile_get_db_password (void);

///gibt einen String mit dem Host für die Datenbank zurück
///@warning muss mit g_free freigegeben werden
///@return gchar *db_host
gchar *keyfile_get_db_host (void);

#endif // KEYFILE_H
