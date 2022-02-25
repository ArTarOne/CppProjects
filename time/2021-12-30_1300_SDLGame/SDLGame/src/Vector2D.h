#pragma once

class Vector2D
{
public:
    Vector2D(float x, float y);

    float getX() const;
    float getY() const;
    void  setX(float x);
    void  setY(float y);
    float length() const;

    /*
     * friend functions allow write:
     *   Vector2D v1(10, 11);
     *   Vector2D v2(35,25);
     *   v1 += v2;
     *   Vector2D v3 = v1 + v2;
     */
    Vector2D         operator+(const Vector2D& v2) const;
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);

    Vector2D  operator*(float scalar) const;
    Vector2D& operator*=(float scalar);

    Vector2D         operator-(const Vector2D& v2) const;
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

    Vector2D  operator/(float scalar) const;
    Vector2D& operator/=(float scalar);

    void normalize();

private:
    float m_x;
    float m_y;
};
