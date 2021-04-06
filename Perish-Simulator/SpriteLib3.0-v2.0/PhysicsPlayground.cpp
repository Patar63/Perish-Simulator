#include "PhysicsPlayground.h"
#include "Utilities.h"

#include <random>

PhysicsPlayground::PhysicsPlayground(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene
	m_gravity = b2Vec2(0.f, 0.f);

	m_physicsWorld->SetContactListener(&listener);
}

static float Px = 0.0, Py = 0.0;
int mainCam = MainEntities::MainCamera();
void PhysicsPlayground::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity
	{

		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "OutsideFull.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 750, 750);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}

	//sets first room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "front foyer.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 250, 250);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1076.f, 176.f, 0.f));
	}
	//boundaries for first room
	Scene::boundary(5, 250, 1210, 176, 0, 0); //wall
	Scene::boundary(5, 250, 940, 176, 0, 0); //wall
	Scene::boundary(250, 5, 1076, 280, 0, 0); //wall
	Scene::boundary(100, 5, 1167, 58, 0, 0); //wall
	Scene::boundary(100, 5, 991, 58, 0, 0); //wall
	Scene::boundary(20, 17, 1200, 137, 0, 0); //counter
	Scene::boundary(20, 18, 955, 133.5, 0, 0); //counter

	//setup second room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "second room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 200);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1076.f, 500.f, 0.f));
	}
	//second room boundaries
	Scene::boundary(5, 200, 1238, 500, 0, 0); //wall
	Scene::boundary(5, 200, 917, 500, 0, 0); //wall
	Scene::boundary(300, 5, 1076, 574, 0, 0); //wall
	Scene::boundary(120, 5, 1160, 404, 0, 0); //wall
	Scene::boundary(120, 5, 989, 404, 0, 0); //wall
	Scene::boundary(5, 150, 936, 539, 0, 0); //book shelf
	Scene::boundary(25, 5, 1000, 539, 0, 0);

	//setup hallway
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "hallway.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 150, 400);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1500.f, 175.f, 0.f));
	}
	Scene::boundary(150, 5, 1500, 310, 0, 0);
	//Scene::boundary(150, 5, 1500, 320, 0, 0);
	Scene::boundary(5, 400, 1417, 175, 0, 0);

	//setsup side room 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "bigsquareroom.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 400, 400);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2000.f, 176.f, 0.f));
	}

	//setsup side room 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "key room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 150);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2000.f, 500.f, 0.f));
	}
	//setsup stairs room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "stairs room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 200);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1000.f, 1000.f, 0.f));
	}

	//setsup final room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "basement.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 500, 500);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 1000.f, 0.f));
	}
	
	//player entity
	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CanJump>(entity);

		//Sets up the components
		std::string fileName = "CharacterStandby.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20,44);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER, 0.5f, 3.f);
		tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetHeight() - shrinkY)/2.f), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER, 0.5f, 3.f);

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
	}


	//Setup the mansion object
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "Mansion.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 250);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-100.f, 200.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-100.f), float32(200.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), 
						float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}




void PhysicsPlayground::Update()
{
	
}


void PhysicsPlayground::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::A) || Input::GetKey(Key::D) || Input::GetKey(Key::W) || Input::GetKey(Key::S))
	{
		if (Input::GetKey(Key::A))
		{
			player.GetBody()->SetLinearVelocity(b2Vec2(-40000.f * speed, 0.f));
		}
		if (Input::GetKey(Key::D))
		{
			player.GetBody()->SetLinearVelocity(b2Vec2(40000.f * speed, 0.f));
		}
		if (Input::GetKey(Key::W))
		{
			player.GetBody()->SetLinearVelocity(b2Vec2(0.f, 40000.f * speed));
		}
		if (Input::GetKey(Key::S))
		{
			player.GetBody()->SetLinearVelocity(b2Vec2(0.f, -40000.f * speed));
		}
	}
	else
	{
		player.GetBody()->SetLinearVelocity(b2Vec2(0.f, 0.f));
	}
	Px = m_sceneReg->get<Camera>(mainCam).GetPositionX();
	Py = m_sceneReg->get<Camera>(mainCam).GetPositionY();
	std::cout << Px << ", " << Py << "\n";

	//works the doors
	//outside to first
	if (Px > -30 && Px < 33 && Py > 44 && Py < 80)
	{
		player.SetPosition(b2Vec2(1075.f, 80.f));
	}
	if (Px > 1049 && Px < 1093 && Py < 75)
	{
		player.SetPosition(b2Vec2(0.f, 25.f));
	}
	//first to second
	if (Px > 1050 && Px < 1100 && Py > 240 && Py < 300)
	{
		player.SetPosition(b2Vec2(1070.f, 435.f));
	}
	if (Px > 1050 && Px < 1100 && Py < 420 && Py > 350)
	{
		player.SetPosition(b2Vec2(1070.f, 225.f));
	}
	//second to hall
	if (Px > 1145 && Px < 1195 && Py > 540 && Py < 560)
	{
		player.SetPosition(b2Vec2(1505.f, 10.f));
	}
	if (Px > 1490 && Px < 1525 && Py < 5)
	{
		player.SetPosition(b2Vec2(1165.f, 525.f));
	}
	//hall to lower 
	if (Px > 1565 && Px < 1585 && Py > 60 && Py < 95)
	{
		player.SetPosition(b2Vec2(1825.f, 220.f));
	}
	if (Px > 1800 && Px < 1810 && Py < 240 && Py > 195)
	{
		player.SetPosition(b2Vec2(1550.f, 85.f));
	}
	if (Px > 1855 && Px < 1870 && Py > 490 && Py < 515)
	{
		player.SetPosition(b2Vec2(1555.f, 235.f));
	}
	if (Px > 1560 && Px < 1570 && Py > 230 && Py < 265)
	{
		player.SetPosition(b2Vec2(1875.f, 500.f));
	}
	if (Px > 1485 && Px < 1515 && Py > 310 && Py < 335)
	{
		player.SetPosition(b2Vec2(965.f, 940.f));
	}
	if (Px > 950 && Px <970 && Py > 920 && Py < 930)
	{
		player.SetPosition(b2Vec2(1500.f, 300.f));
	}
	if (Px > 1000 && Px < 1055 && Py > 955 && Py < 1015)
	{
		player.SetPosition(b2Vec2(-195.f, 985.f));
	}
}

void PhysicsPlayground::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());

	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
}

void PhysicsPlayground::KeyboardUp()
{
}