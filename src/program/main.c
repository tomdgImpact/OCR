#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
# include <gtk/gtk.h>
#include "../../include/matrix.h"
#include "../../include/characterRecognition.h"
#include "../../include/save.h"
#include "../../include/xor.h"

void helper()
{
    printf("Usage : ./main [option]\n");
    printf("Available options : \n");
    printf("-help to show Usage\n");
    printf("-XOR to run xor system\n");
    printf("-OCRT to train the neural network\n");
    printf("-OCR to test the OCR system\n");
    printf("The result of the -OCR command is in text_sample.txt file after loading the image.\n Please quit the window program and load the file in your ");
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "-help") == 0)
        {
            helper();
        }
        if (strcmp(argv[1], "-XOR") == 0)
            XOR();
        if(strcmp(argv[1], "-OCRT") == 0)
        {
            srand(time(NULL));
            Network network;
            char *str = "a bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&'()*+,-/:;<=>?@[\\]^_`{|}~";
            prepare_data_and_train(&network, str, "rand");
        }
        if (strcmp(argv[1], "-OCR") == 0)
        {
            srand(time(NULL));
            GtkBuilder *builder;
            GtkWidget  *window;
            GError     *error = NULL;
        //Initialise
            gtk_init( NULL, NULL );

        //Create a builder
            builder = gtk_builder_new();

        //Load if error quit application
            if(!gtk_builder_add_from_file( builder, "interfaceg2.glade", &error))
            {
                g_warning( "%s", error->message );
                g_free( error );
                return(1);
            }

            window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));

        //Connect signals
            gtk_builder_connect_signals(builder, NULL);

        //Destroy useless builder
            g_object_unref(G_OBJECT( builder));

        //Show window
            gtk_widget_show_all(window);

        // Start main loop
            gtk_main();
       }
    }
    else
    {
        helper();
    }
    return EXIT_SUCCESS;
}

void on_StartTest_clicked(GtkLabel *user)
{
  //Lancer les tests
  //Récuperer le text

  //Afficher le text dans le display label
  gchar *test = "Result will be in test_samples.txt";
  gtk_label_set_text(user, test);
}

void display(GtkWidget *button, GtkWidget *user)
{
  char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
  gtk_image_set_from_file(GTK_IMAGE(user),filename);
  Network network;
  char *str = "a bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&'()*+,-/:;<=>?@[\\]^_`{|}~";
  test(&network, filename, str);
}