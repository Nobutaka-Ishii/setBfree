#include "midi_types.h"

void mkOscGapOnRetrigger(void *instp, const struct bmidi_event_t* ev);

struct b_hold {
	int holdStat; // indicates current hold status. TRUE: enabled, FALSE: disabled
	struct b_instance* parentInst;
	unsigned char heldNoteTbl[3][128];
	unsigned char fingeredNoteTbl[3][128];
	void	(*mkSndGap)(void* instp, const struct bmidi_event_t* ev);
};

extern struct b_hold* allocHold(struct b_instance* i);
extern void initHoldFunc(void *i, void *m);
extern void chAholdEnable(void *h, unsigned char ch);
extern void chBholdEnable(void *h, unsigned char ch);
extern void chCholdEnable(void *h, unsigned char ch);

