//
// Created by auguste on 25/04/22.
//

#ifndef RTB_CHECKPOINT_H
#define RTB_CHECKPOINT_H


class Checkpoint {
private:
    int x, y, id;

public:
    Checkpoint(int x, int y, int id);
    ~Checkpoint();

    int getX();
    int getY();
    int getId();
};


#endif //RTB_CHECKPOINT_H
