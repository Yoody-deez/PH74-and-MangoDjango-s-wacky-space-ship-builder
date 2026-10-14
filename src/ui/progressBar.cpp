#include "progressBar.h"

progressBar::progressBar(float min, float max, Vector2 bCol, Vector2 bgCol, Vector2 pCol)
		: minVal(min), maxVal(max), currentVal(min), borderColor(bCol), bgColor(bgCol), progressColor(pCol) {}

void progressBar::setProgress(float val) {
		if (val < minVal) currentVal = minVal;
		else if (val > maxVal) currentVal = maxVal;
		else currentVal = val;
}

void progressBar::render() {}