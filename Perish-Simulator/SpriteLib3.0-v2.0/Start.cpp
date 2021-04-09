#include "Start.h"
#include "Input.h"
#include <SFML/Audio.hpp>

Start::Start(std::string name)
	: Scene(name)
{
	//no gravity 
	m_gravity = b2Vec2(0.f, 0.f);
}


int MenuCam = MainEntities::MainCamera();
void Start::InitScene(float width, float height)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;
	m_width = width;
	m_height = height;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = width / height;

	//Setup MenuCamera Entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);

		vec4 temp = vec4(float(-width) / 2.f, float(width) / 2.f, float(-height) / 2.f, float(height) / 2.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(width), float(height)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
	}

	//title graphic setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ttl = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Title.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, (2 * width), height);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}

	//start Button setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		strt = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Start(1).png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, m_width / 4, m_height / 8);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-300.f, 50.f, 1.f));
	}

	//exit button setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ext = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Exit(1).png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, m_width / 4, m_height / 8);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(300.f, -50.f, 1.f));
	}

	//controls button setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cntrl = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Controls(1).png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, m_width / 4, m_height / 8);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(300.f, 50.f, 1.f));
	}

	//credits setup
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		crdt = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Credits(1).png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, m_width / 4, m_height / 8);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-300.f, -50.f, 1.f));
	}
}

void Start::InitSound()
{
}

void Start::Update()
{
	//button updates
	if (choice == 0 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(strt);
		std::string fileName = "Start(2).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (choice != 0 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(strt);
		std::string fileName = "Start(1).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (menu == false)
	{

		auto& sprite = ECS::GetComponent<Sprite>(strt);
		std::string fileName = "x.png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}

	if (choice == 1 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(cntrl);
		std::string fileName = "Controls(2).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (choice != 1 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(cntrl);
		std::string fileName = "Controls(1).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (menu == false)
	{

		auto& sprite = ECS::GetComponent<Sprite>(cntrl);
		std::string fileName = "x.png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}

	if (choice == 2 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(crdt);
		std::string fileName = "Credits(2).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (choice != 2 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(crdt);
		std::string fileName = "Credits(1).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (menu == false)
	{

		auto& sprite = ECS::GetComponent<Sprite>(crdt);
		std::string fileName = "x.png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}

	if (choice == 3 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(ext);
		std::string fileName = "Exit(2).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (choice != 3 && menu == true)
	{
		auto& sprite = ECS::GetComponent<Sprite>(ext);
		std::string fileName = "Exit(1).png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}
	else if (menu == false)
	{
		auto& sprite = ECS::GetComponent<Sprite>(ext);
		std::string fileName = "x.png";
		sprite.LoadSprite(fileName, m_width / 4, m_height / 8);
	}


	//load between menus
	if (choice == 1 && Input::GetKey(Key::Space))
	{
		menu = false;

		auto& sprite = ECS::GetComponent<Sprite>(ttl);
		std::string fileName = "controlscreen.png";
		sprite.LoadSprite(fileName, (2 * m_width), m_height);
	}
	if (choice == 2 && Input::GetKey(Key::Space))
	{
		menu = false;

		auto& sprite = ECS::GetComponent<Sprite>(ttl);
		std::string fileName = "creditscreen.png";
		sprite.LoadSprite(fileName, (2 * m_width), m_height);
	}
	if (menu == false && Input::GetKey(Key::Space))
	{
		menu = true;

		auto& sprite = ECS::GetComponent<Sprite>(ttl);
		std::string fileName = "Title.png";
		sprite.LoadSprite(fileName, (2 * m_width), m_height);
	}
}

void Start::KeyboardHold()
{
	if (menu == true)
	{
		if (Input::GetKey(Key::A) && choice == 1)
		{
			choice = 0;
		}
		if (Input::GetKey(Key::A) && choice == 3)
		{
			choice = 2;
		}
		if (Input::GetKey(Key::D) && choice == 2)
		{
			choice = 3;
		}
		if (Input::GetKey(Key::D) && choice == 0)
		{
			choice = 1;
		}

		if (Input::GetKey(Key::W) && choice == 2)
		{
			choice = 0;
		}
		if (Input::GetKey(Key::W) && choice == 3)
		{
			choice = 1;
		}
		if (Input::GetKey(Key::S) && choice == 0)
		{
			choice = 2;
		}
		if (Input::GetKey(Key::S) && choice == 1)
		{
			choice = 3;
		}
	}
}

void Start::KeyboardDown()
{
}

void Start::KeyboardUp()
{
}
