#include "SubWindow.h"

SubWindow::SubWindow(int w, int h, SDL_Renderer *r)
{
	width = w;
	height = h;
	
	viewport.w = w;
	viewport.h = h;
	viewport.x = x;
	viewport.y = y;

	ren = r;
}

bool SubWindow::addObject(Oggetto *obj)
{
	std::cout << "addObject obj-> "<< obj <<std::endl;
	obj->setWLimit(width);
	obj->setHLimit(height);
	objs.push_back(obj);
	return true;
}
void SubWindow::removeObject(Oggetto *obj)
{
	std::cout << "removeObject obj-> "<< obj <<std::endl;
	objs.remove(obj);
}

void SubWindow::render() {
	SDL_RenderSetViewport(ren, &viewport);
	for (auto object : objs) {
		if (object != nullptr)
			object->render(ren);
	}
}

SubWindow::~SubWindow() {
	for (auto object: objs) {
		delete object;
	}
}
