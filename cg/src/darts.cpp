#include <GL/glut.h>

#include "point.cpp"
#include "text.cpp"
#include "circle.cpp"
#include "rectangle.cpp"

#include "../include/darts.h"

// Global variables
int roundNum = 0;
int score = 0;
int powerBarSpeed = 3;
bool powerBarActive = false;
bool powerBarUp = false;
bool dartActive = false;
bool throwActive = false;

// Points
Point gameRoundPt(280, 370);
Point gameScorePt(284, 350);
Point targetCenterPt(152, 570);
Point dartCenterPt(152, 0);
Point powerBarStartPt(0, 0);
Point powerBarEndPt(25, 0);
Point ByPt(480,350);
Point AmitPt(480,330);
Point AgathaPt(480,310);
Point AkshitaPt(480,290);
Point AmulyaPt(480,270);

// Text
Text gameRound(gameRoundPt, "Round: " + std::to_string(roundNum));
Text gameScore(gameScorePt, "Score: " + std::to_string(score));
Text By(ByPt," ");
Text Amit(AmitPt," ");
Text Agatha(AgathaPt," ");
Text Akshita(AkshitaPt," ");
Text Amulya(AmulyaPt," ");

// Circles
Circle firstTarget(targetCenterPt, 120); // Largest target
Circle secondTarget(targetCenterPt, 100);
Circle thirdTarget(targetCenterPt, 80);
Circle fourthTarget(targetCenterPt, 60);
Circle fifthTarget(targetCenterPt, 40);
Circle sixthTarget(targetCenterPt, 20); // Smallest target
Circle dart(dartCenterPt, 5);

// Rectangles
Rectangle powerBar(powerBarStartPt, powerBarEndPt.getX(), powerBarEndPt.getY());

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
}

void display(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  gameRound.setText("Round: " + std::to_string(roundNum));
  gameRound.setColor(1, 1, 1);
  gameRound.draw();
  gameScore.setText("Score: " + std::to_string(score));
  gameScore.setColor(1, 1, 1);
  gameScore.draw();
  By.setText("By:");
  By.setColor(1,1,1);
  By.draw();
  Amit.setText("Amit Kumar Gupta");
  Amit.setColor(0, 0, 255);
  Amit.draw();
  Agatha.setText("Agatha Coutinho");
  Agatha.setColor(0, 0, 255);
  Agatha.draw();
  Akshita.setText("Akshita Mishra");
  Akshita.setColor(0, 0, 255);
  Akshita.draw();
  Amulya.setText("Amulya Yadav");
  Amulya.setColor(0,0,255);
  Amulya.draw();







  // Targets
  firstTarget.setFillColor(75, 0, 130);
  firstTarget.draw();
  secondTarget.setFillColor(0, 0, 255);
  secondTarget.draw();
  thirdTarget.setFillColor(0, 255, 0);
  thirdTarget.draw();
  fourthTarget.setFillColor(255, 255, 0);
  fourthTarget.draw();
  fifthTarget.setFillColor(150, 157, 140);
  fifthTarget.draw();
  sixthTarget.setFillColor(0, 0, 0);
  sixthTarget.draw();

  // Dart
  dart.setCenterPt(dartCenterPt);
  dart.setFillColor(1, 0, 0);
  dart.draw();

  // Power bar
  powerBar.setHeight(powerBarEndPt.getY());
  powerBar.setFillColor(0, 13, 255);
  powerBar.draw();

  glFlush();
  glutSwapBuffers();
}

void getKeyboardInput(unsigned char c, int x, int y)
{
  switch (c)
  {
    // Activate power bar
    case ' ':
      if (!powerBarActive && !dartActive && !throwActive)
      {
        roundNum++;
        dartCenterPt.setY(0);
        powerBarEndPt.setY(0);
        powerBarActive = true;
      }
      break;
    // Stop power bar
    case 's':
      if (powerBarActive && !dartActive && !throwActive)
      {
        powerBarActive = false;
        dartActive = true;
      }
      break;
    // Throw dart
    case 't':
      if (!powerBarActive && dartActive && !throwActive)
      {
        powerBarSpeed += 3;
        throwActive = true;
      }
      break;
    // Quit
    case 'q':
      exit(0);
      break;
  }
}

void animate(int val)
{
  // Power bar animation
  if (powerBarActive && !dartActive && !throwActive)
  {
    if (powerBarUp)
    {
      powerBarEndPt.setY(powerBarEndPt.getY() + powerBarSpeed);
      if (powerBarEndPt.getY() >= 810)
      {
        powerBarUp = false;
      }
    }
    else
    {
      powerBarEndPt.setY(powerBarEndPt.getY() - powerBarSpeed);
      if (powerBarEndPt.getY() <= 0)
      {
        powerBarUp = true;
      }
    }
  }
  // Dart animation
  if (!powerBarActive && dartActive && throwActive == true)
  {
    if (dartCenterPt.getY() < powerBarEndPt.getY())
    {
      dartCenterPt.setY(powerBarEndPt.getY());
    }
    if (dartCenterPt.getY() == powerBarEndPt.getY())
    {
      dartActive = false;
      throwActive = false;
      updateScore(dartCenterPt.getY());
    }
  }

  glutPostRedisplay();
  glutTimerFunc(ANIMATION_MSEC, animate, 0);
}

void updateScore(float dartY)
{

  if ((dartY >= (sixthTarget.getCenterPtY() - sixthTarget.getRadius())) && (dartY <= (sixthTarget.getCenterPtY() + sixthTarget.getRadius())))
  {
    score += 6;
  }
  else if ((dartY >= (fifthTarget.getCenterPtY() - fifthTarget.getRadius())) && (dartY <= (fifthTarget.getCenterPtY() + fifthTarget.getRadius())))
  {
    score += 5;
  }
  else if ((dartY >= (fourthTarget.getCenterPtY() - fourthTarget.getRadius())) && (dartY <= (fourthTarget.getCenterPtY() + fourthTarget.getRadius())))
  {
    score += 4;
  }
  else if ((dartY >= (thirdTarget.getCenterPtY() - thirdTarget.getRadius())) && (dartY <= (thirdTarget.getCenterPtY() + thirdTarget.getRadius())))
  {
    score += 3;
  }
  else if ((dartY >= (secondTarget.getCenterPtY() - secondTarget.getRadius())) && (dartY <= (secondTarget.getCenterPtY() + secondTarget.getRadius())))
  {
    score += 2;
  }
  else if ((dartY >= (firstTarget.getCenterPtY() - firstTarget.getRadius())) && (dartY <= (firstTarget.getCenterPtY() + firstTarget.getRadius())))
  {
    score += 1;
  }
  else
  {
    score += 0;
  }
}
