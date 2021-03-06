//------------------------------------------------
//
//  img_paint
//
//
//-------------------------------------------------




#include <cmath>
#include <omp.h>
#include "imgproc.h"
#include "CmdLineFind.h"
#include <vector>



#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.


#include <iostream>
#include <stack>


using namespace std;
using namespace img;

ImgProc image;

void setNbCores( int nb )
{
   omp_set_num_threads( nb );
}

void cbMotion( int x, int y )
{
}

void cbMouse( int button, int state, int x, int y )
{
}

void cbDisplay( void )
{
   glClear(GL_COLOR_BUFFER_BIT );
   glDrawPixels( image.nx(), image.ny(), GL_RGB, GL_FLOAT, image.raw() );
   glutSwapBuffers();
}

void cbIdle()
{
   glutPostRedisplay();	
}

void cbOnKeyboard( unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 'c':
	 image.compliment();
	 cout << "Compliment\n";
	 break; 


      case 'V':
	 image.increaseBrightness();
	 cout << "Increase brightness\n";
	 break; 
	

      case 'v':
	 image.decreaseBrightness();
	 cout << "Decrease brightness\n";
	 break; 
	

      case 'B':
	 image.increaseBias();
	 cout << "Increase bias\n";
	 break; 
	

      case 'b':
	 image.decreaseBias();
	 cout << "Decrease bias\n";
	 break; 
	

      case 'G':
	 image.increaseGamma();
	 cout << "Increase gamma\n";
	 break; 
	

      case 'g':
	 image.decreaseGamma();
	 cout << "Decrease gamma\n";
	 break; 
	

      case 'w':
	 image.createGrayscale();
	 cout << "Create grayscale\n";
	 break; 
	

      case 'q':
	 image.quantize();
	 cout << "Quantize\n";
	 break; 
	

      case 'C':
	 image.rmsContrast();
	 cout << "rms contrast\n";
	 break; 


      case 'o':
	 image.createImageFile();
	 cout << "Create 'newFile.exr' image file\n";
	 break; 
   }
}

void PrintUsage()
{
   cout << "img_paint keyboard choices\n";
   cout << "c         compliment\n";
   cout << "V         increase brightness\n";
   cout << "v         decrease brightness\n";
   cout << "B         increase bias\n";
   cout << "b         decrease bias\n";
   cout << "G         increase gamma\n";
   cout << "g         decrease gamma\n";
   cout << "w         create grayscale\n";
   cout << "q         quantize\n";
   cout << "C         rms contrast\n";
   cout << "o         create new EXR image file called 'newFile.exr'\n";
}


int main(int argc, char** argv)
{
   lux::CmdLineFind clf( argc, argv );

   setNbCores(8);

   string imagename = clf.find("-image", "", "Image to drive color");

   clf.usage("-h");
   clf.printFinds();
   PrintUsage();

   image.load(imagename);

   // GLUT routines
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize( image.nx(), image.ny() );

   // Open a window 
   char title[] = "img_paint";
   glutCreateWindow( title );
   
   glClearColor( 1,1,1,1 );

   glutDisplayFunc(&cbDisplay);
   glutIdleFunc(&cbIdle);
   glutKeyboardFunc(&cbOnKeyboard);
   glutMouseFunc( &cbMouse );
   glutMotionFunc( &cbMotion );

   glutMainLoop();
   return 1;
};
