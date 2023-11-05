#include "../../geometry/Rect/Rect.hpp"
#include "../../geometry/Vec2/Vec2.hpp"

#include <algorithm>
#include <cmath>

class Collision
{

public:
    // Observa��o: IsColliding espera �ngulos em radianos!
    // Para usar graus, forne�a a sua pr�pria implementa��o de Rotate,
    // ou transforme os �ngulos no corpo de IsColliding.
    static inline bool IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB)
    {
        angleOfA *= PI / 180;
        angleOfB *= PI / 180;
        Vec2 A[] = {Vec2(a.x, a.y + a.h),
                    Vec2(a.x + a.w, a.y + a.h),
                    Vec2(a.x + a.w, a.y),
                    Vec2(a.x, a.y)};
        Vec2 B[] = {Vec2(b.x, b.y + b.h),
                    Vec2(b.x + b.w, b.y + b.h),
                    Vec2(b.x + b.w, b.y),
                    Vec2(b.x, b.y)};

        for (auto &v : A)
        {
            v = Rotate(v - a.GetCenteredVec2(), angleOfA) + a.GetCenteredVec2();
        }

        for (auto &v : B)
        {
            v = Rotate(v - b.GetCenteredVec2(), angleOfB) + b.GetCenteredVec2();
        }

        Vec2 axes[] = {(A[0] - A[1]).GetNormalized(),
                       (A[1] - A[2]).GetNormalized(),
                       (B[0] - B[1]).GetNormalized(),
                       (B[1] - B[2]).GetNormalized()};

        for (auto &axis : axes)
        {
            float P[4];

            for (int i = 0; i < 4; ++i)
                P[i] = Dot(A[i], axis);

            float minA = *min_element(P, P + 4);
            float maxA = *max_element(P, P + 4);

            for (int i = 0; i < 4; ++i)
                P[i] = Dot(B[i], axis);

            float minB = *min_element(P, P + 4);
            float maxB = *max_element(P, P + 4);

            if (maxA < minB || minA > maxB)
                return false;
        }

        return true;
    }

private:
    static inline float Mag(const Vec2 &p)
    {
        return sqrt(p.x * p.x + p.y * p.y);
    }

    static inline Vec2 Norm(Vec2 &p)
    {
        return p / Mag(p);
    }

    static inline float Dot(const Vec2 &a, const Vec2 &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    static inline Vec2 Rotate(const Vec2 &p, float angle)
    {
        float cs = cos(angle), sn = sin(angle);
        return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
    }
};

// Aqui est�o tr�s operadores que sua classe Vec2 deve precisar, se j� n�o tiver.
// Se sua classe tiver m�todos para Mag, Norm, Dot e/ou Rotate, voc� pode substituir
// os usos desses m�todos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }
