/*
 * Square hitting corners in time
*/
#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <time.h>

bool paused = false;
const float factor = 50;
Vector2 window = { 16*factor, 9*factor };

void bounce (Vector2 window, Rectangle *rec, Vector2 *velocity, Color *color);
int sign (int num);
float sigmoid (float num);

int main (void) {
    SetConfigFlags (FLAG_WINDOW_RESIZABLE);
    SetConfigFlags (FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    const char* text = "Hello World";
    const float fontSize = 100;
    InitWindow (window.x, window.y, text);
    SetRandomSeed(clock());
    Rectangle rec = {
        GetRandomValue(0, window.x),
        GetRandomValue (0, window.y),
        window.x/10,
        window.x/10
    };
    Color color = ColorFromHSV(
        GetRandomValue (0, 360),
        1.0f,
        1.0f
    );
    Vector2 velocity = {100, 100}, func;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        window.x = GetRenderWidth();
        window.y = GetRenderHeight();
        func.x = sigmoid(rec.x/window.x - 1);
        func.y = sigmoid(rec.y/window.y - 1);
        if (!paused) {
	        rec.x += velocity.x*func.x*dt;
	        rec.y += velocity.y*func.y*dt;
        }
        bounce(window, &rec, &velocity, &color);
        if (IsKeyPressed (KEY_SPACE))
            paused = !paused;
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(rec, color);
            // DrawCircle(rec.x, rec.y, rec.width, color);
            DrawText(TextFormat("v = (%.3f, %.3f)", velocity.x, velocity.y), 0, 0, fontSize/3, LIME);
            DrawText(TextFormat("f = (%.3f, %.3f)", func.x, func.y), 0, fontSize/3 + 0.01f*window.y, fontSize/3, LIME);
            DrawText (TextFormat("%i FPS", GetFPS()), 0, 2*(fontSize/3+0.01f*window.y), fontSize/3, LIME);
            if (paused) {
                DrawRectangleRec((Rectangle){0, 0, window.x, window.y}, (Color){100, 100, 100, 100});
                const char *pauseText = "Paused!";
	            DrawText (
	                pauseText,
	                window.x/2-(float)MeasureText(pauseText, fontSize)/2,
	                window.y/2-fontSize/2,
	                fontSize,
	                LIME
                );
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void bounce (Vector2 window, Rectangle *rec, Vector2 *velocity, Color *color) {
    Color newColor = ColorFromHSV(GetRandomValue(0, 360), 1.0f, 1.0f);
    if (rec->x > window.x-rec->width) {
        rec->x = window.x-rec->width;
        velocity->x *= -1;
        velocity->y += sign(velocity->y)*1;
        *color = newColor;
    }
    if (rec->x < 0) {
        rec->x = 0;
        velocity->x *= -1;
        velocity->y += sign(velocity->y)*1;
        *color = newColor;
    }
    if (rec->y > window.y-rec->height) {
        rec->y = window.y-rec->height;
        velocity->y *= -1;
        velocity->x += sign(velocity->x)*1;
        *color = newColor;
    }
    if (rec->y < 0) {
        rec->y = 0;
        velocity->y *= -1;
        velocity->x += sign(velocity->x)*1;
        *color = newColor;
    }
}

int sign (int num) {
    if (num < 0) return -1;
    return 1;
}

float sigmoid (float num) {
    return 1/(1+exp(-num));
}