#include "Propability.h"


void Propability::setPropabilities(double trueValue){
    this->m_true = trueValue;
    this->m_false = 1 - trueValue;
    average_sum += 1; //cus true + false (which is 1 - true) = 1
    average_counter+=2;
}

void Propability::setPropabilities(double trueValue, double falseValue){
    this->m_true = trueValue;
    this->m_false = falseValue;
    average_sum += trueValue + falseValue;
    average_counter+=2;
}

void Propability::setQuestionId(int _question_id){
    m_question_id = _question_id;
}

double Propability::True() {
    return m_true;
}

double Propability::False() {
    return m_false;
}
int Propability::question_id() {
    return m_question_id;
}

double Propability::getAverage() {
    return Propability::average_sum/Propability::average_counter;//which is always 0.5, i guess
}


//value_p: return converted double value
bool Propability::validatePropabilityFromQJsonValue(QJsonValue _qValue, double *value_p)
{
    double value = 0;
    try {
        value = _qValue.toDouble();
    } catch (...) {
        return false;
    }

    if (!Propability::validatePropability(value)){
        return false;
    }

    *value_p = value;
    return true;
}

bool Propability::validatePropability(double value)
{
    if (value < 0 && value > 1){
        return false;
    }
    return true;
}
