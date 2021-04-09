#pragma once

#include "Scene.h"
#include "Transform.h"

class Start : public Scene
{
public:
	Start(std::string name);

	void InitScene(float width, float height) override;
	void InitSound();
	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	int choice = 0;
	bool menu = true;

private:
	float m_width;
	float m_height;
	unsigned strt;
	unsigned ext;
	unsigned cntrl;
	unsigned crdt;
	unsigned ttl;
};
