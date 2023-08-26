#include "Simple/Simple.h"
#include <iostream>
#include <GL/glu.h>

int main()
{
	bool run = true;
	try{
		Simple::Window window;
		Simple::Context context = window.GetContext();
		Simple::Event ev;

		while(run)
		{
            while(window.GetEvent(ev))
			{
				switch(ev.Type)
				{
					case ev.Close: run = false;break;
				}
			}

			context.ClearColor(COLOR_MIDNIGHT_BLUE);
			context.Clear();

			context.ResetMatrix();
			glTranslatef(0,0,-3);
			glBegin(GL_TRIANGLES);

			glColor3f(1,0,0);
				glVertex3f(-1,-1,0);
			glColor3f(0,1,0);
				glVertex3f( 0, 1,0);
			glColor3f(0,0,1);
				glVertex3f( 1,-1,0);

			glEnd();

			context.Present();
		}
	}catch(std::exception& e){
		std::cout<<e.what();
	}

	return 0;
}
