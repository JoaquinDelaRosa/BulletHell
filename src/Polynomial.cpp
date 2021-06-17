#include "Polynomial.h"
#include "SFML/Graphics.hpp"
#include "GameEntities.h"
#include<bits/stdc++.h>
#include<Vector.h>

Polynomial::Polynomial(float f){
    this->upperBound = f;
    this->coefficients.push_back(Vector(0.0f, 0.0f));
    this->children.push_back(this);
}

Polynomial::Polynomial(const Polynomial& other){

    this->children = *(new std::vector<Polynomial*>(other.children));
    this->upperBound = *(new float(other.upperBound));
    this->coefficients = *(new std::vector<Vector>(other.coefficients));
    this->terms = *(new std::vector<Polynomial*>( other.terms));

    this->wrappers = *(new int(other.wrappers));
    this->amplitude = *(new Vector(other.amplitude));
    this->frequency = *(new Vector(other.frequency));
    this->phase = *(new Vector(other.phase));
    this->tilt = other.tilt;
}

Polynomial& Polynomial::operator=(const Polynomial& other){
    if(this == &other)   return *this;

    this->children = *(new std::vector<Polynomial*>(other.children));
    this->upperBound = *(new float(other.upperBound));
    this->coefficients = *(new std::vector<Vector>(other.coefficients));
    this->terms = *(new std::vector<Polynomial*>( other.terms));

    this->wrappers = *(new int(other.wrappers));
    this->amplitude = *(new Vector(other.amplitude));
    this->frequency = *(new Vector(other.frequency));
    this->phase = *(new Vector(other.phase));
    this->tilt = other.tilt;

    return *this;
}

void Polynomial::addCoefficient(Vector coeff, int degree, bool addMode){
    while(degree >= (int) this->coefficients.size()){
        this->coefficients.push_back(Vector(0.0f, 0.0f));
    }
    if(! addMode)
        this->coefficients[degree] = coeff;
    else{
        this->coefficients[degree] = this->coefficients[degree] + coeff;
    }
}

void Polynomial::addPolynomial(Polynomial* p){
    this->children.push_back(p);
}

void Polynomial::addTerm(Polynomial* p){
    this->terms.push_back(p);
}

Vector Polynomial::evaluate(float t, bool update){
    int c = this->getNextPieceIndex(t);
    Polynomial* piece;
    float tempoffset = 0;

    if(c == 0)              piece = this;
    else                    piece = this->children[c];

    if(c == 1)
        tempoffset = this->getUpperBound();
    else if(c > 1)
        tempoffset = this->children[c - 1]->getUpperBound();            // horizontally shifted based on the upper bound of the previous term.

    Vector result = piece->coefficients[piece->coefficients.size() - 1];

    t = t - tempoffset;
    int n = piece->coefficients.size() - 2;

    while(n >= 0){
        result = result * t + piece->coefficients[n];
        n--;
    }

    result = piece->evaluateWrapper(result - piece->getCoeff(0)) + piece->getCoeff(0);

    result -= piece->coefficients[0];
    float x = result.x, y = result.y;
    result.x = x * cos(piece->tilt) - y* sin(piece->tilt);
    result.y = x * sin(piece->tilt) + y * cos(piece->tilt);

    result = result + piece->coefficients[0];
    result = result +  piece->evaluateTerms(t);

    if(update && c < (int) this->children.size())
        this->current = c;

    return result;
}


int Polynomial::getNextPieceIndex(float t){
    int c = this->current;                  // Store current in c for now in case we are simply performing a test evaluation (i.e. via the makeContinuous method)
    Polynomial* piece = this->children[c];

    if(c == 0){
        piece = this;
    }

    while(piece->getUpperBound() < t && piece->getUpperBound() >= 0 && c < (int) this->children.size() - 1){
        if(c + 1 < (int) this->children.size())
            c++;
        piece = this->children[c];
    }

    return c;
}

Vector Polynomial::evaluateTerms(float t){

    Vector result = Vector(0.0f, 0.0f);
    // Add other terms to polynomial
    std::vector<Polynomial*>  pieceTerms = this->getTerms();
    for(int i = 0; i < (int) pieceTerms.size(); i++){
        result = result + pieceTerms[i]->evaluate(t, true);
    }

    return result;
}


void Polynomial::makeContinuous(float offset){
    for(int i = 1; i < (int) this->children.size(); i ++){
        if(i == 1){
            this->children[i]->addCoefficient(this->evaluate(this->upperBound, false), 0);
        }
        else{
            float t = this->children[i - 1]->getUpperBound();
            this->children[i]->addCoefficient(this->evaluate(t, false), 0);         // vertically shift based on the value at the upperbound
        }
    }
}


Vector Polynomial::getCoeff(int degree){
    if(degree < (int) this->coefficients.size()){
        return this->coefficients[degree];
    }

    return Vector(0.0f, 0.0f);
}

float Polynomial::getUpperBound(){
    return this->upperBound;
}

void Polynomial::setUpperBound(float f){
    this->upperBound = f;
}

std::vector<Polynomial*>  Polynomial::getTerms(){
    return this->terms;
}

void Polynomial::addWrapper(int wrapper, float amp, float freq, float p){
    this->wrappers = this->wrappers | wrapper;
    if(wrapper == SineX || wrapper == SqrtX){
        this->amplitude.x = amp;
        this->frequency.x = freq;
        this->phase.x = p;
    }
    else if(wrapper == SineY || wrapper == SqrtY){
        this->amplitude.y = amp;
        this->frequency.y = freq;
        this->phase.y = p;
    }
}

Vector Polynomial::evaluateWrapper(Vector result){
    Vector answer = Vector(0, 0);
    if(this->wrappers == 0){
        return result;
    }
    if((this->wrappers & SineX) == SineX){
        answer.x = this->amplitude.x * sin((result.x / (180) * PI - this->phase.x) * this->frequency.x );
    }
    if((this->wrappers & SineY) == SineY){
        answer.y = this->amplitude.y * sin((result.y / (180) * PI - this->phase.y) * this->frequency.y);
    }
    if((this->wrappers & SqrtX) == SqrtX){
        answer.x = this->amplitude.x * sqrt(fabs((result.x - this->phase.x) * this->frequency.x));
    }
    if((this->wrappers & SqrtY) == SqrtY){
        answer.y = this->amplitude.y * sqrt(fabs((result.y - this->phase.y) * this->frequency.y));
    }


    return answer;
}

void Polynomial::setTilt(float angle){
    this->tilt = angle;
}

Polynomial* Polynomial::getPolynomial(int index){
    if(index == 0)
        return this;
    return this->children[index];
}

void Polynomial::setPolynomial(int index, Polynomial *p ){
    if(index >= 0 && index < (int) this->children.size())
        this->children[index] = p;
}

void Polynomial::setTerm(int index, Polynomial *p ){
    if(index >= 0 && index < (int) this->terms.size())
        this->terms[index] = p;
}

std::vector<Polynomial*> Polynomial::getChildren(){
    return this->children;
}

void Polynomial::copyFunctionToThis(Polynomial *other, float tilt){
    int children = other->getChildren().size();
    this->tilt = tilt;

    for(int i = 0; i < children; i++){
        Polynomial* q = new Polynomial(*(other->getPolynomial(i)));
        q->setTilt(tilt);
        this->setPolynomial(i, q);

        std::vector<Polynomial*> otherTerms = other->getPolynomial(i)->getTerms();
        int terms = otherTerms.size();
        for(int j = 0; j < terms; j++){
            Polynomial* p= new Polynomial(*(otherTerms[j]));
            p->setTilt(tilt);
            this->getPolynomial(i)->setTerm(j, p);
        }
    }
}
