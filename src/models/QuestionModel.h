#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include <QObject>

class QuestionModel : public QObject
{
    Q_OBJECT
public:
    explicit QuestionModel(QObject *parent = nullptr);

    enum class Type {
        Plain = 0,
        Ranges = 1,
        Options = 2
    };

    Q_PROPERTY(QString questionText READ questionText WRITE setQuestionText NOTIFY questionTextChanged)
    Q_PROPERTY(QuestionModel::Type questionType READ questionType WRITE setQuestionType NOTIFY questionTypeChanged)

    QString questionText() const;
    void setQuestionText(const QString &newQuestionText);

    QuestionModel::Type questionType() const;
    void setQuestionType(QuestionModel::Type newQuestionType);

signals:

    void questionTextChanged();
    void questionTypeChanged();

private:
    QString m_questionText;
    QuestionModel::Type m_questionType;
};

#endif // QUESTIONMODEL_H
