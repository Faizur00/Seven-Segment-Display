#include <gtk/gtk.h>
#include <cairo.h>

// create the segment
const int segments[10][7] = {
    //A B  C  D  E  F  G     
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int input [10][4] = {
   //w x y y
    {0,0,0,0}, //0
    {0,0,0,1}, //1
    {0,0,1,0}, //2
    {0,0,1,1}, //3
    {0,1,0,0}, //4
    {0,1,0,1}, //5
    {0,1,1,0}, //6
    {0,1,1,1}, //7
    {1,0,0,0}, //8
    {1,0,0,1}  //9
};

// number to displayed
static int current_number = 0;
static int current_input = 0;

// Draw the display
void draw_segments(cairo_t *cr, int number) {
    // Segment positions
    const int segment_width = 60;
    const int segment_height = 10;
    const int offset_x = 95;
    const int offset_y = 50;

    // coordinates for segment
    struct {
        int x, y, w, h;
    } segment_coords[7] = {
        {offset_x, offset_y - 1 * segment_height, segment_width, segment_height},                                                   // A
        {offset_x + segment_width, offset_y, segment_height, segment_width},                                    // B
        {offset_x + segment_width, offset_y + segment_width + segment_height, segment_height, segment_width},   // C
        {offset_x, offset_y + 2 * segment_width + segment_height, segment_width, segment_height},               // D
        {offset_x - segment_height, offset_y + segment_width + segment_height, segment_height, segment_width},  // E
        {offset_x - segment_height, offset_y, segment_height, segment_width},                                   // F
        {offset_x, offset_y + segment_width, segment_width, segment_height}                                     // G
    };

    for (int i = 0; i < 7; i++) {
        if (segments[number][i]) {
            cairo_rectangle(cr, segment_coords[i].x, segment_coords[i].y, segment_coords[i].w, segment_coords[i].h);
            cairo_set_source_rgb(cr, 1, 0, 0);          // colour for active segments
            cairo_fill(cr);
        } else {
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);    // colour for inactive segments
            cairo_rectangle(cr, segment_coords[i].x, segment_coords[i].y, segment_coords[i].w, segment_coords[i].h);
            cairo_fill(cr);
        }
    }
}

// Drawing callback
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    draw_segments(cr, current_number);
    return FALSE;
}

// updating truth tabel
// void update_labels(GtkWidget *grid) {
//     for (int i = 0; i < 4; i++) {
//         GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), i, 0); // Assuming labels are in row 0
//         if (label != NULL) {
//             char tabel_label[5];
//             snprintf(tabel_label, sizeof(tabel_label), "%d", input[current_input][i]);
//             gtk_label_set_text(GTK_LABEL(label), tabel_label);
//         }
//     }
// }


// Button callback
void button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget* drawing_area = GTK_WIDGET(user_data);
    GtkWidget *grid = GTK_WIDGET(user_data);

    current_number = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "number"));
    current_input = current_number;

    // update_labels(grid);
    
    // Trigger redraw
    gtk_widget_queue_draw(drawing_area);

    printf("input: ");
    for (int i = 0; i < 4; i++) {
        printf("%d | ", input[current_input][i]);
    }

    printf("    output: ");
    for (int i = 0; i < 10; i++) {
        printf("%d | ", segments[current_number][i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    //create a standar GTK windows
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Seven Segment Display");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, 200);
    gtk_grid_attach(GTK_GRID(grid), drawing_area, 0, 0, 10, 1);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);

    // make the buttons
    for (int i = 0; i < 10; i++) {
        char button_label[2];
        snprintf(button_label, sizeof(button_label), "%d", i);

        GtkWidget *button = gtk_button_new_with_label(button_label);
        g_object_set_data(G_OBJECT(button), "number", GINT_TO_POINTER(i));
        g_object_set_data(G_OBJECT(button), "grid", GINT_TO_POINTER(i));
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), drawing_area);
        
        gtk_grid_attach(GTK_GRID(grid), button, i % 5, 1 + i / 5, 1, 1);
    }

    // making truth tabel
    // for (int i = 0; i < 4; i++){
    //     char tabel_label[5];
    //     snprintf(tabel_label, sizeof(tabel_label), "%d", input[current_input][i]);

    //     GtkWidget *label = gtk_label_new(tabel_label);

    //     gtk_grid_attach(GTK_GRID(grid), label, i, 0, 1, 1);
    // }

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}