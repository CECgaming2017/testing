#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>//for future use
#include <stdio.h>
int main() {
	ALLEGRO_DISPLAY*display = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_TIMER*timer = NULL;
	ALLEGRO_BITMAP*ball = NULL;
	ALLEGRO_BITMAP*Lpaddle = NULL;
	ALLEGRO_BITMAP*Rpaddle = NULL;//create everything
	ALLEGRO_FONT*font = al_create_builtin_font();
	float ball_x = 288;
	float ball_y = 208;
	float Lpaddle_x = 0;
	float Lpaddle_y = 0;
	float Rpaddle_x = 592;
	float Rpaddle_y = 0;//coordinates and such
	float ball_dx = 4.0, ball_dy = 2.0;


	bool key[4]{ false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();//future use
	al_install_keyboard;

	al_create_display(640, 480);
	timer = al_create_timer(0.2);

	ball = al_create_bitmap(32, 32);
	Lpaddle = al_create_bitmap(48, 96);
	Rpaddle = al_create_bitmap(48, 96);
	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(Lpaddle);
	al_clear_to_color(al_map_rgb(255, 200, 200));
	al_set_target_bitmap(Rpaddle);
	al_clear_to_color(al_map_rgb(200, 200, 255));//player 1, 2, and ball
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_flip_display();
	al_start_timer(timer);
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[0] && Lpaddle_y >= 0) {
				Lpaddle_y -= 4.0;//paddle up
			}
			if (key[1] && Lpaddle_y <= 480 - 96) {
				Lpaddle_y += 4.0;//paddle down
			}
			if (key[2] && Rpaddle_y >= 0) {
				Rpaddle_y -= 4.0;//paddle up
			}
			if (key[3] && Rpaddle_y <= 480 - 96) {
				Rpaddle_y += 4.0;//paddle down
			}
			redraw = true;
		}//end of movement
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}//end of display close
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP://up for p1
				key[0] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[1] = true;//down for p1
				break;
			case ALLEGRO_KEY_W:
				key[2] = true;//up for p2
				break;
			case ALLEGRO_KEY_S:
				key[3] = true;//down for p2
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}//end of keycode switch
		}//end of keycode stuff
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(ball, ball_x, ball_y, 0);
			al_draw_bitmap(Lpaddle, Lpaddle_x, Lpaddle_y, 0);
			al_draw_bitmap(Rpaddle, Rpaddle_x, Rpaddle_y, 0);//redraws
		}//end of redraw
	}//end of while
	al_destroy_bitmap(ball);
	al_destroy_bitmap(Lpaddle);
	al_destroy_bitmap(Rpaddle);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);//destruction
}//end of main