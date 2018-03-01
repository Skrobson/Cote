#pragma once
#include "ATest.h"


class BoxTest : public ATest
{
public:
	BoxTest();

	virtual void update();

	std::shared_ptr<Model> createBox();
	std::shared_ptr<Model> box;
};

