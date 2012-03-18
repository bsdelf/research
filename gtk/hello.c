#include <gtk/gtk.h>

static void destroy(GtkWidget* widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget* wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(wnd, "destroy", G_CALLBACK(destroy), NULL);

    gtk_widget_show(wnd);

    gtk_main();

    return 0;
}
