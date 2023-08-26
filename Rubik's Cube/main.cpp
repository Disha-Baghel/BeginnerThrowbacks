#include "Simple/Simple.h"
#include "Box.h"

class RubiksCube:public Canvas
{
	static const int dim = 3;
	static const int CubeletCount = dim*dim*dim;
	Cubelet cube[CubeletCount];
	float angX = 0;
	float angY = 0;
public:
	RubiksCube(): Canvas(800,500)
	{
		int index = 0;
		for(int x=-1;x<=1;x++)
		{
			for(int y=-1;y<=1;y++)
			{
				for(int z=-1;z<=1;z++)
				{
					Matrix4D matrix;
					matrix.translate(x,y,z);
					cube[index] = Cubelet(matrix);
					index++;
				}
			}
		}
	}

	void turnZ(int index)
	{
		for(int i=0;i<CubeletCount;i++)
		{
			if(cube[i].z() == index)
			{
				cube[i].rotateZ();
			}
		}
	}

	void turnX(int index)
	{
		for(int i=0;i<CubeletCount;i++)
		{
			if(cube[i].x() == index)
			{
				cube[i].rotateX();
			}
		}
	}

	void turnY(int index)
	{
		for(int i=0;i<CubeletCount;i++)
		{
			if(cube[i].y() == index)
			{
				cube[i].rotateY();
			}
		}
	}

	void Update()
	{
		if(KeyIsDown('X'))
		{
			if(KeyDown('1'))
				turnX(1);
			else if(KeyDown('2'))
				turnX(0);
			else if(KeyDown('3'))
				turnX(-1);
		}
		else if(KeyIsDown('Y'))
		{
			if(KeyDown('1'))
				turnY(1);
			else if(KeyDown('2'))
				turnY(0);
			else if(KeyDown('3'))
				turnY(-1);
		}
		else if(KeyIsDown('Z'))
		{
			if(KeyDown('1'))
				turnZ(1);
			else if(KeyDown('2'))
				turnZ(0);
			else if(KeyDown('3'))
				turnZ(-1);
		}

		if(KeyIsDown('W'))
			angX-=0.5;
		else if(KeyIsDown('S'))
			angX+=0.5;

		if(KeyIsDown('A'))
			angY-=0.5;
		else if(KeyIsDown('D'))
			angY+=0.5;
	}

	void Render()
	{
		glTranslatef(0,0,-5);
		glRotatef(angX,1,0,0);
		glRotatef(angY,0,1,0);
		background(COLOR_MIDNIGHT_BLUE);
		for(int i=0;i<CubeletCount;i++)
			cube[i].Show();
	}
};

int main()
{
	RubiksCube rc;
	return rc.Run();
}
