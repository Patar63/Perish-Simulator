#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitEnemy(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);
}

Enemy::~Enemy()
{
}

void Enemy::InitEnemy(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	//Store references to the components
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	//Initialize UVs
	m_animController->InitUVs(fileName);

	//Loads the texture and sets width and height
	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController->SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//IDLE ANIMATIONS\\
	
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());
	//Idle Right
	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());
#ifdef TOPDOWN
	//Idle Up
	m_animController->AddAnimation(animations["IdleUp"].get<Animation>());
	//Idle Down
	m_animController->AddAnimation(animations["IdleDown"].get<Animation>());
#endif

	//Walk Animations\\

	//WalkLeft
	m_animController->AddAnimation(animations["WalkLeft"].get<Animation>());
	//WalkRight
	m_animController->AddAnimation(animations["WalkRight"].get<Animation>());
#ifdef TOPDOWN
	//WalkUP
	m_animController->AddAnimation(animations["WalkUp"].get<Animation>());
	//WalkDown
	m_animController->AddAnimation(animations["WalkDown"].get<Animation>());
#endif

	//Attack Animations\\

	//AttackLeft
	m_animController->AddAnimation(animations["AttackLeft"].get<Animation>());
	//AttackRight
	m_animController->AddAnimation(animations["AttackRight"].get<Animation>());
#ifdef TOPDOWN
	//AttackUp
	m_animController->AddAnimation(animations["AttackUp"].get<Animation>());
	//AttackDown
	m_animController->AddAnimation(animations["AttackDown"].get<Animation>());
#endif

	//Set Default Animation
	m_animController->SetActiveAnim(IDLELEFT);


}

void Enemy::Update()
{
	if (!m_locked)
	{
		MovementUpdate();
	}
	AnimationUpdate();
}

void Enemy::MovementUpdate()
{
}

void Enemy::AnimationUpdate()
{
	int activeAnimation = 0;

	if (m_moving)
	{
		//Puts it into the WALK category
		activeAnimation = WALK;
	}
	else if (m_attacking)
	{
		activeAnimation = ATTACK;

		//Check if the attack animation is done
		if (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone())
		{
			//Will auto set to idle
			m_locked = false;
			m_attacking = false;
			//Resets the attack animation
			m_animController->GetAnimation(m_animController->GetActiveAnim()).Reset();

			activeAnimation = IDLE;
		}
	}
}
