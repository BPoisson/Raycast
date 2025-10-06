#include "game.h"
#include "constants.h"

int main() {
	Game game;
	if (!game.Init("RayCaster", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return -1;
	}
	game.Run();

	return 0;
}