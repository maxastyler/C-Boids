#include "BoidManager.h"

BoidManager::BoidManager(int numBoids, SDL_Rect _bounds){
    bounds=_bounds;
    addBoids(numBoids);
};

void BoidManager::addBoids(int numBoids){
    Vec2 vel;
    for (int i=0; i<numBoids; i++){
        vel.x=rand()%100-50;
        vel.y=rand()%100-50;
        boids.push_back(Boid(Vec2(rand()%bounds.w, rand()%bounds.h), vel ));  
    };
};

void BoidManager::addBoid(int x, int y){
    Vec2 vel;
    vel.x=rand()%100-50;
    vel.y=rand()%100-50;
    boids.push_back(Boid(Vec2(x, y), vel.normalised() ));  
};

void BoidManager::removeNear(int x, int y){
    if (boids.size()>0){
        Vec2 mousePos(x, y);
        int closest=0;
        for (unsigned i=0;i<boids.size();i++){
            if ( (boids[closest].getPos()-mousePos).length()>(boids[i].getPos()-mousePos).length() ){
                closest=i;
            };
        };
        boids.erase(boids.begin()+closest);
    };
};

void BoidManager::render(SDL_Renderer* renderer){
    for (unsigned i=0; i<boids.size(); i++){
        boids[i].render(renderer);
    };
};

void BoidManager::update(int dt, Vec2 pull){
    Vec2 v1, v2, v3, v4;

    for (unsigned i=0; i<boids.size();i++){
        v1=centreOfMass(&boids[i])*0.0001; 
        v2=avoidBoids(&boids[i])*1.5;
        v3=matchVel(&boids[i])*0.001;
        //v4=boundBoids(&boids[i]);
        v4=pull*0.001;

        boids[i].setVel(boids[i].getVel()+(v1+v2+v3+v4));
        boids[i].limitVel();
        boids[i].setPos(boids[i].getPos()+boids[i].getVel());
        if (boids[i].getX()<0) boids[i].setX(bounds.x+bounds.w);
        if (boids[i].getX()>(bounds.x+bounds.w)) boids[i].setX(0);
        if (boids[i].getY()<0) boids[i].setY(bounds.y+bounds.h);
        if (boids[i].getY()>(bounds.y+bounds.h)) boids[i].setY(0);
    };
    
};

Vec2 BoidManager::centreOfMass(Boid *b){
    Vec2 COM(0, 0);
    int count=0;
    for (unsigned i=0; i<boids.size();i++){
        if (b!=&boids[i]){
            if (checkSeen(b, &boids[i])){
                COM+=(boids[i].getPos()-b->getPos());
                count++;
            };
        };
    };
    if (count>0) COM/=count;
    return COM;
};

Vec2 BoidManager::avoidBoids(Boid *b){
    Vec2 c;
    int count=0;
    Vec2 distance;
    for (unsigned i=0; i<boids.size(); i++){
        if (&boids[i]!=b){
            distance = b->getPos()-boids[i].getPos();
            if (distance.length()<b->getScale()+20){
                c+=( distance.normalised()/distance.length() );
                count++;
            };
        };
    };
    if (count>0) c/=count;
    if (c.length()>0){
        c.normalise();
        c*=b->getMaxVel();
        c-=b->getVel();
        c.limit(b->getMaxAcc());
    };
    return c;
};

Vec2 BoidManager::matchVel(Boid *b){
    Vec2 COV;
    int count=0;
    for (unsigned i=0; i<boids.size();i++){
        if (b!=&boids[i]){
            if (checkSeen(b, &boids[i])){
                COV+=boids[i].getVel();
                count++;
            };
        };
    };
    if (count>0){
        COV/=count;
        COV.normalise();
        COV*=b->getMaxVel();
        Vec2 steer=COV-b->getVel();
        steer.limit(b->getMaxAcc());
        return steer;
    };
    return COV;
};

Vec2 BoidManager::boundBoids(Boid *b){
    Vec2 v;
    
    float correction = 10;

    if (b->getX()<bounds.x) v.x=correction;
    if (b->getX()>bounds.x+bounds.w) v.x= -correction;
    if (b->getY()<bounds.y) v.y=correction;
    if (b->getY()>bounds.y+bounds.h) v.y= -correction;


    return v;
};

bool BoidManager::checkAngle(Boid *b, Boid * other){
    float angle;
    angle =acos(b->getPos().normalised().dot(other->getPos().normalised())); 
    if (angle<b->getPerceptionAngle()) return true;
    else return false;
};

bool BoidManager::checkRange(Boid *b, Boid *other){
    if ( (b->getPos()-other->getPos()).length()<b->getPerceptionRange() ) return true;
    else return false;
};

bool BoidManager::checkSeen(Boid *b, Boid *other){
    if (checkRange(b, other) and checkAngle(b, other)) return true;
    else return false;
};
