#pragma once 

#include "Scene.h" 

class Ending : public Scene
{
public:
	Ending(std::string fileName);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides 
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	~Ending();

private:
	float m_width;
	float m_height;
};
#pragma once
