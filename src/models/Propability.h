#ifndef PROPABILITY_H
#define PROPABILITY_H

#include <QJsonValue>
#include <QString>

class Propability{
public:
    void setPropabilities(double trueValue);
    void setPropabilities(double trueValue, double falseValue);
    void setQuestionId(int _question_id);
    double True();
    double False();
    int question_id();

    static double getAverage();

    static bool validatePropabilityFromQJsonValue(QJsonValue _qValue, double *value_p);
    static bool validatePropability(double value);
private:
    double m_true = 0.95;
    double m_false = 0.05;
    int m_question_id = -1;

    static inline double average_sum = 0;
    static inline double average_counter = 0;
};
#endif // PROPABILITY_H
