#include "charsetviewer.h"
#include <QGridLayout>
#include <QSettings>
#include <QAction>
#include <QMenu>

CharSetViewer::CharSetViewer(QWidget *parent) : FileViewerInterface(parent)
{
    m_file = Q_NULLPTR;
    m_cse = Q_NULLPTR;

    QGridLayout *qgl = new QGridLayout(this);
    setLayout(qgl);
    QString title = QString("Character Set Viewer");
    setWindowTitle(title);
}

CharSetViewer::~CharSetViewer()
{
}

void CharSetViewer::setFile(GenericFile *file)
{
    if (dynamic_cast<BinaryFile*>(file))
    {
        BinaryFile *bf = dynamic_cast<BinaryFile*>(file);
        setFile(bf);
    }
}

void CharSetViewer::setFile(BinaryFile *file)
{
    m_file = file;
    QString title = QString("Character Set Viewer: %1").arg(file->filename());
    setWindowTitle(title);
    m_data = file->data();
    m_data.resize(file->length());
    m_charset.buildSetFromSetBlob(m_data);

    int xpos = 0;
    int ypos = 0;
    foreach (CharSetCharacter csc, m_charset.allCharacters())
    {
        CharacterWidget *cw = new CharacterWidget(this,csc);
        cw->showGrid(true);
        cw->enableBitShift(true);
        cw->setBgColor(Qt::white);
        cw->setFgColor(Qt::black);

        QGridLayout *qgl = qobject_cast<QGridLayout*>(this->layout());
        qgl->addWidget(cw,ypos,xpos);
        //cw->move(xpos,ypos);
        cw->show();

        xpos+= cw->width();
        if (xpos/cw->width() > 11) {
            xpos = 0;
            ypos += cw->height();
        }
    }
}

bool CharSetViewer::optionsMenuItems(QMenu *menu)
{
    QSettings settings;

    QAction *action = new QAction("Show &Grid",menu);
    action->setCheckable(true);
    action->setChecked(settings.value("CharSetViewer.ShowGrid",true).toBool());
    showGrid(settings.value("CharSetViewer.ShowGrid",true).toBool());
    connect(action, &QAction::toggled, this, &CharSetViewer::showGrid);
    menu->addAction(action);

    action = new QAction("&Enable Bit Shift",menu);
    action->setCheckable(true);
    action->setChecked(settings.value("CharSetViewer.EnableBitShift",true).toBool());
    enableBitShift(settings.value("CharSetViewer.EnableBitShift",true).toBool());
    connect(action, &QAction::toggled, this, &CharSetViewer::enableBitShift);
    menu->addAction(action);

    menu->addSeparator();

    action = new QAction("&Character Set Explorer...");
    connect(action, &QAction::triggered, this, &CharSetViewer::showExplorer);
    menu->addAction(action);

    return true;
}

void CharSetViewer::showExplorer()
{
    if (!m_cse) {
        m_cse = new CharacterSetExplorer(this);
        connect(m_cse, &CharacterSetExplorer::destroyed, this, &CharSetViewer::cleanupExplorer);
        m_cse->setCharSet(m_charset);
    }
    m_cse->show();
    m_cse->raise();
}

void CharSetViewer::cleanupExplorer()
{
    m_cse = Q_NULLPTR;
}

QList<CharacterWidget *> CharSetViewer::getChildren()
{
    QList<CharacterWidget*> retval;
    foreach (QObject *child, children())
    {
        if (dynamic_cast<CharacterWidget*>(child))
        {
            retval.append(dynamic_cast<CharacterWidget*>(child));
        }
    }
    return retval;
}

void CharSetViewer::setFgColor(QColor color)
{
    foreach (auto child, getChildren())
    {
        child->setFgColor(color);
    }
}

void CharSetViewer::setBgColor(QColor color)
{
    foreach (auto child, getChildren())
    {
        child->setBgColor(color);
    }
}

void CharSetViewer::setGridColor(QColor color)
{
    foreach (auto child, getChildren())
    {
        child->setGridColor(color);
    }
}

void CharSetViewer::showGrid(bool show)
{
    QSettings settings;
    settings.setValue("CharSetViewer.ShowGrid",show);

    foreach (auto child, getChildren())
    {
        child->showGrid(show);
    }
}

void CharSetViewer::enableBitShift(bool enable)
{
    QSettings settings;
    settings.setValue("CharSetViewer.EnableBitShift",enable);

    foreach (auto child, getChildren())
    {
        child->enableBitShift(enable);
    }
}
