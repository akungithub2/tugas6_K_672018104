#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <time.h>

double view[3]={2,2,12.9};
double look[3]={2,2,2};
int flag=-1;
void steps(void);
void window(void);
void gate(void);
double angle=0,speed=5,maino=0,tro=0,romo=0,mgo=0;

//mendeklarasikan objek kuadrat
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;

GLfloat angle1;

//inisialisasi
void myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1*1366/768,1*1366/768,1,200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//mendefinisikan objek quadric baru
    Cylinder = gluNewQuadric();
	//untuk mengatur gaya gambar
    gluQuadricDrawStyle( Cylinder, GLU_FILL);
	//untuk mengatur normals otomatis
    gluQuadricNormals( Cylinder,GLU_SMOOTH);


    Disk = gluNewQuadric();
    gluQuadricDrawStyle( Disk, GLU_FILL);
    gluQuadricNormals( Disk, GLU_SMOOTH);
	GLfloat gam[]={0.2,.2,.2,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);

}

//mengatur properti material
void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}

//untuk membuat dinding
void wall(double thickness)
{
	glPushMatrix();
	glTranslated(2,.5*thickness,2);
	glScaled(4.0,thickness,4.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void compound(void)
{

	GLfloat ambient[]={1,0,0,1};
	GLfloat specular[]={0,1,1,1};
	GLfloat diffuse[]={.7,.7,.7,1};
	GLfloat shininess[]={50};


	matprop(ambient,diffuse,specular,shininess);
	GLfloat lightIntensity[]={.7,.7,.8,1};
	GLfloat light_position[]={2,6,1.5,0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

}


void fanwing(float winglen)// baling-baling kipas
{
    glPushMatrix();

	glRotated(90,1,0,0);
	glRotated(90,0,1,0);
	glScaled(1,15,1);
	gluCylinder(Cylinder,.01,.01,1,4,1);
	glPopMatrix();
}

void fanbottom() //bagian bawah kipas
{
	glPushMatrix();

	glTranslated(1,3.2,1);
	glPushMatrix();
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .2, .2,.05, 128, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0.00025,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.2,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.05,0);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,.2,.15,.1,128,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.1,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.15,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(120,0,1,0);
	glTranslated(.1,0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(240,0,1,0);
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPopMatrix();
}
void fan(void) //kipas
{	glPushMatrix();
	glTranslated(2.5,1.9,0);
	glScaled(.5,.5,.5);
	GLfloat mat_ambient[]={.5,0,0,1};
	GLfloat mat_specular[]={0,1,1,0};
	GLfloat mat_diffuse[]={0,.502,0,1};
	GLfloat mat_shininess[]={50};


	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


if(flag==-1)
{
	glPushMatrix();
	fanbottom();
	glPopMatrix();
}
else

{

	angle+=speed;
	glPushMatrix();
	glTranslated(1,0,1);
	glRotated(angle,0,1,0);
	glTranslated(-1,0,-1);
	fanbottom();
	glPopMatrix();
}

	glPushMatrix();
	glTranslatef(1,3.3,1);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(1,4,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .006, 0.006, .6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,3.96,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPopMatrix();
	if(flag==1)
		glutPostRedisplay();
}
void cleg(float cllen,float clwid)
{
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,clwid,clwid,cllen,32,32);

}
void sleg(float len,float thk)
{
	glScaled(thk,len,thk);
	glutSolidCube(1);

}
void solar(void)
{
	GLfloat	ambient1[]={.1,.1,.1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={1,1,1,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={-20,4,60,0};
	glLightfv(GL_LIGHT2,GL_POSITION,light_position);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lightIntensity);
	glEnable(GL_LIGHT2);
}

void myclock() //jam
{

	GLfloat mat_ambient[]={.4,.8,.4,1};
	GLfloat mat_specular[]={1,1,1,1};
	GLfloat mat_diffuse[]={0,.749,1,1};
	GLfloat mat_shininess[]={50};
	matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);


	int hour_ticks , sec_ticks;
	glPushMatrix();
	glTranslated(2,3.2,-.02);
	glScaled(.03,.06,.03);


	glPushMatrix(); // bentuk jam
	glTranslatef( 0, 0, 1.0);
	gluDisk(Disk, 0, 7, 32, 16);

	glPopMatrix();
	GLfloat mat_ambien[]={1,0,0,1};
	matprop(mat_ambien,mat_diffuse,mat_specular,mat_shininess);

	glPushMatrix();
	glTranslatef( 0, 0, 1.95);
	gluDisk(Disk, 0, .8, 32, 16);

	glPopMatrix();

	GLfloat	ambient[]={0,0,0,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={0,0,0,1};
  	matprop(ambient,diffuse,specular,mat_shininess);
	// jarum/arah jam
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef( 0, 0, 1.5);
	glRotatef( -(360/12) * (newtime->tm_hour+newtime->tm_min/60.0), 0.0, 0.0, 1.0);

	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.45, 0, 4, 16, 16);
	glPopMatrix();
	GLfloat	ambient1[]={0,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0,0,1,1};
  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	// jarum/arah menit
	glPushMatrix();
	glColor3f(1.0, 0.5, 1.0);
	glTranslatef( 0, 0, 1.25);
	glRotatef( -(360/60) * newtime->tm_min, 0.0, 0.0, 1.0);

	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.4, 0, 6, 16, 16);
	glPopMatrix();

	GLfloat	ambient2[]={1,0,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={1,0,0,1};
  	matprop(ambient2,diffuse2,specular2,mat_shininess);
	// jarum/arah detik
	glPushMatrix();
	glTranslatef( 0, 0, 1);
	glRotatef(-(360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.3, 0, 6, 16, 16);
	glPopMatrix();



	GLfloat	ambient3[]={1,1,1,1};
	GLfloat specular3[]={1,1,1,1};
	GLfloat diffuse3[]={0,0,0,1};
  	matprop(ambient3,diffuse3,specular3,mat_shininess);

	for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
	  {
		glPushMatrix();// Draw next arm axis.
        glTranslatef(0.0, 0.0, 1);
		glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
		glTranslatef( 6.0, 0.0, 0.0);
		glutSolidCube(.8);
		glPopMatrix();
	}

	for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	 {
   	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.1);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(6.0, 0.0, 0.0);
	glutSolidCube(0.25);
	glPopMatrix();
	}


  glPopMatrix();

}

void table(float tabwid,float tablen,float tabthk,float llen,float lthk)
{
    glPushMatrix();
    glPushMatrix();
    glTranslated(0,llen,0);
    glScaled(tabwid,tabthk,tablen);

    glutSolidCube(1);
    glPopMatrix();
    float dist1=.95*tablen/2-lthk/2;
    float dist2=.95*tabwid/2-lthk/2;

    glPopMatrix();
}

void chair(float cblen,float cbwid,float cbthk,float cllen,float clwid)
{
    GLfloat	ambient1[]={.5,1,.5,1};
    GLfloat specular1[]={1,1,1,1};
    GLfloat diffuse1[]={0.5,0.5,0.5,1};
    GLfloat mat_shininess[]={50};

    matprop(ambient1,diffuse1,specular1,mat_shininess);
    glPushMatrix();
    glTranslated(0,cllen,0);

    //dasar kursi
    glPushMatrix();
    glScaled(cblen,cbthk,cbwid);
    glutSolidCube(1);
    glPopMatrix();
    float dist=cblen/2-clwid/2;

    //kaki kursi
    glPushMatrix();
    glTranslated(dist,0,dist);
    cleg(cllen,clwid);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-dist,0,dist);
    cleg(cllen,clwid);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-dist,0,-dist);
    cleg(cllen,clwid);
    glPopMatrix();
    glPushMatrix();
    glTranslated(dist,0,-dist);
    cleg(cllen,clwid);
    glPopMatrix();

    //batangan kursi
    glPushMatrix();
    glTranslated(-.085,-clwid/2,cbwid/3);
    glRotated(90,0,1,0);
    gluCylinder(Cylinder,-clwid,clwid,cblen,32,32);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-.085,clwid/2,-cbwid/3);
    glRotated(90,0,1,0);
    gluCylinder(Cylinder,clwid,clwid,cblen,32,32);
    glPopMatrix();

    //batangan kursi untuk belakang
    glPushMatrix();
    glTranslated(-.085,-clwid/2,cbwid/3); glRotated(-90,1,0,0);
    gluCylinder(Cylinder,clwid,clwid,cllen,32,32);
    glPopMatrix();
    glPushMatrix();

    glTranslated(-.085,-clwid/2,-cbwid/3);
    glRotated(-90,1,0,0);
    gluCylinder(Cylinder,clwid,clwid,cllen,32,32);
    glPopMatrix();

    //alas punggung
    glPushMatrix();
    glTranslated(-cblen/2,cllen/2+cblen/2,0);
    glRotated(90,0,0,1);
    glScaled(cblen,.01,cbwid);
    glutSolidCube(1);
    glPopMatrix(); glPopMatrix();
}
void diningtable()
{

    glPushMatrix();
    glTranslated(3,0,1);
    glScaled(1.5,1.5,1.5);
    table(0.3,0.5,0.25,0.4,0.005);

    glPushMatrix();
    glTranslated(-.1,0,.1);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();

    //kursi kiri belakang
    glPushMatrix();
    glTranslated(-.1,0,-.1);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();
    //kursi depan kanan
    glPushMatrix();
    glTranslated(.1,0,.1);
    glRotated(180,0,1,0);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();
    //kursi belakang kanan
    glPushMatrix();
    glTranslated(.1,0,-.1);

    glRotated(180,0,1,0);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();
    //kursi belakang
    glPushMatrix();
    glTranslated(0,0,-.27);
    glRotated(-90,0,1,0);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();
    //kursi depan
    glPushMatrix();
    glTranslated(0,0,.27);
    glRotated(90,0,1,0);
    chair(.15,.15,.02,.3,.005);
    glPopMatrix();

    glPopMatrix();

}


 void house(void)
{
	GLfloat mat_ambient[]={0,0,1,1};
	GLfloat mat_specular[]={1,0,0,1};
	GLfloat mat_diffuse[]={0,1,.7,1};
	GLfloat mat_shininess[]={90};

	matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);


	GLfloat lightIntensity4[]={.7,.7,.7,.7};
	GLfloat light_position4[]={3,1,.5,1};
	glLightfv(GL_LIGHT6,GL_POSITION,light_position4);
	glLightfv(GL_LIGHT6,GL_DIFFUSE,lightIntensity4);
	glEnable(GL_LIGHT6);


	glPushMatrix();
	glTranslated(0,.15,0);
	//atap
    glPushMatrix();
	glTranslated(-.02*4,3.9,-.01*4-.25);
	glScaled(1.5+.05,1.5,1.1);
	wall(0.08);
	glPopMatrix();


	GLfloat ambient2[]={1,1,0,1};
	GLfloat specular2[]={1,0,0,1};
	GLfloat diffuse2[]={0,0,0,1};
	GLfloat shininess[]={50};
		matprop(ambient2,diffuse2,specular2,shininess);

	//lantai
	glPushMatrix();
	glTranslated(-.02*3,-0.05,-.01*4);
	glScaled(1.5+.01,1.5,7);
	wall(0.08);
	glPopMatrix();



matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
	//dinding kiri
	glPushMatrix();

	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//dinding kanan
	glPushMatrix();

	glTranslated(6,0,0);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();

	//dinding belakang
	glPushMatrix();
	glTranslated(-.08,0,0);
	glScaled(1.5+.02,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

	//dinding di atas pintu utama
	glPushMatrix();
	glTranslated(-0.02,3,4);
	glScaled(.13,.23,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

	//dinding langsung ke pintu
	glPushMatrix();
	glTranslated(.48,0,4);
	glScaled(.68,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

	//dinding langsung ke kotak (yang menyerupai jendela)
	glPushMatrix();
	glTranslated(4.8,0,4);
	glScaled(.3,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

	//dinding di bawah kotak (yang menyerupai jendela)
	glPushMatrix();
	glTranslated(3.2,0,4);
	glScaled(.4,.25,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

	//dinding di atas kotak (yang menyerupai jendela)
	glPushMatrix();
	glTranslated(3.2,3.03,4);
	glScaled(.4,.23,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();

    fan();
    myclock();
    diningtable();
	solar();

	GLfloat	ambient[]={1,0.5,.5,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={0.502, 0.502, 0.000,1};
  	matprop(ambient,diffuse,specular,mat_shininess);

  	//pintu
	glPushMatrix();
	glTranslated(0,0,4);
	glRotated(maino,0,1,0);
	glTranslated(0,0,-4);
	glPushMatrix();
	glTranslated(0,0,4);
	glScaled(.12,.75,1);
	glRotated(-90.0,1,0,0);
	wall(0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,4);
	glScaled(.5,1,.2);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
	glPopMatrix();
	glPopMatrix();

    //lemari

	glPushMatrix();
	glTranslated(0,0,2);
	glScaled(.11,.80,1);
	glRotated(-90.0,1,0,0);
	wall(2);
	glPopMatrix();


	glPopMatrix();
    glPopMatrix();
	glFlush();
}


void display(void)
{
	time(&ltime); // waktu
    newtime = localtime(&ltime); // Konversikan ke waktu setempat
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	gluLookAt(view[0],view[1],view[2],look[0],look[1],look[2],0.0,1.0,0.0);
    compound();
	house();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void Keyboard(unsigned char key,int x,int y)
{

	switch(key)
	{
          //perbesat
	    case 'w':
				view[2]-=.1;
				glutPostRedisplay();
	break;
	//perkecil
	case 's':
				view[2]+=.1;
				glutPostRedisplay();
				break;

    //buka & tutup pintu
	case 'r':
	case 'R':
				if(maino==0)
				  maino=85;
				else
					maino=0;

    //on off kipas
	case 'E':
	case 'e':
				flag*=-1;
				glutPostRedisplay();
	break;
	//sudut padang dari dalam
	case 'q':
	case 'Q':
				view[0]=2.8;
				view[1]=2;
				view[2]=4.8;
				look[0]=2.8;
				look[1]=2;
				look[2]=1;
	break;
	//sudut padang dari atas
	case 'Z':
	case 'z':
				view[0]=6;
				view[1]=12;
				view[2]=10;
				look[0]=2;
				look[1]=4;
				look[2]=2;
	break;
    //sudut padang dari depan
	case 'x':
	case 'X':
				view[0]=2;
				view[1]=2;
				view[2]=12.9;
				look[0]=2;
				look[1]=2;
				look[2]=3;
	break;
	//sudut padang dari belakang
	case 'c':
	case 'C':
				view[0]=1;
				view[1]=6;
				view[2]=-7;
				look[0]=2;
				look[1]=4;
				look[2]=2;
	break;

	}


}
int main(int argc,char**argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1255,657);
	glutInitWindowPosition(100,200);
	glutCreateWindow("ERITS TALAPESSY - 672018104");
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0,0,0,0);
	glutMainLoop();
	return 0;
}
