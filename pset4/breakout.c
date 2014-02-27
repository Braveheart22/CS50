//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// height and width of paddle
#define PADDLE_HEIGHT 4
#define PADDLE_WIDTH 50

// axis paddle moves along
#define PADDLEY (HEIGHT - PADDLE_HEIGHT - 100)

// lives
#define LIVES 3

// initial ball movement speed
#define BALLSPEED 7



// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initGameOver(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc, string argv[])
{
    int godMode = 0;
    // Make sure that we only have 1 argument
    if (argc == 2)
        if (strncmp (argv[1],"GOD", 3) == 0)
            godMode = 1;

    // seed pseudorandom number generator
    srand48(time(NULL));
    
    // initial velocity
    double xvelocity = 2.0;
    double yvelocity = (drand48() * 2.0);
    
    if (yvelocity < .5)
        yvelocity += .5;

    // initial ball movement speed
    int ballSpeed = BALLSPEED;

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // store score (up to 999 with '\0'), we need <= 4 chars
    char score[4];

    //Click to start game.
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        move(ball, xvelocity, yvelocity);
        if (godMode == 1)
            setLocation (paddle, getX(ball) - ((PADDLE_WIDTH - RADIUS) / 2), PADDLEY);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }

        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }

        // fell off bottom edge of window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            int x = (WIDTH / 2) - RADIUS;
            int y = (HEIGHT / 2) - RADIUS;
            setLocation (ball, x, y);
            lives--;
            // wait for click before continuing
            waitForClick();
        }

        // linger before moving again
        pause(ballSpeed);
        
        GObject object = detectCollision(window, ball);

        if (object != NULL)
            if (strcmp (getType (object), "GRect") == 0)
            {
                if (object != paddle)
                {
                    removeGWindow (window, object);
                    bricks--;
                    // convert score to string
                    sprintf(score, "%i", (ROWS * COLS) - bricks);
                    ballSpeed = BALLSPEED - (((ROWS * COLS) - bricks) / 10);
                    setLabel(label, score);
                    // When the score reaches double digits, re-center it 1 character
                    if ((ROWS * COLS) - bricks == 10)
                        setLocation(label, getX(label) - 11, getY(label));
                }

                yvelocity = -yvelocity;
            }

        // check for mouse event
        GEvent event;
        if (godMode != 1)
            event = getNextEvent(MOUSE_EVENT);
        else
            event = NULL;

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure the paddle follows the cursor
                double x = getX(event) - PADDLE_WIDTH / 2;
                if (x < 0)
                    x = 0;
                if (x > (WIDTH - PADDLE_WIDTH))
                    x = WIDTH - PADDLE_WIDTH;

                setLocation(paddle, x, PADDLEY);
            }
        }

    }

    // wait for click before exiting
    initGameOver (window);
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int spacer = 4;
    int topOffset = 50;
    string  color = "BLACK";

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            int width = (WIDTH / COLS) - spacer;
            int height = 10;
            int x = ((WIDTH / COLS) * j) + (spacer / 2);
            int y = (height * i) + (spacer * i) + topOffset;
            GRect brick = newGRect(x, y, width, height);
            setFilled(brick, true);
            // Set the color base on the row
            switch (i)
            {
                case 4:
                    color = "BLUE";
                    break;
                case 3:
                    color = "GREEN";
                    break;
                case 2:
                    color = "YELLOW";
                    break;
                case 1:
                    color = "ORANGE";
                    break;
                case 0:
                    color = "RED";
                    break;
                default:
                    color = "BLACK";
                    break;
            }
            setColor(brick, color);
            add(window, brick);
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS;
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int padleX = (WIDTH / 2) - (PADDLE_WIDTH / 2);
    GRect rect = newGRect(padleX, PADDLEY, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(rect, true);
    setColor(rect, "RED");
    add(window, rect);

    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "GRAY");
    int offset = 20;
    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS - offset;
    setLocation(label, x, y);
    add(window, label);
    setLabel(label, "0");

    return label;
}

/**
 * Instantiates, configures, and returns label for Game Over text.
 */
GLabel initGameOver(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "GRAY");
    int offset = 30;
    // 102 is half the width of the words "Game Over"
    int x = (WIDTH / 2) - 102;
    int y = (HEIGHT / 2) + (RADIUS * 2) + offset;
    setLocation(label, x, y);
    add(window, label);
    setLabel(label, "Game Over");

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
