#ifndef MODELS_H
#define MODELS_H

#include <dquest.h>

enum CategoryType {
    CT_MAIN = 0,
    CT_SUBCATEGORY,
    CT_INNERCATEGORY
};


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

class Category : public DQModel
{
    DQ_MODEL
public:
    DQField<QString> title;
    DQForeignKey<Category> parent;
};


class CategoryJoin : public DQModel
{
    DQ_MODEL
public:
    DQForeignKey<Article> article;
    DQForeignKey<Category> category;
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


DQ_DECLARE_MODEL(Category,
    "Category", // the table name.
    DQ_FIELD(title, DQNotNull),
    DQ_FIELD(parent)
)


DQ_DECLARE_MODEL(CategoryJoin,
    "CategoryJoin", // the table name.
    DQ_FIELD(article, DQNotNull | DQUnique),
    DQ_FIELD(category, DQNotNull)
)



#endif // MODELS_H
