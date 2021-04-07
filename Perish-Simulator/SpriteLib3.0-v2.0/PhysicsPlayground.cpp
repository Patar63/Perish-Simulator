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
	Scene::boundary(145, 10, 1060, 512.5, 0, 0);//table and chair

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
	//hallway boundaries
	Scene::boundary(50, 5, 1450, 330, 0, 0); // top wall
	Scene::boundary(50, 5, 1550, 330, 0, 0); // top wall
	Scene::boundary(100, 5, 1500, 340, 0, 0);//door when locked
	Scene::boundary(50, 5, 1450, -18, 0, 0); // bottom wall
	Scene::boundary(50, 5, 1550, -18, 0, 0); // bottom wall
	Scene::boundary(5, 400, 1417, 175, 0, 0); //left wall
	Scene::boundary(5, 75, 1585, 292, 0, 0); //right wall
	Scene::boundary(5, 105, 1585, 152, 0, 0); //right wall
	Scene::boundary(5, 65, 1585, 10, 0, 0); // right wall
	Scene::boundary(5, 45, 1442, 275, 0, 0); // top vase
	Scene::boundary(5, 35, 1442, 115, 0, 0); // bottom vase

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
	//side room 1 boundaries
	Scene::boundary(400, 5, 2000, -20, 0, 0); //bottom wall
	Scene::boundary(400, 5, 2000, 306, 0, 0); //top wall
	Scene::boundary(5, 400, 2208, 176, 0, 0); //right wall
	Scene::boundary(5, 205, 1797, 87.5, 0, 0); //left wall
	Scene::boundary(5, 50, 1797, 270, 0, 0); //left wall
	Scene::boundary(160, 20, 2027.5, 155, 0, 0); //table
	Scene::boundary(60, 5, 2085, 270, 0, 0); //top right shelf
	Scene::boundary(60, 5, 1932.5, 270, 0, 0); //top left shelf
	Scene::boundary(60, 10, 2085, 52.5, 0, 0); //bottom right shelf
	Scene::boundary(60, 10, 1934, 52.5, 0, 0); //bottom left shelf

	//setsup side room 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "key room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 300, 175);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2000.f, 520.f, 0.f));
	}

	//key object setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		key = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "key.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2000.f, 500.f, 1.f));
	}

	//side room 2 boundaries
	Scene::boundary(300, 5, 2000, 582.5, 0, 0); //top wall
	Scene::boundary(300, 5, 2000, 435, 0, 0); //bottom wall
	Scene::boundary(5, 175, 2160, 520, 0, 0); // right wall
	Scene::boundary(5, 40, 1845, 550, 0, 0); //left wall
	Scene::boundary(5, 40, 1845, 465, 0, 0); //left wall

	//setsup stairs room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "stairs room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 155);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1000.f, 1000.f, 0.f));
	}
	//stairs room boundaries
	Scene::boundary(200, 5, 1000, 1060, 0, 0); //top wall
	Scene::boundary(125, 5, 1045, 923, 0, 0); //bottom wall
	Scene::boundary(50, 5, 903, 923, 0, 0); //bottom wall
	Scene::boundary(5, 155, 890, 1000, 0, 0); //left wall
	Scene::boundary(5, 155, 1115, 1000, 0, 0); //right wall
	Scene::boundary(25, 25, 1050, 1000, 0, 0); //trapdoor


	//setsup final room
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "basement.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 350, 350);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-50.f, 1000.f, 0.f));
	}
	//final room boundaries
	Scene::boundary(350, 5, -50, 1123, 0, 0); //top wall
	Scene::boundary(350, 5, -50, 838, 0, 0); //bottom wall
	Scene::boundary(5, 350, -225, 1000, 0, 0); //left wall
	Scene::boundary(5, 350, 125, 1000, 0, 0); // right wall
	
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
	if (lock == false)
	{
		auto& sprite = ECS::GetComponent<Sprite>(key);
		std::string fileName = "x.png";
		sprite.LoadSprite(fileName, 10, 10);
	}
	else
	{
		auto& sprite = ECS::GetComponent<Sprite>(key);
		std::string fileName = "key.png";
		sprite.LoadSprite(fileName, 10, 10);
	}
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

	//variable for key
	if (Px > 1990 && Px < 2015 && Py > 505 && Py < 525)
	{
		lock = false;
	}

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
	//hall to upper
	if (Px > 1855 && Px < 1870 && Py > 475 && Py < 510)
	{
		player.SetPosition(b2Vec2(1555.f, 235.f));
	}
	if (Px > 1560 && Px < 1570 && Py > 215 && Py < 260)
	{
		player.SetPosition(b2Vec2(1875.f, 500.f));
	}
	//hall to stairs
	if (lock == false && Px > 1485 && Px < 1515 && Py > 305 && Py < 335)
	{
		player.SetPosition(b2Vec2(958.f, 945.f));
	}
	if (Px > 950 && Px <970 && Py > 920 && Py < 940)
	{
		player.SetPosition(b2Vec2(1500.f, 285.f));
	}
	//stairs to basement
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