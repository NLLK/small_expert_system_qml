#ifndef SMALLEXPERTSYSTEMALGORITHM_H
#define SMALLEXPERTSYSTEMALGORITHM_H

#include "src/models/Variant.h"

#include <QList>

#include <src/models/QuestionModel.h>
#include <src/models/SimplerVariant.h>

class SmallExpertSystemAlgorithm
{
public:
    SmallExpertSystemAlgorithm();
    static void algorithm(QList<SimplerVariant*> *list, QList<QuestionModel *> *question_list);

private:
    static inline double P_min = 0.05;
    static inline double P_max = 0.95;
};

#endif // SMALLEXPERTSYSTEMALGORITHM_H
