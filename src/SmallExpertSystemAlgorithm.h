#ifndef SMALLEXPERTSYSTEMALGORITHM_H
#define SMALLEXPERTSYSTEMALGORITHM_H

#include "src/models/Variant.h"

#include <QList>

class SmallExpertSystemAlgorithm
{
public:
    SmallExpertSystemAlgorithm();
    static void algorithm(QList<Variant*> *list);

private:
    static inline double P_min = 0.05;
    static inline double P_max = 0.95;
};

#endif // SMALLEXPERTSYSTEMALGORITHM_H
