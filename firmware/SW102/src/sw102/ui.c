#include "ui.h"
#include "buttons.h"
#include "state.h"

const struct screen *activeScreen;
void showScreen(const struct screen *new_screen)
{
	if(new_screen == activeScreen)
		return;

	if(activeScreen && activeScreen->leave)
		activeScreen->leave();

	activeScreen = new_screen;

	if(activeScreen->enter)
		activeScreen->enter();
	else if(activeScreen->idle)
		activeScreen->idle();
}

void lcd_power_off(uint8_t updateDistanceOdo);
int tick;
void ui_update()
{
	buttons_events_t ev = buttons_get_events();

	if(ev & ONOFF_LONG_CLICK)
		lcd_power_off(0);

	if(ev) {
		if(activeScreen && activeScreen->button) 
			activeScreen->button(ev);
		buttons_clear_all_events();
	}

	if(activeScreen && activeScreen->idle)
		activeScreen->idle();

	buttons_clock();

	if((tick%5)==0) { // this needs to be called every 100ms
		automatic_power_off_management();
		rt_processing_stop();
		copy_rt_to_ui_vars();
		rt_processing_start();
		batteryResistance();
	}
	++tick;
}
