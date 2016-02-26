/*
 * Copyright (C) 2015-2016
 *
 * Author: Leo Soares <leojrfs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <gst/gst.h>
#include <glib.h>

gboolean bus_callback(GstBus *bus, GstMessage *msg, gpointer data){
	GstElement *play = GST_ELEMENT(data);
	switch (GST_MESSAGE_TYPE(msg)){
		case GST_MESSAGE_EOS:
			/* restart playback if at end */
			if (!gst_element_seek(play,
						1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
						GST_SEEK_TYPE_SET, 0,
						GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE)){
							g_print("Seek failed!\n");
						}
			break;
		default:
			break;
	}
    return TRUE;
}

gint main (gint argc, gchar *argv[]){
	GMainLoop *loop;
	GstElement *play;
	GstBus *bus;

	/* init GStreamer */
	gst_init (&argc, &argv);
	loop = g_main_loop_new (NULL, FALSE);

	/* make sure we have a URI */
	if (argc != 2) {
	g_print ("Usage: %s <file> \n", argv[0]);
	return -1;
	}

	/* checks if file exists */
	if (!g_file_test(argv[1], G_FILE_TEST_IS_REGULAR)) {
		g_print ("%s: error: no such file: '%s' \n", argv[0], argv[1]);
		return -1;

	}

	/* add "file://" to arg[1] string */
	gchar *concat = g_strjoin("", "file://" ,argv[1], NULL);
	g_print("RESULT STRING: %s", concat);

	/* set up */
	play = gst_element_factory_make ("playbin", "play");
	g_object_set (G_OBJECT (play), "uri", concat, NULL);
	bus = gst_pipeline_get_bus (GST_PIPELINE (play));
	gst_bus_add_watch (bus, bus_callback, play);
	gst_object_unref (bus);

	gst_element_set_state (play, GST_STATE_PLAYING);
	/* now run */
	g_main_loop_run (loop);

	/* also clean up */
	gst_element_set_state (play, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT (play));

	return 0;
}
