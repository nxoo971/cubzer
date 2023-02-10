#include <stdio.h>
#include <math.h>


int main() {
    initWalls();
    float angle = FOV / WIDTH;
    float rayAngle;
    for (int x = 0; x < WIDTH; x++) {
        rayAngle = (FOV / 2) - (angle * x);
        float distanceToWall = INFINITY;
        int wallHit = -1;
        // Tracez le rayon et déterminez la distance à l'objet le plus proche
        for (int i = 0; i < NUM_WALLS; i++) {
            float rayX = sinf(rayAngle);
            float rayY = cosf(rayAngle);
            float wallX = walls[i].x;
            float wallY = walls[i].y;
            float dX = wallX - rayX;
            float dY = wallY - rayY;
            float dist = sqrtf(dX * dX + dY * dY);
            if (dist < distanceToWall) {
                distanceToWall = dist;
                wallHit = i;
            }
        }
        // Dessinez un pixel à la hauteur appropriée pour simuler la perspective 3D
        float wallHeight = WALL_HEIGHT / distanceToWall * HEIGHT / 2;
        for (int y = 0; y < HEIGHT; y++) {
            if (y > HEIGHT / 2 - wallHeight / 2 && y < HEIGHT / 2 + wallHeight / 2) {
                // Dessinez un pixel de couleur pour le mur
                // ...
            }
        }
    }
    return 0;
}
