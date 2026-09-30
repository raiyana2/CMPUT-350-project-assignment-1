#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text drawable(*mFont, text, pixelSize);

    // Calculate the bounding box of the text
    sf::FloatRect bounds = drawable.getLocalBounds();

    // Center the text by adjusting its position
    drawable.setOrigin(bounds.width / 2, bounds.height / 2);
    drawable.setPosition(sf::Vector2f(p.x, p.y));

    drawable.setFillColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(drawable);
}

void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {

    sf::Text drawable(*mFont, text, pixelSize);

    drawable.setPosition(sf::Vector2f(p.x, p.y));

    drawable.setFillColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(drawable);
}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);

    circle.setPosition(sf::Vector2f(p.x - radius, p.y - radius));  // Adjust position to center the circle

    circle.setFillColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rectangle(sf::Vector2f(r.width, r.height));

    rectangle.setPosition(sf::Vector2f(r.topLeft.x, r.topLeft.y));

    rectangle.setFillColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(rectangle);


}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {

    sf::RectangleShape rectangle(sf::Vector2f(r.width, r.height));

    rectangle.setPosition(sf::Vector2f(r.topLeft.x, r.topLeft.y));

    rectangle.setFillColor(sf::Color::Transparent);  // No fill

    rectangle.setOutlineThickness(width);

    rectangle.setOutlineColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(rectangle);

}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    Point2D direction = to - from;

    if (direction == Point2D(0, 0)) {
    
        return;
    }

    direction.Normalize();

    Point2D normal(-direction.y, direction.x);  // Perpendicular vector
    Point2D perpendicular = normal * (width / 2.0f);

    Point2D p1 = from + perpendicular;
    Point2D p2 = from - perpendicular;  
    Point2D p3 = to - perpendicular;
    Point2D p4 = to + perpendicular;

    sf::ConvexShape lineShape;
    lineShape.setPointCount(4);

    lineShape.setPoint(0, sf::Vector2f(p1.x, p1.y));
    lineShape.setPoint(1, sf::Vector2f(p2.x, p2.y));
    lineShape.setPoint(2, sf::Vector2f(p3.x, p3.y));
    lineShape.setPoint(3, sf::Vector2f(p4.x, p4.y));
    lineShape.setFillColor(sf::Color(c.r, c.g, c.b));
    mWindow->draw(lineShape);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
