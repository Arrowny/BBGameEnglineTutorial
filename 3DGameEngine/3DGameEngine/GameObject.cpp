#include "GameObject.h"


GameObject::GameObject()
{
	transform = Transform();
}


GameObject::~GameObject()
{
}

void GameObject::AddChild(GameObject child)
{
	children.push_back(child);
}

void GameObject::AddComponent(GameComponent* comp)
{
	components.push_back(comp);
}

void GameObject::input()
{
	for each (GameComponent* comp in components)
		comp->input(transform);

	for each (GameObject child in children)
		child.input();
}

void GameObject::update()
{

	for each (GameComponent* comp in components)
		comp->update(transform);

	for each (GameObject child in children)
		child.update();
}

void GameObject::render()
{
	for each (GameComponent* comp in components)
		comp->render(transform);

	for each (GameObject child in children)
		child.render();
}

Transform GameObject::GetTransform()
{
	return transform;
}