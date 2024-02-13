#include <gtk/gtk.h>
#include <glib.h>
#include <pango/pango-font.h>

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include "variable_globale.h"
#include "machine_abtraite.h"
#include "affichage.h"

// Function to print the contents of the index1 table
Buffer buffer,buf1 ;
BufferIndexP bufferIndexP;
BufferIndexM bufferIndexM;
Entete header ;
Index indexP ;
IndexM indexM,indexF,indexG;
date currentDate;

int Lecture;
int Ecriture;

/********************** Signal handler to allow only numeric input ******************/
gboolean on_entry_input(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    // Check if the event is a key press
    if (event->type == GDK_KEY_PRESS) {
        GdkEventKey *key_event = (GdkEventKey *)event;

        // Check if the key is a digit or a backspace
        if ((key_event->keyval >= GDK_KEY_0 && key_event->keyval <= GDK_KEY_9) ||
            key_event->keyval == GDK_KEY_BackSpace) {
            // Allow the input
            return FALSE;
        } else {
            // Block the input
            return TRUE;
        }
    }

    // Allow other events
    return FALSE;
}
/******************************************************************************/

// Define a structure to hold both mainWindow and entryBuffer
typedef struct {
    GtkWidget *mainWindow;
    GtkEntryBuffer *entryBuffer;
    FILE * fichier ;
    FILE * fich ;
    FILE * Fi ;
    FILE * F ;
} UserData;

void on_button_clicked(GtkWidget *button, gpointer user_data) {
    gtk_widget_destroy(GTK_WIDGET(user_data));
}

void show_message_window(const gchar *message) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Set RGBA visual for transparency
    GdkScreen *screen = gtk_widget_get_screen(window);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    gtk_widget_set_visual(window, visual);

    // Make the window transparent
    gtk_widget_set_app_paintable(window, TRUE);

    gtk_window_set_decorated(GTK_WINDOW(window), FALSE); // Remove title bar
    gtk_widget_set_size_request(window, 300, 100); // Set window size

    // Create a vertical box to hold the label and button
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label with the message
    GtkWidget *label = gtk_label_new(message);
    PangoFontDescription *font_desc_cout = pango_font_description_from_string("Berlin Sans FB 16"); //* Berlin Sans FB 15 *//
    gtk_widget_override_font(label, font_desc_cout);

    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE); // Enable line wrapping

    GdkRGBA white;
    gdk_rgba_parse(&white, "white");
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &white);

    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 5);
    pango_font_description_free(font_desc_cout);

    // Create a button
    GtkWidget *button = gtk_button_new_with_label("OK");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window); // Connect the button click signal
    gtk_box_pack_end(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Position the window at the bottom left after showing
    screen = gtk_widget_get_screen(window);
    gint screen_width = gdk_screen_get_width(screen);
    gint screen_height = gdk_screen_get_height(screen);
    gtk_window_move(GTK_WINDOW(window), 50, screen_height - 500); // Adjust as needed
}

// Callback function for "Valider" button click
void valider_button_clicked(GtkWidget *widget, gpointer user_data) {

    // Get the user data containing both mainWindow and entryBuffer
    UserData *data = (UserData *)user_data;

    // Get the entered number from the entry buffer
    const char *numberStr = gtk_entry_buffer_get_text(data->entryBuffer);

    int number = atoi(numberStr);

    Lecture = 0;
    Ecriture = 0;

    chargementInitial(data->fichier, number);

    // Create a message window with the printf message
    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de chargement initial est \n         %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                      GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_WARNING,
                                                      GTK_BUTTONS_OK,
                                                      "Chargement initiale fait avec succès");
    gtk_dialog_run(GTK_DIALOG(warningDialog));
    gtk_widget_destroy(warningDialog);

    Fermer(data->fichier);
    Sauvegarde_IndexM(data->fich, indexM);
    Sauvegarde_IndexM(data->Fi, indexF);
    Sauvegarde_IndexM(data->F, indexG);
    Fermer(data->fich);
    Fermer(data->Fi);
    Fermer(data->F);
    // Clean up the allocated user data
    g_free(data);
}

// Function to create content for Button 1
void create_button1_content(GtkWidget *mainWindow, const char *buttonLabel) {

    FILE *fich, *Fi, *F, *fichier;

    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'N');
    Ouvrire(&fich, "MILITAIRE_INDEX.idx", 'N');
    Ouvrire(&Fi, "FORCE_ARME_INDEX.idx", 'N');
    Ouvrire(&F, "GRADE_INDEX.idx", 'N');

    // Create a new window for Button 1 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 300, 100);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create a box to hold the content in the new window
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(buttonWindow), buttonBox);

    // Create a label for Button 1 content
    GtkWidget *buttonLabelWidget = gtk_label_new("Entrer le nombre d'enregistrement");
    gtk_box_pack_start(GTK_BOX(buttonBox), buttonLabelWidget, FALSE, FALSE, 15);

    // Create an entry buffer for the number
    GtkEntryBuffer *entryBuffer = gtk_entry_buffer_new(NULL, 0);

    // Create an entry widget for the number
    GtkWidget *entryNumber = gtk_entry_new_with_buffer(entryBuffer);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryNumber), "Enter a number");

    g_signal_connect(entryNumber, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    // Create a "Valider" button
    GtkWidget *validerButton = gtk_button_new_with_label("Valider");

    // Create user data structure and set its values
    UserData *userData = g_new(UserData, 1);
    userData->mainWindow = buttonWindow;
    userData->entryBuffer = entryBuffer;
    userData->fichier = fichier ;
    userData->fich = fich ;
    userData->Fi = Fi ;
    userData->F = F ;

    // Connect the callback function to the "clicked" signal of the "Valider" button
    g_signal_connect(validerButton, "clicked", G_CALLBACK(valider_button_clicked), userData);

    // Pack widgets into the box
    gtk_box_pack_start(GTK_BOX(buttonBox), entryNumber, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(buttonBox), validerButton, FALSE, FALSE, 5);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);
}

// Function to create content for Button 2
void create_button2_content(GtkWidget *mainWindow, const char *buttonLabel) {

    Sauvegarde_Index(indexP);

    // Show a warning dialog when Button 5 is clicked
    GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
                                                      GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_WARNING,
                                                      GTK_BUTTONS_OK,
                                                      "Sauvegarde de l'index fait avec succès");
    gtk_dialog_run(GTK_DIALOG(warningDialog));
    gtk_widget_destroy(warningDialog);
}

// Function to create content for Button 3
void create_button3_content(GtkWidget *mainWindow, const char *buttonLabel) {

    Chargement_index(&indexP);

    // Show a warning dialog
    GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
                                                      GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_WARNING,
                                                      GTK_BUTTONS_OK,
                                                      "Chargement de l'index fait avec succès");

    gtk_dialog_run(GTK_DIALOG(warningDialog));
    gtk_widget_destroy(warningDialog);

}

// Define a structure to hold both mainWindow and entryBuffer
typedef struct {
    GtkWidget *mainWindow;
    GtkWidget *searchEntry;
} Userdata;

// Define resultWindow globally so it persists across multiple searches
GtkWidget *resultWindow = NULL;

// Function to add a label to the list box
void add_label_to_list_box(GtkWidget *listBox, const char *linePrefix, const char *lineText, const char *prefixColor, const char *textColor) {
    // Create a grid to hold the label and set its border width
    GtkWidget *grid = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER(grid), 5);

    // Create a label for linePrefix with black color
    GtkWidget *prefixLabel = gtk_label_new(linePrefix);
    gtk_label_set_markup(GTK_LABEL(prefixLabel), g_markup_printf_escaped("<span foreground='%s'>%s</span>", prefixColor, linePrefix));
    gtk_widget_set_halign(prefixLabel, GTK_ALIGN_START);

    // Create a label for lineText with brown color
    GtkWidget *textLabel = gtk_label_new(lineText);
    gtk_label_set_markup(GTK_LABEL(textLabel), g_markup_printf_escaped("<span foreground='%s'>%s</span>", textColor, lineText));
    gtk_widget_set_halign(textLabel, GTK_ALIGN_START);

    // Attach labels to the grid
    gtk_grid_attach(GTK_GRID(grid), prefixLabel, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), textLabel, 1, 0, 1, 1);

    // Add the grid to the list box
    gtk_container_add(GTK_CONTAINER(listBox), grid);

    // Show all widgets
    gtk_widget_show_all(grid);
}

void date_to_string(const date *date, char *output, size_t size) {
    snprintf(output, size, "%04d-%02d-%02d", date->year, date->month, date->day);
}

// Callback function for "Valider" button click
void search_button_clicked(GtkWidget *widget, gpointer userdata) {

    Userdata *data = (Userdata *)userdata;

    // Get the entered text from the search entry
    const char *searchText = gtk_entry_get_text(GTK_ENTRY(data->searchEntry));
    // Convert the entered text to an integer
    int enteredNumber = atoi(searchText);

    FILE *fichier , *fich ;
    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'A');
    Ouvrire(&fich, "MILITAIRE_INDEX.idx", 'A');
    Chargement_index(&indexP);
    Chargement_indexM(fich, &indexM);
    Lecture = 0;
    Ecriture = 0;

    int i,j;
    bool trouv;
    Buffer buf_rech = *alloc_bloc(fichier);

    Rech_Militaires(enteredNumber , &trouv , &i , &j , fichier);
    LireDir(fichier,i,&buf_rech);

    if(!trouv){
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "le militaire que vous recherchez n'exsite pas");

        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    } else {

        resultWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(resultWindow), "Result Window");
        gtk_window_set_default_size(GTK_WINDOW(resultWindow), 500, 600);
        gtk_window_set_position(GTK_WINDOW(resultWindow), GTK_WIN_POS_CENTER);

        // Set the background color of the result window
        GdkRGBA backgroundColor;
        gdk_rgba_parse(&backgroundColor, "#ECECEC");  // Replace "your_color_here" with your desired color
        gtk_widget_override_background_color(resultWindow, GTK_STATE_FLAG_NORMAL, &backgroundColor);

/******************************** récuperer les 9 champs de enreg *******************************/
        char labelTextMatricule[7] ;
        snprintf(labelTextMatricule, sizeof(labelTextMatricule), "%d", enteredNumber); ///convertir int to string
        char labelTextNom[31];
        strcpy(labelTextNom,buf_rech.tab[j].Nom);
        char labelTextPrenom[31];
        strcpy(labelTextPrenom,buf_rech.tab[j].Prenom);

        char labelNomPrenom[64] = "";
        strcat(labelNomPrenom,labelTextNom);
        strcat(labelNomPrenom,"  ");
        strcat(labelNomPrenom,labelTextPrenom);

        date SelectedDate = {buf_rech.tab[j].Date_Naissance.day, buf_rech.tab[j].Date_Naissance.month, buf_rech.tab[j].Date_Naissance.year};
        // Convert Date to string
        char labelTextDN[11];
        date_to_string(&SelectedDate, labelTextDN, sizeof(labelTextDN));

        char labelTextWN[32];
        strcpy(labelTextWN,buf_rech.tab[j].Wilaya_Naissance);
        char labelTextGrade[50];
        strcpy(labelTextGrade,buf_rech.tab[j].Grade);
        char labelTextRegion[30];
        strcpy(labelTextRegion,buf_rech.tab[j].Region_militaire);
        char labelTextForce[50];
        strcpy(labelTextForce,buf_rech.tab[j].Force_armee);
        char labelTextGrpS[4];
        strcpy(labelTextGrpS,buf_rech.tab[j].Groupe_sanguin);

/*********************************************************************************************/
        // Create a grid to center the list box
        GtkWidget *resultGrid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(resultWindow), resultGrid);

        // Create a list box to hold the content in the new window
        GtkWidget *resultListBox = gtk_list_box_new();
        PangoFontDescription *font_desc000 = pango_font_description_from_string("Source Sans Pro 15"); //* Britannic 17 *//
        gtk_widget_override_font(resultListBox, font_desc000);

        gtk_grid_attach(GTK_GRID(resultGrid), resultListBox, 0, 0, 1, 1);

        // Create a label for each line and add them to the list box
        add_label_to_list_box(resultListBox, "  Le militaire ayant le matricule ", labelTextMatricule , "black", "brown" );
        add_label_to_list_box(resultListBox, "  se nomme ", labelNomPrenom , "black", "brown");
        add_label_to_list_box(resultListBox, "  Né le ", labelTextDN , "black", "brown");
        add_label_to_list_box(resultListBox, "  À ", labelTextWN , "black", "brown");
        add_label_to_list_box(resultListBox, "  il est rattaché à la région militaire ", labelTextRegion ,"black", "brown");
        add_label_to_list_box(resultListBox, "  Son grade est ", labelTextGrade , "black", "brown");
        add_label_to_list_box(resultListBox, "  son groupe sanguin est ", labelTextGrpS , "black", "brown");
        add_label_to_list_box(resultListBox, "  et il fait partie de la force armée ", labelTextForce , "black", "brown");

        // Set centering options for the grid
        gtk_widget_set_halign(resultGrid, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(resultGrid, GTK_ALIGN_CENTER);

        // Don't forget to free the font description when you're done
        pango_font_description_free(font_desc000);

        // Show all widgets in the new window
        gtk_widget_show_all(resultWindow);
    }

    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de recherche par matricule est \n            %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    Fermer(fichier);
    Fermer(fich);
}

// Function to create content for Button 4
void create_button4_content(GtkWidget *mainWindow, const char *buttonLabel) {

    // Create a new window for Button 4 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 350, 150);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create a box to hold the content in the new window
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(buttonWindow), buttonBox);

    // Create a label or other content for Button 4
    GtkWidget *buttonLabelWidget = gtk_label_new("Entrer le matricule de militaire recherché");
    gtk_box_pack_start(GTK_BOX(buttonBox), buttonLabelWidget, FALSE, FALSE, 20);

    // Create a search entry
    GtkWidget *searchEntry = gtk_search_entry_new();
    GtkEntryBuffer *searchEntryBuffer = gtk_entry_get_buffer(GTK_ENTRY(searchEntry));
    gtk_entry_buffer_set_max_length(searchEntryBuffer, 6);  // Set maximum length to 6 characters

    // Connect the signal handler to the "key-press-event" signal
    g_signal_connect( searchEntry , "key-press-event", G_CALLBACK(on_entry_input), NULL);

    gtk_box_pack_start(GTK_BOX(buttonBox), searchEntry, FALSE, FALSE, 0);

    // Create a "Valider" button
    GtkWidget *validerButton = gtk_button_new_with_label("SEARCH");

    // Create user data structure and set its values
    Userdata *userdata = g_new(Userdata, 1);
    userdata->mainWindow = buttonWindow;
    userdata->searchEntry = searchEntry ;

    // Connect the callback function to the "clicked" signal of the "Valider" button
    g_signal_connect(validerButton, "clicked", G_CALLBACK(search_button_clicked), userdata);

    // Pack widgets into the box
    gtk_box_pack_start(GTK_BOX(buttonBox), validerButton, FALSE, FALSE, 5);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);
}

// Define a structure to hold the user data for Button 5
typedef struct {
    GtkWidget *mainWindow;
    GtkEntryBuffer *entryBufferMatricule;
    GtkEntryBuffer *entryBufferNom;
    GtkEntryBuffer *entryBufferPrenom;
    GtkWidget *selectedOptions[5];  // Array to store selected options from combo boxes
    GtkWidget *datePicker;  // Date picker widget
} UserDataButton5;

// Callback function for "VALIDER" button click in Button 5
void valider_button5_clicked(GtkWidget *widget, gpointer user_data) {

    FILE *fichier ,*fich ,*Fi ,*F ;

    // Get the user data containing mainWindow and entry buffers
    UserDataButton5 *data = (UserDataButton5 *)user_data;

    // Get the entered data from the entry buffers
    const char *matricule = gtk_entry_buffer_get_text(data->entryBufferMatricule);
    int numero_matricule = atoi(matricule);
    const char *nom = gtk_entry_buffer_get_text(data->entryBufferNom);
    const char *prenom = gtk_entry_buffer_get_text(data->entryBufferPrenom);
    const char *wilaya = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->selectedOptions[0]);
    const char *grp_sanguaine = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->selectedOptions[1]);
    const char *grade = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->selectedOptions[2]);
    const char *force = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->selectedOptions[3]);
    const char *region = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->selectedOptions[4]);

    // Get the selected date from the date picker
    GtkCalendar *calendar = GTK_CALENDAR(data->datePicker);
    guint year, month, day;
    gtk_calendar_get_date(calendar, &year, &month, &day);

    // Create a GDate structure and set the selected date
    struct date selectedDate;
    selectedDate.year = year;
    selectedDate.month = month + 1;  // Adjust for zero-based month in GtkCalendar
    selectedDate.day = day;

    /** ICI ON AJOUTE : Inser_enreg(enreg,Fd); **/
    tenrg e ;
    e.Matricule = numero_matricule;
    strcpy(e.Nom , nom);
    strcpy(e.Prenom , prenom);
    strcpy(e.Wilaya_Naissance , wilaya);
    strcpy(e.Region_militaire , region);
    strcpy(e.Groupe_sanguin , grp_sanguaine);
    strcpy(e.Grade , grade);
    strcpy(e.Force_armee , force);
    e.Date_Naissance = selectedDate ;

    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'A');
    Ouvrire(&fich, "MILITAIRE_INDEX.idx", 'A');
    Ouvrire(&Fi, "FORCE_ARME_INDEX.idx", 'A');
    Ouvrire(&F, "GRADE_INDEX.idx", 'A');
    Chargement_indexM(fich, &indexM);
    Chargement_indexM(Fi, &indexF);
    Chargement_indexM(F, &indexG);
    Chargement_index(&indexP);
    Lecture = 0;
    Ecriture = 0;

    /************************************************************************************/
    Menrg menrg1,menrg2;
    int k, N, nb;
    bool trouv = false;
    rechDicoTableIndex(e.Matricule, &trouv, &k, indexP);
    if (trouv == false) {
        Ienrg ienrg;
        Menrg menrg;
        N = entete(fichier, 1);
        if (N != 0) {
            LireDir(fichier, N, &buffer);
            nb = entete(fichier, 2);
        } else {
            N = 1;
            aff_entete(fichier, 1, 1);
            nb = 0;
            aff_entete(fichier, 2, nb);
        }
        if (nb < 1024) {
            nb += 1;
            buffer.tab[nb - 1] = e;
            EcrireDir(fichier, N, &buffer);
        } else {
            nb = 1;
            buffer = *alloc_bloc(fichier);
            buffer.tab[nb - 1] = e;
            EcrireDir(fichier, N + 1, &buffer);
            aff_entete(fichier, 1, N + 1);
        }
        aff_entete(fichier, 2, nb);
        ienrg.cle = e.Matricule;
        ienrg.adress.nbBloc = entete(fichier, 1);
        ienrg.adress.nbEnrg = entete(fichier, 2)-1;

        menrg.indice = getIndiceMilitaire(e.Region_militaire);
        menrg.cle = e.Matricule;

        menrg1.indice = getIndiceForce(e.Force_armee);
        menrg1.cle = e.Matricule;

        menrg2.indice = getIndiceGrade(e.Grade);
        menrg2.cle = e.Matricule;

        insertionIndex(ienrg, k, &indexP);
        insertionIndexS(menrg, &indexM);
        insertionIndexS(menrg1,&indexF);
        insertionIndexS(menrg2,&indexG);
    }
    /************************************************************************************/

    if(trouv == false){
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "Insertion fait avec succès");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);

        gchar message[100];
        g_snprintf(message, sizeof(message), " Le cout d'insertion est \n     %d lecture et %d écriture ", Lecture, Ecriture);
        show_message_window(message);

    } else {
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "l'enregistrement que vous voulez inserer existe deja");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    }

    Sauvegarde_IndexM(fich, indexM);
    Sauvegarde_IndexM(Fi, indexF);
    Sauvegarde_IndexM(F, indexG);
    Sauvegarde_Index(indexP);
    Fermer(fichier);
    Fermer(fich);
    Fermer(Fi);
    Fermer(F);
    // Clean up the allocated user data
    g_free(data);
}

// Function to create content for Button 5
void create_button5_content(GtkWidget *mainWindow, const char *buttonLabel) {
// Create a new window for Button 5 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 650, 700);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create a box to hold the content in the new window
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(buttonBox,GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(buttonBox, 300, -1); // Set width to 300
    PangoFontDescription *font_desc_Box = pango_font_description_from_string("Algerian 12"); //* Berlin Sans FB 15 *//
    gtk_widget_override_font(buttonBox, font_desc_Box);

    gtk_container_add(GTK_CONTAINER(buttonWindow), buttonBox);
    pango_font_description_free(font_desc_Box);

    // Create a label for the information
    GtkWidget *infoLabel = gtk_label_new("Entrer les informations de militaire");
    gtk_widget_set_halign(infoLabel,GTK_ALIGN_CENTER);
    PangoFontDescription *font_desc_T = pango_font_description_from_string("Berlin Sans FB 17"); //* Berlin Sans FB 15 *//
    gtk_widget_override_font(infoLabel, font_desc_T);

    gtk_box_pack_start(GTK_BOX(buttonBox), infoLabel, FALSE, FALSE, 15);
    // Don't forget to free the font description when you're done
    pango_font_description_free(font_desc_T);

    // Create an HBox for the first entry buffer (Matricule)
    GtkWidget *hboxMatricule = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_widget_set_halign(hboxMatricule,GTK_ALIGN_CENTER);

    // Create a label for Matricule
    GtkWidget *labelMatricule = gtk_label_new("Matricule :");
    gtk_box_pack_start(GTK_BOX(hboxMatricule), labelMatricule, FALSE, FALSE, 5);

    // Create a PangoFontDescription for Algerian font with size 12
    PangoFontDescription *fontDesc2 = pango_font_description_from_string("Algerian 12");

// Apply the font description to a GTK widget (e.g., a label)
    gtk_widget_override_font(labelMatricule, fontDesc2);

// Don't forget to free the font description when you're done
    pango_font_description_free(fontDesc2);

    // Create the entry buffer for Matricule
    GtkEntryBuffer *entryBufferMatricule = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(entryBufferMatricule, 6);  // Set maximum length to 6 characters
    GtkWidget *entryMatricule = gtk_entry_new_with_buffer(entryBufferMatricule);
    gtk_widget_set_size_request(entryMatricule, 300, -1); // Set width to 300
    gtk_box_pack_start(GTK_BOX(hboxMatricule), entryMatricule, FALSE, FALSE, 5);

    g_signal_connect(entryMatricule, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    gtk_box_pack_start(GTK_BOX(buttonBox), hboxMatricule, FALSE, FALSE, 5);

    // Create an HBox for the second entry buffer (Nom and Prenom)
    GtkWidget *hboxNomPrenom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 25);

    // Create a label for Nom
    GtkWidget *labelNom = gtk_label_new("Nom :");
    gtk_box_pack_start(GTK_BOX(hboxNomPrenom), labelNom, FALSE, FALSE, 5);

    // Create the entry buffer for Nom
    GtkEntryBuffer *entryBufferNom = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(entryBufferNom, 30);  // Set maximum length to 30 characters
    GtkWidget *entryNom = gtk_entry_new_with_buffer(entryBufferNom);
    gtk_widget_set_size_request(entryNom, 145, -1); // Set width to 145
    gtk_box_pack_start(GTK_BOX(hboxNomPrenom), entryNom, FALSE, FALSE, 0);

    // Create a label for Prenom
    GtkWidget *labelPrenom = gtk_label_new("Prenom :");
    gtk_box_pack_start(GTK_BOX(hboxNomPrenom), labelPrenom, FALSE, FALSE, 5);

    // Create the entry buffer for Prenom
    GtkEntryBuffer *entryBufferPrenom = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(entryBufferPrenom, 30);  // Set maximum length to 30 characters
    GtkWidget *entryPrenom = gtk_entry_new_with_buffer(entryBufferPrenom);
    gtk_widget_set_size_request(entryPrenom, 145, -1); // Set width to 145
    gtk_box_pack_start(GTK_BOX(hboxNomPrenom), entryPrenom, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(buttonBox), hboxNomPrenom, FALSE, FALSE, 5);

    // Create an HBox for the date picker
    GtkWidget *hboxDatePicker = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);

    // Create a label for the date picker
    GtkWidget *labelDatePicker = gtk_label_new("Date :");
    gtk_box_pack_start(GTK_BOX(hboxDatePicker), labelDatePicker, FALSE, FALSE, 5);

    // Create the date picker
    GtkWidget *datePicker = gtk_calendar_new();
    gtk_widget_set_size_request(datePicker, 300, -1); // Set width to 300
    gtk_box_pack_start(GTK_BOX(hboxDatePicker), datePicker, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(buttonBox), hboxDatePicker, FALSE, FALSE, 5);

    // Create an HBox for each combo box
    const char *options[][59] = {
            {"Wilaya de naissance :", "Adrar", "Chlef", "Laghouat", "Oum_El_Bouaghi", "Batna", "Bejaïa", "Biskra",
                                                                            "Bechar", "Blida", "Bouira", "Tamanrasset", "Tebessa", "Tlemcen", "Tiaret",
                                                                                                                                                                       "Tizi_Ouzou", "Alger", "Djelfa", "Jijel", "Setif", "Saïda", "Skikda", "Sidi_Bel_Abbès",
                    "Annaba", "Guelma", "Constantine", "Medea", "Mostaganem", "M'Sila", "Mascara", "Ouargla",
                    "Oran", "El_Bayadh", "Illizi", "Bordj_Bou_Arreridj", "Boumerdès", "El_Tarf", "Tindouf",
                    "Tissemsilt", "El_Oued", "Khenchela", "Souk_Ahras", "Tipaza", "Mila", "Aïn_Defla", "Naâma",
                    "Aïn_Temouchent", "Ghardaïa", "Relizane", "El_M'ghair", "El Menia", "Ouled Djellal",
                    "Bordj Badji Mokhtar", "Béni Abbès", "Timimoun", "Touggourt", "Djanet", "In Salah", "In Guezzam"},
            {"Groupe Sanguin :", "O+", "A+", "B+", "O-", "A-", "AB+", "B-", "AB-"},
            {"Grade :", "General d'Armee", "General de corps d’armee", "General-Major",
                                                                    "General", "Colonel", "Lieutenant-colonel", "Commandant",
                                                                            "Capitaine", "Lieutenant", "Sous-lieutenant", "Aspirant",
                                                                                                                        "Adjudant-Major", "Adjudant-Chef", "Adjudant", "Sergent-Chef",
                                                                                                                                                                                     "Sergent", "Caporal-Chef", "Caporal", "Djoundi"},
            {"Force Armée :", "Armee_de_terre", "Armee_de_l’air", "Marine_nationale",
                                                                    "Defense_aerienne_du_territoire", "Gendarmerie_nationale",
                                                                                               "Garde_republicaine", "Departement_du_renseignement_et_de_la_securite",
                                                                            "Sante_militaire"},
            {"Région militaire :", "1RM-Blida", "2RM-Oran", "3RM-Béchar", "4RM-Ouargla", "5RM-Constantine", "6RM-Tamanrasset"}
    };

    // Declare UserDataButton5 structure
    UserDataButton5 *userData = g_new(UserDataButton5, 1);

    // Create an array to store combo boxes
    GtkWidget *combo_boxes[5];

    for (int i = 0; i < 5; ++i) {
        GtkWidget *hboxComboBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);

        // Create a label for the combo box
        GtkWidget *labelComboBox = gtk_label_new(options[i][0]);
        gtk_box_pack_start(GTK_BOX(hboxComboBox), labelComboBox, FALSE, FALSE, 10);

        // Create the combo box
        GtkWidget *comboBox = gtk_combo_box_text_new();

        // Add options based on the array for the current combo box
        for (int j = 1; j < sizeof(options[i]) / sizeof(options[i][0]); ++j) {
            if (options[i][j] != NULL) {
                gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox), options[i][j]);
            } else {
                break; // Stop adding options if NULL is encountered
            }
        }

        // Store the combo box in the array
        combo_boxes[i] = comboBox;

        gtk_widget_set_size_request(comboBox, 300, -1); // Set width to 300
        gtk_box_pack_start(GTK_BOX(hboxComboBox), comboBox, FALSE, FALSE, 5);

        gtk_box_pack_start(GTK_BOX(buttonBox), hboxComboBox, FALSE, FALSE, 5);
    }

    // Create a "VALIDER" button
    GtkWidget *validerButton = gtk_button_new_with_label("VALIDER");

    // Set values for userData
    userData->mainWindow = buttonWindow;
    userData->entryBufferMatricule = entryBufferMatricule;
    userData->entryBufferNom = entryBufferNom;
    userData->entryBufferPrenom = entryBufferPrenom;

    // Store the combo boxes in UserDataButton5
    for (int i = 0; i < 5; ++i) {
        userData->selectedOptions[i] = combo_boxes[i];
    }

    // Store the date picker in UserDataButton5
    userData->datePicker = datePicker;

    // Connect the callback function to the "clicked" signal of the "VALIDER" button
    g_signal_connect(validerButton, "clicked", G_CALLBACK(valider_button5_clicked), userData);

    // Pack the "VALIDER" button into the box
    gtk_box_pack_start(GTK_BOX(buttonBox), validerButton, FALSE, FALSE, 5);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);
}

// Callback function for "Valider" button click
void supprimer_button_clicked(GtkWidget *widget, gpointer user_data) {
    // Get the user data containing both mainWindow and entryBuffer
    UserData *data = (UserData *)user_data;

    // Get the entered number from the entry buffer
    const char *number = gtk_entry_buffer_get_text(data->entryBuffer);
    int cle = atoi(number) ;

    FILE *fichier ,*fich ,*Fi ,*F ;
    Chargement_index(&indexP);
    Ouvrire(&fichier,"PERSONNEL-ANP_DZ.dat",'A');
    Ouvrire(&Fi,"MILITAIRE_INDEX.idx",'A');
    Ouvrire(&fich,"FORCE_ARME_INDEX.idx",'A');
    Ouvrire(&F,"GRADE_INDEX.idx",'A');
    Chargement_indexM(Fi,&indexM);
    Chargement_indexM(fich,&indexF);
    Chargement_indexM(F,&indexG);
    Lecture =0;
    Ecriture = 0;

    /***********************************************************************/
    bool trouv = false,trouv1 = false;
    int k =0,k1 = 0;
    int N = 2;
    int i = 1;
    int j = 0;
    int nb =0;
    Buffer buf = *alloc_bloc(fichier);
    //N : le nombre des bloques
    //i,j : les indices
    //nb : le nombre des enrg dans le dernier bloque
    //k : l'indice d'enrg qu'on va supprimer
    rechDicoTableIndex(cle, &trouv, &k, indexP);
    if (trouv) {
        N = entete(fichier, 1);
        i = indexP.tab[k].adress.nbBloc;
        j = indexP.tab[k].adress.nbEnrg;
        nb = entete(fichier, 2);
        if (i != N) {
            LireDir(fichier, i, &buf);
            LireDir(fichier, N, &buf1);
            buf.tab[j] = buf1.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
            if(trouv1){
                indexP.tab[k1].adress.nbBloc = i;
                indexP.tab[k1].adress.nbEnrg = j;
            }
            EcrireDir(fichier, i, &buf);
            --nb;
            if (nb > 0) {
                EcrireDir(fichier, N, &buf1);
                aff_entete(fichier, 2, nb);
            } else {
                aff_entete(fichier, 1, N - 1);
                aff_entete(fichier, 2, 1024);
            }
        } else {
            LireDir(fichier, N, &buf);
            buf.tab[j] = buf.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
            if(trouv1){
                indexP.tab[k1].adress.nbEnrg = j;
            }
            --nb;
            if (nb > 0) {
                EcrireDir(fichier, N, &buf);
                aff_entete(fichier, 2, nb);
            } else {
                aff_entete(fichier, 1, N - 1);
                aff_entete(fichier, 2, 1024);
            }
        }
        suppersionIndex(k, &indexP);

    }
    /**********************************************************************/
    if(trouv == true){
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "Suppression d'enregistrement fait avec succès");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    } else {
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "l'enregistrement que vous voulez supprimer n'existe pas");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    }

    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de suppression est \n       %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    Sauvegarde_Index(indexP);
    Sauvegarde_IndexM(Fi,indexM);
    Sauvegarde_IndexM(fich,indexF);
    Sauvegarde_IndexM(F,indexG);
    Fermer(fichier);
    Fermer(Fi);
    Fermer(fich);
    Fermer(F);
    // Clean up the allocated user data
    g_free(data);
}

// Function to create content for Button 6
void create_button6_content(GtkWidget *mainWindow, const char *buttonLabel) {

    // Create a new window for Button 1 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 300, 100);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create a box to hold the content in the new window
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(buttonWindow), buttonBox);

    // Create a label for Button 1 content
    GtkWidget *buttonLabelWidget = gtk_label_new("   Entrer le matricule d'enregistrement que vous voulez supprimer   ");
    gtk_box_pack_start(GTK_BOX(buttonBox), buttonLabelWidget, FALSE, FALSE, 15);

    // Create an entry buffer for the number
    GtkEntryBuffer *entryBuffer = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(entryBuffer, 6);  // Set maximum length to 6 characters

    // Create an entry widget for the number
    GtkWidget *entryNumber = gtk_entry_new_with_buffer(entryBuffer);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryNumber), "Enter a number");

    g_signal_connect(entryNumber, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    // Create a "Valider" button
    GtkWidget *validerButton = gtk_button_new_with_label("Supprimer");

    // Create user data structure and set its values
    UserData *userData = g_new(UserData, 1);
    userData->mainWindow = buttonWindow;
    userData->entryBuffer = entryBuffer;

    // Connect the callback function to the "clicked" signal of the "Valider" button
    g_signal_connect(validerButton, "clicked", G_CALLBACK(supprimer_button_clicked), userData);

    // Pack widgets into the box
    gtk_box_pack_start(GTK_BOX(buttonBox), entryNumber, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(buttonBox), validerButton, FALSE, FALSE, 5);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);
}

typedef struct {
    GtkWidget *mainWindow;
    GtkEntryBuffer *entryBuffer;
    GtkComboBox *regionComboBox;
} UserData2;

// Callback function for "Valider" button click
void modifier_button_clicked(GtkWidget *widget, gpointer user_data) {
    // Get the user data containing both mainWindow and entryBuffer
    UserData2 *data = (UserData2 *)user_data;

    // Get the entered number from the entry buffer
    const char *number = gtk_entry_buffer_get_text(data->entryBuffer);
    int matricule = atoi(number) ;
    const char *region = gtk_combo_box_text_get_active_text(data->regionComboBox);
    bool existe ;
    Chargement_index(&indexP);
    Lecture = 0;
    Ecriture = 0;
    modifRegionMelitaire(matricule , region , &existe);

    if(existe == true){
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "Modification fait avec succès");   ///fait || faite
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    } else {
        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "l'enregistrement que vous voulez changes sa region Milittaire n'existe pas");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);
    }

    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de modification est \n          %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    // Clean up the allocated user data
    g_free(data);
}

// Function to create content for Button 7
void create_button7_content(GtkWidget *mainWindow, const char *buttonLabel) {

    // Create a new window for Button 1 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 300, 100);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create a box to hold the content in the new window
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(buttonWindow), buttonBox);

    /******************************* LE MATRICULE *******************************/
    // Create a label for Button 1 content
    GtkWidget *buttonLabelWidget = gtk_label_new("  Entrer le matricule de militaire que vous voulez modifier sa region  ");
    gtk_box_pack_start(GTK_BOX(buttonBox), buttonLabelWidget, FALSE, FALSE, 10);

    // Create an entry buffer for the number
    GtkEntryBuffer *entryBuffer = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(entryBuffer, 6);  // Set maximum length to 6 characters

    // Create an entry widget for the number
    GtkWidget *entryNumber = gtk_entry_new_with_buffer(entryBuffer);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryNumber), " Ex: 111111");

    g_signal_connect(entryNumber, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    gtk_box_pack_start(GTK_BOX(buttonBox), entryNumber, FALSE, FALSE, 5);

    /******************************* LA NOUVELLE REGION *******************************/

    GtkWidget *buttonLabelWidget2 = gtk_label_new("   Entrer la nouvelle region militaire   ");
    gtk_box_pack_start(GTK_BOX(buttonBox), buttonLabelWidget2, FALSE, FALSE, 10);

    // Create a combo box for region selection
    GtkWidget *regionComboBox = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "1RM-Blida");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "2RM-Oran");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "3RM-Béchar");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "4RM-Ouargla");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "5RM-Constantine");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(regionComboBox), "6RM-Tamanrasset");

    gtk_box_pack_start(GTK_BOX(buttonBox), regionComboBox, FALSE, FALSE, 5);

    // Create a "Valider" button
    GtkWidget *validerButton = gtk_button_new_with_label("Modifier");

    // Create user data structure and set its values
    UserData2 *userData = g_new(UserData2, 1);
    userData->mainWindow = buttonWindow;
    userData->entryBuffer = entryBuffer;
    userData->regionComboBox = regionComboBox; // Pass the region combo box to UserData

    // Connect the callback function to the "clicked" signal of the "Valider" button
    g_signal_connect(validerButton, "clicked", G_CALLBACK(modifier_button_clicked), userData);

    // Pack widgets into the box
    gtk_box_pack_start(GTK_BOX(buttonBox), validerButton, FALSE, FALSE, 5);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);

}

// Define a structure to hold both mainWindow and entryBuffer
typedef struct {
    GtkWidget *mainWindow;
    GtkWidget *searchEntry1;
    GtkWidget *searchEntry2;
} UserDataM1M2;

enum {
    COLUMN_TEXT,
    NUM_COLUMNS
};

// Function to create a new tree model row with the given data
void append_data_to_tree_store(GtkTreeStore *treestore, struct Tenrg *data) {
    GtkTreeIter iter;
    gtk_tree_store_append(treestore, &iter, NULL);

    gchar *text = g_strdup_printf(
            "  Nom & Prenom :   %s  %s\n"
            "  Né le :   %d/%d/%d  à  %s\n"
            "  Groupe sanguin :   %s\n"
            "  Région militaire :   %s\n"
            "  Grade :   %s\n"
            "  Force armée :   %s\n",
            data->Nom, data->Prenom,
            data->Date_Naissance.day, data->Date_Naissance.month, data->Date_Naissance.year,
            data->Wilaya_Naissance, data->Groupe_sanguin,
            data->Grade, data->Region_militaire, data->Force_armee
    );

    gtk_tree_store_set(treestore, &iter, COLUMN_TEXT, text, -1);
    g_free(text);
}

// Function to create a new tree view with the given data
GtkWidget *create_tree_view(struct Tenrg *data) {
    // Create a tree store with one string column
    GtkTreeStore *treestore = gtk_tree_store_new(NUM_COLUMNS, G_TYPE_STRING);

    // Append data to the tree store
    append_data_to_tree_store(treestore, data);

    // Create a tree view with the tree store as the model
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treestore));

    char str_matricule[8];  // Allocate enough space for the string
    sprintf(str_matricule, "  %d", data->Matricule);

    // Create a renderer for the text column
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(str_matricule, renderer, "text", COLUMN_TEXT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Apply the font to the tree view
    PangoFontDescription *font_desc = pango_font_description_from_string("Source Sans Pro 15");
    gtk_widget_override_font(treeview, font_desc);
    // Free the font description when done
    pango_font_description_free(font_desc);

    return treeview;
}

void searchM1M2_button_clicked(GtkWidget *widget, gpointer userdata){

    UserDataM1M2 *data = (UserDataM1M2 *)userdata;

    // Get the entered text from the search entry
    const char *searchText1 = gtk_entry_get_text(GTK_ENTRY(data->searchEntry1));
    const char *searchText2 = gtk_entry_get_text(GTK_ENTRY(data->searchEntry2));
    // Convert the entered text to an integer
    int M1 = atoi(searchText1);
    int M2 = atoi(searchText2);

    Chargement_index(&indexP);
    Lecture= 0;Ecriture = 0;

    int inf, sup;
    bool trouv1, trouv2;
    struct Tenrg e ;
    FILE *fichier;
    Ouvrire(&fichier, "PERSONNEL-ANP_DZ.dat", 'A');
    rechDicoTableIndex(M1, &trouv1, &inf, indexP);
    rechDicoTableIndex(M2, &trouv2, &sup, indexP);
    if (!trouv2) {
        --sup;
    }
    int i = inf;
    int j;
    Buffer *bufer = alloc_bloc(fichier);
    LireDir(fichier, indexP.tab[i].adress.nbBloc, bufer);

    GtkWidget *resultWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(resultWindow), "Result Window");
    gtk_window_set_default_size(GTK_WINDOW(resultWindow), 750, 650);
    gtk_window_set_position(GTK_WINDOW(resultWindow), GTK_WIN_POS_CENTER);

    // Create a ListBox to display the results
    GtkWidget *listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox, "myListBox");

    // Add each row to the ListBox
    for (i = inf ; i <= sup ; i++) {
        if (indexP.tab[i].adress.nbBloc != indexP.tab[i - 1].adress.nbBloc) {
            free(bufer);
            bufer = alloc_bloc(fichier);
            LireDir(fichier, indexP.tab[i].adress.nbBloc, bufer);
        }

        j = indexP.tab[i].adress.nbEnrg; //j : l'indice de l'enregistrement
        // Recupere l'enrg qui a M1
        e = bufer->tab[j] ;
        GtkWidget *row = create_tree_view(&e);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
    }
// Create a scrolled window
    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

// Set the policy for the horizontal and vertical scrollbars
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

// Add the list box to the scrolled window
    gtk_container_add(GTK_CONTAINER(scrolledWindow), listbox);

// Set the scrolled window as the content of the main window
    gtk_container_add(GTK_CONTAINER(resultWindow), scrolledWindow);
    // Show all widgets in the new window
    gtk_widget_show_all(resultWindow);

    free(bufer);
    Fermer(fichier);
}

// Function to create content for Button 8 (List Box pour afficher les militaire)
void create_button8_content(GtkWidget *mainWindow, const char *buttonLabel) {

    // Create a new window for Button 1 content
    GtkWidget *buttonWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(buttonWindow), buttonLabel);
    gtk_window_set_default_size(GTK_WINDOW(buttonWindow), 300, 200);
    gtk_window_set_position(GTK_WINDOW(buttonWindow), GTK_WIN_POS_CENTER);

    // Create the vertical box to hold both M1 and M2 entries and the button
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Create the horizontal box for "Entrer M1" + EntryBuffer
    GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    // Create labels and entry buffers for M1
    GtkWidget *label1 = gtk_label_new("   Entrer M1 : ");
    GtkWidget *entry1 = gtk_entry_new();
    gtk_entry_set_max_length((GtkEntry *) entry1, 6);  // Set maximum length to 6 characters
    g_signal_connect(entry1, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    // Pack M1 label and entry buffer into the first horizontal box
    gtk_box_pack_start(GTK_BOX(hbox1), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), entry1, FALSE, FALSE, 5);

    // Create the horizontal box for "Entrer M2" + EntryBuffer
    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    // Create labels and entry buffers for M2
    GtkWidget *label2 = gtk_label_new("   Entrer M2 : ");
    GtkWidget *entry2 = gtk_entry_new();
    gtk_entry_set_max_length((GtkEntry *) entry2, 6);  // Set maximum length to 6 characters
    g_signal_connect(entry2, "key-press-event", G_CALLBACK(on_entry_input), NULL);

    // Pack M2 label and entry buffer into the second horizontal box
    gtk_box_pack_start(GTK_BOX(hbox2), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), entry2, FALSE, FALSE, 5);

    // Create the "Valider" button
    GtkWidget *validerButton = gtk_button_new_with_label("Valider");

    // Create user data structure and set its values
    UserDataM1M2 *userdata = g_new(UserDataM1M2, 1);
    userdata->mainWindow = buttonWindow;
    userdata->searchEntry1 = entry1 ;
    userdata->searchEntry2 = entry2 ;

    g_signal_connect(validerButton, "clicked", G_CALLBACK(searchM1M2_button_clicked), userdata);

    // Pack the horizontal boxes and "Valider" button into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 15);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 15);
    gtk_box_pack_start(GTK_BOX(vbox), validerButton, FALSE, FALSE, 0);

    // Pack the vertical box into the main window
    gtk_container_add(GTK_CONTAINER(buttonWindow), vbox);

    // Show all widgets in the new window
    gtk_widget_show_all(buttonWindow);
}

const gchar *option_labels[] = {"Supprimer les enregistrements d'une force armée",
                                "Affichage des enregistrements d'une région militaire avec Âge entre deux valeurs",
                                "Affichage des enregistrements par Catégorie de Grades",
                                "Fragmentation en six fichiers par Région Militaire"};

const gchar *regions[] = {"1RM-Blida", "2RM-Oran", "3RM-Béchar", "4RM-Ouargla", "5RM-Constantine", "6RM-Tamanrasset"};

typedef struct {
    GtkWidget *mainWindow;
    GtkComboBoxText *comboBox;
} UserData_option1_3;

// Callback function for the "Validate" button
void validate_button1_clicked(GtkWidget *widget, gpointer userData_option1_3) {
    UserData_option1_3 *data = (UserData_option1_3 *)userData_option1_3;

    // Retrieve the entered region from the entry buffer
    const char *selected_option = gtk_combo_box_text_get_active_text(data->comboBox);

    Lecture = 0;
    Ecriture = 0;
    /**********************************************************************/
    int indice = getIndiceForce(selected_option);
    FILE *F;
    FILE *fich;
    FILE *Fi;
    FILE *fichierSource;
    Ouvrire(&fichierSource, "PERSONNEL-ANP_DZ.dat", 'A');
    Chargement_index(&indexP);
    Ouvrire(&fich,"FORCE_ARME_INDEX.idx",'A');
    Chargement_indexM(fich,&indexF);
    int i, j, nb;
    Buffer buf;
    int s, sCopy;
    int beforI;
    int k = 0;
    nb = indexP.nb;

    //affichIndexPrimaire(indexP);

    //POSITION OF THE FIRST RECORD OF THE FORCE ARME
    while(indice != indexF.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexF.nb) {
        _Bool trouv = false;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE FORCE ARME IN THE PRIMARY INDEX
        rechDicoTableIndex(indexF.tab[k].cle, &trouv, &s, indexP);
        i = indexP.tab[s].adress.nbBloc;
        j = indexP.tab[s].adress.nbEnrg;
        beforI = i;
        buf = *alloc_bloc(fichierSource);
        LireDir(fichierSource, i, &buf);

        //SuppersionEnrg(fichierSource,&buf,i,j,&indexP);
        /***************************************************************************/
        bool trouv1 = false;
        int k1 = 0;
        int N = 2;
        int nb = 0;

        N = entete(fichierSource, 1);
        nb = entete(fichierSource, 2);
        if (i != N) {
            LireDir(fichierSource, N, &buf1);
            buf.tab[j] = buf1.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
            if(trouv1){
                indexP.tab[k1].adress.nbBloc = i;
                indexP.tab[k1].adress.nbEnrg = j;
            }
            EcrireDir(fichierSource, i, &buf);
            --nb;
            if (nb > 0) {
                EcrireDir(fichierSource, N, &buf1);
                aff_entete(fichierSource, 2, nb);
            } else {
                aff_entete(fichierSource, 1, N - 1);
                aff_entete(fichierSource, 2, 1024);
            }
        } else {
            buf.tab[j] = buf.tab[nb - 1];
            rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
            if(trouv1){
                indexP.tab[k1].adress.nbEnrg = j;
            }
            --nb;
            if (nb > 0) {
                EcrireDir(fichierSource, N, &buf);
                aff_entete(fichierSource, 2, nb);
            } else {
                aff_entete(fichierSource, 1, N - 1);
                aff_entete(fichierSource, 2, 1024);
            }
        }
        suppersionIndex(k1, &indexP);
        /**************************************************************************/
        suppersionIndex(s, &indexP);
        k++;
        // DO THE SAME FOR THE REST OF THE RECORDS IN THE FORCE ARME
        while (k < nb) {
            int cle =0;
            cle =indexF.tab[k].cle;
            //FIND THE ADRESS OF THE RECORD IN THE PRIMARY INDEX
            rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
            if(indexF.tab[k].indice == indice && trouv) {
                s = sCopy;
                j = indexP.tab[s].adress.nbEnrg;
                i = indexP.tab[s].adress.nbBloc;
                //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                if (i != beforI) {
                    buf = *alloc_bloc(fichierSource); // Refresh the buffer for each record
                    LireDir(fichierSource, i, &buf);
                }
                //DELETE THE RECORD FROM THE MAIN FILE AND UPDATE THE INDEXES
                //SuppersionEnrg(fichierSource, &buf, i, j, &indexP);
                /***************************************************************************/
                bool trouv1 = false;
                int k1 = 0;
                int N = 2;
                int nb = 0;

                N = entete(fichierSource, 1);
                nb = entete(fichierSource, 2);
                if (i != N) {
                    LireDir(fichierSource, N, &buf1);
                    buf.tab[j] = buf1.tab[nb - 1];
                    rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
                    if(trouv1){
                        indexP.tab[k1].adress.nbBloc = i;
                        indexP.tab[k1].adress.nbEnrg = j;
                    }
                    EcrireDir(fichierSource, i, &buf);
                    --nb;
                    if (nb > 0) {
                        EcrireDir(fichierSource, N, &buf1);
                        aff_entete(fichierSource, 2, nb);
                    } else {
                        aff_entete(fichierSource, 1, N - 1);
                        aff_entete(fichierSource, 2, 1024);
                    }
                } else {
                    buf.tab[j] = buf.tab[nb - 1];
                    rechDicoTableIndex(buf.tab[j].Matricule,&trouv1,&k1,indexP);
                    if(trouv1){
                        indexP.tab[k1].adress.nbEnrg = j;
                    }
                    --nb;
                    if (nb > 0) {
                        EcrireDir(fichierSource, N, &buf);
                        aff_entete(fichierSource, 2, nb);
                    } else {
                        aff_entete(fichierSource, 1, N - 1);
                        aff_entete(fichierSource, 2, 1024);
                    }
                }
                suppersionIndex(k1, &indexP);
                /**************************************************************************/
                suppersionIndex(s, &indexP);
                //UPDATE THE PREVIOUS BLOCK
                beforI = i;
            };
            trouv =false;
            k++;
        }
    }

    //affichIndexPrimaire(indexP);
    /**********************************************************************/

    GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(data->mainWindow),
                                                      GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_WARNING,
                                                      GTK_BUTTONS_OK,
                                                      "Supression des enregistrements d'une force armée fait avec succès");
    gtk_dialog_run(GTK_DIALOG(warningDialog));
    gtk_widget_destroy(warningDialog);

    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de suppression est \n       %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    //SAVE THE UPDATED INDEXES
    Sauvegarde_Index(indexP);
    Fermer(fichierSource);
    Sauvegarde_IndexM(fich,indexF);
    Fermer(fich);
    g_free(data);
}

void option1_clicked(GtkWidget *widget, gpointer data) {
    GtkPopover *popover = GTK_POPOVER(data);
    gtk_popover_popdown(popover);

    // Create a new window
    GtkWidget *button1_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(button1_window), "Button 1 Window");
    gtk_window_set_default_size(GTK_WINDOW(button1_window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(button1_window), GTK_WIN_POS_CENTER);

    // Create a vertical box to hold the label, entry, and "Validate" button
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(button1_window), vbox);

    // Label for the region entry
    GtkWidget *label = gtk_label_new("Entrer la Force Armée à supprimer ces enregistrements:");

    // Combo box with options
    GtkWidget *comboBox = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Armee_de_terre");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Armee_de_l’air");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Marine_nationale");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Defense_aerienne_du_territoire");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Gendarmerie_nationale");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Garde_republicaine");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Departement_du_renseignement_et_de_la_securite");
    gtk_combo_box_text_append_text((GtkComboBoxText *) comboBox, "Sante_militaire");

    // "Validate" button
    GtkWidget *validate_button = gtk_button_new_with_label("Valider");

    // Create user data structure and set its values
    UserData_option1_3 *userData_option1_3 = g_new(UserData_option1_3, 1);
    userData_option1_3->mainWindow = button1_window;
    userData_option1_3->comboBox = (GtkComboBoxText *) comboBox;

    // Connect the callback function to the "clicked" signal of the "Validate" button
    g_signal_connect(validate_button, "clicked", G_CALLBACK(validate_button1_clicked), userData_option1_3);

    // Pack label, entry, and "Validate" button into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), comboBox, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), validate_button, FALSE, FALSE, 5);

    // Show all widgets
    gtk_widget_show_all(button1_window);
}

typedef struct {
    GtkWidget *mainWindow;
    GtkWidget *combobox;
    GtkEntryBuffer *entryBuffer2;
    GtkEntryBuffer *entryBuffer3;
} UserData_option1;

int calculateAge(date birthDate) {
    currentDate.day = 31;
    currentDate.month = 12;
    currentDate.year = 2023;

    int age = currentDate.year - birthDate.year;

    if (currentDate.month < birthDate.month ||
        (currentDate.month == birthDate.month && currentDate.day < birthDate.day)) {
        age--;
    }
    return age;
}

// Callback function for the "Validate" button
void validate_button2_clicked(GtkWidget *widget, gpointer userData_option1) {

    UserData_option1 *data = (UserData_option1 *)userData_option1;

    char *region = gtk_combo_box_text_get_active_text((GtkComboBoxText *) data->combobox);
    const char *age1 = gtk_entry_buffer_get_text(data->entryBuffer2);
    int min_age = atoi(age1) ;
    const char *age2 = gtk_entry_buffer_get_text(data->entryBuffer3);
    int max_age = atoi(age2) ;

    tenrg e;
    FILE *Fi;
    Ouvrire(&Fi,"MILITAIRE_INDEX.idx",'A');
    Chargement_indexM(Fi,&indexM);
    Chargement_index(&indexP);
    Lecture = 0;
    Ecriture = 0;

    GtkWidget *resultWindow2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(resultWindow2), "Result Window");
    gtk_window_set_default_size(GTK_WINDOW(resultWindow2), 750, 650);
    gtk_window_set_position(GTK_WINDOW(resultWindow2), GTK_WIN_POS_CENTER);

    // Create a ListBox to display the results
    GtkWidget *listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox, "myListBox");

    int indice = getIndiceMilitaire(region);
    int i, j, nb, age;
    int s,sCopy;
    FILE *fichier;
    int beforI;
    int k = 0; // Initialize 'k' to 0
    Ouvrire(&fichier,"PERSONNEL-ANP_DZ.dat",'A');
    nb = indexP.nb;
    //POSITION OF THE FIRST RECORD OF THE REGION
    while(indice != indexM.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexM.nb) {
        _Bool trouv;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE REGION IN THE PRIMARY INDEX
        rechDicoTableIndex(indexM.tab[k].cle, &trouv, &s, indexP);
        if(trouv){
            i = indexP.tab[s].adress.nbBloc;
            j = indexP.tab[s].adress.nbEnrg;
            beforI = i;
            buffer = *alloc_bloc(fichier);
            LireDir(fichier, i, &buffer);
            //CHECK IF THE FIRST RECORD IS IN THE AGE INTERVAL AND PRINT IT THEN
            age = calculateAge(buffer.tab[j].Date_Naissance);
            if ((age >= min_age) && (age <= max_age)) {

                e = buffer.tab[j];
                GtkWidget *row = create_tree_view(&e);
                gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
            }
        }
        int z = 1;
        k++;
        // DO THE SAME FOR THE REST OF THE RECORDS IN THE REGION
        while (k < nb) {
            //IF THE REGION IS THE SAME AS THE  PARAMETER REGION
            if(indexM.tab[k].indice == indice) {
                int cle =0;
                cle =indexM.tab[k].cle;
                //FIN THE ADRESS OF THE RECORD IN THE PRIMARY INDEX

                rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
                if(trouv){
                    s = sCopy;
                    j = indexP.tab[s].adress.nbEnrg;
                    i = indexP.tab[s].adress.nbBloc;
                    //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                    if (i != beforI) {
                        buffer = *alloc_bloc(fichier); // Refresh the buffer for each record
                        LireDir(fichier, i, &buffer);
                    }
                    //CHECK IF THE RECORD IS IN THE AGE INTERVAL AND PRINT IT THEN
                    age = calculateAge(buffer.tab[j].Date_Naissance);
                    if ((age >= min_age) && (age <= max_age)) {

                        e = buffer.tab[j];
                        GtkWidget *row = create_tree_view(&e);
                        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
                        z++;
                    }
                    //UPDATE THE BREVIOUS BLOCK
                    beforI =i;
                }
            }
            k++;
        }
    } else {
        printf("il n'y a pas de militaire dans cette region \n");
    }
    Fermer(fichier);

    gchar message[100];
    g_snprintf(message, sizeof(message), " Le cout de recherche est \n        %d lecture et %d écriture ", Lecture, Ecriture);
    show_message_window(message);

    // Create a scrolled window
    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

// Set the policy for the horizontal and vertical scrollbars
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

// Add the list box to the scrolled window
    gtk_container_add(GTK_CONTAINER(scrolledWindow), listbox);

// Set the scrolled window as the content of the main window
    gtk_container_add(GTK_CONTAINER(resultWindow2), scrolledWindow);
    // Show all widgets in the new window
    gtk_widget_show_all(resultWindow2);

    Fermer(Fi);
    g_free(data);
}

void option2_clicked(GtkWidget *widget, gpointer data) {
    GtkPopover *popover = GTK_POPOVER(data);
    gtk_popover_popdown(popover);

    // Create a new window
    GtkWidget *option1_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(option1_window), "Option 1 Window");
    gtk_window_set_default_size(GTK_WINDOW(option1_window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(option1_window),GTK_WIN_POS_CENTER);

    // Create three horizontal boxes
    GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    // Labels for each box
    GtkWidget *label1 = gtk_label_new(" Entrer la région : ");
    GtkWidget *label2 = gtk_label_new(" Entrer l'âge 1 : ");
    GtkWidget *label3 = gtk_label_new(" Entrer l'âge 2 : ");

    // Combo Box for the regions
    GtkWidget *region_combo = gtk_combo_box_text_new();

    // Add options based on the array for the current combo box
    for (int i = 0; i < G_N_ELEMENTS(regions); ++i) {
        if (regions[i] != NULL) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(region_combo), regions[i]);
        } else {
            break; // Stop adding options if NULL is encountered
        }
    }
    // Entry buffers for each entry
    GtkEntryBuffer *buffer2 = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(buffer2, 2);
    GtkEntryBuffer *buffer3 = gtk_entry_buffer_new(NULL, 0);
    gtk_entry_buffer_set_max_length(buffer3, 2);

    // Entry widgets for each box
    GtkWidget *entry2 = gtk_entry_new_with_buffer(buffer2);
    GtkWidget *entry3 = gtk_entry_new_with_buffer(buffer3);

    // Create user data structure and set its values
    UserData_option1 *userData_option1 = g_new(UserData_option1, 1);
    userData_option1->mainWindow = option1_window ;
    userData_option1->combobox = region_combo ;
    userData_option1->entryBuffer2 = buffer2 ;
    userData_option1->entryBuffer3 = buffer3 ;

    // "Validate" button
    GtkWidget *validate_button = gtk_button_new_with_label("Valider");

    // Connect the callback function to the "clicked" signal of the "Validate" button
    g_signal_connect(validate_button, "clicked", G_CALLBACK(validate_button2_clicked), userData_option1);

    // Pack labels and entries into the horizontal boxes
    gtk_box_pack_start(GTK_BOX(hbox1), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), region_combo, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox2), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), entry2, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox3), label3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), entry3, FALSE, FALSE, 5);

    // Create a main vertical box to hold the three horizontal boxes and the "Validate" button
    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(option1_window), main_vbox);

    // Pack the three horizontal boxes into the main vertical box
    gtk_box_pack_start(GTK_BOX(main_vbox), hbox1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(main_vbox), hbox2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(main_vbox), hbox3, FALSE, FALSE, 5);

    // Pack the "Validate" button into the main vertical box
    gtk_box_pack_start(GTK_BOX(main_vbox), validate_button, FALSE, FALSE, 5);

    // Show all widgets
    gtk_widget_show_all(option1_window);

}

// Callback function for the "Validate" button
void validate_button3_clicked(GtkWidget *widget, gpointer userData_option1_3) {

    UserData_option1_3 *data = (UserData_option1_3 *)userData_option1_3;

    GtkWidget *resultWindow3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(resultWindow3), "Result Window");
    gtk_window_set_default_size(GTK_WINDOW(resultWindow3), 750, 650);
    gtk_window_set_position(GTK_WINDOW(resultWindow3), GTK_WIN_POS_CENTER);

    // Create a ListBox to display the results
    GtkWidget *listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox, "myListBox");

    // Retrieve the entered region from the entry buffer
    const char *selected_option = gtk_combo_box_text_get_active_text(data->comboBox);

    FILE *F ;
    Ouvrire(&F,"GRADE_INDEX.idx",'A');
    Chargement_indexM(F,&indexG);
    Chargement_index(&indexP);

    int indice = getGrade(selected_option);
    FILE *fichierSource;
    Ouvrire(&fichierSource, "PERSONNEL-ANP_DZ.dat", 'A');
    int i, j, nb;
    Buffer buf;
    tenrg e;
    int s, sCopy;
    int beforI;
    int k = 0;
    int z;
    nb = indexP.nb;
    //POSITION OF THE FIRST RECORD OF THE GRADE
    while(indice != indexG.tab[k].indice){
        k++;
    }
    //IF THE FILE IS NOT EMPTY
    if (k != indexG.nb) {
        bool trouv = false;
        //FIND THE ADRESS OF THE FIRST RECORD OF THE GRADE IN THE PRIMARY INDEX
        rechDicoTableIndex(indexG.tab[k].cle, &trouv, &s, indexP);
        if(trouv){
            i = indexP.tab[s].adress.nbBloc;
            j = indexP.tab[s].adress.nbEnrg;
            beforI = i;
            buf = *alloc_bloc(fichierSource);
            LireDir(fichierSource, i, &buf);
            //PRINT THE FIRST RECORD OF THE GRADE
            e = buf.tab[j];
            GtkWidget *row = create_tree_view(&e);
            gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);

        }
        trouv = false;
        k++;
        z = 1;
        // DO THE SAME FOR THE REST OF THE RECORDS OF THE GRADE
        while (k < nb) {
            if(indexG.tab[k].indice == indice) {
                int cle =0;
                cle =indexG.tab[k].cle;
                //FIND THE ADRESS OF THE RECORD IN THE PRIMARY INDEX
                rechDicoTableIndex(cle, &trouv, &sCopy, indexP);
                if(trouv){
                    s = sCopy;
                    j = indexP.tab[s].adress.nbEnrg;
                    i = indexP.tab[s].adress.nbBloc;
                    //WE READ A NEW BUFFER JUST IF THE RECORD ADDRESS IS IN A NEW BLOCK
                    if (i != beforI) {
                        buf = *alloc_bloc(fichierSource); // Refresh the buffer for each record
                        LireDir(fichierSource, i, &buf);
                    }
                    //PRINT THE RECORD
                    e = buf.tab[j];
                    GtkWidget *row = create_tree_view(&e);
                    gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
                    //UPDATE THE PREVIOUS BLOCK
                    beforI = i;
                    z++;
                }
            }
            k++;
        }
    } else {
        printf("il n'y a pas de militaire avec ce grade \n");
    }
    Fermer(fichierSource);

    // Create a scrolled window
    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

// Set the policy for the horizontal and vertical scrollbars
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

// Add the list box to the scrolled window
    gtk_container_add(GTK_CONTAINER(scrolledWindow), listbox);

// Set the scrolled window as the content of the main window
    gtk_container_add(GTK_CONTAINER(resultWindow3), scrolledWindow);
    // Show all widgets in the new window
    gtk_widget_show_all(resultWindow3);

    Fermer(F);
    g_free(data);
}

const gchar *grades[] = {"Officiers_generaux", "officiers_superieurs", "officiers", "sous_officiers", "hommes_de_troupe"};

void option3_clicked(GtkWidget *widget, gpointer data) {
    GtkPopover *popover = GTK_POPOVER(data);
    gtk_popover_popdown(popover);

    // Create a new window
    GtkWidget *button1_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(button1_window), "Button 1 Window");
    gtk_window_set_default_size(GTK_WINDOW(button1_window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(button1_window), GTK_WIN_POS_CENTER);

    // Create a vertical box to hold the label, entry, and "Validate" button
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(button1_window), vbox);

    // Label for the region entry
    GtkWidget *label = gtk_label_new("Selectioner la catégorie de grade");

    // Combo box with options
    GtkComboBoxText *comboBox = (GtkComboBoxText *) gtk_combo_box_text_new();
    for (int i = 0; i < G_N_ELEMENTS(grades); ++i) {
        gtk_combo_box_text_append_text(comboBox, grades[i]);
    }
    // "Validate" button
    GtkWidget *validate_button = gtk_button_new_with_label("Valider");

    // Create user data structure and set its values
    UserData_option1_3 *userData_option1_3 = g_new(UserData_option1_3, 1);
    userData_option1_3->mainWindow = button1_window;
    userData_option1_3->comboBox = comboBox;

    // Connect the callback function to the "clicked" signal of the "Validate" button
    g_signal_connect(validate_button, "clicked", G_CALLBACK(validate_button3_clicked), userData_option1_3);

    // Pack label, entry, and "Validate" button into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), (GtkWidget *) comboBox, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), validate_button, FALSE, FALSE, 5);

    // Show all widgets
    gtk_widget_show_all(button1_window);

}

void option4_clicked(GtkWidget *widget, gpointer data) {
    GtkPopover *popover = GTK_POPOVER(data);
    gtk_popover_popdown(popover);

    // Create a confirmation message dialog
    GtkWidget *confirmationDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(data)),
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_QUESTION,
                                                           GTK_BUTTONS_YES_NO,
                                                           "Confirmez-vous la fragmentation de fichier ?");

    // Set the dialog title
    gtk_window_set_title(GTK_WINDOW(confirmationDialog), "Confirmation");

    // Run the dialog and get the response
    gint response = gtk_dialog_run(GTK_DIALOG(confirmationDialog));

    // Check the user's response
    if (response == GTK_RESPONSE_YES) {
        // User clicked Yes, perform the desired action
        g_print("Fragmentation confirmée!\n");

        FILE *fich, *Fi;
        Ouvrire(&fich, "PERSONNEL-ANP_DZ.dat", 'A');
        Ouvrire(&Fi,"MILITAIRE_INDEX.idx",'A');
        Chargement_index(&indexP);
        Chargement_indexM(Fi,&indexM);
        Lecture = 0;Ecriture = 0;
        Fragmentation(fich);

        gchar message[100];
        g_snprintf(message, sizeof(message), " Le cout de fragmentation est \n          %d lecture et %d écriture ", Lecture, Ecriture);
        show_message_window(message);

        Fermer(fich);
        Fermer(Fi);

        GtkWidget *warningDialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(data)),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_WARNING,
                                                          GTK_BUTTONS_OK,
                                                          "Fragmentation fait avec succès");
        gtk_dialog_run(GTK_DIALOG(warningDialog));
        gtk_widget_destroy(warningDialog);

        // Close the popover after the action is performed
        gtk_popover_popdown(popover);
    } else {
        // User clicked No or closed the dialog, do nothing or handle accordingly
        g_print("Fragmentation annulée!\n");
    }

    // Destroy the dialog
    gtk_widget_destroy(confirmationDialog);
}

// Callback function for button clicks
void button_clicked(GtkWidget *widget, gpointer data) {
    // Get the top-level window
    GtkWidget *mainWindow = gtk_widget_get_toplevel(widget);

    // Check which button is clicked and create content accordingly
    const char *buttonLabel = (const char *)data;
    if (strcmp(buttonLabel, "Chargement initiale") == 0) {
        create_button1_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Sauvegarde de l'index") == 0) {
        create_button2_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Chargement de l'index") == 0) {
        create_button3_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Recherche d'un militaire par son matricule") == 0) {
        create_button4_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Insertion d'un nouveau enregistrement") == 0) {
        create_button5_content(mainWindow, buttonLabel);
    }else if (strcmp(buttonLabel, "Suppression d'un enregistrement") == 0) {
        create_button6_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Modifier la region melitaire d'un enregistrement") == 0) {
        create_button7_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "Afficher les enregistrements qui ils ont [M1 , M2]") == 0) {
        create_button8_content(mainWindow, buttonLabel);
    } else if (strcmp(buttonLabel, "fonctions suppplimentaires") == 0) {

        // Create a popover for Button 9
        GtkPopover *popover = GTK_POPOVER(gtk_popover_new(widget));

        // Create a box to hold the options
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_container_add(GTK_CONTAINER(popover), box);

        GtkCssProvider *provider0 = gtk_css_provider_new();
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider0), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        gtk_css_provider_load_from_data(provider0, "button#custom-button:hover { color: #007bff; }", -1, NULL);

        // Add 4 buttons as options to the popover
        for (int i = 0; i < G_N_ELEMENTS(option_labels); ++i) {
            GtkWidget *option_button = gtk_button_new_with_label(option_labels[i]);
            gtk_box_pack_start(GTK_BOX(box), option_button, FALSE, FALSE, 10);

            PangoFontDescription *fontDesc_menu2 = pango_font_description_from_string("Source Sans Pro 14");  // Adjust font name and size as needed
            gtk_widget_override_font(gtk_bin_get_child(GTK_BIN(option_button)), fontDesc_menu2);
            // Free the font description when finished
            pango_font_description_free(fontDesc_menu2);

            // Connect the appropriate callback function to the "clicked" signal of each option button
            if (i == 0) {
                g_signal_connect(option_button, "clicked", G_CALLBACK(option1_clicked), popover);
            } else if (i == 1) {
                g_signal_connect(option_button, "clicked", G_CALLBACK(option2_clicked), popover);
            } else if (i == 2) {
                g_signal_connect(option_button, "clicked", G_CALLBACK(option3_clicked), popover);
            } else if (i == 3) {
                g_signal_connect(option_button, "clicked", G_CALLBACK(option4_clicked), popover);
            }
        }

        // Apply corner radius to the popover
        GtkCssProvider *provider_popover = gtk_css_provider_new();
        const gchar *cssData_popover = ".popover { border-radius: 50px; background-color: #FFD700; }";
        gtk_css_provider_load_from_data(provider_popover, cssData_popover, -1, NULL);
        gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(popover)), GTK_STYLE_PROVIDER(provider_popover), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider_popover);

        // Show all widgets in the popover
        gtk_widget_show_all(GTK_WIDGET(popover));

        // Set the relative position of the popover to the right of the button
        gtk_popover_set_relative_to(popover, widget);
        gtk_popover_set_position(popover, GTK_POS_RIGHT);

        // Present the popover next to the button
        gtk_popover_popup(popover);
    }
    g_print("Button %s clicked!\n", buttonLabel);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {

    // Load the image at its original size
    GdkPixbuf *background = gdk_pixbuf_new_from_file("C:\\Users\\Admin\\CLionProjects\\TP_01\\images\\image000.jpg", NULL);

    if (background != NULL) {
        // Get the actual size of the drawing area
        int width = gtk_widget_get_allocated_width(widget);
        int height = gtk_widget_get_allocated_height(widget);

        // Scale the image to cover the entire drawing area
        GdkPixbuf *scaled_background = gdk_pixbuf_scale_simple(
                background,
                width,
                height,
                GDK_INTERP_BILINEAR
        );

        // Draw the scaled image to cover the entire drawing area
        gdk_cairo_set_source_pixbuf(cr, scaled_background, 0, 0);
        cairo_paint(cr);

        // Clean up
        g_object_unref(scaled_background);
        g_object_unref(background);
    } else {
        g_printerr("Error loading the background image\n");
    }
    // Let the default handler do its job
    return FALSE;
}


gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {

    // Load the image at its original size
    GdkPixbuf *background = gdk_pixbuf_new_from_file("C:\\Users\\Admin\\CLionProjects\\TP_01\\images\\splash0.jpg", NULL);

    if (background != NULL) {
        // Get the actual size of the drawing area
        int width = gtk_widget_get_allocated_width(widget);
        int height = gtk_widget_get_allocated_height(widget);

        // Scale the image to cover the entire drawing area
        GdkPixbuf *scaled_background = gdk_pixbuf_scale_simple(
                background,
                width,
                height,
                GDK_INTERP_BILINEAR
        );

        // Draw the scaled image to cover the entire drawing area
        gdk_cairo_set_source_pixbuf(cr, scaled_background, 0, 0);
        cairo_paint(cr);

        // Clean up
        g_object_unref(scaled_background);
        g_object_unref(background);
    } else {
        g_printerr("Error loading the background image\n");
    }
    // Let the default handler do its job
    return FALSE;
}

GtkWidget *splash_window;
GtkWidget *window;

static gboolean splash_timeout(gpointer data) {
    gtk_widget_hide(splash_window);
    gtk_widget_show_all(window); // Show the main window after hiding the splash screen
    return G_SOURCE_REMOVE;
}

void on_image_clicked(GtkWidget *widget, gpointer data) {
    // Now, quit the GTK main loop
    gtk_main_quit();
}


int main(int argc, char *argv[]) {

    // Initialize GTK
    gtk_init(&argc, &argv);

    splash_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

// Set window properties
    gtk_window_set_title(GTK_WINDOW(splash_window), "Your Program Name");
    gtk_window_set_decorated(GTK_WINDOW(splash_window), FALSE); // Remove title bar and borders
    gtk_window_set_position(GTK_WINDOW(splash_window), GTK_WIN_POS_CENTER); // Center the window
    gtk_widget_set_size_request(splash_window, 700, 400); // Set window size

    // Set the draw signal handler for the main window
    g_signal_connect(splash_window, "draw", G_CALLBACK(on_draw), NULL);

    // Allow the window to be painted
    gtk_widget_set_app_paintable(splash_window, TRUE);

    // Create a vertical box to hold the title label and buttons
    GtkWidget *vvbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 25);
    gtk_container_add(GTK_CONTAINER(splash_window), vvbox);

    // Create the title label
    GtkWidget *titleLabel1 = gtk_label_new("ECOLE NATIONALE SUPERIEURE DE L'INFORMATIQUE");
    PangoFontDescription *font_desc1 = pango_font_description_new();
    pango_font_description_set_size(font_desc1, PANGO_SCALE * 15); // Set font size
    pango_font_description_set_weight(font_desc1, PANGO_WEIGHT_MEDIUM);
    pango_font_description_set_family(font_desc1, "Source Sans Pro"); // Set font family
    gtk_widget_override_font(titleLabel1, font_desc1);
    gtk_widget_set_halign(titleLabel1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vvbox), titleLabel1, FALSE, FALSE, 20);

    // Create the title label2
    GtkWidget *titleLabel2 = gtk_label_new("TP2 : GestMilitaireANP");
    PangoFontDescription *font_desc2 = pango_font_description_new();
    pango_font_description_set_size(font_desc2, PANGO_SCALE * 25); // Set font size
    pango_font_description_set_weight(font_desc2, PANGO_WEIGHT_BOLD);
    pango_font_description_set_family(font_desc2,"Algerian"/*"Berlin Sans FB"*/); // Set font family
    gtk_widget_override_font(titleLabel2, font_desc2);
    gtk_widget_set_halign(titleLabel2, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vvbox), titleLabel2, FALSE, FALSE, 75);

    // Create the title label3
    GtkWidget *titleLabel3 = gtk_label_new("Copyright © tout droits resérvés");
    PangoFontDescription *font_desc3 = pango_font_description_new();
    pango_font_description_set_weight(font_desc3, PANGO_WEIGHT_SEMILIGHT);
    gtk_widget_override_font(titleLabel3, font_desc3);
    gtk_widget_set_halign(titleLabel3, GTK_ALIGN_CENTER);
    pango_font_description_set_size(font_desc3, PANGO_SCALE * 9); // Set font size
    gtk_box_pack_start(GTK_BOX(vvbox), titleLabel3, FALSE, FALSE, 15);

// Pack the label box into the splash window
    gtk_container_add(GTK_CONTAINER(splash_window), vvbox);
/************************************************************************************/

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "LYES");
    //gtk_window_set_default_size(GTK_WINDOW(window), 750, 700);
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 25);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Set the draw signal handler for the main window
    g_signal_connect(window, "draw", G_CALLBACK(on_draw_event), NULL);

    // Allow the window to be painted
    gtk_widget_set_app_paintable(window, TRUE);

// Create a vertical box to hold the title label and buttons
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 25);
    gtk_container_add(GTK_CONTAINER(window), vbox);

// Create a horizontal box to hold the images and title
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 400);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

// Create the first image button
    GtkWidget *image1 = gtk_image_new_from_file("C:\\Users\\Admin\\CLionProjects\\TP_01\\images\\exit.png");
    gtk_widget_set_size_request(image1, 25, 25);
    GtkWidget *button_img1 = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button_img1), image1);
    g_signal_connect(button_img1, "clicked", G_CALLBACK(on_image_clicked), NULL);
    GdkRGBA transparent1;
    transparent1.red = 0.0;
    transparent1.green = 0.0;
    transparent1.blue = 0.0;
    transparent1.alpha = 0.0;
    gtk_widget_override_background_color(button_img1, GTK_STATE_FLAG_NORMAL, &transparent1);

// Pack the first image button into the horizontal box with left alignment
    gtk_box_pack_start(GTK_BOX(hbox), button_img1, FALSE, FALSE, 0);
    gtk_widget_set_halign(button_img1, GTK_ALIGN_START);

// Create the second image button
    GtkWidget *image2 = gtk_image_new_from_file("C:\\Users\\Admin\\CLionProjects\\TP_01\\images\\help.png");
    gtk_widget_set_size_request(image2, 25, 25);
    GtkWidget *button_img2 = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button_img2), image2);

// Pack the second image button into the horizontal box with right alignment
    gtk_box_pack_end(GTK_BOX(hbox), button_img2, FALSE, FALSE, 5);
    gtk_widget_set_halign(button_img2, GTK_ALIGN_END);

// Create the title label
    GtkWidget *titleLabel = gtk_label_new("BIENVENUE DANS NOTRE PROGRAMME");
    PangoFontDescription *font_desc = pango_font_description_from_string("Britannic 19");
    pango_font_description_set_weight(font_desc, PANGO_WEIGHT_HEAVY);
    gtk_widget_override_font(titleLabel, font_desc);

    GdkRGBA gold;
    gdk_rgba_parse(&gold, /*"#006400"*/"#000000");  // Gold or Yellow color
    gtk_widget_override_color(titleLabel, GTK_STATE_FLAG_NORMAL, &gold);

// Create a box to hold the title label and center it
    GtkWidget *labelBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(labelBox), titleLabel, FALSE, FALSE, 5);
    gtk_widget_set_halign(labelBox, GTK_ALIGN_CENTER);

// Pack the labelBox into the horizontal box
    gtk_box_pack_start(GTK_BOX(hbox), labelBox, FALSE, FALSE, 5);

// Don't forget to free the font description when you're done
    pango_font_description_free(font_desc);

    // Create the second label
    GtkWidget *secondLabel = gtk_label_new("</>   M E N U   </>");
    PangoFontDescription *font_desc00 = pango_font_description_from_string("Berlin Sans FB 15"); //* Britannic 17 *//

    gtk_widget_override_color(secondLabel, GTK_STATE_FLAG_NORMAL, &gold);

    pango_font_description_set_weight(font_desc00, PANGO_WEIGHT_MEDIUM);
    gtk_widget_override_font(secondLabel, font_desc00);
    gtk_widget_set_halign(secondLabel, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), secondLabel, FALSE, FALSE, 10);
    // Don't forget to free the font description when you're done
    pango_font_description_free(font_desc00);

    // Create a box to hold the buttons and center it
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(buttonBox, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(vbox), buttonBox);

    // Create five buttons with the color orange
    const char *button_labels[] = {"Chargement initiale", "Sauvegarde de l'index", "Chargement de l'index", "Recherche d'un militaire par son matricule", "Insertion d'un nouveau enregistrement", "Suppression d'un enregistrement", "Modifier la region melitaire d'un enregistrement", "Afficher les enregistrements qui ils ont [M1 , M2]", "fonctions suppplimentaires"};

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_css_provider_load_from_data(provider, "button#custom-button:hover { color: #007bff; }", -1, NULL);

    for (int i = 0; i < 9; ++i) {

        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        gtk_widget_set_name(button, "custom-button");  // Give a name to each button

        // Create a PangoFontDescription for the desired font
        PangoFontDescription *fontDesc_menu = pango_font_description_from_string("Source Sans Pro 15");  // Adjust font name and size as needed
        gtk_widget_override_font(gtk_bin_get_child(GTK_BIN(button)), fontDesc_menu);
        // Free the font description when finished
        pango_font_description_free(fontDesc_menu);

        gtk_box_pack_start(GTK_BOX(buttonBox), button, FALSE, FALSE, 5);
        gtk_widget_set_size_request(button, 460, 30);

        // Set border-radius for rounded corners
        GtkCssProvider *provider_btn = gtk_css_provider_new();
        const gchar *cssData = "button { border: 1.5px solid #808080; border-radius: 19px; }";
        gtk_css_provider_load_from_data(provider_btn, cssData, -1, NULL);
        gtk_style_context_add_provider(gtk_widget_get_style_context(button), GTK_STYLE_PROVIDER(provider_btn), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider_btn);

        // Connect the callback function to the "clicked" signal of each button
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), (gpointer)button_labels[i]);
    }

    // Show all widgets
    gtk_widget_show_all(window);
    gtk_widget_hide(window);

    // Start the splash timeout function
    g_timeout_add_seconds(3, splash_timeout, NULL);

    // Show the splash window and run the main loop
    gtk_widget_show_all(splash_window);

    // Connect the "destroy" signal of the window to gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Run the GTK main loop
    gtk_main();

    return 0;
}