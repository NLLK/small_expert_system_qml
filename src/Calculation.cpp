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

        variant->setAnswersList(m_commonAnswersValues);
        calculateProbabilitiesForVariant(variant);

        m_variantList.append(variant);
    }
}

void Calculation::precalculateCommonAnswers(){
    m_commonAnswersValues.clear();
    //budget
    double budget = 0;
    QuestionModel* foundQuestion = QuestionModel::findQuestionInListById(&m_questionsList, QuestionModel::Tags::budget);
    budget = foundQuestion->value();

    m_commonAnswersValues.append(budget < Calculation::Constants::budget_middle_from ? 1.0f : 0.0f);
    m_commonAnswersValues.append(budget >= Calculation::Constants::budget_middle_from && budget < Calculation::Constants::budget_high_from ? 1.0f : 0.0f);
    m_commonAnswersValues.append(budget > Calculation::Constants::budget_high_from ? 1.0f : 0.0f);

    //perfomance
    double perfomance_avg = 0;
    int perfomance_number_of_questions = 0;

    for (int i = QuestionModel::Tags::perfomance_from; i <= QuestionModel::Tags::perfomance_to; i++){
        QuestionModel* foundQuestion = QuestionModel::findQuestionInListById(&m_questionsList, i);
        if (foundQuestion == nullptr) continue;
        perfomance_avg += foundQuestion->relative_value();
        perfomance_number_of_questions++;
    }
    perfomance_avg = perfomance_avg/double(perfomance_number_of_questions);

    m_commonAnswersValues.append(perfomance_avg < Calculation::Constants::perfomance_middle_from ? 1.0f : 0.0f);
    m_commonAnswersValues.append(perfomance_avg >= Calculation::Constants::perfomance_middle_from && budget < Calculation::Constants::perfomance_high_from ? 1.0f : 0.0f);
    m_commonAnswersValues.append(perfomance_avg > Calculation::Constants::perfomance_high_from ? 1.0f : 0.0f);
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
            QString side_model = model->side().toUpper();
            p_list->append(createPropabilityPointer(side_model == "AMD" ? 0.95f: 0.05f));
            p_list->append(createPropabilityPointer(side_model == "INTEL" ? 0.95f: 0.05f));

            QuestionModel* foundQuestion = QuestionModel::findQuestionInListById(&m_questionsList, QuestionModel::Tags::cpu_side);

            QVariantList list = foundQuestion->optionsOptions();
            QString side_choosed = list[int(foundQuestion->relative_value())].toString().toUpper();

            variant->addToAnswersList(side_model == "AMD" ? 1.0 : 0.0);
            variant->addToAnswersList(side_model == "INTEL" ? 1.0 : 0.0);

            break;
        }
        case ComputerPart::Type::Videocard:
        {
            QString side_model = model->side().toUpper();

            p_list->append(createPropabilityPointer(side_model == "AMD" ? 0.95f: 0.05f));
            p_list->append(createPropabilityPointer(side_model == "NVIDIA" ? 0.95f: 0.05f));

            QuestionModel* foundQuestionSide = QuestionModel::findQuestionInListById(&m_questionsList, QuestionModel::Tags::videocard_side);

            QVariantList list = foundQuestionSide->optionsOptions();
            QString side_choosed = list[int(foundQuestionSide->relative_value())].toString().toUpper();

            variant->addToAnswersList(side_model == "AMD" ? 1.0 : 0.0);
            variant->addToAnswersList(side_model == "NVIDIA" ? 1.0 : 0.0);

            QuestionModel* foundQuestion = QuestionModel::findQuestionInListById(&m_questionsList, QuestionModel::Tags::videocard_vendor);
            if(foundQuestion == nullptr) {
                printf("ERROR. There is no question with id %d", QuestionModel::Tags::videocard_vendor);
            }

            QVariantList optionsForVideocard = foundQuestion->optionsOptions();
            QString _vendor = model->vendor().toLower();
            QString choosed_vendor = optionsForVideocard[int(foundQuestion->relative_value())].toString().toLower();

            for(QVariant variable : optionsForVideocard){
                p_list->append(createPropabilityPointer(variable.toString().toLower() == _vendor ? 0.95f : 0.05));
                variant->addToAnswersList(variable.toString().toLower() == choosed_vendor ? 1.0 : 0.0);
            }
            break;
        }
        default:{
            p_list->append(createPropabilityPointer(0.5f));//amd
            p_list->append(createPropabilityPointer(0.5f));//nvidia / intel

            variant->addToAnswersList(0.5f);
            variant->addToAnswersList(0.5f);

            if (model->type() == ComputerPart::Type::Motherboard){
                QuestionModel* foundQuestion = QuestionModel::findQuestionInListById(&m_questionsList, QuestionModel::Tags::motherboard_vendor);
                if(foundQuestion == nullptr) {
                    printf("ERROR. There is no question with id %d", QuestionModel::Tags::motherboard_vendor);
                }

                QVariantList optionsForMotherboard = foundQuestion->optionsOptions();
                QString _vendor = model->vendor().toLower();
                QString choosed_vendor = optionsForMotherboard[int(foundQuestion->relative_value())].toString().toLower();
                for(QVariant variable : optionsForMotherboard){
                    p_list->append(createPropabilityPointer(variable.toString().toLower() == _vendor ? 0.95f : 0.05));
                    variant->addToAnswersList(variable.toString().toLower() == choosed_vendor ? 1.0 : 0.0);
                }
            }

            break;
        }
    }

    variant->setPropabilitiesList(*p_list);
}

void Calculation::smallExpertSystemAlgorithm()
{
    SmallExpertSystemAlgorithm::algorithm(&m_variantList);
}
