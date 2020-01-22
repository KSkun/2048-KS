#include "k2_util.h"

gchar *k2_to_utf8(char *str) {
	return g_locale_to_utf8(str, -1, NULL, NULL, NULL);
}