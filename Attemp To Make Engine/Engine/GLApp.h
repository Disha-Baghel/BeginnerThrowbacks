#ifndef GLAPP_H
#define GLAPP_H

#include "Glutil.h"

class GLApp
{
public:
    GLApp(void);
    virtual ~GLApp();

    int Run();

    virtual void Setup() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    void CreateCanvas(int width,int height);

    LRESULT MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

    //Getter Functions
    int GetWidth(){return m_ClientWidth;}
    int GetHeight(){return m_ClientHeight;}

    //Setter Functions
    void SetAppName(const char* AppTitle)
    {
        m_AppTitle = AppTitle;
        SetWindowText(m_hAppWnd,AppTitle);
    }

    //Draw Functions
    void strokeWeight(float sWeight){glPointSize(sWeight);}

    void DrawPoint(GLfloat x,GLfloat y,GLfloat z = 0);
    void DrawPoints(Vec3D v[],int Count);

    void DrawLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);
    void DrawLines(Vec3D v1[],Vec3D v2[],int Count);

protected:
    HWND            m_hAppWnd;
    HINSTANCE       m_hAppInstance;
    HDC             m_hDevContext;
    HGLRC           m_hRenderContext;
    UINT            m_ClientWidth;
    UINT            m_ClientHeight;
    DWORD           m_WindowStyle;
    const char*     m_AppTitle;
    float           m_FPS;
private:
    bool Init();
    bool InitGL();
    bool InitWindow();

    GLvoid ReSizeGlScene(GLsizei width,GLsizei height);

    void CalculateFPS(float dt);
    void Shutdown();
};

#endif // GLAPP_H
