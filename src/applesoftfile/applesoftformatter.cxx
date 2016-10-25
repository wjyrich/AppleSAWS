#include "applesoftformatter.h"
#include "util.h"

ApplesoftFormatter::ApplesoftFormatter(QObject *parent) :
    QObject(parent)
{
    m_file = 0;
}

void ApplesoftFormatter::setFile(ApplesoftFile *file)
{
    m_file = file;
    emit newFile(file);
}

QString ApplesoftFormatter::formatText()
{
    if (!m_file) {
        return ("No File");
    }

    QString retval;
    m_flowTargets.clear();

    foreach (ApplesoftLine line, m_file->getLines()) {
        QString linestring = QString("%1 ").arg(line.linenum,5,10,QChar(' '));

        int indentlevel = 1;
        retval.append(linestring);

        QVectorIterator<ApplesoftToken> tokenIt(line.tokens);
        ApplesoftToken previousToken;
        bool firstToken = true;
        while (tokenIt.hasNext())
        {
            ApplesoftToken token = tokenIt.next();
            bool isFlowTarget = false;

            QString tokenstr = token.getRawPrintableString();

            if (firstToken)
            {
                if (!tokenstr.startsWith(" "))
                {
                    tokenstr.prepend(" ");
                }
                firstToken = false;
            }

            //TODO: Move this to the parser.
            //TODO: This doesn't yet handle: ON expr GOTO/GOSUB n1,n2,n3,...
            if (previousToken.getTokenId() == ApplesoftToken::ASGoto  ||
                    previousToken.getTokenId() == ApplesoftToken::ASGosub ||
                    previousToken.getTokenId() == ApplesoftToken::ASThen)
            {
                isFlowTarget = false;
                if (previousToken.getTokenId() == ApplesoftToken::ASGoto ||
                    previousToken.getTokenId() == ApplesoftToken::ASGosub)
                {
                    isFlowTarget = true;
                }
                else if (previousToken.getTokenId() == ApplesoftToken::ASThen &&
                        token.getTokenId() == ApplesoftToken::IntegerTokenVal)
                {
                    isFlowTarget = true;
                }

                if (isFlowTarget)
                {
                    QPair<quint16,quint16> pair;
                    pair.first = line.linenum;
                    pair.second = token.getWordValue();
                    m_flowTargets.append(pair);
                }
            }

            if (m_format_options.testFlag(ShowIntsAsHex)) {
                if (token.getTokenId() == ApplesoftToken::IntegerTokenVal)
                {
                    bool okToConvert = !isFlowTarget;

                    if (okToConvert)
                    {
                        quint32 ui32val = token.getUnsignedIntegerValue();
                        qint32  i32val = token.getIntegerValue();
qDebug() << "UI32: " << ui32val << " I32: " << i32val;
                        if ((i32val < 128 && i32val >= -128) || ui32val < 256)
                        {
                            quint8 ui8 = ui32val;
                            tokenstr = "0x"+uint8ToHex(ui8);
                        }
                        else if ((i32val < 32768 && i32val >= -32768) || ui32val < 65536)
                        {
                            quint16 ui16 = ui32val;
                            tokenstr = "0x"+uint16ToHex(ui16);
                        }
                        else
                        {
                            tokenstr = "0x"+uint32ToHex(ui32val);
                        }
                    }
                }
            }

            if (m_format_options.testFlag(BreakAfterReturn)) {
                if (token.getTokenId() == ApplesoftToken::ASReturn)
                {
                    tokenstr += "\n";
                }
            }

            if (m_format_options.testFlag(ReindentCode))
            {
                if (token.getTokenId() == ':')
                {
                    tokenstr += "\n";
                    for (int ind = 0; ind < indentlevel; ind++)
                    {
                        tokenstr += "      ";
                    }
                    if (!tokenIt.peekNext().getRawPrintableString().startsWith(" "))
                    {
                        tokenstr += " ";
                    }
                }
                if (token.getTokenId() == ApplesoftToken::ASThen)
                {
                    indentlevel++;
                    if (tokenIt.peekNext().getTokenId() != ApplesoftToken::IntegerTokenVal)
                    {
                        tokenstr += "\n";
                        for (int ind = 0; ind < indentlevel; ind++)
                        {
                            tokenstr += "      ";
                        }
                        if (!tokenIt.peekNext().getRawPrintableString().startsWith(" "))
                        {
                            tokenstr += " ";
                        }
                    }
                }
            }

#define noDEBUGTOKENS
#ifdef DEBUGTOKENS
            if (token.getTokenId() >= 0x80)
            {
                tokenstr = QString("{%1 (%2)}").arg(tokenstr).arg(uint16ToHex(token.getTokenId()));
                // tokenstr = " __ ";
            }

#endif

            if (m_format_options.testFlag(ShowCtrlChars))
            {
                tokenstr.replace(QChar(0x7f),QChar(0x2401));

                for (int idx = 1; idx <= 0x1f; idx++) {
                    if (idx == '\n') continue;
                    tokenstr.replace(QChar(idx),QChar(idx+0x2400));
                    //              tokenstr.replace(QChar(idx), QString("<%1>").arg(uint8ToHex(idx)));
                }
            }

            retval.append(tokenstr);
            previousToken = token;
        }

        retval.append("\n");
        if (m_format_options.testFlag(ReindentCode))
        {
  //          retval.append("\n");
        }

    }
    return retval;
}
