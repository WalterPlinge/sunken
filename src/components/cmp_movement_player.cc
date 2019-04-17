#include "cmp_movement_player.hh"

#include <maths.hh>
#include <engine.hh>

// Class overrides
CmpMovementPlayer::CmpMovementPlayer(Entity* p) : CmpMovement(p) {}

// Logic
void CmpMovementPlayer::update(const float& delta_time)
{
	// Input decides direction vector
	sf::Vector2f movement(0.0f, 0.0f);

	if (engine::keyboard[sf::Keyboard::Left])
		--movement.x;
	if (engine::keyboard[sf::Keyboard::Right])
		++movement.x;
	if (engine::keyboard[sf::Keyboard::Up])
		--movement.y;
	if (engine::keyboard[sf::Keyboard::Down])
		++movement.y;

	// Normalise movement vector
	movement  = sf::normalise(movement);
	movement *= speed_ * delta_time;

	// Move player
	move(movement);
}

void CmpMovementPlayer::render() {}

