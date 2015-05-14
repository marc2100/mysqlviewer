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

#include "keyfile.h"
GKeyFile *global_keyfile = NULL;



//läd die Keyfile *filename oder bie NULL die default keyfile_file
//@return true bei erfolg, bei fehlern false
gboolean keyfile_init (const gchar *filename){
	GError *error = NULL;
	GKeyFile *keyfile;
	keyfile = g_key_file_new ();

	//Falls Dateiname übergeben wurde, versuchen die Datei zu laden
	if (filename!=NULL){
		if (!g_key_file_load_from_file(keyfile,
																filename,
																G_KEY_FILE_KEEP_COMMENTS,
																&error))
		{
			g_warning("%s",error->message);
			g_error_free(error);
			error = NULL;
			return FALSE;
		}
	}
	//ansonsten die "default" Datei laden, die definiert wurde mit keyfile_file
	else
	{
		if (!g_key_file_load_from_file(keyfile,
																keyfile_file,
																G_KEY_FILE_KEEP_COMMENTS,
																&error))
		{
			g_warning("%s",error->message);
			g_error_free(error);
			error = NULL;
			return FALSE;
		}
	}
	//Falls schon eine Keyfile bereit gestellt wurde, alte freigeben
	if (global_keyfile!=NULL)
	{
		g_key_file_free (global_keyfile);
	}
	//keyfile global verfügbar machen
	global_keyfile = keyfile;
	return TRUE;
}

//gibt einen String mit dem User für die Datenbank zurück
//muss mit g_free freigegeben werden
gchar *keyfile_get_db_user (void){
GError *error = NULL;
gchar *user = NULL;

//checken ob Keyfile eingelesen wurde
if (global_keyfile==NULL)
{
	g_warning ("Noch kein \"keyfile_init()\" aufgerufen\n");
	if (!keyfile_init (NULL))
	{
		g_error ("Konnte Keyfile nicht laden, bitte erst keyfile_init() aufrufen!");
	}
}


//String aus Keyfile laden
user = g_key_file_get_string(	global_keyfile,
															"datenbank",
															"user",
															&error);
//auf fehler prüfen
if (error!=NULL||user==NULL)
{
	g_error("%s",error->message);
	g_error_free(error);
	error = NULL;
}

return user;
}

//gibt einen String mit dem Passwort für die Datenbank zurück
//muss mit g_free freigegeben werden
gchar *keyfile_get_db_password (void){
GError *error = NULL;
gchar *password = NULL;

//checken ob Keyfile eingelesen wurde
if (global_keyfile==NULL)
{
	g_warning ("Noch kein \"keyfile_init()\" aufgerufen\n");
	if (!keyfile_init (NULL))
	{
		g_error ("Konnte Keyfile nicht laden, bitte erst keyfile_init() aufrufen!");
	}
}


//String aus Keyfile laden
password = g_key_file_get_string(	global_keyfile,
															"datenbank",
															"password",
															&error);
//auf fehler prüfen
if (error!=NULL||password==NULL)
{
	g_error("%s",error->message);
	g_error_free(error);
	error = NULL;
}

return password;
}

//gibt einen String mit dem Host für die Datenbank zurück
//@warning muss mit g_free freigegeben werden
//@return gchar *db_host
gchar *keyfile_get_db_host (void){
GError *error = NULL;
gchar *db_host = NULL;

//checken ob Keyfile eingelesen wurde
if (global_keyfile==NULL)
{
	g_warning ("Noch kein \"keyfile_init()\" aufgerufen\n");
	if (!keyfile_init (NULL))
	{
		g_error ("Konnte Keyfile nicht laden, bitte erst keyfile_init() aufrufen!");
	}
}


//String aus Keyfile laden
db_host = g_key_file_get_string(	global_keyfile,
															"datenbank",
															"host",
															&error);
//auf fehler prüfen
if (error!=NULL||db_host==NULL)
{
	g_error("%s",error->message);
	g_error_free(error);
	error = NULL;
}

return db_host;

}
