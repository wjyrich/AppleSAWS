#ifndef APPLESOFTFILEVIEWER_H
#define APPLESOFTFILEVIEWER_H

#include <QWidget>
#include "applesoftfile.h"
#include "applesoftformatter.h"

namespace Ui {
class ApplesoftFileViewer;
}

class ApplesoftFileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ApplesoftFileViewer(QWidget *parent = 0);
    ~ApplesoftFileViewer();

   // void setFormatter(ApplesoftFormatter *formatter);

public slots:
    void setFile(ApplesoftFile *m_file);
    void setData(QByteArray data);
    void setText(QString text);
    void findText();


protected:
protected slots:
    void setIndentCode(bool enabled);
    void setIntsAsHex(bool enabled);
    void launchVarBrowser();
    void reformatText();

private:
    ApplesoftFile *m_file;
    ApplesoftFormatter *m_formatter;
    bool m_isFirstFind;
    Ui::ApplesoftFileViewer *ui;
};

#endif // APPLESOFTFILEVIEWER_H
