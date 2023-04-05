#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include <QObject>
#include <QVariant>

class QuestionModel : public QObject
{
    Q_OBJECT
public:
    explicit QuestionModel(QObject *parent = nullptr);
    ~QuestionModel(){};
    enum class Type {
        Plain = 0,
        Ranges = 1,
        Options = 2
    };

    Q_PROPERTY(QString questionText READ questionText WRITE setQuestionText NOTIFY questionTextChanged)
    Q_PROPERTY(QuestionModel::Type questionType READ questionType WRITE setQuestionType NOTIFY questionTypeChanged)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

    Q_PROPERTY(int plainMinimum READ plainMinimum WRITE setPlainMinimum NOTIFY plainMinimumChanged)
    Q_PROPERTY(int plainMaximum READ plainMaximum WRITE setPlainMaximum NOTIFY plainMaximumChanged)
    Q_PROPERTY(int plainStep READ plainStep WRITE setPlainStep NOTIFY plainStepChanged)

    Q_PROPERTY(QVariantList optionsOptions READ optionsOptions WRITE setOptionsOptions NOTIFY optionsOptionsChanged)

    QString questionText() const;
    void setQuestionText(const QString &newQuestionText);

    QuestionModel::Type questionType() const;
    void setQuestionType(QuestionModel::Type newQuestionType);
    void setQuestionType(QString s_questionType);

    int plainMinimum() const;
    void setPlainMinimum(int newPlainMinimum);

    int plainMaximum() const;
    void setPlainMaximum(int newPlainMaximum);

    int plainStep() const;
    void setPlainStep(int newPlainStep);

    QVariantList optionsOptions() const;
    void setOptionsOptions(const QVariantList &newOptionsOptions);

    static QuestionModel::Type stringToQuestionType(QString s_questionType);

    double value() const;
    void setValue(double newValue);

signals:

    void questionTextChanged();
    void questionTypeChanged();

    void plainMinimumChanged();
    void plainMaximumChanged();
    void plainStepChanged();

    void optionsOptionsChanged();

    void valueChanged();

private:
    QString m_questionText;
    QuestionModel::Type m_questionType;
    int m_plainMinimum = 0;
    int m_plainMaximum = 10;
    int m_plainStep;
    QVariantList m_optionsOptions;
    double m_value = 0;
    double m_relative_value = 0;

    double valueToRelativeValue(double value);
};

#endif // QUESTIONMODEL_H
