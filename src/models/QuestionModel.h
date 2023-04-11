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

    class Tags{
    public:
        static inline int budget = 50;
        static inline int videocard_side= 51;
        static inline int videocard_vendor = 106;
        static inline int motherboard_vendor = 107;
        static inline int cpu_vendor = 52;
        static inline int perfomance_from = 1;
        static inline int perfomance_to = 49;
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

    int id() const;

    void setId(int newId);

    static QuestionModel* findQuestionInListById(QList<QuestionModel*> *list, int id);
    double relative_value() const;

signals:

    void questionTextChanged();
    void questionTypeChanged();

    void plainMinimumChanged();
    void plainMaximumChanged();
    void plainStepChanged();

    void optionsOptionsChanged();

    void valueChanged();

private:
    int m_id = -1;
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
