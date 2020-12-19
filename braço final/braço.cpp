/***************************************

braço
braço.cpp

Prof: Gustavo Vinhal

Alunos: GIULIANNO G LATORRACA
		VINICIUS HENRIQUE DA SILVA SOUZA
		RAIANE PEREIRA ALCANTARA
		
		
		UM BRAÇO EM 3D e com textura de uma pele humana e com iluminação
		Modelos geomátricos foram usados para criar o braço e cada parte
		
		Os dedos, Punho, Ombro e Cotovelo se mexem ao apertas as teclas do teclado
		C - todos os dedos
		T - poelegar
		R - indicador
		M - Anelar
		P - mindinho
		
		E - cotovelo
		S - Ombro
		H - punho
		
		Segurando Shift faz as função ao contrário		
		

****************************************/


#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <iostream>

using namespace std;

//iniciando posição
static int ombro = 0, cotovelo = 0, mao = 0, polegar = 0, apontar = 0, meio = 0, anelar = 0, mindinho = 0;

//dedos
static int polegarcap = 0, apontarcap = 0, meiocap = 0, anelarcap = 0, mindinhocap = 0;

//tamanho da janela
static int sWidth = 1000, sHeight = 1000;


/*GLuint LoadTextureRAW( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    GLubyte * data;
    FILE * file;

    //textura
    file = fopen( filename, "rb" );
    if ( file == NULL ){
	cout<<"Falhou ao abrir o arquivo";
	return 0;
	}

    // buffer
    width = 256;
    height = 256;
    data = new GLubyte[width * height * 3];

    // lendo a textura
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // alocando a textura
    glGenTextures( 1, &texture );

    // selecionando a textura
    glBindTexture( GL_TEXTURE_2D, texture );

    // textura modulo
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // quando a textura é menor
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR );
    // quando a textura é maior
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // construir as texturas
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );
	

    // free buffer
    free( data );

    return texture;
}*/

GLuint idTextura;

void loadBMP(char *filename) {

	unsigned int width, height;
	unsigned char header[54];

	unsigned char * data;

	FILE * file;
	file = fopen(filename, "rb");

	if (file == NULL)
		return;

	
	if (fread(header, 1, 54, file) != 54) {
		printf("erro ao ler arquivo\n");
		return;
	}
	width = *(int*) &(header[0x12]);
	height = *(int*) &(header[0x16]);

	data = (unsigned char *) malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i) {
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
	GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}



void robotarm(void)
{
   glClear (GL_DEPTH_BUFFER_BIT);
   glEnable( GL_TEXTURE_2D );
   
   
       //habilitar luz
	   glEnable( GL_LIGHTING );
	   glEnable( GL_LIGHT0 );
	   GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
	   glLightfv( GL_LIGHT0, GL_SPECULAR, qaSpecularLight );

   
   
   //ombro
   glPushMatrix();
   
    GLfloat qaLightPosition[] = {1, 1, 1, 1};
	glLightfv( GL_LIGHT0, GL_POSITION, qaLightPosition );
	GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.9};
   
   //glBindTexture(GL_TEXTURE_2D,text1);
   //glGenTextures(5,VarPtr Texture[0]);
   glTranslatef (-1.0, 0.0, 0.0);         
   glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) ombro, 0.5, 0.0, 0.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(1.0,1.0,1.0);
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();
   
   
   //cotovelo
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(0.0,1.0,1.0);
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();
   
   //mão
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) mao, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glColor3f(0.0,0.0,1.0);
   glScalef (0.5, 0.5, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();
   
   
   //polegar
   glPushMatrix();
   glTranslatef (0.0, 0.125, -0.2);
   glRotatef ((GLfloat) polegar, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.8);
   glPushMatrix();
   glColor3f(1.0,0.0,0.0);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   
   glTranslatef (0.15, 0.0, -0.8);
   glRotatef ((GLfloat) polegar, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.8);
   glPushMatrix();
   glColor3f(1.0,0.0,0.0);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();
   
   
   //dedo apontar
   glPushMatrix();
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) apontar, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.4);
   glPushMatrix();
   glColor3f(0.8,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   
   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) apontar, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(0.8,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();       
   glPopMatrix();
 
   
   //dedo meio
   glPushMatrix();
   glTranslatef (0.5, 0.10, 0.0);
   glRotatef ((GLfloat) meio, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(0.65,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   
   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) meio, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(0.65,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();
   
   
   //dedo anelar
   glPushMatrix();
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) anelar, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.4);
   glPushMatrix();
   glColor3f(0.5,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) anelar, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.1,  0.0);
   glPushMatrix();
   glColor3f(0.5,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();
   
   
   //dedo mindinho
   glPushMatrix();
   glTranslatef (0.2, 0.1, 0.0);
   glRotatef ((GLfloat) mindinho, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.6);
   glPushMatrix();
   glColor3f(0.35,0.0,0.0);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();

   glTranslatef (0.4, 0.1, 0.0);
   glRotatef ((GLfloat) mindinho, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.1, 0.0);
   glPushMatrix();
   glColor3f(0.35,0.0,0.0);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();

   
   //fim
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   sWidth=w;
   sHeight=h;
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  for(int i = 0; i <= 4; i++) {
    if(i == 0) {
	glViewport(0, sHeight/2, sWidth/2, sHeight/2);
        glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) sWidth/(GLfloat) sHeight, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
        robotarm();
    } else if(i == 1) {
        glViewport (sWidth/2, sHeight/2, sWidth/2, sHeight/2);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) sWidth/(GLfloat) sHeight, 1.0, 20.0);
	gluLookAt(6,0,-5.0, 0,0,-5.0, 0,1,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
        robotarm();
    } else if(i == 2) {
        glViewport (sWidth/2, 0, sWidth/2, sHeight/2);
        glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) sWidth/(GLfloat) sHeight, 1.0, 20.0);
	gluLookAt(6,6,-0.0, 0,0,-5.0, 0,1,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
        robotarm();
    } else if(i == 3) {
        glViewport (0, 0, sWidth/2, sHeight/2);
        glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) sWidth/(GLfloat) sHeight, 1.0, 20.0);
	gluLookAt(6,0,-5.0, 0,0,-5.0, 0,-1,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
        robotarm();
    }
  }
  glFlush();
  glutSwapBuffers();
}


void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      //ombro
      case 's':
         ombro = (ombro + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         ombro = (ombro - 5) % 360;
         glutPostRedisplay();
         break;
      //cotovelo
      case 'e':
	 if (cotovelo < 180)
         cotovelo = (cotovelo + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
	 if (cotovelo > 0)
         cotovelo = (cotovelo - 5) % 360;
         glutPostRedisplay();
         break;
      //mão
      case 'h':
	 if (mao < 90)
	 mao = (mao + 5) % 360;
         glutPostRedisplay();
         break;
      case 'H':
	 if (mao > 0)
	 mao = (mao - 5) % 360;
         glutPostRedisplay();
         break;
	 
      //polegar 
      case 'f':
	 if (polegar < 90)
         polegar = (polegar + 5) % 360;
         glutPostRedisplay();
         break;
      case 'F':
	 if (polegar > 0)
         polegar = (polegar - 5) % 360;
         glutPostRedisplay();
         break;
	 
      //dedo apontar
      case 'p':
	 if (apontar < 90)
         apontar = (apontar + 5) % 360;
         glutPostRedisplay();
         break;
      case 'P':
	 if (apontar > 0)
         apontar = (apontar - 5) % 360;
         glutPostRedisplay();
         break;
	 
      //dedo meio
      case 'm':
	 if (meio < 90)
         meio = (meio + 5) % 360;
         glutPostRedisplay();
         break;
      case 'M':
	 if (meio > 0)
         meio = (meio - 5) % 360;
         glutPostRedisplay();
         break;
	 
      //dedo anelar
      case 'r':
	 if (anelar < 90)
         anelar = (anelar + 5) % 360;
         glutPostRedisplay();
         break;
      case 'R':
	 if (anelar > 0)
         anelar = (anelar - 5) % 360;
         glutPostRedisplay();
         break;
	 
      //dedo mindinho
      case 't':
	 if (mindinho < 90)
         mindinho = (mindinho + 5) % 360;
         glutPostRedisplay();
         break;
      case 'T':
	 if (mindinho > 0)
         mindinho = (mindinho - 5) % 360;
         glutPostRedisplay();
	 break;

      //toda a mão
      case 'c':
         if (polegar < 90)
         polegar = (polegar + 5) % 360;
         if (apontar < 90)
         apontar = (apontar + 5) % 360;
         if (meio < 90)
         meio = (meio + 5) % 360;
         if (anelar < 90)
         anelar = (anelar + 5) % 360;
         if (mindinho < 90)
         mindinho = (mindinho + 5) % 360;
         glutPostRedisplay();
         break;
      case 'C':
         if (polegar > 0)
         polegar = (polegar - 5) % 360;
         if (apontar > 0)
         apontar = (apontar - 5) % 360;
         if (meio > 0)
         meio = (meio - 5) % 360;
         if (anelar > 0)
         anelar = (anelar - 5) % 360;
	 if (mindinho > 0)
         mindinho = (mindinho - 5) % 360;
         glutPostRedisplay();
	 break;

      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   
   GLfloat luzAmbiente[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat luzDifusa[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat posicaoLuz[4] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 60;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
   
   loadBMP("pele.bmp");
  
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (sWidth, sHeight); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("braço");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
