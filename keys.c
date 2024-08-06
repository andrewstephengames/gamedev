/*
 * Keys controlling a rectangle
*/
#include <raylib.h>
#include <math.h>
#include <time.h>

const float factor = 50;
Vector2 window = { 16*factor, 9*factor };

void keys (Vector2 *position, float distance);
void bounds (Vector2 *position, Rectangle *rec);
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
        GetRandomValue (0, window.x),
        GetRandomValue (0, window.y),
        window.x/10,
        window.x/10
    };
    Color color = ColorFromHSV(
        GetRandomValue (0, 360),
        1.0f,
        1.0f
    );
    Vector2 position = {0, 0};
    float velocity = 5000;
    float seconds = 0.0f;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        seconds += dt;
        window.x = GetRenderWidth();
        window.y = GetRenderHeight();
        float distance = velocity*sigmoid(position.x/window.x - 1)*dt;
        keys(&position, distance);
        bounds(&position, &rec);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleV(position, (Vector2){rec.width, rec.height}, color);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void keys (Vector2 *position, float distance) {
    if (IsKeyDown(KEY_W))
        position->y -= distance;
    if (IsKeyDown (KEY_A))
        position->x -= distance;
    if (IsKeyDown (KEY_S))
        position->y += distance;
    if (IsKeyDown (KEY_D))
        position->x += distance;
}

void bounds (Vector2 *position, Rectangle *rec) {
    if (position->x > window.x-rec->width)
        position->x = window.x-rec->width;
    if (position->x < 0)
        position->x = 0;
    if (position->y > window.y-rec->height)
        position->y = window.y-rec->height;
    if (position->y < 0)
        position->y = 0;
}

float sigmoid (float num) {
    return 1/(1+exp(-num));
}