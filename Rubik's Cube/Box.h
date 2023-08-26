#include "Renderer.h"

class Cubelet: private Renderer
{
public:
	Matrix4D matrix;
	Cubelet(){}
	Cubelet(Matrix4D matrix)
	{
		this->matrix = matrix;
	}

	int x() const {return std::round(matrix[12]);}
	int y() const {return std::round(matrix[13]);}
	int z() const {return std::round(matrix[14]);}

	void rotateZ()
	{
		matrix.rotateZ(90);
	}

	void rotateX()
	{
		matrix.rotateX(90);
	}

	void rotateY()
	{
		matrix.rotateY(90);
	}

	void Show()
	{
		glPushMatrix();
			glMultMatrixf(matrix.get());
			box(1,COLOR_RED,COLOR_GREEN,COLOR_ORANGE,COLOR_BLUE,COLOR_WHITE,COLOR_YELLOW);
			fill(COLOR_BLACK);
			boxMesh(1+0.013);
		glPopMatrix();
	}
};
