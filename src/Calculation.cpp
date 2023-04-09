#include "Calculation.h"

Calculation::Calculation()
{

}

void Calculation::precalculateVariants(QList<ComputerPart*> *variantsList)
{
    for (int i = 0; i < variantsList->count(); i++){

        Variant* variant = new Variant;

        ComputerPart* model = variantsList->at(i);
        //define budget type
        model->setBudget(Calculation::BudgetPrices::getBudgetByPriceNType(model->price(), model->type()));

        variant->setPart(model);

        calculateProbabilitiesForVariant(variant);

        m_variantList.append(variant);
    }
}

void Calculation::setVariantList(const QList<Variant *> &newVariantList)
{
    m_variantList = newVariantList;
}

QList<Variant *> Calculation::getVariantList() const
{
    return m_variantList;
}

void Calculation::setQuestionsList(const QList<QuestionModel *> &newQuestionsList)
{
    m_questionsList = newQuestionsList;
}

Variant::Propability* Calculation::createPropabilityPointer(double propability){
    Variant::Propability* pointer = new Variant::Propability;
    pointer->setPropabilities(propability);
    return pointer;
}

void Calculation::calculateProbabilitiesForVariant(Variant* variant)
{
    //int variantQuestionsCount = 5;
    //questions:
    //0: need low/mid/high-perfomance pc
    //3: budget low/mid/high
    //6: side (for non cpu or video - 0.5)
    //8: vendor (for special one - 0.95; other - 0.5)

    ComputerPart* model = variant->part();

    QList<Variant::Propability*>* p_list = new QList<Variant::Propability*>;

    //perfomance
    ComputerPart::Perfomance _perfomance = model->perfomance();

    p_list->append(createPropabilityPointer(_perfomance == ComputerPart::Perfomance::Low    ? 0.95f : 0.05));
    p_list->append(createPropabilityPointer(_perfomance == ComputerPart::Perfomance::Middle ? 0.95f : 0.05));
    p_list->append(createPropabilityPointer(_perfomance == ComputerPart::Perfomance::High   ? 0.95f : 0.05));

    //budget
    ComputerPart::Budget _budget = model->budget();

    p_list->append(createPropabilityPointer(_budget == ComputerPart::Budget::Low    ? 0.95f : 0.05));
    p_list->append(createPropabilityPointer(_budget == ComputerPart::Budget::Middle ? 0.95f : 0.05));
    p_list->append(createPropabilityPointer(_budget == ComputerPart::Budget::High   ? 0.95f : 0.05));

    //side (like amd or not?) and vendor
    switch(model->type()){
        case ComputerPart::Type::CPU:
        {
            p_list->append(createPropabilityPointer(model->side().toUpper() == "AMD" ? 0.95f: 0.05f));
            p_list->append(createPropabilityPointer(model->side().toUpper() == "INTEL" ? 0.95f: 0.05f));
            break;
        }
        case ComputerPart::Type::Videocard:
        {
            p_list->append(createPropabilityPointer(model->side().toUpper() == "AMD" ? 0.95f: 0.05f));
            p_list->append(createPropabilityPointer(model->side().toUpper() == "NVIDIA" ? 0.95f: 0.05f));

            auto itr = std::find_if(m_questionsList.begin(), m_questionsList.end(), [](QuestionModel* someclass) { return someclass->id() == QuestionModel::Tags::videocard_vendor; });
            QuestionModel* foundQuestion = (*itr);
            if(itr == m_questionsList.end()) {
                printf("ERROR. There is no question with id 6");
            }

            QVariantList optionsForVideocard = foundQuestion->optionsOptions();
            QString _vendor = model->vendor().toLower();

            for(QVariant variable : optionsForVideocard){
                p_list->append(createPropabilityPointer(variable.toString().toLower() == _vendor ? 0.95f : 0.05));
            }
            break;
        }
        default:{
            p_list->append(createPropabilityPointer(0.5f));//amd
            p_list->append(createPropabilityPointer(0.5f));//nvidia / intel

            if (model->type() == ComputerPart::Type::Motherboard){
                auto itr = std::find_if(m_questionsList.begin(), m_questionsList.end(), [](QuestionModel* someclass) { return someclass->id() == QuestionModel::Tags::motherboard_vendor; });
                QuestionModel* foundQuestion = (*itr);
                if(itr == m_questionsList.end()) {
                    printf("ERROR. There is no question with id 6");
                }

                QVariantList optionsForMotherboard = foundQuestion->optionsOptions();
                QString _vendor = model->vendor().toLower();

                for(QVariant variable : optionsForMotherboard){
                    p_list->append(createPropabilityPointer(variable.toString().toLower() == _vendor ? 0.95f : 0.05));
                }
            }

            break;
        }
    }

    variant->setPropabilitiesList(*p_list);
}

void Calculation::smallExpertSystemAlgorithm()
{

}
