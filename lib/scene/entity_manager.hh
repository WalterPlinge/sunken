#pragma once

// STD
#include <memory>
#include <vector>

// PROJECT
#include <ecm.hh>



// Entity manager
struct Entities {
	void update(const float& delta_time) const;

	void render() const;

	void add(std::unique_ptr<Entity> entity);
	void clear();

private:
	// List of managed entities
	std::vector<std::unique_ptr<Entity>> entities_;
};
