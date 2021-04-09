#include "Ending.h" 
#include "Transform.h" 

Ending::Ending(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene 
	m_gravity = b2Vec2(0.f, 0.f);
}

int EndCam = MainEntities::MainCamera();
void Ending::InitScene(float width, float height)
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

	//ending graphic setup 
	{
		//Creates entity 
		auto entity = ECS::CreateEntity();

		//Add components 
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components 
		std::string fileName = "End.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, (2 * width), height);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}
}

void Ending::Update()
{
}

void Ending::KeyboardHold()
{
}

void Ending::KeyboardDown()
{
}

void Ending::KeyboardUp()
{
}

Ending::~Ending()
{
}