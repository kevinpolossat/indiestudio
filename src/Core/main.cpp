#include <boost/python.hpp>
#include "Game.hh"

int main(void) {
	Game bomberman;

	return bomberman.run();
}