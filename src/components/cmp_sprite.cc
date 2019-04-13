#include "cmp_sprite.hh"

#include <system_renderer.hh>

// Class overrides
CmpSprite::CmpSprite(Entity* p) : Component(p) {};

// Logic
void CmpSprite::update(const float& delta_time)
{
	sprite_->setPosition(parent_->position());
}

void CmpSprite::render()
{
	renderer::queue(sprite_.get());
}

// Reference to sprite
sf::Sprite& CmpSprite::sprite() const
{
	return *sprite_;
}
