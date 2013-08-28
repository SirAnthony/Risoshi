#ifndef MODELS_H
#define MODELS_H

#include <dquest.h>
#include <QList>

enum CategoryType {
    CT_MAIN = 0,
    CT_SUBCATEGORY,
    CT_INNERCATEGORY
};

static const QString fields = \
        "title,authors,type,link,mag,volume,issue,year,first_page,last_page,keywords,file,abstract";

static const QList<QString> Types = QList<QString>() << "book" << "article"
                                                     << "paper" << "eres"
                                                     << "journal";
inline int index_from_type( QString search ){
    for( int i=0; i < Types.size(); ++i )
        if( Types[i] == search )
            return i;
    return -1;
}


enum Columns {
    cId = 0, cTitle, cAuthors, cType, cLink, cMag, cVolume, cIssue, cYear,
    cFirstPage, cLastPage, cKeywords, cFile, cAbstract
};

class Article : public DQModel
{
    DQ_MODEL
public:
    DQField<QString> title;
    DQField<QString> authors;
    DQField<QString> type;
    DQField<QString> link;
    DQField<QString> mag;
    DQField<int> volume;
    DQField<int> issue;
    DQField<int> year;
    DQField<int> first_page;
    DQField<int> last_page;
    DQField<QString> keywords;
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
    DQ_FIELD(authors, DQNotNull),
    DQ_FIELD(type, DQNotNull),
    DQ_FIELD(mag, DQNotNull),
    DQ_FIELD(volume, DQNotNull),
    DQ_FIELD(issue, DQNotNull),
    DQ_FIELD(year, DQNotNull),
    DQ_FIELD(first_page, DQNotNull),
    DQ_FIELD(last_page, DQNotNull),
    DQ_FIELD(keywords, DQNotNull),
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
