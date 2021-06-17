#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
#include<Vector.h>

class Polynomial
{
    private:
        std::vector<Vector> coefficients = std::vector<Vector>();
        std::vector<Polynomial*> terms = std::vector<Polynomial*>();
        float upperBound = -1;
        int current = 0;
        std::vector<Polynomial*> children = std::vector<Polynomial*>();

        int getNextPieceIndex(float t);
        Vector evaluateTerms(float t);
        Vector evaluateWrapper(Vector result);


        int wrappers = 0;
        Vector amplitude;
        Vector frequency;
        Vector phase;
        float tilt = 0;

    public:
        Polynomial(float upperBound = -1);
        Polynomial(const Polynomial& other);
        Polynomial& operator=(const Polynomial& other);
        void addCoefficient(Vector coeff, int degree, bool addMode = false);
        void addPolynomial(Polynomial* p);
        void addTerm(Polynomial* p);
        void makeContinuous(float offest = 0);

        enum wrappers{SineX = 1, SineY = 2, SqrtX = 4, SqrtY = 8};

        Vector evaluate(float t, bool update = true);
        Vector getCoeff(int degree);
        std::vector<Polynomial*> getTerms();
        std::vector<Polynomial*> getChildren();

        float getUpperBound();
        void setUpperBound(float f);

        void addWrapper(int wrapper, float amp = 1, float freq = 1, float p = 0);
        void setTilt(float angle);
        Polynomial* getPolynomial(int index);
        void setPolynomial(int index, Polynomial* p);
        void setTerm(int index, Polynomial *p);

        void copyFunctionToThis(Polynomial *other, float tilt = 0 );

};

#endif // POLYNOMIAL_H
