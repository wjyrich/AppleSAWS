#include "viewerbase.h"
#include "ui_viewerbase.h"

#include <QCloseEvent>
#include <QToolBar>
#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>

#include "applesoftfileviewer.h"
#include "hexdumpviewer.h"
#include "texthexdumpviewer.h"
#include "charsetviewer.h"
#include "IntBasicFile.h"
#include "intbasicfileviewer.h"
#include "hiresviewwidget.h"
#include "disassemblerviewer.h"
#include "textfile.h"
#include "mazeviewer.h"

ViewerBase::ViewerBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerBase)
{
    setAttribute(Qt::WA_DeleteOnClose);

    m_stack = new QStackedWidget(this);
    ui->setupUi(this);

    setCentralWidget(m_stack);

    m_toolbar = new QToolBar(this);
    addToolBar(m_toolbar);

    QLabel *label = new QLabel("View With:  ");
    m_toolbar->addWidget(label);

    m_viewercombo = new QComboBox(m_toolbar);
    m_toolbar->addWidget(m_viewercombo);

    m_optionMenu = new QMenu("&Viewer");
    menuBar()->addMenu(m_optionMenu);
    m_optionMenu->setEnabled(false);
}

ViewerBase::~ViewerBase()
{
    emit viewerClosing(this);
    delete ui;
}

void ViewerBase::setFile(GenericFile *file)
{
    m_file = file;

    QString descriptor;
    QString defaultViewerDescriptor;

    HexDumpViewer *hdv = new HexDumpViewer(0);
    if (dynamic_cast<ApplesoftFile*>(file))
        hdv->setFile(file,0x801);  //TODO: Double check this offset.
    else
        hdv->setFile(file,m_file->address());
    descriptor = ("Hex Dump Viewer");
    addViewer(descriptor,hdv);
    defaultViewerDescriptor = descriptor;

    if (dynamic_cast<ApplesoftFile*>(file))
    {
        ApplesoftFileViewer *afv = new ApplesoftFileViewer(0);
        afv->setFile(file);
        descriptor="Applesoft File Viewer";
        addViewer(descriptor,afv);
        defaultViewerDescriptor = descriptor;
    }
    else if (dynamic_cast<IntBasicFile*>(file))
    {
        IntBasicFileViewer *ibf = new IntBasicFileViewer(0);
        ibf->setFile(file);
        descriptor="Integer Basic File Viewer";
        addViewer(descriptor, ibf);
        defaultViewerDescriptor = descriptor;



    }
    else if (dynamic_cast<BinaryFile*>(file))
    {
        BinaryFile *bf = dynamic_cast<BinaryFile*>(file);

        CharSetViewer *csv = new CharSetViewer();
        csv->setFile(bf);
        descriptor ="HRCG Character Set Viewer";
        addViewer(descriptor,csv);

        HiresViewWidget *hrvw = new HiresViewWidget();
        hrvw->setFile(bf);
        descriptor = "HiRes Image Viewer";
        addViewer(descriptor,hrvw);

        MazeViewer *mv = new MazeViewer();
        mv->setFile(file);
        descriptor = "MissingRing Maze Viewer";
        addViewer(descriptor,mv);

        DisassemblerViewer *dv = new DisassemblerViewer();
        dv->setFile(bf);
        descriptor = "Disassembler Viewer";
        addViewer(descriptor,dv);
        defaultViewerDescriptor = descriptor;

        if (bf->filename().toUpper().endsWith(".SET"))
        {
            defaultViewerDescriptor ="HRCG Character Set Viewer";
        }
        if (bf->filename().toUpper().startsWith("MAZE"))
        {
            defaultViewerDescriptor = "MissingRing Maze Viewer";
        }
        if ((bf->address() == 0x2000 || bf->address() == 0x4000)
            && bf->length() == 0x2000)
        {
            defaultViewerDescriptor = "HiRes Image Viewer";
        }

    }
    else if (dynamic_cast<TextFile*>(file))
    {
        TextFile *bf = dynamic_cast<TextFile*>(file);

        TextHexDumpViewer *thdv = new TextHexDumpViewer();
        thdv->setFile(bf);
        descriptor = QString("Text/Hex Dump Viewer");
        addViewer(descriptor,thdv);

        defaultViewerDescriptor = descriptor;
    }
    else if (dynamic_cast<RelocatableFile*>(file))
    {
        DisassemblerViewer *dv = new DisassemblerViewer();
        dv->setFile(file);
        descriptor = "Relocatable Disassembler Viewer";
        addViewer(descriptor,dv);
        defaultViewerDescriptor = descriptor;

    }
    connect(m_viewercombo, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &ViewerBase::showViewer);
    showViewer(defaultViewerDescriptor);
}

void ViewerBase::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ViewerBase::addViewer(QString descriptor, FileViewerInterface *viewer)
{
    if (!m_viewers.contains(descriptor))
    {
        m_stack->addWidget(viewer);
        m_viewers[descriptor] = viewer;
        m_viewercombo->addItem(descriptor);
    }
}

void ViewerBase::showViewer(const QString& descriptor)
{
    FileViewerInterface *fvi = m_viewers[descriptor];
    if (fvi)
    {
        ui->actionExport->disconnect(SIGNAL(triggered(bool)));
        ui->actionExport->setEnabled(fvi->canExport());
        connect(ui->actionExport, &QAction::triggered,
                fvi, &FileViewerInterface::doExport);

        ui->action_Print->disconnect(SIGNAL(triggered(bool)));
        ui->action_Print->setEnabled(fvi->canPrint());
        connect(ui->action_Print, &QAction::triggered,
                fvi, &FileViewerInterface::doPrint);

        m_optionMenu->clear();
        m_viewercombo->setCurrentText(descriptor);
        m_stack->setCurrentWidget(fvi);
        setWindowTitle(fvi->windowTitle());

        if (m_optionMenu)
        {
            if (!fvi->optionsMenuItems(m_optionMenu))
            {
                m_optionMenu->setEnabled(false);
            }
            else
            {
                m_optionMenu->setEnabled(true);
            }
        }
    }
    else
    {
        qDebug() << "Could not find widget for descriptor" << descriptor;
    }

}
