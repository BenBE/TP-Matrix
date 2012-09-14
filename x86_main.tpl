#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>  

void *loop_thread_wrapper(void *){
  while(1){
    loop();
  }
  pthread_exit(NULL);
}

void glinit() {
  /* set clear color to black */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho( 0, DISPLAY_WIDTH  * 1.0
         , 0, DISPLAY_HEIGHT * 1.0
         , 0, 1.0);
}

void glutReshapeEvent(int width, int height) {
  glutReshapeWindow(DISPLAY_WIDTH * 12,DISPLAY_HEIGHT * 12);
}

void glutKeyboardEvent(unsigned char key, int x, int y){
  if(key == 'q' || key == 'Q'){
    exit(0);
  }
}

int main(int argc, char *argv[]) {

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(DISPLAY_WIDTH * 12,DISPLAY_HEIGHT * 12);
  glutInitWindowPosition(0,0);
  glutCreateWindow("TP-Matrix Simulator");
  glutDisplayFunc(display_interrupt);
  glutReshapeFunc(glutReshapeEvent);
  glutKeyboardFunc(glutKeyboardEvent);

  setup();
  glinit();

  pthread_t loop_thread;
  pthread_create(&loop_thread,NULL,loop_thread_wrapper,NULL); 

  glutMainLoop();

  return 0;
}
