#include "TestFileParser.h"

TestFileParser::TestFileParser()
{

}

bool TestFileParser::checkFilePath(QString filePath)
{
    if (filePath.length() == 0){
        return false;
    }
    QUrl fileUrl = QUrl(filePath);
    QString fileExtenstion = fileUrl.fileName();
    QStringList splitList = fileExtenstion.split('.');
    bool isFileOkFlag = true;
    QFile file;

    if (splitList.length() < 2){
        isFileOkFlag = false;
    }
    else {
        fileExtenstion = fileExtenstion.split('.')[1];
    }

    if (isFileOkFlag){
        if  (fileExtenstion != StaticStringConstants::FileParser::fileExtenstion){
            isFileOkFlag = false;
        }
        else {
            file.setFileName(fileUrl.toLocalFile());
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                isFileOkFlag = false;
            }
            else{
                file.close();
//                m_file = file;
            }
        }
    }

    if (!isFileOkFlag){
        return false;
    }

    m_fileUrl = fileUrl;

    return true;
}

bool TestFileParser::parseFile()
{
    bool isFileOk = true;
    QString __dataName = "";
    int __questions_number = -1;
    int __variants_number = -1;

    QFile file(m_fileUrl.toLocalFile());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString fileContainment = file.readAll();
    file.close();

    QJsonParseError errHandler;
    QJsonDocument jDoc = QJsonDocument::fromJson(fileContainment.toUtf8(), &errHandler);
    isFileOk = (errHandler.error == QJsonParseError::NoError);

    if (isFileOk){
        if (!jDoc.isObject()) isFileOk = false;
        else{
            QJsonObject jObj = jDoc.object();
            __dataName = jObj[StaticStringConstants::FileParser::jsonf_dataName].toString(StaticStringConstants::FileParser::jsonf_dataName_default);

            QJsonArray jQuestions = jObj[StaticStringConstants::FileParser::jsonf_questions].toArray();
            if (jQuestions.count() != 0){
                __questions_number = jQuestions.count();
                isFileOk = parseQuestions(jQuestions);
            }
            else isFileOk = false;

            if (isFileOk){
                QJsonArray jVariants = jObj[StaticStringConstants::FileParser::jsonf_variants].toArray();
                if (jVariants.count() != 0){
                    __variants_number = jVariants.count();
                    isFileOk = parseVariants(jVariants);
                }
                else isFileOk = false;
            }

        }

    }
    if (!isFileOk){
        m_dataName = StaticStringConstants::FileParser::dataName_fileParsing_error;
        m_questions_number = 0;
        m_variants_number = 0;
        return false;
    }
    else {
        m_dataName = __dataName;
        m_questions_number = __questions_number;
        m_variants_number = __variants_number;
        return true;
    }


}

bool TestFileParser::parseQuestions(QJsonArray jsonArray)
{
    for (QuestionModel* model: m_questionsList){
        delete model;
    }
    m_questionsList.clear();

    for (int i = 0; i < jsonArray.count(); i++){
        QuestionModel *model = new QuestionModel;
        QJsonObject jObj = jsonArray[i].toObject();
        int _id = -1;
        try {
            _id = jObj[StaticStringConstants::FileParser::jobj_question_text].toInt(0);
        } catch (...) {
            printf("Error in question field \"id\". Question index is %d\n", i);
            return false; //TODO: mem leak
        }

        model->setId(_id);

        QString _text = jObj[StaticStringConstants::FileParser::jobj_question_text].toString(StaticStringConstants::FileParser::jobj_question_text_default);
        QString _type = jObj[StaticStringConstants::FileParser::jobj_question_type].toString(StaticStringConstants::FileParser::jobj_question_type_default);

        model->setQuestionText(_text);
        model->setQuestionType(_type);

        if (jObj.keys().contains(StaticStringConstants::FileParser::jobj_question_data)){
            QJsonObject jObjData = jObj[StaticStringConstants::FileParser::jobj_question_data].toObject();
            if (model->questionType() == QuestionModel::Type::Options){
                QJsonArray _jArrayOptions = jObjData[StaticStringConstants::FileParser::jobj_question_data_options].toArray();
                if (_jArrayOptions.count() == 0){
                    printf("Error in options array. It is empty. Question index is %d\n", i);
                    return false; //TODO: mem leak
                }
                QVariantList _options = _jArrayOptions.toVariantList();
                model->setOptionsOptions(_options);
            }

        }

        m_questionsList.append(model);
    }

    return true;
}

bool TestFileParser::parseVariants(QJsonArray jsonArray)
{
    for (ComputerPart* model: m_variantsList){
        delete model;
    }
    m_variantsList.clear();

    for (int i = 0; i < jsonArray.count(); i++){
        ComputerPart *model = new ComputerPart;
        QJsonObject jObj = jsonArray[i].toObject();

        //check if there are required fields
        if (!jObj.keys().contains(StaticStringConstants::FileParser::jobj_variant_type)       ||
            !jObj.keys().contains(StaticStringConstants::FileParser::jobj_variant_vendor)     ||
            !jObj.keys().contains(StaticStringConstants::FileParser::jobj_variant_price)      ||
            !jObj.keys().contains(StaticStringConstants::FileParser::jobj_variant_perfomance))
        {
            printf("Error in variant object. It doesnt have required fields, which are: %s; %s; %s; %s. Array index is %d\n",
                   qPrintable(StaticStringConstants::FileParser::jobj_variant_type),
                   qPrintable(StaticStringConstants::FileParser::jobj_variant_vendor),
                   qPrintable(StaticStringConstants::FileParser::jobj_variant_price),
                   qPrintable(StaticStringConstants::FileParser::jobj_variant_perfomance),
                   i);
            return false; //TODO: mem leak
        }
        //object have all required fields
        QString _type = jObj[StaticStringConstants::FileParser::jobj_variant_type].toString();
        QString _compatibility = jObj[StaticStringConstants::FileParser::jobj_variant_compatibility].toString(StaticStringConstants::FileParser::jobj_variant_compatibility_default);
        QString _product = jObj[StaticStringConstants::FileParser::jobj_variant_product].toString(StaticStringConstants::FileParser::jobj_variant_product_default);
        QString _vendor = jObj[StaticStringConstants::FileParser::jobj_variant_vendor].toString();
        QString _perfomance = jObj[StaticStringConstants::FileParser::jobj_variant_perfomance].toString();

        double _price = 0;
        try {
            _price = jObj[StaticStringConstants::FileParser::jobj_variant_price].toDouble();
        } catch (...) {
            printf("Error in price field \"id\". Variant index is %d\n", i);
            return false;//TODO: mem leak
        }

        model->setType(_type);
        if (model->type() == ComputerPart::Type::Videocard || model->type() == ComputerPart::Type::CPU){
            if (!jObj.keys().contains(StaticStringConstants::FileParser::jobj_variant_side)) {
                printf("The \"side\" field required for videocards and cpu. Variant index is %d\n", i);
                return false;//TODO: mem leak
            }
            QString _side = jObj[StaticStringConstants::FileParser::jobj_variant_side].toString();
            model->setSide(_side);
        }

        model->setCompatibility(_compatibility);
        model->setName(_product);
        model->setVendor(_vendor);
        model->setPerfomance(_perfomance);
        model->setPrice(_price);

        m_variantsList.append(model);
    }
    return true;
}

int TestFileParser::questions_number()
{
    if (m_questions_number == -1)
        return 0;
    else return m_questions_number;
}

int TestFileParser::variants_number()
{
    if (m_variants_number == -1)
        return 0;
    else return m_variants_number;
}

QString TestFileParser::dataName() const
{
    return m_dataName;
}

QList<QuestionModel*>* TestFileParser::questionsList()
{
    return &m_questionsList;
}

QList<ComputerPart *> *TestFileParser::variantsList()
{
    return &m_variantsList;
}


