#include "stdafx.h"
#include "HeavyPlane.h"

HeavyPlane::HeavyPlane(float x, float y, std::map<std::string, sf::Texture>& texture_sheet,
	std::vector<Bullet*>& enemyBullets) :
	textures(texture_sheet), enemyBullets(enemyBullets)
{
	attackTimer.restart();
	attackTimerMax = 2700.f;

	buffer.loadFromFile("Resource/Music/rocket-launcher.wav");
	this->fireSound.setBuffer(buffer);
	this->fireSound.setVolume(20);

	this->creatMovementComponent(150.f, 40.f, 4.f);
	this->createHitbpxComponent(this->sprite, -5.f, -15.f, 90, 55);
	this->createAnimationComponent(this->textures["ENEMY_HEAVY_PLANE"]);
	this->createAttributeComponent(2);
	this->setRotation(180.f);
	this->setPosition(x, y);

	this->animationComponent->addAnimation("IDLE", 0, 0, 0, 0, 0, 103, 80);
}

HeavyPlane::~HeavyPlane()
{
}

unsigned int HeavyPlane::getType()
{
	return 2;
}

void HeavyPlane::fire()
{
	if (fireTimer() && sprite.getPosition().y > 0)
	{
		fireSound.play();
		this->enemyBullets.emplace_back(new Bullet(
			sprite.getPosition().x - sprite.getGlobalBounds().width / 2.f - 6,
			sprite.getPosition().y, 0.f, 1.f,
			700, this->textures["FIRE_EN"]));
		this->enemyBullets.emplace_back(new Bullet(
			sprite.getPosition().x - sprite.getGlobalBounds().width / 2.f - 6,
			sprite.getPosition().y, 0.5f, 1.f,
			700, this->textures["FIRE_EN"]));
		this->enemyBullets.emplace_back(new Bullet(
			sprite.getPosition().x - sprite.getGlobalBounds().width / 2.f - 6,
			sprite.getPosition().y, -0.5f, 1.f,
			700, this->textures["FIRE_EN"]));
	}

}


bool HeavyPlane::fireTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= (this->attackTimerMax - (rand() % 500)))
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}

void HeavyPlane::update(const float& dt)
{
	this->move(0.f, 1.f, dt);
	this->movementComponent->update(dt);
	this->animationComponent->setOneFrame("IDLE", 0, 0);

	this->hitboxComponent->update();
}

void HeavyPlane::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}