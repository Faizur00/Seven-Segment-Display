# Seven-Segment-Display
**Final Assignment for 2024 Digital System Class Hasanuddin University**
`Ahmad Faizur Rahman | D121241107`

## overview
This Project aim to demonstrate how seven segment display works. Using C GTK 3.24 for the GUI, it illustrates how certain input from BCD can make some output and simulating it on the display number (0-9) just like the LED version.

## Feature
* Displaying Number 0-9 on the GUI
* Buttons to select certain number
* Displaying the input and output in terminal for each selected number


## How It Works

#### Seven Segment Display
In seven segement display, each number controlled by 7 segment (just like it names) where each segment is an LED, the seven segment organized in a way that can be illustrated as follows:

<p align = left>
    <img src="/pict for readme/Seven segment_inactive.png" alt="example" style="width:300px; height:auto;">
</p>
Each segment can be on active state or inactive state. To display certain number, specific segment are will be on active state while others are on inactive. For example to display number three the A,B,C,D, and G gonna turned on like below:

<p>
    <img src="/pict for readme/Seven segment_active.png" alt="example" style="width:300px; height:auto;">
</p>

The seven segment display also can display in form of alphabets A,B,C,D,E, and F, so using two of these, it can be used to display a hexadecimal digits.

#### Truth Tabel
For active site on the display we can represented it as number `1` and for the inactive site we can use number `0`, so that we can make the truth tabel for each number on each decimal digits like below:

<p align = left>
    <img src="/pict for readme/truth table.png" style="width:400px; height:auto;">
</p>

To controll the digits that want to be displayed, a binary-coded decimal (BCD) that have 4 bits to representing a binary needed. The decoder maps the input to activating corresponding segment. For example input from BCD is `1,0,0,1 `which then translated to `9` (based on BCD to decimal translation), later number 9 gonna be displayed on the seven segment display by converting the value of 9 which is `1,1,1,1,0,1,1 `


## Code Struture

### Creating a Gtk window and Gtk grid
On the first part on Main function, standard GTK window and  a GTK  grid made to hold all of our feature like the drawing area and the button
```C
    //create GTK Window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Seven Segment Display");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    //call back to quit the window when the quit button clicked
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //create GTK grid
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

        //another code here ....

    //fucntion to show the window
    gtk_widget_show_all(window);
    gtk_main();
```
### Creating the Drawing Area
The Drawing area is the place where the decimal digits displayed and changed. The drawing area gonna connected to below function
```c
    static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
``` 
which is our drawing callback so the diplayed number can actaully changes based on the active segment

### Creating the buttons
One more part in our main function is where we created buttons to choose decimal digits to be displayed. The buttons then gonna connected to our button callback:

```C
    void button_clicked(GtkButton *button, gpointer user_data)
```
to make the button work when we clicked it

### Important Variable
1. **Name :** `segments`
   **Purpose:** An array representing the state of each segment in the seven-segment display. Each index corresponds to one of the seven segments (A-G), and the value indicates whether the segment is on (`1`) or off (`0`).
   **Example :**

```c
    const int segments[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        // another segments
    }
```
2.  **Name:** `Input`
    **Purpose:** An array representing the BCD input for each digits. Each index corresponds to one of the seven segments input, and the value indicates whether the segment is on (`1`) or off (`0`).
    **Example :** 
```c
    const int input [10][4] = {
        {0,0,0,0}, //0
        {0,0,0,1}, //1
        // another input
    }
```
3.  **Name:** `current_number` and`current_input`
    **Purpose:** Store the value of the number and input that used for mapping each corresponding segments and input that later were going to displayed on drawing area and terminal
    **Example:** 
```c
    static int current_number = 0;
    static int current_input = 0;
```
### Important Function
1.  **Name:** `void draw_segments(cairo_t *cr, int number)`
    **Purpose:** our core function to draw the segments. In this function the segments position, segments coordinate, and the drawing happen. This function also set the segments size and colour whether its active or not.

2. **Name:** `static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data)`
    **Purpose:** This fucntion is signal handler for the draw event. It is responsible for rendering graphical content onto a GtkWidget using the `draw_segments` function.
3. **Name:** `void button_clicked(GtkButton *button, gpointer user_data)`
    **Purpose:** Callback function for the `Gtk button`. This function will change the `current_number` and the `current_input` based on the button that clicked. This function also print all the BCD and segments binary onto terminal.


***
## How To Run


### Setting Things Up
In this project im using external library which is GTK 3.24 so make sure you also have this library installed on your device, if you have not install this library you can run this command to install it. 

```bash
    sudo apt-get install libgtk-3-dev
```
or if you using windows you can install Unix-like environment to run this library like MYSYS2 that also comes with package manager (`pacman`) that makes it easy to install GTK and its dependencies.

The code directory is pretty simple where theres only `.c` file and `Makefile` for make the compiling easier. To build the project on Linux, you can use the GCC or other suitable like clang compiler with `pkg-config` to include the necessary GTK flags and libraries.

If you're using the most used text editor (VSCode), a preconfigured build task is provided for your convenience. The `tasks.json` file, located in the `.vscode` folder, automates the build process. Code should be laid out in the following directory structure

```bash
    .
    ├── .vscode
    │   └── tasks.json
    ├── Makefile
    └── seven_segment.c
```
### Compiling
Since were having the `MakeFile` we just need to write:
```bash
    make
```
to compile it make sure to install and use the correct compiler that same with the one that used on the make file, or you can change the compiler on the make file by editing compiler on `cc` . Then we can start the file using

```bash
    ./seven-segment
```
and now we can use the program. 

****

## Future Improvements
1. Feature for displaying the input from BCD and each segment binary onto the GUI
2. Feature to manually inputting the BCD binary to choose the displayed number
3. Improving the UI and portability

## Acknowledgments
Since its a self assignment im making this all by my self (im not bragging i just want to add Acknowledgments section to make this looks proffesional)

<img src="/pict for readme/pfp.jpg" alt="example" style="width:250px; height:auto;">
