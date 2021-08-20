#include <iostream>
#include <GL/glut.h>  //include GLUT library. Also includes gl.h glu.h, and glx.h automatically
#include <string.h>   //for using string functions
#include <fstream>

 using namespace std;

//generating the x y coordinates of obstacle. For x, each of the blocks will be 200px apart and random 50 values of y are placed into the array
float xObstacle[50];
float yObstacle[50] = {-350,350,70,-45,100,-200,250,89,30,-150,-300,130,-90,-255,285,20,-30,310,190,-110,-350,350,70,-45,100,-200,250,89,30,-150,-300,130,-90,-255,285,20,-30,310,190,-110,30,-150,-300,130,-90,-255,285,20,-30,310};
int obstacleAlive[50]; // to check the status of obstacles - alive=1, dead=0

//generating the x y coordinates of yellow life and score objects. For x, each of the blocks will be 400px apart and random 10 values of y are placed into the array
float xLife[10];
float yLife[10] = {320,-390,-30,65,-130,210,-270,-59,-30,100};
int lifeAcquired[10];  // to check the status of yellow objects - captured=1, not captured=0

//generating the x y coordinates of brown obstacles. For x, each of the blocks will be 1200px apart and random 9 values of y are placed into the array
float xBludger[9];
float yBludger[9] = {380,-130,200,30,-200,290,130,-250,-70};
int bludgerHit[9];    // to check the status of brown obstacles - not hit=0, hit=1

float transFactor, transFactor2, transFactor3, transFactor4;  //translation factor

////main part of player. Hitting this past of the player will cause points to be increased or decreased
float x1Player, x2Player, x3Player, x4Player;
float y1Player, y2Player, y3Player, y4Player;

//Character design
float pcx1, pcx2, pcx3, pcx4, pcy1, pcy2, pcy3, pcy4;
float pbx1, pbx2, pbx3, pbx4, pby1, pby2, pby3, pby4;
float phx1, phx2, phx3, phx4, phy1, phy2, phy3, phy4;

//Broom
float bsx1, bsx2, bsx3, bsx4;
float bsy1, bsy2, bsy3, bsy4;
float bbx1, bbx2, bbx3, bbx4;
float bby1, bby2, bby3, bby4;

int pauseFlag ;

int score,total;

int gameLevel;

int healthLife;
float xHealthBarStart;		//Health bar starting coordinate
//Health Bar
float hbx1, hbx2, hbx3, hbx4, hby1, hby2, hby3, hby4;

bool mButtonPressed;

void gameOverScreen();
void backGround();

void setup()
{
    glClear(GL_COLOR_BUFFER_BIT);       //clear buffers currently enabled for color writing to preset values
    glClearColor(0.0, 0.0, 0.0, 0.0);    //initialize background color - R, G, B, opacity
	glLoadIdentity();                   //Reset the drawing perspective. To fix proper dimensions in relation to the frame with identity matrix
	glMatrixMode(GL_MODELVIEW);          //Applies subsequent matrix operations to the modelview matrix stack.
}

void valuesInitialize()
{
    transFactor = 1.0;
    transFactor2 = 1.0;
    transFactor3 = 1.0;
    transFactor4 = 1.0;

    ///main part of player
    x1Player = -0.75f;
    x2Player = -0.625f;
    x3Player = -0.5f;
    x4Player = -0.625f;

    y1Player = -0.68f;
    y2Player = -0.53f;
    y3Player = -0.68f;
    y4Player = -0.83f;

    ///Character design starting coordinates
    pcx1 = -0.77f;
    pcx2 = -0.74f;
    pcx3 = -0.75f;
    pcx4 = -0.76f;
    pcy1 = -0.60f;
    pcy2 = -0.60f;
    pcy3 = -0.53f;
    pcy4 = -0.53f;

    pbx1 = -0.80f;
    pbx2 = -0.75f;
    pbx3 = -0.75f;
    pbx4 = -0.76f;
    pby1 = -0.71f;
    pby2 = -0.71f;
    pby3 = -0.60f;
    pby4 = -0.60f;

    phx1 = -0.71f;
    phx2 = -0.70f;
    phx3 = -0.75f;
    phx4 = -0.77f;
    phy1 = -0.69f;
    phy2 = -0.69f;
    phy3 = -0.63f;
    phy4 = -0.63f;

    bsx1 = -0.9f;
    bsx2 = -0.599f;
    bsx3 = -0.599f;
    bsx4 = -0.9f;
    bsy1 = -0.7f;
    bsy2 = -0.7f;
    bsy3 = -0.68f;
    bsy4 = -0.68f;

    bbx1 = -0.95f;
    bbx2 = -0.9f;
    bbx3 = -0.9f;
    bbx4 = -0.95f;
    bby1 = -0.75f;
    bby2 = -0.70f;
    bby3 = -0.68f;
    bby4 = -0.63f;

    pauseFlag = 0;

    score = 0;
    total = 0;
    gameLevel = 1;

    healthLife = 1000;
    xHealthBarStart = 1000;		//Health bar starting coordinate
    ///Health Bar
    hbx1 = -.7f;
    hbx2 = -.5f;
    hbx3 = -.5f;
    hbx4 = -.7f;

    hby1 = .75f;
    hby2 = .75f;
    hby3 = .8f;
    hby4 = .8f;

    mButtonPressed = false;
}

float getX(int val)  //to adjust with screen width
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    float frac = (float)val/((float)width/2);
    return frac;
}

float getY(int val)   //to adjust with screen height
{
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float frac = (float)val/((float)height/2);
    return frac;
}

void createObstacleArray()
{

    xObstacle[0]= 10000;
    for (int i = 0; i<50; i++)
    {
        xObstacle[i+1]=xObstacle[i]-200;
        obstacleAlive[i] = 1;
    }
}

void drawObstacle(int i)
{
    glColor3ub(29,152,60);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transFactor,0,0);
        glBegin(GL_QUADS);
            glVertex2f(getX(xObstacle[i]),getY(yObstacle[i]));
            glVertex2f(getX(xObstacle[i]+50),getY(yObstacle[i]));
            glVertex2f(getX(xObstacle[i]+50),getY(yObstacle[i]+50));
            glVertex2f(getX(xObstacle[i]),getY(yObstacle[i]+50));
        glEnd();
    glPopMatrix();
}


void createLifeArray()
{
    xLife[0]= 4000;
    for (int i = 0; i<10; i++)
    {
        xLife[i+1]=xLife[i]-400;
        lifeAcquired[i] = 0;
    }
}

void drawLife(int i)
{
     glColor3f(1.0f, 0.75f, 0.0f);
     glPushMatrix();
         glTranslatef(getX(xLife[i]) , getY(yLife[i]) ,0);
         glTranslatef(transFactor2, 0, 0);
         glScalef(1,1,1);
         glutSolidSphere(0.05,40,10);
     glPopMatrix();
}


void createBludgerArray()
{
    xBludger[0]= 6000;
    for (int i = 0; i<9; i++)
    {
        xBludger[i+1]=xBludger[i]-1200;
        bludgerHit[i] = 0;
    }
}

void drawBludger(int i)
{
     glColor3ub(150, 92, 62);
     glPushMatrix();
         glTranslatef(getX(xBludger[i]) , getY(yBludger[i]) ,0);
         glTranslatef(transFactor3, 0,0);
         glScalef(1,1,1);
         glutSolidSphere(0.09,50,20);
     glPopMatrix();
}


void drawHealthBar()
{
    glColor3f(0.0,0.0,0.0);
    glPointSize(5.0);
    glBegin(GL_LINE_LOOP);
         glVertex2f(-0.701f, 0.75f);
         glVertex2f(-0.4999f, 0.75f);
         glVertex2f(-0.4999f, 0.8f);
         glVertex2f(-0.701f, 0.8f);
         glVertex2f(-0.701f, 0.75f);
    glEnd();

     if(hbx1< -0.7f || hbx3<-0.7f)
     {
         gameOverScreen();
     }

     else if(hbx2<=-.65f || hbx3<=-.65f)
     {
         glColor3f(1.0,0.0,0.0);
     }
     else
     {
        glColor3f(0.0,1.0,0.0);
     }
     glBegin(GL_QUADS);
         glVertex2f(hbx1, hby1);
         glVertex2f(hbx2, hby2);
         glVertex2f(hbx3, hby3);
         glVertex2f(hbx4, hby4);
    glEnd();
}


void CheckForHits(float oFactor, float lFactor, float bFactor1, float bFactor2)
{
    for (int i = 0; i<50; i++)
    {
        if(obstacleAlive[i] == 1 && ((getX(xObstacle[i])+oFactor < x3Player) && (getX(xObstacle[i])+oFactor > x1Player) && (getY(yObstacle[i]) < y2Player) && (getY(yObstacle[i]) > y4Player) ))
        {
            obstacleAlive[i] = 0;
            if(healthLife>=0)
            {
                healthLife-=5;
                hbx2-=((5/xHealthBarStart)*0.2);
                hbx3-=((5/xHealthBarStart)*0.2);
                drawHealthBar();
            }
            break;
        }
    }

    for (int i = 0; i<10; i++)
    {
        if(((getX(xLife[i])+lFactor < x3Player) && (getX(xLife[i])+lFactor > x1Player) && (getY(yLife[i]) < y2Player) && (getY(yLife[i]) > y4Player) ))
        {
            lifeAcquired[i] = 1;
            score +=10;
            total +=10;
            if(healthLife<1000)
            {
                healthLife+=10;
                hbx2+=((10/xHealthBarStart)*0.2);
                hbx3+=((10/xHealthBarStart)*0.2);
                drawHealthBar();
            }
            break;
        }
    }

    if(gameLevel >= 2)
    {
        for (int i = 0; i<9; i++)
        {
            if(((getX(xBludger[i])+bFactor1 < x3Player) && (getX(xBludger[i])+bFactor1 > x1Player) && (getY(yBludger[i]) < y2Player) && (getY(yBludger[i]) > y4Player) ))
            {
                bludgerHit[i] = 1;
                if(healthLife>=0)
                {
                    healthLife-=20;
                    hbx2-=((20/xHealthBarStart)*0.2);
                    hbx3-=((20/xHealthBarStart)*0.2);
                    drawHealthBar();
                }
                break;
            }
        }
    }
}

void sPrint( float x, float y, char *st)     //text printing function
{
    int l,i;

    l=strlen( st );                // see how many characters are in text string.
    glColor3f(1.0,0.0,0.7);
    glRasterPos2f( x, y);           // location to start printing text
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}

void menu() //the first scene when game starts
{
    transFactor2 = 0; transFactor=0; transFactor3=0; transFactor4=0; //to stop all animation before game starts
    setup();

    glColor3ub(255,255,0);
	glBegin(GL_POLYGON);               //Border
		glVertex2f(getX(-630),getY(-300));
		glVertex2f(getX(630),getY(-300));
		glVertex2f(getX(630),getY(300));
		glVertex2f(getX(-630),getY(300));
	glEnd();

	sPrint(getX(-300),getY(-50),"  Press ESC or right-click mouse to EXIT ");
	sPrint(getX(-300),getY(50),"  Press ENTER or left-click mouse to Start Game ");
	sPrint(getX(-300),getY(0),"  Press P to pause the Game ");
	glutSwapBuffers();
}

void pauseScreen()
{
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(getX(-130),getY(-80));
        glVertex2f(getX(130),getY(-80));
        glVertex2f(getX(130),getY(50));
        glVertex2f(getX(-130),getY(50));
    glEnd();

    sPrint(getX(-50),getY(0),"  PAUSED ");
    sPrint(getX(-90),getY(-30),"  Press P to resume ");
}

void backGround()
{
    ///Background Design
    //setup();

    ///First Part
     for(int i=-400;i<400;i+=100){
            for(int j=-700;j<650;j+=250){
                glColor3ub(185,122,87);
                glBegin(GL_QUADS);
                    glVertex2f(getX(j), getY(i+50));
                    glVertex2f(getX(j+150), getY(i+50));
                    glVertex2f(getX(j+150), getY(i));
                    glVertex2f(getX(j), getY(i));
                glEnd();

                ///Line
                glColor3ub(0,0,0);
                glBegin(GL_LINES);
                    glVertex2f(getX(j+150), getY(i));
                    glVertex2f(getX(j+150), getY(i+50));
                glEnd();
            }
     }

     for(int i=-400;i<400;i+=100){
            for(int j=-550;j<650;j+=250){
                glColor3ub(98,61,40);
                glBegin(GL_QUADS);
                    glVertex2f(getX(j), getY(i+50));
                    glVertex2f(getX(j+100), getY(i+50));
                    glVertex2f(getX(j+100), getY(i));
                    glVertex2f(getX(j), getY(i));
                glEnd();
                glColor3ub(0,0,0);
                glBegin(GL_LINES);
                    glVertex2f(getX(j+100), getY(i));
                    glVertex2f(getX(j+100), getY(i+50));
                glEnd();
            }
     }

     ///Second Part
     for(int i=-350;i<400;i+=100){
            for(int j=-700;j<650;j+=250){
                glColor3ub(98,61,40);
                glBegin(GL_QUADS);
                    glVertex2f(getX(j), getY(i+50));
                    glVertex2f(getX(j+100), getY(i+50));
                    glVertex2f(getX(j+100), getY(i));
                    glVertex2f(getX(j), getY(i));
                glEnd();
                glColor3ub(0,0,0);
                glBegin(GL_LINES);
                    glVertex2f(getX(j+100), getY(i));
                    glVertex2f(getX(j+100), getY(i+50));
                glEnd();
            }
     }

     for(int i=-350;i<400;i+=100){
            for(int j=-600;j<850;j+=250){
                glColor3ub(185,122,87);
                glBegin(GL_QUADS);
                    glVertex2f(getX(j), getY(i+50));
                    glVertex2f(getX(j+150), getY(i+50));
                    glVertex2f(getX(j+150), getY(i));
                    glVertex2f(getX(j), getY(i));
                glEnd();
                glColor3ub(0,0,0);
                glBegin(GL_LINES);
                    glVertex2f(getX(j+150), getY(i));
                    glVertex2f(getX(j+150), getY(i+50));
                glEnd();
            }
     }

     ///Black Lines
     for(int i=-400;i<400;i+=50)
     {
         glColor3ub(0,0,0);
         glPointSize(2.0);
            glBegin(GL_LINES);
                glVertex2f(getX(-700), getY(i));
                glVertex2f(getX(700), getY(i));
            glEnd();
     }

     ///Door Side Wall
     for(int i=-150;i<150;i+=280){
        for(int j=-400;j<400;j+=100){
            glColor3ub(160,82,45);
            glBegin(GL_QUADS);
                glVertex2f(getX(i), getY(j));
                glVertex2f(getX(i+20), getY(j));
                glVertex2f(getX(i+20), getY(j+100));
                glVertex2f(getX(i), getY(j+100));
            glEnd();
            glColor3ub(0,0,0);
            glBegin(GL_LINES);
                glVertex2f(getX(i), getY(j));
                glVertex2f(getX(i+20), getY(j));
            glEnd();
        }
     }

     ///Door
     glColor3ub(166,128,100);
     glBegin(GL_QUADS);
         glVertex2f(getX(-130), getY(-400));
         glVertex2f(getX(130), getY(-400));
         glVertex2f(getX(130), getY(400));
         glVertex2f(getX(-130), getY(400));
     glEnd();

     ///Door Black Line
     for(int i=-110;i<130;i+=20)
     {
         glColor3ub(0,0,0);
         glPointSize(2.0);
            glBegin(GL_LINES);
            glVertex2f(getX(i), getY(-400));
            glVertex2f(getX(i), getY(400));
        glEnd();
     }

    ///Lock
     glColor3ub(60,60,60);
     glBegin(GL_QUADS);
         glVertex2f(getX(-105), getY(-140));
         glVertex2f(getX(-90), getY(-140));
         glVertex2f(getX(-90), getY(-110));
         glVertex2f(getX(-105), getY(-110));
     glEnd();
     glColor3ub(0,0,0);
     glBegin(GL_QUADS);
         glVertex2f(getX(-100), getY(-130));
         glVertex2f(getX(-95), getY(-130));
         glVertex2f(getX(-95), getY(-120));
         glVertex2f(getX(-100), getY(-120));
     glEnd();

     ///Key
     glColor3ub(30,30,30);
     glBegin(GL_QUADS);
         glVertex2f(getX(-98), getY(-124));
         glVertex2f(getX(-70), getY(-124));
         glVertex2f(getX(-70), getY(-126));
         glVertex2f(getX(-98), getY(-126));
     glEnd();
     glColor3ub(30,30,30);
     glBegin(GL_QUADS);
         glVertex2f(getX(-72), getY(-125));
         glVertex2f(getX(-60), getY(-132));
         glVertex2f(getX(-60), getY(-116));
         glVertex2f(getX(-72), getY(-125));
     glEnd();
}

void gameInitialize()
{
    setup();
    glPointSize(1.0);
	char temp[40];

	backGround();

	sprintf(temp,"SCORE = %d",score);
	glPushMatrix();
	    sPrint(getX(-300),getY(300),temp);
	glPopMatrix();

	sprintf(temp,"LEVEL = %d",gameLevel);
	glPushMatrix();
	    sPrint(getX(10),getY(300),temp);
	glPopMatrix();

	sprintf(temp,"LIFE = %d",healthLife);
	glPushMatrix();
	    sPrint(getX(-460),getY(300),temp);
	glPopMatrix();

	//Health Bar
    drawHealthBar();

	for(int i = 0; i<50; i++)
    {
        if(obstacleAlive[i] == 1)
        {
            drawObstacle(i);
        }
    }
    for(int i = 0; i<10; i++)
    {
        if(lifeAcquired[i] == 0)
        {
            drawLife(i);
        }
    }

    if (gameLevel >= 2)
    {
        for(int i = 0; i<9; i++)
        {
            if(bludgerHit[i] == 0)
            {
                drawBludger(i);
            }
        }
    }

    if (pauseFlag == 1)
    {
        pauseScreen();
    }

    ///Character Design Layout

    ///Broom stick
     glColor3ub(255,255,74);
     glBegin(GL_QUADS);
         glVertex2f(bsx1, bsy1);
         glVertex2f(bsx2, bsy2);
         glVertex2f(bsx3, bsy3);
         glVertex2f(bsx4, bsy4);
     glEnd();

     ///Broom main
     glColor3ub(255,128,64);
     glBegin(GL_QUADS);
         glVertex2f(bbx1, bby1);
         glVertex2f(bbx2, bby2);
         glVertex2f(bbx3, bby3);
         glVertex2f(bbx4, bby4);
     glEnd();

     ///Cap
     glColor3ub(128,0,0);
     glBegin(GL_QUADS);
         glVertex2f(pcx1, pcy1);
         glVertex2f(pcx2, pcy2);
         glVertex2f(pcx3, pcy3);
         glVertex2f(pcx4, pcy4);
     glEnd();


     ///Body
     glColor3ub(0,0,0);
     glBegin(GL_QUADS);
         glVertex2f(pbx1, pby1);
         glVertex2f(pbx2, pby2);
         glVertex2f(pbx3, pby3);
         glVertex2f(pbx4, pby4);
     glEnd();

     ///Hand
     glColor3ub(0,0,0);
     glBegin(GL_QUADS);
         glVertex2f(phx1, phy1);
         glVertex2f(phx2, phy2);
         glVertex2f(phx3, phy3);
         glVertex2f(phx4, phy4);
     glEnd();

    //main part of player

    glColor3ub(168,0,0);
     glBegin(GL_QUADS);
         glVertex2f(x1Player, y1Player);
         glVertex2f(x2Player, y2Player);
         glVertex2f(x3Player, y3Player);
         glVertex2f(x4Player, y4Player);
     glEnd();

     glColor3ub(242,231,0);
     glBegin(GL_QUADS);
         glVertex2f((x1Player+0.03f), y1Player);
         glVertex2f(x2Player, (y2Player-0.03f));
         glVertex2f((x3Player-0.03f), y3Player);
         glVertex2f(x4Player, (y4Player+0.03f));
     glEnd();

     if(healthLife<0)
     {
        ofstream myfile;
          myfile.open ("score.txt");
          myfile << "again.\n",score;
          myfile.close();
          gameOverScreen();
     }
    glutSwapBuffers();
}

void update(int value)
{
    if(pauseFlag==0)
    {
        transFactor-=0.01f;
        if(transFactor<-getX(10500))
        {
            transFactor = 1 * getX(400*2);
            for(int i=0; i<10; i++)
            {
                lifeAcquired[i] = 0;
            }
        }
    }

    if(pauseFlag==0)
    {
        transFactor2-=0.005f;
        if(transFactor2<-getX(4500))
        {
            transFactor2 = 1 * getX(400*2);
        }
    }

    if(score == 2000)
    {
        gameLevel = 2;
        score += 200;
    }

    if(pauseFlag==0)
    {
        if(gameLevel>=2)
        {
            transFactor3-=0.05f;
            if(transFactor3<-getX(6200))
            {
                transFactor3 = 1 * getX(600*2);
            }
        }
    }

    createObstacleArray();
    //createLifeArray();
    createBludgerArray();

    CheckForHits(transFactor, transFactor2, transFactor3, transFactor4);

    glutPostRedisplay();
    glutTimerFunc(25, update, 0); //Notify GLUT to call update again in 25 milliseconds

}

void gameOverScreen()
{
    setup();
    transFactor2 = 0; transFactor=0; transFactor3=0; transFactor4=0;

    glColor3ub(255,255,0);
	glBegin(GL_POLYGON);               //Border
		glVertex2f(getX(-630),getY(-300));
		glVertex2f(getX(630),getY(-300));
		glVertex2f(getX(630),getY(300));
		glVertex2f(getX(-630),getY(300));
	glEnd();

	char temp[40];

	sprintf(temp,"You Have Scored : %d",total);
	sPrint(getX(-300),getY(150),"  GAME OVER !!!");
	sPrint(getX(-300),getY(100),temp);
	sPrint(getX(-300),getY(50)," Press ENTER to RESTART a New Game ");
	sPrint(getX(-300),getY(0),"  Press ESC to EXIT ");

	glFlush();
}

void specialKeys(int key, int x, int y) //function for moving player across the screen using up, down, left, right keys
{
    if (pauseFlag == 0)
    {
       switch (key)
       {
        case GLUT_KEY_UP:

          bsy1+=0.01f;
          bsy2+=0.01f;
          bsy3+=0.01f;
          bsy4+=0.01f;
          bby1+=0.01f;
          bby2+=0.01f;
          bby3+=0.01f;
          bby4+=0.01f;

          y1Player += 0.01f;
          y2Player += 0.01f;
          y3Player += 0.01f;
          y4Player += 0.01f;

          pby1 += 0.01f;
          pby2 += 0.01f;
          pby3 += 0.01f;
          pby4 += 0.01f;
          pcy1 += 0.01f;
          pcy2 += 0.01f;
          pcy3 += 0.01f;
          pcy4 += 0.01f;
          phy1 += 0.01f;
          phy2 += 0.01f;
          phy3 += 0.01f;
          phy4 += 0.01f;
          break;

        case GLUT_KEY_DOWN:

          bsy1-=0.01f;
          bsy2-=0.01f;
          bsy3-=0.01f;
          bsy4-=0.01f;
          bby1-=0.01f;
          bby2-=0.01f;
          bby3-=0.01f;
          bby4-=0.01f;

          y1Player -= 0.01f;
          y2Player -= 0.01f;
          y3Player -= 0.01f;
          y4Player -= 0.01f;

          pby1 -= 0.01f;
          pby2 -= 0.01f;
          pby3 -= 0.01f;
          pby4 -= 0.01f;
          pcy1 -= 0.01f;
          pcy2 -= 0.01f;
          pcy3 -= 0.01f;
          pcy4 -= 0.01f;
          phy1 -= 0.01f;
          phy2 -= 0.01f;
          phy3 -= 0.01f;
          phy4 -= 0.01f;
          break;

        case GLUT_KEY_RIGHT:

          bsx1+=0.01f;
          bsx2+=0.01f;
          bsx3+=0.01f;
          bsx4+=0.01f;
          bbx1+=0.01f;
          bbx2+=0.01f;
          bbx3+=0.01f;
          bbx4+=0.01f;

          x1Player += 0.01f;
          x2Player += 0.01f;
          x3Player += 0.01f;
          x4Player += 0.01f;

          pbx1 += 0.01f;
          pbx2 += 0.01f;
          pbx3 += 0.01f;
          pbx4 += 0.01f;
          pcx1 += 0.01f;
          pcx2 += 0.01f;
          pcx3 += 0.01f;
          pcx4 += 0.01f;
          phx1 += 0.01f;
          phx2 += 0.01f;
          phx3 += 0.01f;
          phx4 += 0.01f;
          break;

        case GLUT_KEY_LEFT:

          bsx1-=0.01f;
          bsx2-=0.01f;
          bsx3-=0.01f;
          bsx4-=0.01f;
          bbx1-=0.01f;
          bbx2-=0.01f;
          bbx3-=0.01f;
          bbx4-=0.01f;

          x1Player -= 0.01f;
          x2Player -= 0.01f;
          x3Player -= 0.01f;
          x4Player -= 0.01f;

          pbx1 -= 0.01f;
          pbx2 -= 0.01f;
          pbx3 -= 0.01f;
          pbx4 -= 0.01f;
          pcx1 -= 0.01f;
          pcx2 -= 0.01f;
          pcx3 -= 0.01f;
          pcx4 -= 0.01f;
          phx1 -= 0.01f;
          phx2 -= 0.01f;
          phx3 -= 0.01f;
          phx4 -= 0.01f;
          break;
       }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13:     // Enter key
            score = 100;
            valuesInitialize();
            glutDisplayFunc(gameInitialize);
            break;
        case 27:     // ESC key
            exit(0);
            break;
        case 'p':
            if(pauseFlag==0)
            {
                pauseFlag = 1;
            }
            else
            {
                pauseFlag = 0;
            }
            break;
    }
}

void mouseClick(int buttonPressed ,int state ,int x, int y) {

        if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
		    mButtonPressed = true;
		    valuesInitialize();
		    glutDisplayFunc(gameInitialize);
        }
		else if(buttonPressed == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
            mButtonPressed = false;
            exit(0);
		}
}

int main(int argc, char** argv) {                      //main function. The code initializes from here
	glutInit(&argc, argv);                             //initialize the tools of glut - internal resources
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);       //sets initial display mode - GLUT_DOUBLE means double buffered window and GLUT_RGB to select a color index mode window
	glutInitWindowSize(1350,690);                      //set window size to 1350 and 690 pixels in the x and y direction respectively
	glutInitWindowPosition(0,0);                       //open window at 0,0 point of display. For GLUT it is top-left
	glutCreateWindow("Obstacle game");                 //set the window name

	createLifeArray();
	glutDisplayFunc(menu);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);


	glutTimerFunc(25, update, 0);

	glutMainLoop(); //infinite loop holds output display
	return 0;
}
