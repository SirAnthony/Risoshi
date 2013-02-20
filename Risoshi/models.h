#ifndef MODELS_H
#define MODELS_H

#include <dquest.h>


class Article : public DQModel
{
    DQ_MODEL
public:
    DQField<QString> title;
    DQField<QString> link;
    DQField<QString> mag;
    DQField<int> volume;
    DQField<int> issue;
    DQField<int> year;
    DQField<QString> file;
    DQField<QString> abstract;

    /// Model fields validation
    virtual bool clean();
};

/// Declare the model and the field clause
DQ_DECLARE_MODEL(Article,
    "Article", // the table name.
    DQ_FIELD(title, DQNotNull | DQUnique),
    DQ_FIELD(link, DQNotNull | DQUnique),
    DQ_FIELD(mag, DQNotNull),
    DQ_FIELD(volume, DQNotNull),
    DQ_FIELD(issue, DQNotNull),
    DQ_FIELD(year, DQNotNull),
    DQ_FIELD(file, DQNotNull),
    DQ_FIELD(abstract, DQNotNull)
)


#endif // MODELS_H
