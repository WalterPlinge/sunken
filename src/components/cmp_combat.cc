#include "cmp_combat.hh"

#include <iostream>

#include <scene.hh>

#include "cmp_torpedo.hh"

CmpCombat::CmpCombat(Entity* p) : Component(p), ammo_(5) {}

// fires missile
void CmpCombat::fire()
{
	if (ammo_ == 0)
		return;
	if (fire_cooldown_ > 0.0f)
		return;

	std::cout << "FIRE" << std::endl;

	auto e = parent_->scene->make_entity();

	auto t = e->add_component<CmpTorpedo>();

	//Entity torpedo;
	//auto t = torpedo.add_component<CmpShape>();
	////auto t = torpedo.add_component<CmpTorpedo>();

	//t->use_shape<sf::CircleShape>(12.f);
	//t->shape().setFillColor(sf::Color::Yellow);
	//t->shape().setOrigin(sf::Vector2f(50.f, 50.f));

	--ammo_;
	fire_cooldown_ = 2.0f;
	// create missile object
	// sets it's position
	// set its speed a trajectory
}

// checks ammo
unsigned CmpCombat::ammo()
{
	return ammo_;
}

// adds more ammo upon pickup
void CmpCombat::set_ammo(float pickup)
{
	ammo_ += pickup;
}

void CmpCombat::update(const float& delta_time) {
	if(fire_cooldown_ > 0.0f)
		fire_cooldown_ -= delta_time;
}
