#ifndef MASKS_H_
#define MASKS_H_

struct Masks {
	unsigned int autoColor:1,
				 effectNo:3,
				 blinkingCounter:8,
				 debouncingModeCounter:8,
				 debouncingEffectCounter:8,
				 switchModeDebouncing:1,
				 switchEffectDebouncing:1;
};

#endif
