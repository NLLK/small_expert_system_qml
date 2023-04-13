#include "SmallExpertSystemAlgorithm.h"

SmallExpertSystemAlgorithm::SmallExpertSystemAlgorithm()
{

}

void SmallExpertSystemAlgorithm::algorithm(QList<Variant *> *list)
{
    float P_average = Variant::Propability::getAverage();
    float min = P_min;
    float max = P_max;

    for (Variant* variant : *list){

        for (int i = 0; i < variant->propabilitiesList().count(); i++){
            Variant::Propability *propability = variant->propabilitiesList()[i];

            float answerValue = variant->answersList()[i];
            float p_apr = variant->value();
            float p_hPrev = variant->value();
            if (answerValue < P_average){
                float p_hne = ((1 - propability->True()) * p_apr) / ((1 - propability->True()) * p_apr + (1 - propability->False()) * (1 - p_apr));
                float p_h = p_hne + ((answerValue - min) * (p_hPrev - p_hne)) / (P_average - min);

                variant->setValue(p_h);
            }
            else {
                float p_he = (propability->True() * p_apr) / (propability->True() * p_apr + propability->False() * (1 - p_apr));
                float p_h = p_hPrev + ((answerValue - P_average) * (p_he - p_hPrev)) / (max - P_average);

                variant->setValue(p_h);
            }
        }
    }
}
