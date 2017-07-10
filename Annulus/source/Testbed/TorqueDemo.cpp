#include "pch.h"
#include "TorqueDemo.h"

namespace Demos
{
	TorqueDemo::TorqueDemo(sf::RenderWindow& renderWindow, Annulus::World& world) :
		Demo(renderWindow, world)
	{
		mRectangle = new sf::RectangleShape(sf::Vector2f(100, 70));

		Initialize();
	}

	TorqueDemo::~TorqueDemo()
	{
		delete mRectangle;
	}

	void TorqueDemo::Initialize()
	{
		mRectangle->setFillColor(sf::Color::Yellow);
		mRectangle->setPosition(mView->getSize().x / 2, mView->getSize().y / 2);
	}

	void TorqueDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
	}

	void TorqueDemo::Draw()
	{
		mRenderWindow.draw(*mRectangle);
	}
}
