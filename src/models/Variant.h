#ifndef VARIANT_H
#define VARIANT_H

#include "src/models/ComputerPart.h"

class Variant
{
public:
    Variant();
    ~Variant();
    class Propability{
    public:
        void setPropabilities(double trueValue){
            this->m_true = trueValue;
            this->m_false = 1 - trueValue;
            average_sum += 1; //cus true + false (which is 1 - true) = 1
            average_counter+=2;
        };
        void setTrue(double newTrue);

        double True() {return m_true;}
        double False() {return m_false;}

        static double getAverage() {
            return Propability::average_sum/Propability::average_counter;//which is always 0.5, i guess
        };

    private:
        double m_true = 0.95;
        double m_false = 0.05;
        static inline double average_sum = 0;
        static inline double average_counter = 0;
    };

    ComputerPart *part() const;
    void setPart(ComputerPart *newPart);

    void setPropabilitiesList(const QList<Variant::Propability *> &newPropabilitiesList);

    QList<Variant::Propability *> propabilitiesList() const;

    void setAnswersList(const QList<double> &newAnswersList);
    void addToAnswersList(double value);

    QList<double> answersList() const;

    double value() const;

    void setValue(double newValue);

private:
    ComputerPart* m_part;

    double m_value = 0.5f;
    QList<Variant::Propability*> m_propabilitiesList; //TODO: mem leak
    QList<double> m_answersList;
};

#endif // VARIANT_H
