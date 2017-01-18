//
// Created by ayistar on 1/17/17.
//

// define a pair of classes X and Y
// X has a pointer to Y
// and Y has an object of type X

class Y;

class X {
    Y *ptrY;
};

class Y {
    X objX;
};

int main()
{
    return 0;
}