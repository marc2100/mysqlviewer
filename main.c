#include <stdlib.h>
#include <gtk/gtk.h>
#include "own_mysql.h"
#include "treeviewer.h"

#define VERSION_MySQL_Viewer 0.5


int main (int argc, char *argv[])
{


  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  //Keyfile laden
  keyfile_init (NULL);

	gui_init ();
  return 0;
}



