#include "UIClassInt.h"
#include <QtWidgets>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include "sharedptrwithname.h"
//#include <../../MEPHILabsMyselfThirdSemester/FirstLaboratorySmartPointers/MEPHI_ThirdSemestr_Laba1_SmartPointers/Sequence/ArraySequence.h>
#include "Sequence/ArraySequence.h"
UIClassInt::UIClassInt()
{
    QWidget* wg = new QWidget;
    QPushButton* PushButtonCreateShared = new QPushButton("Create SharedPtr");
    QPushButton* PushButtonView = new QPushButton("View Objects");
    QPushButton* PushButtonDelete = new QPushButton("Delete Object");
    QPushButton* PushButtonChange = new QPushButton("Change value");
    QVBoxLayout* VLayout = new QVBoxLayout;
    VLayout->addWidget(PushButtonCreateShared);
    VLayout->addWidget(PushButtonView);
    VLayout->addWidget(PushButtonChange);
    VLayout->addWidget(PushButtonDelete);
    wg->setLayout(VLayout);

    QObject::connect(PushButtonCreateShared, SIGNAL(clicked(bool)),
            this, SLOT(SlotCreateShared()));

    connect(PushButtonView, SIGNAL(clicked(bool))
            , this, SLOT(SlotViewObjects()) );

    connect(PushButtonDelete, SIGNAL(clicked(bool)),
            this, SLOT(SlotDeleteObject()));
    connect(PushButtonChange, SIGNAL(clicked(bool))
            , this, SLOT(SlotChangeValue()));
    wg->show();
}

void UIClassInt::SlotCreateShared()
{
    QWidget* wg = new QWidget;
    QLabel* LabelName = new QLabel("Enter Name of Object");
    QLabel* LabelValue = new QLabel("Enter Value of Object(integer or name of another SharedPtr)");

    QLineEdit* LineName = new QLineEdit();
    QLineEdit* LineValue = new QLineEdit();
    QPushButton* ButtonCreate = new QPushButton("Create");

    LineClassName_ = LineName;
    LineClassValue_ = LineValue;
    LineClassWg_ = wg;

    QVBoxLayout* VLayoutName = new QVBoxLayout;
    QVBoxLayout* VLayoutValue = new QVBoxLayout;
    QVBoxLayout* VLayoutWithButton = new QVBoxLayout;
    QHBoxLayout* HLayout1 = new QHBoxLayout;

    VLayoutName->addWidget(LabelName);
    VLayoutName->addWidget(LineName);

    VLayoutValue->addWidget(LabelValue);
    VLayoutValue->addWidget(LineValue);

    HLayout1->addLayout(VLayoutName);

    HLayout1->addLayout(VLayoutValue);

    VLayoutWithButton->addLayout(HLayout1);
    VLayoutWithButton->addWidget(ButtonCreate);

    wg->setLayout(VLayoutWithButton);

    wg->show();
    connect(ButtonCreate, SIGNAL(clicked(bool)),
            this, SLOT(SlotCreateButton()));

}

void UIClassInt::SlotCreateButton()
{
    QObject* Sender = sender();

    QString QName = LineClassName_->text();
    QString QValue = LineClassValue_->text();
    if(QName.isEmpty() || QValue.isEmpty())
    {
        QWidget* Parent = new QWidget;
        QMessageBox::warning(Parent, "Pay attention", "You must fill the fields");
        return;
    }

    for(int i = 0; i < Array_.GetLength(); i++) //надо сделать отдельно набор объектов для манипуляции с шаред поинтером а в qt
    {
        if(Array_.Get(i).Name_ == MyString(QName.toStdString().c_str()))
        {
                    QWidget* Parent = new QWidget;
                    QMessageBox::warning(Parent, "Pay attention", "You have SharedPtr with same name");
                    return;
        }
    }

    bool IsNumber = 1;
    int Value = QValue.toInt(&IsNumber);
    if(!QName.isEmpty() && IsNumber)
    {
        LineClassWg_->hide();
        disconnect(Sender, SIGNAL(clicked(bool))
                   , this, SLOT(SlotCreateButton()));
        connect(this, SIGNAL(Create(MyString,int)),
                this, SLOT(SlotFinalCreate(MyString,int)));
        MyString str((QName.toStdString()).c_str());
        emit Create(str, Value);
        return;
    }

    for(int i = 0; i < Array_.GetLength(); i++)
    {
        if(Array_.Get(i).Name_ == MyString(QValue.toStdString().c_str()))
        {
            SharedPtr<int> Pointer = Array_.Get(i).Pointer_;
            Array_.Prepend(SharedPtrWithName<int>(QName.toStdString().c_str(), std::move(Pointer)));
            LineClassWg_->hide();
            return;
        }
    }
    /*disconnect(Sender, SIGNAL(clicked(bool))
               , this, SLOT(SlotCreateButton()));*/

}
void UIClassInt::SlotFinalCreate(MyString Name, int Value)
{

    QObject* Sender = sender();
    disconnect(Sender, SIGNAL(Create(MyString, int))
               , this, SLOT(SlotFinalCreate(MyString,int)));
    /*if(Array_.GetLength() > 2)
    {
        qDebug() << "Start Debug";
    }*/

    SharedPtr<int> Ptr = MakeShared<int>(Value);
        qDebug() << "Array_.Length() = " << Array_.GetLength();
    Array_.Prepend(SharedPtrWithName<int>(Name,  std::move(Ptr) ));
        qDebug() << "Array_.Length() = " << Array_.GetLength();

    for(int i = 0; i < Array_.GetLength(); i++)
    {
        qDebug() << Array_.Get(i).Name_.str;

    }

    qDebug() << "--------------";
}

void UIClassInt::SlotViewObjects()
{
    QScrollArea* Scroll = new QScrollArea;
    Scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    Scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget* WidgetPrint = new QWidget;
    QVBoxLayout* VLayout = new QVBoxLayout;




    for(int i = 0; i < Array_.GetLength(); i++)
    {
        QString StringOut;
        SharedPtrWithName<int> NamedPtr = Array_.Get(i);

        StringOut += NamedPtr.Name_.str;
        StringOut += '\t';
        QString Value;
        Value.setNum(NamedPtr.Pointer_.Get());
        StringOut += Value;
        QLabel* LabelOut = new QLabel(StringOut);
        VLayout->addWidget(LabelOut);

    }
    WidgetPrint->setLayout(VLayout);
    Scroll->setWidget(WidgetPrint);
        Scroll->show();
}

void UIClassInt::SlotDeleteObject()
{
    QLabel* Label = new QLabel("Enter name of Object");

    QLineEdit* LineEdit = new QLineEdit;
    LineNameToDelete_ = LineEdit;
    QVBoxLayout* Layout = new QVBoxLayout;
    QPushButton* PushButtonDelete = new QPushButton("Delete Pointer");
    QWidget* wg = new QWidget;


    Layout->addWidget(Label);

    Layout->addWidget(LineEdit);
    Layout->addWidget(PushButtonDelete);
    connect(PushButtonDelete, SIGNAL(clicked(bool))
            , this, SLOT(SlotDeleteObjectFinal()));
    wg->setLayout(Layout);
    wg->show();
    WidgetToDelete_ = wg;

}

void UIClassInt::SlotDeleteObjectFinal()
{
    QString QName = LineNameToDelete_->text();
    if(QName.isEmpty())
    {
        QWidget* wg = new QWidget;
        QMessageBox::warning(wg, "Pay Attention", "You should fill the field");

    }

    MyString MyName(QName.toStdString().c_str());


    for(int i = 0; i < Array_.GetLength(); i++)
    {
        if(Array_.Get(i).Name_ == MyName)
        {
            Array_.DeleteElement(i);
            WidgetToDelete_->hide();
            return;

        }
    }

    QWidget* wg = new QWidget;
    QMessageBox::warning(wg, "Pay Attention", "There is no SharedPtr named that");

}

void UIClassInt::SlotChangeValue()
{
    QWidget* Wg = new QWidget;
    QLabel* LabelName = new QLabel("Enter name of SharedPtr");
    QLabel* LabelValue = new QLabel("Enter new value of SharedPtr");
    QLineEdit* LineEditName = new QLineEdit;
    QLineEdit* LineEditValue = new QLineEdit;
    QVBoxLayout* VLayoutName = new QVBoxLayout;
    QVBoxLayout* VLayoutValue = new QVBoxLayout;
    QVBoxLayout* VLayoutWithButton = new QVBoxLayout;
    QHBoxLayout* HLayout = new QHBoxLayout;
    QPushButton* PushButtonChange = new QPushButton("Change");

    VLayoutName->addWidget(LabelName);
    VLayoutName->addWidget(LineEditName);

    VLayoutValue->addWidget(LabelValue);
    VLayoutValue->addWidget(LineEditValue);

    HLayout->addLayout(VLayoutName);
    HLayout->addLayout(VLayoutValue);

    VLayoutWithButton->addLayout(HLayout);
    VLayoutWithButton->addWidget(PushButtonChange);

    Wg->setLayout(VLayoutWithButton);
    Wg->show();

    WidgetChange_ = Wg;
    LineNameToChange_ = LineEditName;
    LineValueToChange_ = LineEditValue;

    connect(PushButtonChange, SIGNAL(clicked(bool))
            , this, SLOT(SlotChangeValueFinal()));



}
void UIClassInt::SlotChangeValueFinal() {
    QObject* Sender = sender();

    QString QName = LineNameToChange_->text();
    QString QValue = LineValueToChange_->text();

    if(QName.isEmpty() || QValue.isEmpty())
    {
        QWidget* wg = new QWidget;
        QMessageBox::warning(wg, "Pay attention", "You should fill the fields");
        return;
    }

    bool IsInt = 1;
    int value = QValue.toInt(&IsInt);

    if(IsInt == false)
    {
        QWidget* wg = new QWidget;
        QMessageBox::warning(wg, "Pay attention", "You should fill the integer value");
        return;
    }

    for(int i = 0; i < Array_.GetLength(); i++)
    {
        if(Array_.Get(i).Name_ == MyString(QName.toStdString().c_str()))
        {
            SharedPtrWithName<int> PtrWithName = const_cast<SharedPtrWithName<int>&>(Array_.Get(i));
            PtrWithName.Pointer_.Get() = value;
            WidgetChange_->hide();
            return;
        }
    }


    QWidget* wg = new QWidget;
    QMessageBox::warning(wg, "Pay attention", "You have no SharedPtr with that name");
    return;


}
