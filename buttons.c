#include "buttons.h"
//lokale struct
struct REFRESH{
struct GUI_ELEMENTE *gui;
gint eingabe;
gint anzahl_zeilen;
GtkListStore *store;
};

//lokale Variablen
gboolean thread_status = FALSE;

//lokale funktionen
gpointer *thread_refresh_button (gpointer data);
gboolean thread_catcher_refresh (gpointer data);


void button_refresh_clicked(GtkWidget *widget, gpointer data)
{
	//Variablen erzeugen
	struct REFRESH *thread_data = g_malloc(sizeof(struct REFRESH));
	gchar *texteingabe = NULL;
	GThread *thread_id;
	GtkListStore *store = NULL;

	//übergebene Daten in Thread struct verpacken
	thread_data->gui = (struct GUI_ELEMENTE*) data;

	//Textbuffer auslesen, in Int wandeln und in Thread_daten verpacken
	texteingabe = gtk_entry_get_text(GTK_ENTRY(thread_data->gui->texteingabe));
	thread_data->eingabe = g_ascii_strtod(texteingabe,NULL);
	//2. Textbuffer auslesen
	texteingabe = gtk_entry_get_text(GTK_ENTRY(thread_data->gui->texteingabe_spalten_anzahl));
	thread_data->anzahl_zeilen = g_ascii_strtod (texteingabe,NULL);

	//Wenn anzahl_zeilen = 0, auf eins setzten, damit einen Zeile ausgegeben wird
	if (thread_data->anzahl_zeilen<=0) thread_data->anzahl_zeilen=1;

	//Prüfen ob Eingabe != 0 ist, falls ja, die Anzahl an Zeilen anfordern
	if (thread_data->eingabe!=0){
		//den Button ausgrauen
		g_object_set(widget,"sensitive",FALSE,NULL);
		//Spinner sichbar machen und aktivieren
		g_object_set(gui_get_spinner(),"visible",TRUE,NULL);
		gtk_spinner_start (gui_get_spinner());

		//prüfen ob schon ein Model verbunden ist
		store = (GtkListStore*)gtk_tree_view_get_model (gui_get_gtk_tree_viewer());
		if(store!=NULL)
		{
			//falls schon ein Model verbunden ist,
			//müssen wir die Ref() holen, sonst wird die Liste freigegeben, nach der trennung ;)
			//danach vom viewer trennen
			//und den Inhalt des Stores löschen
			g_object_ref(store);
			gtk_tree_view_set_model (gui_get_gtk_tree_viewer(),NULL);
			gtk_list_store_clear (store);
		}
		else
		{
			// ansonsten einen neuen store erzeugen
			store = gui_get_list_store();
		}
		//store in Thread-variable übergeben
		thread_data->store = store;
		//thread starten
		thread_id=g_thread_new("refresh_thread",(GThreadFunc)thread_refresh_button,(gpointer)thread_data);
		//Timer starten um Thread wieder zu "fangen"
		g_timeout_add (100,thread_catcher_refresh,(gpointer)thread_id);
	}
	//Sonst beenden
	else
	{
	g_print("Eingabe war keine Zahle oder 0 ;)\n");
	}
	return;
}

void button_exit_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}

gpointer *thread_refresh_button (gpointer data){
	//Variablen anlegen
	struct REFRESH *thread = (struct REFRESH*) data;
	GtkListStore *thread_store = thread->store;
	while(thread->anzahl_zeilen!=0)
	{
		//store mit Daten füllen
		gui_modell_fill_row (thread_store,thread->eingabe);
		thread->eingabe++;
		thread->anzahl_zeilen--;
	}

	//Speicher freigeben
	g_free(thread);
	thread_status = TRUE;
	g_thread_exit (thread_store);
	//wird nicht erreicht
	return (gpointer)thread_store;
}

gboolean thread_catcher_refresh (gpointer data){
	GtkListStore *store=NULL;
	//check ob thread fertig
	//nötig, da die GUI sonst einfriert
	if (!thread_status)
	{
		return TRUE;
	}
	//auf Thread warten
	store = (GtkListStore*)g_thread_join ((GThread*)data);
	//status = false setzten, solange kein neuer Thread schreibend zugreifen kann
	thread_status = FALSE;
	//den Button wieder freischalten
	g_object_set(gui_get_button_refresh(),"sensitive",TRUE,NULL);
	//Das Model mir dem Viewer verbinden
	gtk_tree_view_set_model (gui_get_gtk_tree_viewer(),(GtkTreeModel*)store);
	//Spinner unsichbar machen und deaktivieren
	g_object_set(gui_get_spinner(),"visible",FALSE,NULL);
	gtk_spinner_stop (gui_get_spinner());
	//store freigeben, er bleibt bestehen, da er mit dem Viewer verknüpft ist
	g_object_unref(store);

	return FALSE;
}

//Ändert die Hintergrundfarbe der Buttons, wenn mit Maus darüber
void buttons_entered (GtkWidget *widget, gpointer data){
  GdkRGBA color;
  color.red = 27000;
  color.green = 30325;
  color.blue = 30000;
  color.alpha = 15000;
  gtk_widget_override_background_color(widget, GTK_STATE_PRELIGHT, &color);

}

