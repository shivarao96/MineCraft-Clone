#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class SFMLRenderer
{
public:
	SFMLRenderer() = default;
	~SFMLRenderer() = default;
	void add(const sf::Drawable& draw);
	void render(sf::RenderWindow& window);
private:
	void reset();
	std::vector<const sf::Drawable*> m_draws;
};

