#include <iostream>
#include "SnakeObject.h"

void SnakeObject::Update(double deltaTime) {
			//case SDL_KEYDOWN:
			//	SDL_KeyboardEvent* keybevt = (SDL_KeyboardEvent*)&evt;
			//	switch (keybevt->keysym.sym)
			//	{
			//	case SDLK_UP:
			//		velocity.setX(0);
			//		velocity.setY(-1);
			//		currentDirection = Direction::Up;
			//		break;

			//	case SDLK_LEFT:
			//		velocity.setX(-1);
			//		velocity.setY(0);
			//		currentDirection = Direction::Left;
			//		break;

			//	case SDLK_DOWN:
			//		velocity.setX(0);
			//		velocity.setY(1);
			//		currentDirection = Direction::Down;
			//		break;

			//	case SDLK_RIGHT:
			//		velocity.setX(1);
			//		velocity.setY(0);
			//		currentDirection = Direction::Right;
			//		break;
			//	}
			//	break;

			//	//-----------

			//	currentMoveTime += deltaTime;

			//	if (currentMoveTime >= moveTime) {
			//		snakeBody.pop_back();
			//		Vectormath::Vector2 headPosition = { snakeBody[0].getX() + velocity.getX() * UNIT_SIZE, snakeBody[0].getY() + velocity.getY() * UNIT_SIZE };
			//		snakeBody.push_front(headPosition);

			//		for (unsigned int i = 0; i < snakeBody.size(); i++) {
			//			Vectormath::Vector2 point = snakeBody[i];

			//			int spriteIndex = currentDirection;

			//			if (i != 0)
			//			{
			//				spriteIndex = 4;
			//			}

			//			TLN_SetSpritePicture(i, spriteIndex);
			//			TLN_SetSpritePosition(i, point.getX(), point.getY());
			//		}

			//		currentMoveTime = 0;
			//	}

			//	if (snakeBody[0].getX() == fruitPosition.getX() && snakeBody[0].getY() == fruitPosition.getY())
			//	{
			//		/*	Vectormath::Vector2 headPosition = { snakeBody[0].getX() + velocity.getX() * UNIT_SIZE, snakeBody[0].getY() + velocity.getY() * UNIT_SIZE };
			//			snakeBody.push_front(headPosition);*/

			//		fruitPosition = GetRandomPosition();
			//	}
}

void SnakeObject::Draw(double deltaTime) {

}