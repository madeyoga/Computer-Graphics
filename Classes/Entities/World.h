#pragma once

class World
{
private:
	std::vector <Mesh> __meshses;
public:
	World()
	{

	}
	World(std::vector<Mesh> meshses)
	{
		__meshses = meshses;
	}
	void add_mesh(Mesh _mesh)
	{
		__meshses.push_back(_mesh);
	}
	void draw(Camera _cam)
	{
		for (int i = 0; i < __meshses.size(); i++)
		{
			__meshses[i].drawMesh(_cam);
		}
	}
};