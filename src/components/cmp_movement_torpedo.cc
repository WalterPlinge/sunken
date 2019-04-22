#include "cmp_movement_torpedo.hh"
#include "cmp_shape.hh"
#include "cmp_health_player.hh"
#include "cmp_health_enemy.hh"

#include <iostream>

#include <level_loader.hh>
#include <scene.hh>

CmpMovementTorpedo::CmpMovementTorpedo(Entity* const p, const sf::Vector2f& direction)
: CmpMovement(p),
  direction_(direction)
{
	speed_ = level::tile_size();
}

void CmpMovementTorpedo::update(const float & delta_time)
{
	// Normalise movement vector
	direction_ = sf::normalise(direction_);
	direction_ *= speed_ * delta_time;

	// Move player
	move(direction_);

	if (!valid_move(direction_))
	{
		parent_->delete_please();
	}

	// Gets torpedo tag
	std::set<std::string>::iterator it = parent_->tags().begin();
	std::advance(it, 0);
	std::string tag = *it;

	// Get shape component of torpedo
	auto ts = parent_->compatible_components<CmpShape>().front();

	// Enemy torpedo collision
	if (tag == "enemy_torpedo")
	{
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Gets player shape and health components
		auto ps = player->compatible_components<CmpShape>().front();
		auto ph = player->compatible_components<CmpHealthPlayer>().front();

		// If the enemy torpedo colides with the player
		if (ps->shape().getGlobalBounds().intersects(ts->shape().getGlobalBounds())) {
			parent_->delete_please();
			ph->set_health(ph->health()-30);
			std::cout << "HIT PLAYER | Health: " << ph->health() << std::endl;
		}
	} 

	// Player torpedo collision
	else if (tag == "player_torpedo")
	{
		// Loops through enemies
		std::vector<Entity*> enemies = parent_->scene->entities().find("enemy");
		for (auto e : enemies) {
			// Gets shape and health components
			auto es = e->compatible_components<CmpShape>().front();
			auto eh = e->compatible_components<CmpHealthEnemy>().front();

			// Checks collision and asjusts health
			if (es->shape().getGlobalBounds().intersects(ts->shape().getGlobalBounds())) {
				parent_->delete_please();
				eh->set_health(eh->health() - 40);
				std::cout << "HIT ENEMY | Health: " << eh->health() << std::endl;
			}
		}
	}
}

void CmpMovementTorpedo::render()
{}
