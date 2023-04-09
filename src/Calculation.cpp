#include "Calculation.h"

Calculation::Calculation()
{

}

void Calculation::precalculateVariants(QList<ComputerPart*> *variantsList)
{
    for (int i = 0; i < variantsList->count(); i++){
        ComputerPart* model = variantsList->at(i);
        //define budget type
        model->setBudget(Calculation::BudgetPrices::getBudgetByPriceNType(model->price(), model->type()));
    }
}
