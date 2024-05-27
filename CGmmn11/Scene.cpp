#include "Scene.h"

//macros
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "drawPaperPlane"
#define MaxFPS 60

#define SELECTED_COLOR_R 1
#define SELECTED_COLOR_G 0
#define SELECTED_COLOR_B 0

#define PRESENT_COLOR_R 0
#define PRESENT_COLOR_G 1
#define PRESENT_COLOR_B 1


int scale_x_start = -960;
int scale_x_end = 960;
int scale_y_start = -540;
int scale_y_end = 540;
int scale_z_start = 960;
int scale_z_end = -960;

int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 1920;
int CurrentSceneHeight = 1080;

int WindowRectBounds_x = 0;
int WindowRectBounds_y = 0;
int WindowRectBounds_width = 0;
int WindowRectBounds_height = 0;

AnimationTimer* MyAnimationTimer;
UserPref CurrentUserControl;

void CleanupAndExit()
{
	exit(0);
}

//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;

	WindowRectBounds_x = StartPos_X;
	WindowRectBounds_y = StartPos_Y;
	WindowRectBounds_width = finalW;
	WindowRectBounds_height = finalH;
}


void drawRotatingObject(SceneObj ShapeToDraw, float red, float green, float blue)
{
	glColor3f(red, green, blue);
	switch (ShapeToDraw)
	{
	case enum_Sphere:
		DrawSceneObjSphere();
		break;
	case enum_Cube:
		DrawSceneObjCube();
		break;
	case enum_Cone:
		DrawSceneObjCone();
		break;
	case enum_Torus:
		DrawSceneObjTorus();
		break;
	case enum_Dodecahedron:
		DrawSceneObjDodecohedron();
		break;
	case enum_Octahedron:
		DrawSceneObjOctahedron();
		break;
	case enum_Tetrahedron:
		DrawSceneObjTetrahedron();
		break;
	case enum_Icosahedron:
		DrawSceneObjCosahedron();
		break;
	case enum_Teapot:
		DrawSceneObjTeapot();
		break;
	default:
		break;
	}

}

void DrawMenu()
{
	//draw menu
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10,10,-10,10,-10,40);
	glOrtho(-10, 10, -10, 10, -1, 40);//orthogonal shows diensions better
	//gluOrtho2D(0,1,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 0, 4,
		0, 0, 0,
		0, 1, 0);

	float val = MyAnimationTimer->GetCurrentAnimationValue();

	//show options
	//glScalef(0.03,0.03,0.03);
	for (int i = enum_Sphere; i <= enum_Teapot; i++)
	{
		glPushMatrix();
		glScalef(0.3, 0.3, 0.3);
		glTranslatef(30 - (4 * i), 30, 0);
		glRotatef(val, 0, 1, 0);
		if ((SceneObj)i == CurrentUserControl.currentObj)
		{
			drawRotatingObject((SceneObj)i, SELECTED_COLOR_R, SELECTED_COLOR_G, SELECTED_COLOR_B);
		}
		else
		{
			drawRotatingObject((SceneObj)i, PRESENT_COLOR_R, PRESENT_COLOR_G, PRESENT_COLOR_B);
		}
		glPopMatrix();
	}


}


#define ORTHO_X 10
#define ORTHO_Y 10

#define FRUSTUM_X 2
#define FRUSTUM_Y 2

void DrawScene(bool IsOrtho)
{
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();

	if (IsOrtho)
		glOrtho(-ORTHO_X / 2, ORTHO_X / 2, -ORTHO_Y / 2, ORTHO_Y / 2, -1, 50);
	else
		glFrustum(-FRUSTUM_X / 2, FRUSTUM_X / 2, -FRUSTUM_Y / 2, FRUSTUM_Y / 2, 0.4, 200.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawBackgroundWithColor(1, 1, 1);
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	Draw3DAxis(true, true, false);
	float val = MyAnimationTimer->GetCurrentAnimationValue();
	glRotatef(val, 0, 1, 0);
	drawRotatingObject(CurrentUserControl.currentObj, 0, 1, 1);
}

//Redraw callback
void DisplayCallback()
{
	//draw all three scenes on one window
	FixAspectRatio();
	glViewport(WindowRectBounds_x, WindowRectBounds_y, WindowRectBounds_width, WindowRectBounds_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawScene(CurrentUserControl.IsOrtho);
	DrawMenu();

	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;
	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;
	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);
}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'a'://left object
	case 'A':
		CurrentUserControl.currentObj = (SceneObj)(((int)CurrentUserControl.currentObj) + 1);
		break;

	case 'D'://right object
	case 'd':
		CurrentUserControl.currentObj = (SceneObj)(((int)CurrentUserControl.currentObj) - 1);
		break;

	case '+'://faster animation
		CurrentUserControl.AnimationSpeed = CurrentUserControl.AnimationSpeed / 1.1;
		break;

	case '-'://slower animation
		CurrentUserControl.AnimationSpeed = CurrentUserControl.AnimationSpeed * 1.1;
		break;

	case 'c':
	case 'C':
		CurrentUserControl.IsOrtho = !CurrentUserControl.IsOrtho;
		break;
	case 'q':
	case 'Q':
		exit(0);
		break;
	}


	if (CurrentUserControl.currentObj < 0)
	{
		CurrentUserControl.currentObj = enum_Teapot;
	}

	if (CurrentUserControl.currentObj > enum_Teapot)
	{
		CurrentUserControl.currentObj = enum_Sphere;
	}

	MyAnimationTimer->SetSpeed(CurrentUserControl.AnimationSpeed);
}

void timerCallback(int value) {
	glutPostRedisplay();  // Mark the current window as needing to be redisplayed
	glutTimerFunc(1000 / 60, timerCallback, 0);  // Register the timer callback again to achieve 60 FPS
}


//my initiation function
void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1920;
	CurrentSceneHeight = 1080;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);
	AspectRatioDenominator = CurrentSceneHeight / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(MY_HEADER);

	//set startup settings
	CurrentUserControl.currentObj = enum_Dodecahedron;
	CurrentUserControl.AnimationSpeed = 3;
	CurrentUserControl.IsOrtho = true;

	MyAnimationTimer = new AnimationTimer(CurrentUserControl.AnimationSpeed, 0, 360);
	MyAnimationTimer->StartTimer();


	glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);
	glutKeyboardFunc(KeyboardEventCallback);
	glutTimerFunc(0, timerCallback, 0);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{

	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();
}