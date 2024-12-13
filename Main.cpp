#include "SVGDocuments.h"

int main() {
	SVGDocuments svg;
	svg = svg.loadFile("sample.svg");
	svg.render();

	return 0;
}