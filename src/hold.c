#include <alsa/asoundlib.h>
#include "global_inst.h"
#include "midi.h"
#include "midi_types.h"

/*
 *  This hold function is implemented in alsa-seq layer, but not synthesizer key table one.
 *  Because I don't wanna touch any sounding mechanism in setBfree itself.
 */

struct b_hold*
allocHold (struct b_instance* i)
{
	int j,k;
	struct b_hold* h = (struct b_hold*)calloc( 1, sizeof(struct b_hold) );

	h->parentInst = i;
	h->holdStat = 0;
	for( j = 0; j < 3; j++) // i=0,1,2 mean channel A,B,C respectively.
		for( k = 0; k < 128; k++){
			h->heldNoteTbl[j][k] = 0;
			h->fingeredNoteTbl[j][k] = 0;
		}

	if (!h) return NULL;
	else return h;
}

void
holdControlFunction(void *i, unsigned char ch)
{
	struct b_instance* instp = (struct b_instance*)i;
	struct b_hold *h = instp->hold;
	struct bmidi_event_t bev;
	int chItr, noteItr;

	// making hold instance to make a gap in the event of retriggering
	h->mkSndGap = &mkOscGapOnRetrigger;

	// toggle current hold-button status.
	h->holdStat ? ( h->holdStat = 0 ) : ( h->holdStat = 1 );

	if ( h->holdStat ){
		for ( chItr = 0; chItr < 3; chItr++)
			for ( noteItr=0; noteItr < 128; noteItr++)
				h->heldNoteTbl[chItr][noteItr] = h->fingeredNoteTbl[chItr][noteItr];
	} else {
		for ( chItr = 0; chItr < 3; chItr++){
			for( noteItr = 0; noteItr < 128; noteItr++){
				h->heldNoteTbl[chItr][noteItr] -= h->fingeredNoteTbl[chItr][noteItr];
				if ( h->heldNoteTbl[chItr][noteItr] ){
					memset (&bev, 0, sizeof (struct bmidi_event_t));
					bev.type         = NOTE_OFF;
					bev.channel      = chItr;
					bev.d.tone.note  = noteItr;
					bev.d.tone.velocity = 0;
					process_midi_event(instp, &bev);

					h->heldNoteTbl[chItr][noteItr] = 0;
				}
			}
		}
	}
}

void mkOscGapOnRetrigger(void* instp, const struct bmidi_event_t* ev)
{
	struct bmidi_event_t noteOnEv = *ev;
	struct bmidi_event_t noteOffEv = *ev;

	noteOffEv.type = NOTE_OFF;
	process_midi_event(instp, &noteOffEv);
}

void
chAholdEnable(void *h, unsigned char ch)
{
}

void
chBholdEnable(void *h, unsigned char ch)
{
}

void
chCholdEnable(void *h, unsigned char ch)
{
}

void
initHoldFunc(void *i, void *m){
	useMIDIControlFunction (m, "hold", holdControlFunction, i);
/*
	useMIDIControlFunction (m, "hold.chA", chAholdEnable, h);
	useMIDIControlFunction (m, "hold.chB", chBholdEnable, h);
	useMIDIControlFunction (m, "hold.chC", chCholdEnable, h);
*/
}

