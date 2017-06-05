#pragma once

#include <chrono>

#define GLM_FORCE_CXX98
#include "glm/vec2.hpp"

namespace Annulus
{
	/**
	* The settings for a world instance. Used for instantiating a world.
	*/
	class Settings
	{
		/**
		* Default gravity vector for a world.
		*/
		static const glm::vec2 sDefaultGravity;
	public:
		/**
		* Constructor.
		* @param timeStep The amount of time after which the world should perform a physics update. Default value corresponds to 60 (roughly 16 milliseconds) times per second.
		* @param gravity The gravitational force for the world.
		*/
		Settings(std::chrono::milliseconds timeStep = std::chrono::milliseconds(sTimeFor60FPS), glm::vec2 gravity = sDefaultGravity);
		/**
		* Default destructor.
		*/
		~Settings() = default;
		/*
		* Get the amount of time after which a physic update should be performed on the world.
		* @return The duration of time step as a sixtieth of a second.
		*/
		const std::chrono::milliseconds& GetTimeStep() const;
		/*
		* Set the amount of time after which a physics update should be performed on the world.
		* @param updateRate The number of times a physics update should occur in a second. The value should be either 30 or 60.
		*/
		void SetTimeStep(const std::uint32_t updateRate);
		/*
		* Get the graviational force acting on all the non-static rigid bodies in the world.
		* @return The constant graviational force for this world.
		*/
		const glm::vec2& GetGravity() const;
		/**
		* Set the gravity for the associated world.
		* @param gravity The gravitational force to set for the associated world.
		*/
		void SetGravity(const glm::vec2& gravity);
	private:
		/**
		* The amount of fixed time after which a physics update should be performed for a world.
		*/
		std::chrono::milliseconds mTimeStep;
		/**
		* The gravitational force which acts on all non-static rigid bodies present in the associated world.
		*/
		glm::vec2 mGravity;
		/**
		* The amount of time in milliseconds for 30 frames to execute in 1 second.
		*/
		static const std::int32_t sTimeFor30FPS;
		/**
		* The amount of time in milliseconds for 60 frames to execute in 1 second.
		*/
		static const std::int32_t sTimeFor60FPS;
	};
}