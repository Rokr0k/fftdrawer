#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "dft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ccircleRGBA(surface, o, rad, r, g, b, a) circleRGBA(surface, creal(o), cimag(o), rad, r, g, b, a)
#define clineRGBA(surface, s, e, r, g, b, a) lineRGBA(surface, creal(s), cimag(s), creal(e), cimag(e), r, g, b, a)

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 0;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 0;
    }

    size_t length;
    fscanf(input, "%lu", &length);
    double complex *const path = malloc(sizeof(double complex) * length);
    for (size_t i = 0; i < length; i++)
    {
        double re, im;
        fscanf(input, "%lf%lf", &re, &im);
        path[i] = re + im * I;
    }
    fclose(input);

    double complex *const transformed = malloc(sizeof(double complex) * length);
    dft(path, transformed, length);

    double complex *const queue = malloc(sizeof(double complex) * length);
    memset(queue, 0, sizeof(double complex) * length);
    size_t queueIdx = 0;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 0, 0);

    SDL_Event event;
    int quit = 0;
    double time = 0;
    Uint32 delay = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    delay++;
                    break;
                case SDLK_DOWN:
                    if (delay > 0)
                    {
                        delay--;
                    }
                    break;
                }
                break;
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

        double complex offset = screen->w / 2 + screen->h / 2 * I;

        double complex pos = 0;
        for (size_t i = 0; i < length; i++)
        {
            double complex prevPos = pos;

            double frequency = i;
            double radius = sqrt(pow(creal(transformed[i]), 2) + pow(cimag(transformed[i]), 2));
            double phase = atan2(cimag(transformed[i]), creal(transformed[i]));

            pos += radius * cexp(I * (frequency * time + phase));

            ccircleRGBA(screen, prevPos + offset, radius, 0x7f, 0x7f, 0x7f, 0x7f);
            clineRGBA(screen, prevPos + offset, pos + offset, 0x7f, 0x7f, 0x00, 0xff);
        }

        queue[queueIdx] = pos;
        queueIdx = (queueIdx + 1) % length;
        for (size_t i = 1; i < queueIdx; i++)
        {
            clineRGBA(screen, queue[i] + offset, queue[i - 1] + offset, 0xff, 0xff, 0xff, 0xff);
        }

        char delayStr[20] = {0};
        sprintf(delayStr, "Delay: %ums", delay);
        stringRGBA(screen, 2, 2, delayStr, 0xff, 0xff, 0xff, 0xff);

        SDL_Flip(screen);

        time += 2 * M_PI / length;
        if (time > 2 * M_PI)
        {
            time -= 2 * M_PI;
        }
        SDL_Delay(delay);
    }

    SDL_Quit();
    free(path);
    free(transformed);
    free(queue);
    return 0;
}