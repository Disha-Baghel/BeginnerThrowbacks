#ifndef IOBJECT_H
#define IOBJECT_H

class IObject {
  public:
    virtual void Draw() = 0;
    virtual void update(float dt) = 0;
    virtual void Clear() = 0;
};

#endif // IOBJECT_H
