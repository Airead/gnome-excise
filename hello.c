/* −*−coding: utf−8;−*− */
/**
 * @file hello.c
 * @brief a simple demo
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/04/16 10:40:49
 *
 * This program is just a demonstration. type the name of one application in the
 * entry and hit the button, the application will run.
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <gtk/gtk.h>

gint delete_event(GtkWidget *widget, GdkEvent event, gpointer data)
{
    /* when this function returns FALSE, the delete-event signal becomes a
     * destroy signal */
    return FALSE;
}

void end_program(GtkWidget *widget, gpointer data)
{
    /* End the main loop */
    gtk_main_quit();
}

/**
 * @brief run applications
 * @param widget
 * @param data
 * @return void
 *
 * this is a simple implement for `quick run', So it can not support for
 * starting application with option. I can add that feature if you need.
 */
void run_app(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry_box;
    const char *str;
    pid_t pid;

    if (data == NULL) {
        g_printerr("data is NULL!\n");
        return ;
    }
    
    entry_box = (GtkEntry *)data;

    str = gtk_entry_get_text(entry_box);
    
    if ((pid = fork()) < 0) {
        g_printerr("fork failed: %s\n", strerror(errno));
        gtk_main_quit();
        return ;
    } else if (pid == 0) {      /* child process */
        g_print("child run %s\n", str);
        if (execlp(str, str, NULL) < 0) {
        g_printerr("execl failed: %s\n", strerror(errno));
            exit(1);
        }
    } /* child end */

    g_print("parent run %s, PID: %d\n", str, pid);
}

int main(int argc, char *argv[])
{
    GtkWindow *window;
    GtkLabel *label;
    GtkEntry *entry_box;
    GtkButton *button;
    GtkVBox *vbox;

    /* Initialize GTK+ */
    gtk_init(&argc, &argv);

    /* create window, set default height and width to 200 pixels */
    window = g_object_new(GTK_TYPE_WINDOW,
                          "default-height", 200,
                          "default-width", 200,
                          "border-width", 12,
                          "title", "quick run",
                          NULL);

    /* add signal handlers for window */
    g_signal_connect(window,
                     "delete-event", G_CALLBACK(delete_event),
                     NULL);

    g_signal_connect(window,
                     "destroy", G_CALLBACK(end_program),
                     NULL);

    /* create a vertical box and pack it into window  */
    vbox = g_object_new(GTK_TYPE_VBOX, "spacing", 6, NULL);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));

    /* a new label. */
    label = g_object_new(GTK_TYPE_LABEL, "label", "Hello, world", NULL);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(label));

    /* create an entry box */
    entry_box = g_object_new(GTK_TYPE_ENTRY, "text", "firefox", NULL);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(entry_box));

    /* create a button */
    button = g_object_new(GTK_TYPE_BUTTON, "label", "run", NULL);

    /* install signal handlers for button */
    g_signal_connect(button, "clicked", G_CALLBACK(run_app), entry_box);

    g_signal_connect_swapped(button,
                             "clicked", G_CALLBACK(gtk_widget_destroy),
                             window);

    gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(button));

    /* show all */
    gtk_widget_show_all(GTK_WIDGET(window));

    /* start main event loop */
    gtk_main();
    
    return 0;
}

