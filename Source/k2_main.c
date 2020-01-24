#include "k2_ui.h"

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	k2_ui_init();

	gtk_widget_show_all(GTK_WIDGET(k2_ui_window));
	gtk_main();

	return 0;
}