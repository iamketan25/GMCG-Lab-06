//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>
#include <GL/GL.h>

// Acknowldgement: 
// This code is an adapted version of the original source code
// published on the LearnOpenGL.com (Downloaded date - 5th April 2020)


using namespace std::chrono;


// settings
const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 600;
const unsigned int N_CURVE_PTS = 1001;  // change N_CURVE_PTS= 1001 for actual implementation
float controlPts[] = { -1.50f, 0.25f, 0.0f, -0.25f, 0.75f, 0.0f, 0.25f, 0.50f, 0.0f, 0.50, 0.00f, 0.0f };
// Note that it is normalized coordinate space; ideally control polygon can come from user clicks.

struct point
{
	float x;
	float y;
	float z;
};

void polygon(void)
{
	glBegin(GL_LINE_STRIP);
	glColor3ub(255, 200, 0);
	glVertex3f(-1.50f, 0.25f, 0.f);
	glVertex3f(-0.25f, 0.75f, 0.f);
	glVertex3f(0.25f, 0.5f, 0.f);
	glVertex3f(0.5f, 0.f, 0.f);
	
	glEnd();
	
}

point pointarray[N_CURVE_PTS];
void getVertices_bez3DeCasteljau(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter deCasteljau code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	for (int i = 0; i <= N_CURVE_PTS; i++)
	{
		float i1 = (float)i / N_CURVE_PTS;

		pointarray[i].x = pow((1 - i1), 3)*controlPts[0] + 3 * pow((1 - i1), 2)*i1*controlPts[3] + 3 * controlPts[6] * (1 - i1) * (pow((i1), 2)) + pow(i1, 3) * controlPts[9];
		pointarray[i].y = pow((1 - i1), 3)*controlPts[1] + 3 * pow((1 - i1), 2)*i1*controlPts[4] + 3 * controlPts[7] * (1 - i1)* (pow((i1), 2)) + pow(i1, 3) * controlPts[10];
		pointarray[i].z = pow((1 - i1), 3)*controlPts[2] + 3 * pow((1 - i1), 2)*i1*controlPts[5] + 3 * controlPts[8] * (1 - i1)* (pow((i1), 2)) + pow(i1, 3) * controlPts[11];

		vertices[i] = pointarray[i].x;
		vertices[i + N_CURVE_PTS] = pointarray[i].y;
		vertices[i + 2 * N_CURVE_PTS] = pointarray[i].z;

		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex3f(pointarray[i].x, pointarray[i].y, pointarray[i].z);
		glVertex3f(pointarray[i].x + 0.002f, pointarray[i].y, pointarray[i].z);
		glVertex3f(pointarray[i].x + 0.002f, pointarray[i].y + 0.002f, pointarray[i].z);
		glVertex3f(pointarray[i].x, pointarray[i].y + 0.002f, pointarray[i].z);
		glEnd();
	}

}
point pointarray1[N_CURVE_PTS];
void getVertices_bez3Mat(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter debez3Mat code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	for (int i = 0; i <= N_CURVE_PTS; i++)
	{
		float t = (float)i / N_CURVE_PTS;

		pointarray1[i].x = (-t * t*t + 3 * t*t - 3 * t + 1)*controlPts[0] + (3 * t*t*t - 6 * t*t + 3 * t)*controlPts[3] + (-3 * t*t*t + 3 * t*t)*controlPts[6] + t * t*t*controlPts[9];
		pointarray1[i].y = (-t * t*t + 3 * t*t - 3 * t + 1)*controlPts[1] + (3 * t*t*t - 6 * t*t + 3 * t)*controlPts[4] + (-3 * t*t*t + 3 * t*t)*controlPts[7] + t * t*t*controlPts[10];
		pointarray1[i].z = (-t * t*t + 3 * t*t - 3 * t + 1)*controlPts[2] + (3 * t*t*t - 6 * t*t + 3 * t)*controlPts[5] + (-3 * t*t*t + 3 * t*t)*controlPts[8] + t * t*t*controlPts[11];
		//std::cout << x1 << " " << y1 << std::endl;
		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex3f(pointarray1[i].x, pointarray1[i].y, pointarray1[i].z);
		glVertex3f(pointarray1[i].x + 0.002f, pointarray1[i].y, pointarray1[i].z);
		glVertex3f(pointarray1[i].x + 0.002f, pointarray1[i].y + 0.002f, pointarray1[i].z);
		glVertex3f(pointarray1[i].x, pointarray1[i].y + 0.002f, pointarray1[i].z);
		glEnd();
		vertices[i] = pointarray1[i].x;
		vertices[i + N_CURVE_PTS] = pointarray1[i].y;
		vertices[i + 2 * N_CURVE_PTS] = pointarray1[i].z;
	
	}


}


point pointarray2[N_CURVE_PTS];
void getVertices_bez3Horner(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter deHorner code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	for (int i = 0; i <= N_CURVE_PTS; i++)
	{
		float t = (float)i / N_CURVE_PTS;
		
		float cx0, cx1, cx2, cx3;
		float cy0, cy1, cy2, cy3;
		float cz0, cz1, cz2, cz3;

		cx0 = controlPts[0];
		cx1 = 3 * controlPts[3] - 3 * controlPts[0];
		cx2 = 3 * controlPts[0] - 6 * controlPts[3] + 3 * controlPts[6];
		cx3 = controlPts[9] - controlPts[0] + 3 * controlPts[3] - 3 * controlPts[6];


		cy0 = controlPts[1];
		cy1 = 3 * controlPts[4] - 3 * controlPts[1];
		cy2 = 3 * controlPts[1] - 6 * controlPts[4] + 3 * controlPts[7];
		cy3 = controlPts[10] - controlPts[1] + 3 * controlPts[4] - 3 * controlPts[7];


		cz0 = controlPts[2];
		cz1 = 3 * controlPts[5] - 3 * controlPts[2];
		cz2 = 3 * controlPts[2] - 6 * controlPts[5] + 3 * controlPts[8];
		cz3 = controlPts[11] - controlPts[2] + 3 * controlPts[5] - 3 * controlPts[8];

		pointarray2[i].x = cx0 + t * (cx1 + t * (cx2 + t * (cx3)));
		pointarray2[i].y = cy0 + t * (cy1 + t * (cy2 + t * (cy3)));
		pointarray2[i].z = cz0 + t * (cz1 + t * (cz2 + t * (cz3)));

		vertices[i] = pointarray2[i].x;
		vertices[i + N_CURVE_PTS] = pointarray2[i].y;
		vertices[i + 2 * N_CURVE_PTS] = pointarray2[i].z;

		glBegin(GL_QUADS);
		glColor3ub(255, 0, 231);
		glVertex3f(pointarray2[i].x, pointarray2[i].y, pointarray2[i].z);
		glVertex3f(pointarray2[i].x + 0.002f, pointarray2[i].y, pointarray[i].z);
		glVertex3f(pointarray2[i].x + 0.002f, pointarray2[i].y + 0.002f, pointarray2[i].z);
		glVertex3f(pointarray2[i].x, pointarray2[i].y + 0.002f, pointarray2[i].z);
		glEnd();
		
		


	}
}

int main(void)                                              //main function
{
	std::cout << "Bezier Curve" << std::endl;
	GLFWwindow* window;                                     //initializing GLFW and creating a GLFW window object
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(1800, 1480, "Bezier Curve", NULL, NULL); //properties of window such as size 1800 x 1480
	//glfwSetMouseButtonCallback(window, mouseButtonCallback);
	if (!window)
	{
		glfwTerminate();                                     //destroys all thw windows
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	int m = 0;
	unsigned int chunkSzBytes = N_CURVE_PTS * 3 * sizeof(float);
	float *vertices = (float*)malloc(chunkSzBytes);   //note that malloc always should come with corresponding free() at the end

	auto start = high_resolution_clock::now();  //Note need C++11 and #include <chrono> using namespace std::chrono

	getVertices_bez3DeCasteljau(N_CURVE_PTS, vertices);

	auto stop_1 = high_resolution_clock::now();

	getVertices_bez3Mat(N_CURVE_PTS, vertices);

	auto stop_2 = high_resolution_clock::now();

	getVertices_bez3Horner(N_CURVE_PTS, vertices);

	auto stop_3 = high_resolution_clock::now();

	auto duration_bez3DeCasteljau = duration_cast<microseconds>(stop_1 - start);
	std::cout << "de Casteljau time (ms)=  " << duration_bez3DeCasteljau.count() << std::endl;

	auto duration_bez3Mat = duration_cast<microseconds>(stop_2 - stop_1);
	std::cout << "bezMat time (ms)=  " << duration_bez3Mat.count() << std::endl;

	auto duration_bez3Horner = duration_cast<microseconds>(stop_3 - stop_2);
	std::cout << "Horner time (ms)=  " << duration_bez3Horner.count() << std::endl;

	std::cout << vertices[0] << " " << vertices[1] << " " << vertices[2] << "\n" << vertices[3] << " " << vertices[4] << " " << vertices[5] << " " << std::endl;

	while (!glfwWindowShouldClose(window))                  //loop that terminates when window is closed
	{

		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);    //retrieves the size of the window in pixels
		ratio = (float)width / (float)height;

		glViewport(0, 0, width, height);                    //affine transformation form normalized to window coordinates
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);                        //assigns current matrix mode
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);       //the current matrix by orthographic matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();     //replaces current matrix with identity matrix

	

		
		getVertices_bez3DeCasteljau(N_CURVE_PTS, vertices);
		polygon();
		getVertices_bez3Horner(N_CURVE_PTS, vertices);

		


		glfwSwapBuffers(window);             //swaps front and back buffers of the specified window

		glfwPollEvents();


	};


	free(vertices);
	glfwDestroyWindow(window);                       //destroys specified window and its context
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

