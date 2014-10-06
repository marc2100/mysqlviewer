#include "own_mysql.h"
#define buffer_size 64


void finish_with_error(MYSQL *con);

//stellt das charset auf utf8
void charset_utf8_mysql (MYSQL *con);
//skaliert das Bild, beim laden
void image_scale_event (GtkWidget *widget,gpointer *data);

void get_mysql_version (void){
	printf("MySQL client version: %s\n", mysql_get_client_info());
}



//ließt die Zeile mit der übergebenen ID aus
struct DB_STRUCT *read_row_mysql (guint ID){
	MYSQL *con = mysql_init(NULL);
	MYSQL_ROW row;
	gchar *user = NULL,*password = NULL,*host=NULL;

	struct DB_STRUCT *db_data = g_malloc(sizeof(struct DB_STRUCT));

	//Nutzernamen abrufen
	user = keyfile_get_db_user ();
	password = keyfile_get_db_password ();
	host = keyfile_get_db_host();
	//Verbindung öffnen
  if (mysql_real_connect(con, host, user, password,
          "eva_pferde", 0, NULL, 0) == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

	charset_utf8_mysql (con);

	//query-anfrage-string generieren
	GString *query = g_string_new ("SELECT * FROM Pferde WHERE id = ");
	gchar buffer[buffer_size];
	g_snprintf (buffer,buffer_size,"%d",ID);
	g_string_append (query,buffer);

	//DB wählen
	//if (mysql_query(con, "SELECT Bild FROM Pferde WHERE Id=1"))
  //if (mysql_query(con, "SELECT * FROM Pferde WHERE id = 1"))
  if (mysql_query(con, query->str))
  {
      finish_with_error(con);
      g_string_free(query,TRUE);
  }
	g_string_free(query,TRUE);
  //result speichern
  MYSQL_RES *result = mysql_store_result(con);
  //Error checken
  if (result == NULL)
  {
      finish_with_error(con);
  }


	//prüfen wie viele einträge es gibt
	db_data->num_fields = mysql_num_fields(result);

	row = mysql_fetch_row(result);

	if (row==NULL)
	{
		g_warning("Kein Eintrag gefunden in Zeile: %d",ID);
		g_free(db_data);
		return NULL;
	}

	//die Länge der Einträge speichern
	//mysql_fetch_lengths darf erst nach ..fetch_row() aufgerufen werden..
	db_data->element_size = mysql_fetch_lengths(result);
	//pointerarry anlegen um Daten zu speichern
	db_data->ptr_array = g_ptr_array_new ();
	gint i = 0;
   for(i = 0; i < db_data->num_fields; i++)
   {
			//ergebnis in das pointerarray packen

			//das Bild laden, sofern vorhanden (element-size > 0)
			if (i==COLUMN_Bild&&db_data->element_size[i])
			{
				//Variablen für das Laden des Bildes
				GdkPixbufLoader *pixbuf_loader = NULL;
				GdkPixbuf *pixbuf = NULL;
				GError *error=NULL;

				//neuen Loader erstellen, und Bild laden
				pixbuf_loader = gdk_pixbuf_loader_new();
				//signal “size-prepared” verknüpfen, um Bild zu skalieren
				g_signal_connect(pixbuf_loader,"size-prepared",G_CALLBACK(image_scale_event),NULL);
				gdk_pixbuf_loader_write (pixbuf_loader,(const guchar*)row[i],(gsize)db_data->element_size[i],&error);
				//auf Error prüfen
				if (error!=NULL)
				{
					g_error("Beim laden des Bildes ist folgender Fehler aufgetreten:\n%s",error->message);
					g_error_free(error);
				}
				//laden beenden
				gdk_pixbuf_loader_close (pixbuf_loader,&error);
				if (error!=NULL)
				{
					g_warning("Beim schließen des PixBufLoaders ist folgender Fehler aufgetreten:\n%s",error->message);
					g_error_free(error);
				}
				//das fertige Pixbuf abholen
				pixbuf = gdk_pixbuf_loader_get_pixbuf (pixbuf_loader);
				if (pixbuf==NULL) g_warning("Kein Bild vorhanden\n");
				//und den Ref-counter erhöhen
				g_object_ref (pixbuf);
				//den Loader freigeben
				g_object_unref(pixbuf_loader);
				g_ptr_array_add (db_data->ptr_array, (gpointer) pixbuf);
			}
			//restlichen Daten als textstring speichern
			else
			{
				//den String kopieren
				g_ptr_array_add (db_data->ptr_array, (gpointer) g_strdup(row[i]));

			}

   }


	//verbindung freigeben
  mysql_free_result(result);
  mysql_close(con);

	return db_data;
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//stellt das charset auf utf8
void charset_utf8_mysql (MYSQL *con){
	if (!mysql_set_character_set(con, "utf8"))
	{
			//printf("New client character set: %s\n",mysql_character_set_name(con));
	}
}

void image_scale_event (GtkWidget *widget,gpointer *data){
//g_print("Signale “size-prepared” wurde gesendet\n");
gdk_pixbuf_loader_set_size ((GdkPixbufLoader*)widget,80,60);
}
