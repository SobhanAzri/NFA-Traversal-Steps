//
// Created by nryxenon on 12/11/25.
//

#include "Renderer/renderer.h"
#include "Automatas/nfa.h"
#include "Tools/raygui.h"
#include "Tools/constants.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

#define WINDOW_WIDTH GetMonitorWidth(0)
#define WINDOW_HEIGHT GetMonitorHeight(0)

#define LINE_COLOR BLACK
#define RADIUS 60

std::unique_ptr<Renderer> Renderer::s_pInstance = nullptr;


void drawArrow(const Font &font, const Vector2 &start, const Vector2 &end, const std::string symbols);
void drawCurvedArrow(const Font &font, const Vector2 &start, const Vector2 &end, const std::string symbols);
void drawLoop(const Font &font, const Vector2 &statePosition, const std::string symbols);

// i copied these two from internet to act as a clone to that unavailable raylib functions that are not available public
Vector2 QuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, float t);
void DrawQuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, float thickness, Color color, int segments = 24);


Renderer& Renderer::getInstance() {
    if (!s_pInstance)
        s_pInstance.reset(new Renderer);

    return *s_pInstance;
}

void Renderer::initializeVisualModel(const NFA &nfa) {
    errorsContext = nfa.getErrorsContext();

    if (!errorsContext.empty())
        return;

    auto *allStates = &nfa.getAllStates();
    stateCount = static_cast<int>(allStates->size());
    int iterator = stateCount - 1;

    computePositions();

    // first Initialize Alphabet
    alphabet = nfa.getAlphabet();

    // first loop for initializing State Properties
    for (auto &[name, statePointer] : *allStates)
    {
        StateProperties properties;
        properties.name = name;
        properties.bIsInitial = statePointer->isInitialState();
        properties.bIsFinal = statePointer->isFinalState();
        properties.radius = RADIUS;
        properties.position = statePositions[iterator];

        iterator--;
        visualStates[name] = properties;
    }

    // second loop for initializing Transition properties
    for (auto &[name, statePointer] : nfa.getAllStates())
    {
        for (auto &[destinationName , transitionPointer] : statePointer->getAllTransitions())
        {
            TransitionProperties properties;
            properties.currentState = statePointer->getStateName();
            properties.destinationState = destinationName;
            properties.symbols = transitionPointer->getSymbols();

            visualTransitions.push_back(properties);
        }
    }
}

void Renderer::computePositions() {
    statePositions.clear();

    int columns = ceil(sqrt(stateCount));
    int rows = ceil((float)stateCount / columns);

    float cellWidth = (float)WINDOW_WIDTH / columns;
    float cellHeight = (float)WINDOW_HEIGHT / rows;

    for (int i = 0; i < stateCount; i++)
    {
        int r = i / columns;
        int c = i % columns;

        float x = c * cellWidth + cellWidth / 2.0f;
        float y = r * cellHeight + cellHeight / 2.0f;

        statePositions.push_back({x, y});
    }
}

void Renderer::drawVisualModel() {

    DrawTextEx(font,"Edit Automata.txt and Click Reload Button!",
        {static_cast<float>(WINDOW_WIDTH / 2 - 210),15},
        24,1, BLACK);

    DrawTextEx(font,"Sobhan Azari",
        {1750,static_cast<float>(WINDOW_HEIGHT - 30)},
        24,1, BLACK);

     if (!errorsContext.empty()){

         Vector2 screenCenter = {450,static_cast<float>(WINDOW_HEIGHT / 6)};

        DrawTextEx(font, errorsContext.data(), screenCenter, 64, 1, RED);

        return;
    }

    // drawing Alphabet
    if (!alphabet.empty()){

        std::string alphabetText = "Σ = { ";

        for (auto const &symbol : alphabet) {
            if (symbol == NFA_EPSILON)
                continue;

            alphabetText += symbol;
            alphabetText += " , ";
        }
        alphabetText.replace(alphabetText.length() - 2,1,"}");

        DrawTextEx(font, alphabetText.data(), {12,12}, 42, 1, LINE_COLOR);
    }

    // drawing states
    for (auto &[name, stateProperty] : visualStates)
    {
        DrawCircleLinesV(stateProperty.position,stateProperty.radius,LINE_COLOR);

        if (stateProperty.bIsInitial)
            drawArrow(font,
                      {stateProperty.position.x - RADIUS - 150, stateProperty.position.y},
                      {stateProperty.position.x,stateProperty.position.y}, "");
        if (stateProperty.bIsFinal)
            DrawCircleLinesV(stateProperty.position,(stateProperty.radius * .8f),LINE_COLOR);

       DrawTextEx(font,stateProperty.name.data(),
           {stateProperty.position.x,stateProperty.position.y},
           32,1, BLACK);

    }

    // drawing transitions

    for (const auto &iterator : visualTransitions)
    {
        bool isLoop = false;

        std::string symbols = "{ ";
        for (auto const character : iterator.symbols) {

            if (character == NFA_EPSILON)
                symbols += "λ";
            else
                symbols += character;
            symbols += ",";
        }
        symbols.replace(symbols.length() - 1,1," }");


        if (iterator.currentState == iterator.destinationState) {
            drawLoop(font, visualStates[iterator.currentState].position, symbols);
            isLoop = true;
        }
        else
            drawCurvedArrow(font, visualStates[iterator.currentState].position,
                 visualStates[iterator.destinationState].position, symbols);
    }
}

void Renderer::resetRenderer() {
     stateCount = 0;
     alphabet.clear();
     errorsContext = "";

     visualStates.clear();
     visualTransitions.clear();
     statePositions.clear();
}



void drawArrow(const Font &font, const Vector2 &start, const Vector2 &end, const std::string symbols) {


    /*          Default Lines - i removed them from being "Default" because when i have 2 transitions between 2 states , they overlap !
     *          so im just gonna use it for initial state and ill use Curved Transition Lines as default!
     */

    float dx = (end.x - start.x);
    float dy = (end.y - start.y);


    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));

    float angle = atan2f(dy, dx);

    Vector2 newStart = {start.x + direction.x * RADIUS,start.y + direction.y * RADIUS};
    Vector2 newEnd = {end.x - direction.x * RADIUS,end.y - direction.y * RADIUS};

    Vector2 left = {
            newEnd.x - 20 * cosf(angle - .5f),
            newEnd.y - 20 * sinf(angle - .5)
    };

    Vector2 right = {
            newEnd.x - 20 * cosf(angle + .5f),
            newEnd.y - 20 * sinf(angle + .5)
    };


    DrawLineEx(newStart, newEnd, 2, LINE_COLOR);
    DrawLineEx(newEnd, left, 2,LINE_COLOR);
    DrawLineEx(newEnd, right, 2,LINE_COLOR);

    // drawing symbols of a transition

    if (!symbols.empty())
    {
        DrawRectangle((start.x + end.x) /2 + 5, (start.y + end.y) /2 + 5, symbols.length() * 11, 35, WHITE);
        DrawTextEx(font, symbols.data(), {(start.x + end.x) /2 + 5, (start.y + end.y) /2 + 5}, 32, 1, BLACK);
    }
}

void drawCurvedArrow(const Font &font, const Vector2 &start, const Vector2 &end, const std::string symbols) {

    /*
     *                                     Curved Lines for Transitions !
     *
     *      i replaced default transition lines with curved lines to prevent transition overlappings.
     *      the logic behind it is i compute distance between two states and then i compute a curve
     *      amount according to the distance. then i curve the lines a bit to their right in their
     *      direction !
     *
     *      the more the distance, the curvier the linessss!
     *
     */

    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));
    Vector2 normal = { -direction.y , direction.x };

    Vector2 newStart = {start.x + direction.x * (RADIUS * .65f),start.y + direction.y * (RADIUS * .7f)};
    Vector2 newEnd = {end.x - direction.x * (RADIUS * .7f),end.y - direction.y * (RADIUS * .7f)};

    float distance = Vector2Distance(newStart, newEnd);
    float curveAmount = Clamp(distance * .25f, 30.f, 80.f);


    Vector2 mid = Vector2Lerp(newStart, newEnd, 0.5f);
    Vector2 control = Vector2Add(mid, Vector2Scale(normal, curveAmount));

    // drawing the line itself

    Vector2 p0 = QuadraticBezier(newStart, control, newEnd, 0.05f);
    Vector2 p1 = QuadraticBezier(newStart, control, newEnd, 0.95f);

    DrawQuadraticBezier(p0, control, p1, 2.0f, LINE_COLOR);


    Vector2 t1 = QuadraticBezier(newStart, control, newEnd, 0.90f);
    Vector2 t2 = QuadraticBezier(newStart, control, newEnd, 1.00f);
    Vector2 tan = Vector2Normalize(Vector2Subtract(t2, t1));

    float angle = atan2f(tan.y, tan.x);

    Vector2 left = {
        p1.x - 18 * cosf(angle - 0.5f),
        p1.y - 18 * sinf(angle - 0.5f)
    };

    Vector2 right = {
        p1.x - 18 * cosf(angle + 0.5f),
        p1.y - 18 * sinf(angle + 0.5f)
    };

    DrawLineEx(p1, left, 2, LINE_COLOR);
    DrawLineEx(p1, right, 2, LINE_COLOR);


    Vector2 labelPos = QuadraticBezier(newStart, control, newEnd, 0.5f);

    DrawRectangle(labelPos.x, labelPos.y, symbols.length() * 10, 32, WHITE);
    DrawTextEx(font, symbols.c_str(), labelPos, 28, 1, BLACK);

}

void drawLoop(const Font &font, const Vector2 &statePosition, const std::string symbols) {
    float loopRadius = 40;
    int lineThickness = 2;

    Vector2 loopCenter = {0,0};

    Vector2 arrowTip = {0,0};
    Vector2 arrowLeftWing = {0,0};
    Vector2 arrowRightWing = {0,0};

    if (statePosition.y <= (static_cast<int>(GetScreenHeight() / 2))) {
        loopCenter = {statePosition.x, statePosition.y - RADIUS - loopRadius};
        arrowTip = {loopCenter.x, loopCenter.y + loopRadius};
    }
    else {
        loopCenter = {statePosition.x , statePosition.y + RADIUS + loopRadius};
        arrowTip = {loopCenter.x, loopCenter.y - loopRadius};
    }

    arrowLeftWing = {arrowTip.x + 10, arrowTip.y + 10};
    arrowRightWing = {arrowTip.x + 10, arrowTip.y - 10};


    for (int i = 0; i < lineThickness; i++)
        DrawCircleLines(loopCenter.x, loopCenter.y, loopRadius - i, LINE_COLOR);
    DrawLineEx(arrowTip, arrowLeftWing, 2,LINE_COLOR);
    DrawLineEx(arrowTip, arrowRightWing, 2,LINE_COLOR);

    DrawRectangle(loopCenter.x + 50, loopCenter.y, symbols.length() * 10, 28, WHITE);
    DrawTextEx(font, symbols.data(), {loopCenter.x + 50, loopCenter.y}, 28, 1, BLACK);
}

Vector2 QuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, float t)
{
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;

    return {
        uu * p0.x + 2.0f * u * t * p1.x + tt * p2.x,
        uu * p0.y + 2.0f * u * t * p1.y + tt * p2.y
    };
}


void DrawQuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, float thickness, Color color, int segments) {
    Vector2 prev = p0;

    for (int i = 1; i <= segments; i++) {
        float t = (float)i / segments;
        Vector2 curr = QuadraticBezier(p0, p1, p2, t);

        DrawLineEx(prev, curr, thickness, color);
        prev = curr;
    }
}
