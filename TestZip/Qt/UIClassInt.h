#ifndef UICLASSINT_H
#define UICLASSINT_H
#include <QtWidgets>
#include <QPushButton>
#include "sharedptrwithname.h"

//#include <../../MEPHILabsMyselfThirdSemester/FirstLaboratorySmartPointers/MEPHI_ThirdSemestr_Laba1_SmartPointers/Sequence/ArraySequence.h>
#include "Sequence/ArraySequence.h"
//#include <../../MEPHILabsMyselfThirdSemester/FirstLaboratorySmartPointers/MEPHI_ThirdSemestr_Laba1_SmartPointers/TypesOfData/MyString.h>
#include "TypesOfData/MyString.h"
//фиксирую структуру дерева папок что не хорошо
class UIClassInt : public QObject
{
    Q_OBJECT
private:
    MutableArraySequence<SharedPtrWithName<int>> Array_;
    QLineEdit* LineClassName_{nullptr};
    QLineEdit* LineClassValue_{nullptr};
    QWidget* LineClassWg_{nullptr};
    QLineEdit* LineNameToDelete_{nullptr};
    QWidget* WidgetToDelete_{nullptr};
    QLineEdit* LineNameToChange_{nullptr};
    QLineEdit* LineValueToChange_{nullptr};
    QWidget* WidgetChange_{nullptr};
public:

    UIClassInt();

public slots:

    void SlotCreateShared();
    void SlotCreateButton();
    void SlotFinalCreate(MyString Name, int value);
    void SlotViewObjects();
    void SlotDeleteObject();
    void SlotDeleteObjectFinal();
    void SlotChangeValue();
    void SlotChangeValueFinal();
signals:
    void Create(MyString Name, int value);
};
#endif // UICLASSINT_H
