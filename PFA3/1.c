#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    SHAPE_DOT = 0,
    SHAPE_LINE = 1,
    SHAPE_TRIANGLE = 2,
    SHAPE_SQUARE = 3,
    SHAPE_RECTANGLE = 4
};

enum
{
    PROPERTY_AREA = 1,
    PROPERTY_PERIMETER = 2,
    PROPERTY_DISTANCE_FROM_ORIGIN = 3
};

struct Dot
{
    int type;
    float x;
    float y;
};

struct Line
{
    int type;
    float x1;
    float y1;
    float x2;
    float y2;
};

struct Triangle
{
    int type;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
};

struct Square
{
    int type;
    float x;
    float y;
    float side;
};

struct Rectangle
{
    int type;
    float x;
    float y;
    float width;
    float height;
};

static float distanceBetween(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrtf(dx * dx + dy * dy);
}

float calculateProperty(void *shapePtr, int propertyType)
{
    int shapeType;

    if (shapePtr == NULL)
        return NAN;

    shapeType = *(int *)shapePtr;
    switch (shapeType)
    {
    case SHAPE_DOT:
    {
        const struct Dot *dot = (const struct Dot *)shapePtr;

        if (propertyType == PROPERTY_DISTANCE_FROM_ORIGIN)
            return distanceBetween(0.0f, 0.0f, dot->x, dot->y);
        if (propertyType == PROPERTY_AREA || propertyType == PROPERTY_PERIMETER)
            return 0.0f;
        return NAN;
    }

    case SHAPE_LINE:
    {
        const struct Line *line = (const struct Line *)shapePtr;

        if (propertyType == PROPERTY_PERIMETER)
            return distanceBetween(line->x1, line->y1, line->x2, line->y2);
        if (propertyType == PROPERTY_DISTANCE_FROM_ORIGIN)
            return distanceBetween(0.0f, 0.0f,
                                  (line->x1 + line->x2) / 2.0f,
                                  (line->y1 + line->y2) / 2.0f);
        if (propertyType == PROPERTY_AREA)
            return 0.0f;
        return NAN;
    }

    case SHAPE_TRIANGLE:
    {
        const struct Triangle *triangle = (const struct Triangle *)shapePtr;
        float side1 = distanceBetween(triangle->x1, triangle->y1,
                                      triangle->x2, triangle->y2);
        float side2 = distanceBetween(triangle->x2, triangle->y2,
                                      triangle->x3, triangle->y3);
        float side3 = distanceBetween(triangle->x3, triangle->y3,
                                      triangle->x1, triangle->y1);

        if (propertyType == PROPERTY_AREA)
        {
            float twiceArea = triangle->x1 * (triangle->y2 - triangle->y3) +
                              triangle->x2 * (triangle->y3 - triangle->y1) +
                              triangle->x3 * (triangle->y1 - triangle->y2);
            return fabsf(twiceArea) / 2.0f;
        }
        if (propertyType == PROPERTY_PERIMETER)
            return side1 + side2 + side3;
        if (propertyType == PROPERTY_DISTANCE_FROM_ORIGIN)
            return distanceBetween(0.0f, 0.0f,
                                   (triangle->x1 + triangle->x2 + triangle->x3) / 3.0f,
                                   (triangle->y1 + triangle->y2 + triangle->y3) / 3.0f);
        return NAN;
    }

    case SHAPE_SQUARE:
    {
        const struct Square *square = (const struct Square *)shapePtr;

        if (propertyType == PROPERTY_AREA)
            return square->side * square->side;
        if (propertyType == PROPERTY_PERIMETER)
            return 4.0f * fabsf(square->side);
        if (propertyType == PROPERTY_DISTANCE_FROM_ORIGIN)
            return distanceBetween(0.0f, 0.0f,
                                   square->x + square->side / 2.0f,
                                   square->y + square->side / 2.0f);
        return NAN;
    }

    case SHAPE_RECTANGLE:
    {
        const struct Rectangle *rectangle = (const struct Rectangle *)shapePtr;

        if (propertyType == PROPERTY_AREA)
            return fabsf(rectangle->width * rectangle->height);
        if (propertyType == PROPERTY_PERIMETER)
            return 2.0f * (fabsf(rectangle->width) + fabsf(rectangle->height));
        if (propertyType == PROPERTY_DISTANCE_FROM_ORIGIN)
            return distanceBetween(0.0f, 0.0f,
                                   rectangle->x + rectangle->width / 2.0f,
                                   rectangle->y + rectangle->height / 2.0f);
        return NAN;
    }

    default:
        return NAN;
    }
}

static const char *shapeName(int shapeType)
{
    switch (shapeType)
    {
    case SHAPE_DOT:
        return "Dot";
    case SHAPE_LINE:
        return "Line";
    case SHAPE_TRIANGLE:
        return "Triangle";
    case SHAPE_SQUARE:
        return "Square";
    case SHAPE_RECTANGLE:
        return "Rectangle";
    default:
        return "Unknown shape";
    }
}

static void freeShapes(void **shapes, int shapeCount)
{
    int index;

    if (shapes == NULL)
        return;

    for (index = 0; index < shapeCount; index++)
    {
        free(shapes[index]);
        shapes[index] = NULL;
    }
    free(shapes);
}

int main(void)
{
    const int shapeCount = 5;
    void **shapes = malloc(5 * sizeof(*shapes));
    int index;

    if (shapes == NULL)
    {
        perror("Could not allocate the shape list");
        return 1;
    }
    for (index = 0; index < shapeCount; index++)
        shapes[index] = NULL;

    shapes[0] = malloc(sizeof(struct Dot));
    shapes[1] = malloc(sizeof(struct Line));
    shapes[2] = malloc(sizeof(struct Triangle));
    shapes[3] = malloc(sizeof(struct Square));
    shapes[4] = malloc(sizeof(struct Rectangle));
    for (index = 0; index < shapeCount; index++)
    {
        if (shapes[index] == NULL)
        {
            perror("Could not allocate a shape");
            freeShapes(shapes, shapeCount);
            shapes = NULL;
            return 1;
        }
    }

    *(struct Dot *)shapes[0] = (struct Dot){SHAPE_DOT, 3.0f, 4.0f};
    *(struct Line *)shapes[1] = (struct Line){SHAPE_LINE, 0.0f, 0.0f, 3.0f, 4.0f};
    *(struct Triangle *)shapes[2] =
        (struct Triangle){SHAPE_TRIANGLE, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 3.0f};
    *(struct Square *)shapes[3] = (struct Square){SHAPE_SQUARE, 1.0f, 1.0f, 2.0f};
    *(struct Rectangle *)shapes[4] =
        (struct Rectangle){SHAPE_RECTANGLE, -1.0f, -2.0f, 4.0f, 2.0f};

    printf("Distance is measured to the point, line midpoint, or shape center.\n");
    for (index = 0; index < shapeCount; index++)
    {
        int shapeType = *(int *)shapes[index];

        printf("\n%s\n", shapeName(shapeType));
        printf("Area: %.2f\n",
               calculateProperty(shapes[index], PROPERTY_AREA));
        printf("Perimeter/length: %.2f\n",
               calculateProperty(shapes[index], PROPERTY_PERIMETER));
        printf("Distance from origin: %.2f\n",
               calculateProperty(shapes[index], PROPERTY_DISTANCE_FROM_ORIGIN));
    }

    freeShapes(shapes, shapeCount);
    shapes = NULL;
    return 0;
}
