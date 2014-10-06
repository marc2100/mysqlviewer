#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "own_mysql.h"
#include "treeviewer.h"
#include "buttons.h"

struct GUI_ELEMENTE{
	GtkWidget *mainwindow;
	GtkWidget *treeview;
	GtkWidget *texteingabe;
	GtkWidget *texteingabe_spalten_anzahl;
	GtkWidget *button_refresh;
	GtkWidget *button_exit;
	GtkWidget *statusbar;
	GtkWidget *spinner;
};

enum {
  COLUMN_ID,
  COLUMN_INDEX,
  COLUMN_Name,
  COLUMN_Rasse,
	COLUMN_Farbe,
	COLUMN_Geschlecht,
	COLUMN_Vater,
	COLUMN_Mutter,
	COLUMN_Stockmass,
	COLUMN_Nachkommen,
	COLUMN_Verwendung,
	COLUMN_verkaeuflich,
	COLUMN_Herkunftsland,
	COLUMN_Marke,
	COLUMN_Bild,
	COLUMN_Geburtstag,
  N_COLUMNS
};

void gui_init (void);

GtkListStore *gui_model_fill_data (gint anzahl_zeilen);

gboolean gui_modell_fill_row (GtkListStore *store,gint zeile);

GtkProgressBar *gui_get_progressbar (void);

void gui_pulse_progressbar (void);

//erzeugt den store
GtkListStore * gui_get_list_store(void);

//gibt den Refresh_button zurück
GtkWidget *gui_get_button_refresh (void);
//gibt den Viewer zurück
GtkTreeView *gui_get_gtk_tree_viewer (void);

GtkSpinner *gui_get_spinner (void);


#endif // TREEVIEWER_H
