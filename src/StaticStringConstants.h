#ifndef STATICSTRINGCONSTANTS_H
#define STATICSTRINGCONSTANTS_H

#include <qstring.h>

class StaticStringConstants final{
private: StaticStringConstants() = delete;
public:
    class FileParser final{
    private: FileParser() = delete;
    public:
        static inline QString fileExtenstion = "ses";
        static inline QString jsonf_dataName = "name";
        static inline QString jsonf_dataName_default = "Название не указано";
        static inline QString jsonf_questions= "questions";
        static inline QString jsonf_variants= "variants";

        //Question parsing
        static inline QString jobj_question_id = "id";

        static inline QString jobj_question_text = "text";
        static inline QString jobj_question_text_default = "Текст вопроса не был указан!";

        static inline QString jobj_question_type = "type";
        static inline QString jobj_question_type_default = "plain";



        static inline QString dataName_fileParsing_error = "Ошибка в парсинге файла";

    };
};

#endif // STATICSTRINGCONSTANTS_H
