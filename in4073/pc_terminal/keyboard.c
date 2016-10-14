/*------------------------------------------------------------
 * Keyboard
 * process the keyboard command
 * 
 *------------------------------------------------------------
 */

#include "keyboard.h"

void KeyboardCommand(char c, struct msg_combine_all_t* combine_msg_all)
{
	if(combine_msg_all->mode != MODE_SAFE && combine_msg_all->mode != MODE_PANIC){
		switch(c) {
			// Controls
			case 'a': //thrust up
				if (combine_msg_all->thrust < MAX_THRUST_COM ) {	
					combine_msg_all->thrust+=KEY_INC;
				}
				break;
			case 'z': //thrust down
				if (combine_msg_all->thrust > MIN_THRUST_COM) {
					combine_msg_all->thrust-=KEY_INC;
				}
				break;

			case 'w': // yaw up (right)
				if (combine_msg_all->yaw < MAX_ATTITUDE_COM) {
					combine_msg_all->yaw+=KEY_INC;
				}
				break;

			case 'q': // yaw down (left)
				if (combine_msg_all->yaw > MIN_ATTITUDE_COM) {
					combine_msg_all->yaw-=KEY_INC;
				}
				break;
			
			case 66: // down arrow = pitch up
				if (combine_msg_all->pitch < MAX_ATTITUDE_COM) {
					combine_msg_all->pitch+=KEY_INC;
				}
				break;
			
			case 65: // up arrow = pitch down
				if (combine_msg_all->pitch > MIN_ATTITUDE_COM) {
					combine_msg_all->pitch-=KEY_INC;
				}
				break;
			
			case 68: // left arrow = roll up
				if (combine_msg_all->roll < MAX_ATTITUDE_COM) {
					combine_msg_all->roll+=KEY_INC;
				}
				break;

			case 67: // right arrow = roll down
				if (combine_msg_all->roll > MIN_ATTITUDE_COM) {
					combine_msg_all->roll-=KEY_INC;
				}
				break;

			// we can only go to these two modes from the other "dynamic mode"  
			case '0':	// go back to safe mode
				combine_msg_all->mode = MODE_SAFE;
				break;

			case '1':	// go to panic mode 
				combine_msg_all->mode = MODE_PANIC;
				break;

			case 'u':	// increase the yaw gain
				if(combine_msg_all->mode == MODE_YAW || combine_msg_all->mode == MODE_FULL)
				{
					if (combine_msg_all->P < MAX_P) {combine_msg_all->P+=1;}
					combine_msg_all->update = TRUE;
				}
				break;

			case 'j': // decrease the yaw gain
				if(combine_msg_all->mode == MODE_YAW || combine_msg_all->mode == MODE_FULL)
				{	
					if (combine_msg_all->P > 0) {combine_msg_all->P-=1;}
					combine_msg_all->update = TRUE;
				}
				break;
			
			case 'i':	// increase the P1 gain
				if(combine_msg_all->mode == MODE_FULL)
				{	
					if (combine_msg_all->P1 < MAX_P1) {combine_msg_all->P1+=1;}
					combine_msg_all->update = TRUE;
				}
				break;

			case 'k': // decrease the P1 gain
				if(combine_msg_all->mode == MODE_FULL)
				{	
					if (combine_msg_all->P1 > 0) {combine_msg_all->P1-=1;}
					combine_msg_all->update = TRUE;
				}
				break;
	
			case 'o':	// increase the P2 gain
				if(combine_msg_all->mode == MODE_FULL)
				{	
					if (combine_msg_all->P2 < MAX_P2) {combine_msg_all->P2+=1;}
					combine_msg_all->update = TRUE;
				}
				break;

			case 'l': // decrease the P2 gain
				if(combine_msg_all->mode == MODE_FULL)
				{
					if (combine_msg_all->P2 > 0) {combine_msg_all->P2-=1;}
					combine_msg_all->update = TRUE;
				}
				break;

			// additional
			case 'm': // start flexible logging 
				if (combine_msg_all->log_flag == FALSE) 
				{
					combine_msg_all->log_flag = TRUE;
					//printf("masuk ke false");
				}
				else if (combine_msg_all->log_flag == TRUE) {
					combine_msg_all->log_flag = FALSE;
					//printf("masuk ke true");
				}
				combine_msg_all->update = TRUE;
				//printf("masuk update");
			break;

			case 'n': // toggle the stop sending bool
				if (stop_sending == FALSE) 
				{
					stop_sending = TRUE;
					// printf("stop true %d\n", stop_sending);
				}
				else if (stop_sending == TRUE) {
					stop_sending = FALSE;
					// printf("stop false%d\n", stop_sending);
				}
				// printf("toggle\n");				
			break;

			default:
				break;
		}
	}
	
	// we can go to any other mode if we are in the safe mode
	// abort/exit only can be reach by doing the safe mode first
	if(combine_msg_all->mode == MODE_SAFE && combine_msg_all->thrust == 0)
	{
		switch(c) {
			case '0':
				combine_msg_all->mode = MODE_SAFE;
				break;
			case '1':
				combine_msg_all->mode = MODE_PANIC;
				break;
			case '2': 
				combine_msg_all->mode = MODE_MANUAL;
				break;	
			case '3': 
				combine_msg_all->mode = MODE_CALIBRATION;
				break;	
			case '4': 
				combine_msg_all->mode = MODE_YAW;
				break;	
			case '5': 
				combine_msg_all->mode = MODE_FULL;
				break;	
			case '6': 
				combine_msg_all->mode = MODE_RAW;
				break;	
			case '7': 
				combine_msg_all->mode = MODE_HEIGHT;
				break;	
			case 27: 
				combine_msg_all->mode = ESCAPE;
				break;

			// additional
			case 'm': // start flexible logging 
				if (combine_msg_all->log_flag == FALSE) 
				{
					combine_msg_all->log_flag = TRUE;
					//printf("masuk ke false");
				}
				else if (combine_msg_all->log_flag == TRUE) {
					combine_msg_all->log_flag = FALSE;
					//printf("masuk ke true");
				}
				combine_msg_all->update = TRUE;
				//printf("masuk update");
			break;


			default:
				break;
		}
	}		
}
