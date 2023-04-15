#include "SmallExpertSystemAlgorithm.h"

SmallExpertSystemAlgorithm::SmallExpertSystemAlgorithm()
{

}

void SmallExpertSystemAlgorithm::algorithm(QList<SimplerVariant *> *variant_list, QList<QuestionModel *> *question_list)
{
    double P_average = Propability::getAverage();
    double min = P_min;
    double max = P_max;

    for (int i = 0; i < question_list->size(); i++){
        QuestionModel* question = question_list->at(i);
        double answerValue = question->relative_value();

        for(SimplerVariant* variant : *variant_list){
            Propability p = variant->propabilities_list().at(i);

            double p_apr = variant->value();
            float p_hPrev = variant->value();

            if (answerValue < P_average){
                double p_hne = ((1 - p.True()) * p_apr) / ((1 - p.True()) * p_apr + (1 - p.False()) * (1 - p_apr));
                double p_h = p_hne + ((answerValue - min) * (p_hPrev - p_hne)) / (P_average - min);

                variant->setValue(p_h);
            }
            else{
                float p_he = (p.True() * p_apr) / (p.True() * p_apr + p.False() * (1 - p_apr));
                float p_h = p_hPrev + ((answerValue - P_average) * (p_he - p_hPrev)) / (max - P_average);

                variant->setValue(p_h);
            }

        }
    }
}
